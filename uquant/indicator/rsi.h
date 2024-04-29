#pragma once

#include "../base/future_period.h"
#include "../base/new_talib.h"
#include <cmath>

namespace uBEE {

/*
LC:
  =REF(CLOSE,1);
RSI1:
SMA(MAX(CLOSE-LC,0),N1,1)/SMA(ABS(CLOSE-LC),N1,1)*100;
*/

template <int... N> class IND_RSI : public OhlcvSerial<N...> {
  public:
    int N1{7};

  public:
    FutureSerial<N...> O{'o'};
    FutureSerial<N...> H{'h'};
    FutureSerial<N...> L{'l'};
    FutureSerial<N...> C{'c'};
    FutureSerial<N...> V{'v'};

    SMA_t<N...> sma_max;
    SMA_t<N...> sma_abs;
    FutureSerial<N...> rsi;

  public:
    IND_RSI(int n = 7) : N1(n) {
        std::cout << "BBB IND_RSI construction !! " << std::endl;
        PLOT(rsi, 0);
        std::cout << "EEE IND_MA construction !! " << std::endl;
    };
    ~IND_RSI(){};
    void run() {
        //   sma_max.sma(std::max((C.cur() - C.ref(1)), 0.0), N1, 1);
        //   sma_abs.sma(std::abs(C.cur() - C.ref(1)), N1, 1);
        //   rsi = sma_max / sma_abs * 100;
        rsi = sma_max.sma(std::max((C - C.ref(1)), 0.0), N1, 1) / sma_abs.sma(std::abs(C - C.ref(1)), N1, 1) * 100;
    };
};

} // end namespace uBEE
