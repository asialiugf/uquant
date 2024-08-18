// main.cpp
#include "Derived.h"
#include <iostream>

int main() {
    // 创建Derived类的实例
    //   Derived d;
    Base *b;
    //   b = &d;
    Base::Open(&b);
    b->pureVirtualFunction();

    // 调用Derived类中重写的pureVirtualFunction函数
    //  d.pureVirtualFunction();

    return 0;
}
