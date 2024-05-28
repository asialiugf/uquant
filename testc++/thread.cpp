#include <iostream>
#include <thread>
#include <chrono>

void threadFunction() {
    // 尝试访问一个未初始化的指针，这将导致程序崩溃
    volatile int* p = nullptr;
    *p = 1; // 这一行将导致段错误（segmentation fault）
}

int main() {
    // 创建新线程并立即分离它
    std::jthread t(threadFunction);
    // t.detach();

    std::cout << "Main thread is running and will sleep every second..." << std::endl;

    while (true) {
        // 主线程休眠1秒
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // 打印一条消息，表明主线程仍然在运行
        std::cout << "Main thread is alive." << std::endl;
    }

    // 主线程永远不会到达这里，因为它处于一个无限循环中
    return 0;
}
