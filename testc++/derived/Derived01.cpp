// Derived.cpp
#include <iostream>
#include "Derived.h"

void Derived::pureVirtualFunction()
{
    // 具体的实现代码
    std::cout << "Derived class implementation of pureVirtualFunction." << std::endl;
    Base::pureVirtualFunction();
}

void Base::pureVirtualFunction()
{
    // 具体的实现代码
    std::cout << "Base class implementation of pureVirtualFunction." << std::endl;
}

void Base::Open(Base **ptr)
{
    Derived *dd = new Derived();
    *ptr = dd;
}

Derived::Derived()
{
    std::cout << " Derived constructed" << std::endl;
}