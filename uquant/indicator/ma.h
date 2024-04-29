#pragma once

#include "../base/future_period.h"
#include "../base/new_talib.h"
#include <cmath>

namespace uBEE {

#define fu2305 7
#define au2306 8
#define xu1801 0
#define tu1801 1
#define ru1805 2
#define ru1809 3
#define xu1807 4
#define zz1805 5
#define ag1912 6
#define fu2305 7
#define fu2309 8

template <int... N> class IND_MA : public OhlcvSerial<N...> {
  public:
    int N1{5};
    int N2{13};
    int N3;

  public:
    FutureSerial<N...> O{'o'};
    FutureSerial<N...> H{'h'};
    FutureSerial<N...> L{'l'};
    FutureSerial<N...> C{'c'};
    FutureSerial<N...> V{'v'};

    MA_t<N...> m5{OHLCV::C1, N1};
    MA_t<N...> m13{OHLCV::C1, N2};
    MA_t<N...> m21;
    MA_t<N...> m34;
    MA_t<N...> m55;
    MA_t<N...> m89;
    MA_t<N...> m144;
    MA_t<N...> m233;
    MA_t<N...> m377;
    MA_t<N...> m610;
    MA_t<N...> m987;
    MA_t<N...> m1597;

  public:
    IND_MA(int n1 = 5, int n2 = 13) : N1(n1), N2(n2) {
        std::cout << "BBB IND_MA construction !! " << std::endl;
        //  m5.ma(OHLCV::C1, N1);
        //  m13.ma(OHLCV::C1, N2);  // 在上面初始化
        N3 = 21;
        //  m21.ma(C, 21);  // 在切片 run()函数 中调用
        m34.ma(OHLCV::C1, 34);
        m55.ma(OHLCV::C1, 55);
        m89.ma(OHLCV::C1, 89);
        // m144.ma(OHLCV::C1, 144);  // 在切片 run()函数 中调用
        m233.ma(OHLCV::C1, 233); //
        m377.ma(OHLCV::C1, 377);
        m610.ma(OHLCV::C1, 610);
        m987.ma(OHLCV::C1, 987);
        m1597.ma(OHLCV::C1, 1597);

        PLOT(m5, 0);
        PLOT(m13, 0);
        PLOT(m21, 0);
        PLOT(m34, 0);
        PLOT(m55, 0);
        PLOT(m89, 0);
        PLOT(m144, 0);
        PLOT(m233, 0);
        PLOT(m377, 0);
        PLOT(m610, 0);
        PLOT(m987, 0);
        PLOT(m1597, 0);
        std::cout << "EEE IND_MA construction !! " << std::endl;
    };
    ~IND_MA(){};
    void run() {
        m21.ma(C, 21);
        m144.MA(C.cur(), 144);
        m233.ma(m21.C, 233);

        // m5.
        // m5.x;
        std::cout << "index: " << m5.x << std::endl;
    };
};

class example {
  public:
    int a;
    int b;
    example(int x = 0, int y = 0) : a(x), b(y) {}
};

} // end namespace uBEE
