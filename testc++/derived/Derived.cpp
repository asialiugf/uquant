// Derived.cpp
#include <iostream>
#include "Derived.h"

void Derived::pureVirtualFunction()
{
    // 具体的实现代码
    std::cout << "Derived class implementation of pureVirtualFunction." << std::endl;
    Base::pureVirtualFunction();
}

Derived::Derived()
{
    std::cout << " Derived constructed" << std::endl;
}

void Base::Open(Base **ptr)
{
    Derived *dd = new Derived();
    *ptr = dd;
}
