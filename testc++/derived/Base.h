// Base.h
#ifndef BASE_H
#define BASE_H

class Base
{
public:
    int x;
    Base() = default;
    virtual ~Base() {} // 虚析构函数
    static void Open(Base **);

    // 纯虚函数
    virtual void pureVirtualFunction() = 0;
};

#endif // BASE_H
