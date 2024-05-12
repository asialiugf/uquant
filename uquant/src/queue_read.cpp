#include <atomic>

#include "Bars.h"
#include "base/timestamp.h"
#include "global.h"

// inline uint64_t rdtsc() { return __builtin_ia32_rdtsc(); }

bool cpupin(int cpuid) {
    cpu_set_t my_set;
    CPU_ZERO(&my_set);
    CPU_SET(cpuid, &my_set);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &my_set)) {
        std::cout << "sched_setaffinity error: " << strerror(errno) << std::endl;
        return false;
    }

    return true;
}

const uint64_t MaxI = 9223372036854775807;

//
void tick_save(int tid, int cpu) {
#define ERR_MSG_LEN 2048
    if (cpu >= 0) {
        cpupin(cpu);
    }
    char ca_errmsg[2048];

    auto reader = uBEE::g_tick_queue->getReader();
    while (true) {
        CThostFtdcDepthMarketDataField *tick = reader.read();
        if (!tick) {
            uBEE::spin_loop_pause();
            continue;
        };
        uBEE::SaveTick(tick); // 这个是非线程安全的  有多个线程时会出错。
        snprintf(ca_errmsg, ERR_MSG_LEN, "A:%s %s %s T:%s O:%g H:%g L:%g C:%g V:%d \n", tick->ActionDay,
                 tick->InstrumentID, tick->TradingDay, tick->UpdateTime, tick->LastPrice, tick->AskPrice1,
                 tick->BidPrice1, tick->AskPrice2, tick->Volume);
        std::cout << ca_errmsg << std::endl;
    }
    std::cout << endl;
}

// 从队列中读取tick，计算Kbar 并存储
void kbar_save(int tid, int cpu) {
    uint64_t before;
    uint64_t latency;

#define ERR_MSG_LEN 2048
    if (cpu >= 0) {
        cpupin(cpu);
    }
    char ca_errmsg[2048];

    auto reader = uBEE::g_tick_queue->getReader();
    while (true) {
        CThostFtdcDepthMarketDataField *tick = reader.read();
        if (!tick) {
            uBEE::spin_loop_pause();
            continue;
        };

        // map<std::string, uBEE::FuBo*>::iterator iter;
        auto iter = uBEE::map_futures_block.find(tick->InstrumentID);
        if (iter == uBEE::map_futures_block.end()) {
            sprintf(ca_errmsg, "InstrumentID:%s is not found!", tick->InstrumentID);
            uBEE::ErrLog(1000, "InstrumentID is not found!", 1, 0, 0);
        } else {
            before = rdtsc();
            uBEE::HandleTick(iter->second, tick, SEND_SAVE_ALL);
            latency = rdtsc() - before;
            std::cout << "\n latency ----HandleTick---------- Dealar::  " << latency << std::endl;
        }
    }
}

vector<std::jthread> reader_threads;

void TickWrite() {
    int cpu_start = 0;
    if (cpu_start >= 0) {
        cpupin(cpu_start);
    }
    reader_threads.emplace_back(tick_save, 0, cpu_start);
    std::this_thread::sleep_for(1s);
    // std::this_thread::sleep_for(100ms);
    // std::this_thread::sleep_for(100us);
}

void KbarHandle() {
    int cpu_start = 1;
    if (cpu_start >= 0) {
        cpupin(cpu_start);
    }
    reader_threads.emplace_back(kbar_save, 1, cpu_start);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}