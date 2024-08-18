// Derived.h
#ifndef DERIVED_H
#define DERIVED_H

#include "Base.h"

class Derived : public Base
{
public:
    // 实现基类的纯虚函数
    Derived();
    void pureVirtualFunction() override;

private:
    //   friend class Base ;
};

#endif // DERIVED_H
