/*
MIT License

Copyright (c) 2020 Meng Rao <raomeng1@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "base/error_log.h"
namespace uBEE {

inline uint64_t rdtsc() { return __builtin_ia32_rdtsc(); }

static inline void cpu_pause(void) {
    /* The asm prevents compiler from moving loads and stores beyond this point. */
    asm volatile("" ::: "memory");
    __builtin_ia32_pause();
    asm volatile("" ::: "memory");
}

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
#include <emmintrin.h>
constexpr int CACHE_LINE_SIZE = 64;
static inline void spin_loop_pause() noexcept { _mm_pause(); }

#elif defined(__arm__) || defined(__aarch64__)
constexpr int CACHE_LINE_SIZE = 64;
static inline void spin_loop_pause() noexcept {
#if (defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || \
     defined(__ARM_ARCH_6T2__) || defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) ||  \
     defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__) ||  \
     defined(__ARM_ARCH_8A__) || defined(__aarch64__))
    asm volatile("yield" ::: "memory");
#else
    asm volatile("nop" ::: "memory");
#endif
}
#elif defined(__ppc64__) || defined(__powerpc64__)
constexpr int CACHE_LINE_SIZE = 128;  // TODO: Review that this is the correct value.
static inline void spin_loop_pause() noexcept {
    asm volatile("or 31,31,31 # very low priority");  // TODO: Review and benchmark that this is the
                                                      // right instruction.
}
#elif defined(__s390x__)
constexpr int CACHE_LINE_SIZE = 256;  // TODO: Review that this is the correct value.
static inline void spin_loop_pause() noexcept {
}  // TODO: Find the right instruction to use here, if any.
#elif defined(__riscv)
constexpr int CACHE_LINE_SIZE = 64;
static inline void spin_loop_pause() noexcept { asm volatile(".insn i 0x0F, 0, x0, x0, 0x010"); }
#else
#warning \
    "Unknown CPU architecture. Using L1 cache line size of 64 bytes and no spinloop pause instruction."
constexpr int CACHE_LINE_SIZE = 64;  // TODO: Review that this is the correct value.
static inline void spin_loop_pause() noexcept {}
#endif

// T 是指消息的类型。比如 (CThostFtdcDepthMarketDataField)
// using Q = SPMCQueue<CThostFtdcDepthMarketDataField, 256>;
// extern Q q;

template <class T, uint64_t CNT>
class SPMCQueue {
   public:
    static_assert(CNT && !(CNT & (CNT - 1)), "CNT must be a power of 2");

    struct Reader {
        operator bool() const { return q; }
        T* read() {
            auto& element = q->elements[reader_idx & mask];
            asm volatile("" : "=m"(element) : :);

            // 非阻塞：if (reader_idx >= *pwrite_idx) return nullptr;
            // 阻塞版本：
            // 读序号是否>=写序号，如果读序号比写序号小的话，则表示有队列中有消息了。
            while (reader_idx >= *pwrite_idx) {
                spin_loop_pause();
            }

            std::cout << "from read: idx: " << reader_idx << " masked_idx: " << (reader_idx & mask)
                      << std::endl;
            reader_idx++;
            return &element.data;
        }

        T* readLast() {
            uint64_t last_idx = *(volatile uint64_t*)&q->write_idx;
            if ((int)last_idx - (int)reader_idx <= 0) return nullptr;
            reader_idx = last_idx;
            return &q->elements[last_idx % CNT].data;
        }

        void setReaderIndex(uint64_t x) {
            if (x >= 0) {
                this->reader_idx = x;
            }
        }

        SPMCQueue<T, CNT>* q = nullptr;
        uint64_t reader_idx;
        uint64_t mask;
        uint64_t* pwrite_idx;
    };

    // getReader() 得到一个reader对象，每个对象保存有自己的reader.idx。
    // *pwrite_idx 是producer的写入序号，每写一个会自增1。
    // reader_idx 是读取序号，每读一次，自增1.
    // 如果producer已经运行了一段时间，这里初始的reader_idx = &this->write_idx; 表示：
    // 现在当前get到的reader对象，应该从当前（writer_idx处）开始处理消息。
    // 如果想自已定义从哪里开始处理消息，则可以 read.setReaderIndex(100); 自己设定。
    // 要注意，这里的队列是一个循环队列，如果队列的长度比较小的话，有可能数据会循环了好几轮。
    Reader getReader() {
        Reader reader;
        reader.q = this;
        reader.reader_idx = write_idx;
        reader.mask = mask;
        reader.pwrite_idx = &this->write_idx;
        return reader;
    }

    uint64_t getWriterIndex() { return this->write_idx; }

    // push 传参，实际上是传入一个lambda 函数。
    // 调用 方法
    // while(xxxx) {
    //     q.push([&pDepthMarketData](CThostFtdcDepthMarketDataField& msg) {
    //         memcpy(&msg, pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
    //     });
    // }
    // producer自己维护一个循环，在这个循环内，一直push即可。

    template <typename P>
    void push(P producer) {
        masked_index = (write_idx)&mask;
        auto& element = elements[masked_index];

        std::cout << "from  producer  mask: " << mask << "  masked_index: " << masked_index
                  << " write_index: " << write_idx << std::endl;

        producer(element.data);
        asm volatile("" : : "m"(element) :);
        ++write_idx;
        asm volatile("" : : "m"(write_idx) :);
    }

    SPMCQueue() { this->mask = CNT - 1; }

   private:
    friend class Reader;
    struct alignas(64) Block {
        // uint64_t idx = 0;
        T data;
    } elements[CNT];

    uint64_t mask;
    uint64_t masked_index;  // 这个值可能有用？
    alignas(128) uint64_t write_idx = 0;
};
}  // namespace uBEE