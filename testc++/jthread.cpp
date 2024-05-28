#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <exception>

std::jthread::id mainThreadId = std::this_thread::get_id();

void threadFunction() {
    std::cout << "Thread function started with ID: " << std::this_thread::get_id() << std::endl;

    // 尝试访问一个未初始化的指针，这将导致程序崩溃
    int x;
    try {
        volatile int* p = &x;
        *p = 1; // 这一行将导致段错误（segmentation fault）
    } catch (const std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << std::endl;
    }

    std::cout << "sub thread ID: " << std::this_thread::get_id() << std::endl;

    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "sub thread ID: " << std::this_thread::get_id() << std::endl;
    }


}

int main() {
    std::cout << "Main thread ID: " << mainThreadId << std::endl;
    
    // 创建新线程
    std::jthread t(threadFunction);
    std::jthread t1(threadFunction);
    std::jthread t2(threadFunction);
    std::jthread t3(threadFunction);
    std::jthread t4(threadFunction);
    std::jthread t5(threadFunction);

    std::cout << "Main thread is running and will sleep every second..." << std::endl;

    while (true) {
        // 主线程休眠1秒
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // 打印一条消息，表明主线程仍然在运行
        std::cout << "Main thread is alive." << std::endl;

        // 检查新线程是否已经启动
        if (t.get_id() != std::thread::id()) {
            std::cout << "Thread is joinable: " << t.joinable() << std::endl;
        }
    }

    // 主线程永远不会到达这里，因为它处于一个无限循环中
    return 0;
}
