#include <iostream>

int main() {
    // 声明一个未初始化的指针
    int* p = nullptr;

    try {
        // 尝试访问该指针，这将导致程序崩溃
        std::cout << "Value at p: " << *p << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
