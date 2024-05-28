#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

// int counter = 0; // 共享资源，没有进行同步
std::atomic<uint64_t> counter{0}; // 使用std::atomic封装

void increment() {
    for (int i = 0; i < 10000; ++i) {
        // ++counter; // 非原子操作
        counter.fetch_add(1, std::memory_order_relaxed); // 原子操作

    }
}

int main() {
    std::vector<std::thread> threads;
    int num_threads = 10;


    std::cout << "is lock free: " <<  counter.is_lock_free() << std::endl;


    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(increment);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    // 打印最终的计数值，由于竞态条件，这个值很可能是错误的
    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
