
#pragma once
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <functional>

#include "../ctp/ThostFtdcMdApi.h"
#include "libdeflate.h"
#include "see_talib.h"
#include "sig_slot.h"
#include "stdio.h"
#include "zlib.h"

namespace uBEE {
using lSignal::Connection;
using lSignal::Signal;
using lSignal::Slot;

Signal<void()> Update[50];

enum OHLCV { O1, H1, L1, C1, V1 };
// enum ohlcv { OPEN, HIGH, LOW, CLOSE, VOL };

template <int... N> class KDJ;

template <int... N> class MACD : public PeriodBase<N...> {
  public:
    /*
     */

    MACD() {
        std::cout << "macd constructor !!! -- :  before  PeriodBase<N...>::UnitCheck() ;" << std::endl;
        PeriodBase<N...>::UnitCheck();
        std::cout << "macd constructor !!! -- :  after  PeriodBase<N...>::UnitCheck() ;" << std::endl;

        std::cout << "macd constructor !!! -- 2 :  func_signal->Connect macd(); " << 5 << std::endl;
        PeriodBase<N...>::func_signal->Connect(this, &MACD<N...>::macd);
    }

    void macd() { std::cout << "from macd(): " << 3 << " " << 3 << " " << this->OO[this->x] << std::endl; };

  public:
    FutureSerial<N...> x1;
    FutureSerial<N...> x2;
    KDJ<N...> kdj;

    // Base* b;
};

/*
template <int... N>
class KDJ : public PeriodBase<N...> {
   public:
    KDJ() {
        std::cout << "KDJ constructor !!! -- :  before  PeriodBase<N...>::UnitCheck() ;" << std::endl;
        PeriodBase<N...>::UnitCheck();
        std::cout << "KDJ constructor !!! -- :  after  PeriodBase<N...>::UnitCheck() ;" << std::endl;

        // Update[0].Connect(this, &KDJ<N...>::kdj);
        // Future<N...>::future_fun_list[0].Connect(this, &KDJ<N...>::kdj);  //
        // Future<N...>::future_fun_list[0].Connect(this, &KDJ<N...>::kdj);  //
        PeriodBase<N...>::func_signal->Connect(this, &KDJ<N...>::kdj);
        std::cout << "kdj  init !! ---- " << std::endl;
    };
    void kdj() { std::cout << "from kdj(): " << 5 << " " << 5 << " " << this->OO[*index] << std::endl; };
};
*/

// typedef struct Order {
//     int idx;        // 位置数组下标
//     int order_type; // buyopen, buyclose, sellopen, sellclose, cancel
//     int mount;      // 交易数量
// } Order;

// // ====================== Trader ===========================================================
// template <int... N> class Trader : public FutureSerial<N...> {
//   public:
//     std::vector<Order> tradepoints_;

//     bool value_;

//   public:
//     // 构造函数继承、等号运算符继承
//     using FutureSerial<N...>::FutureSerial;
//     using FutureSerial<N...>::operator=;

//   public:
//     Trader() { std::cout << "B:constructor !! Trader --------------------*****" << std::endl; };

//     ~Trader() { std::cout << " Trader release ---- !" << std::endl; };

//   public:
//     inline const void buyopen(int x) {
//         Order order;
//         order.idx = this->unit->index;
//         order.order_type = 1;
//         order.mount = x;
//         tradepoints_.push_back(order);
//         // 当前下定单，下一个Kbar以开盘价成交
//     };
//     inline const void buyclose(int x) {
//         Order order;
//         order.idx = this->unit->index;
//         order.order_type = 2;
//         order.mount = x;
//         tradepoints_.push_back(order);
//     };
//     inline const void sellopen(int x) {
//         Order order;
//         order.idx = this->unit->index;
//         order.order_type = 3;
//         order.mount = x;
//         tradepoints_.push_back(order);
//     };
//     inline const void sellclose(int x) {
//         Order order;
//         order.idx = this->unit->index;
//         order.order_type = 4;
//         order.mount = x;
//         tradepoints_.push_back(order);
//     };
//     inline const double &cancel(){};

//   private:
//     // 简单计算 以当前 kbar开盘价为准，计算前一个kbar的下单。
//     // 真实的下单，要看ctp是如何确认交易是否成功，再确定如何计算。
//     inline void _ma() {
//         // 反向查找  tradepoints_
//         this->data[this->unit->index] = 1000.00;
//     };

//   public:
//     // 用于将某对象的数据传给前端显示，在base.cpp的sendTradingData()中会处理
//     // 在unit中有一个vector: pointslist_output。
//     // 每个对象在调用这个plot时，会传入自已的对象名、要前端显示的颜色及方式。【talib_define.h: #define PLOT(obj, aa) obj.plot(#obj, aa) 】
//     // 这个plot会将本对象的 data指针放到这个vector中。
//     void plot(std::string name, int color) override {
//         FutureSerial<N...>::plot(name, color);

//         // std::tuple<std::string, std::vector<int> *, int> temp = std::make_tuple(name, &tradepoints_, color);
//         // this->unit->pointslist_output.push_back(temp);
//     }
// };

// ====================== MA ===========================================================
template <int... N> class MA_t : public FutureSerial<N...>, public OhlcvSerial<N...> {
  public:
    int N_{0};

  private:
    double *in{nullptr};
    double *din{nullptr}; // double in，下面 ma(double,int) 用到。

  private:
    // 构造函数继承、等号运算符继承
    using FutureSerial<N...>::FutureSerial;
    using FutureSerial<N...>::operator=;

  public:
    MA_t(FutureSerial<N...> &p, int n) {
        std::cout << "B:constructor !! MA() " << std::endl;
        // PeriodBase<N...>::UnitCheck();
        //    PeriodBase<N...>::func_signal->Connect(this, &MA<N...>::u_ma);
        N_ = n;
        in = p.data;
    };

    MA_t() {
        std::cout << "B:constructor !! MA() --------------------*****" << std::endl;
        in = nullptr;
        this->din = nullptr;
    };

    MA_t(int x, int n) {
        std::cout << "constructor !! MA() : input OHLCV::X N ! " << std::endl;
        // PeriodBase<N...>::UnitCheck();

        if (x == OHLCV::O1) {
            in = this->OO;
        } else if (x == OHLCV::H1) {
            in = this->unit->HH;
        } else if (x == OHLCV::L1) {
            in = this->LL;
        } else if (x == OHLCV::C1) {
            in = this->CC;
        } else if (x == OHLCV::V1) {
            in = this->unit->VV; // volume => from int to double
        } else {
            std::cout << "MA() input error !  EMA<> x(O,10) \n";
        }
        N_ = n;
        PeriodBase<N...>::func_signal->Connect(this, &MA_t<N...>::_ma);
        _ma();
    }

    ~MA_t() {
        if (din != nullptr) {
            delete[] din;
        }
        std::cout << " MA_t release ---- !" << std::endl;
    };

  private:
    inline void _ma() { uBEE::SEE_MA(this->x, this->x, in, N_, this->data); };

  public:
    inline const double &ma() {
        if (nullptr == in) {
            std::cout << "ma() data need to be initial !!" << std::endl;
            exit(-1);
        }
        return uBEE::SEE_MA(this->x, this->x, in, N_, this->data);
    };

    inline const double &ma(FutureSerial<N...> &p, int n) {
        if (nullptr == p.data) {
            std::cout << "ma(p,n) data need to be initial !!" << std::endl;
            exit(-1);
        }
        if (in == nullptr) {
            in = p.data;
            N_ = n;
        } else {
            if (in != p.data) {
                std::cout << " error ! ma(input, N): another input serial is asigned !! " << std::endl;
                exit(-1);
            }
        }
        return uBEE::SEE_MA(this->x, this->x, in, N_, this->data);
    };

    inline const double &ma(double d, int n) {
        if (this->din == in && in != nullptr) {
            in[this->x] = d;
            return uBEE::SEE_MA(this->x, this->x, in, N_, this->data);
        } else if (in == nullptr) {
            in = new double[this->unit->ohlcv_len];
            for (int i = 0; i < this->unit->ohlcv_len; i++) {
                in[i] = NAN;
            }
            N_ = n;
            this->din = in;
            in[this->x] = d;

            PeriodBase<N...>::func_signal_end->Connect(this, &MA_t<N...>::_update);
            return uBEE::SEE_MA(this->x, this->x, in, N_, this->data);
        } else {
            std::cout << " ma(double d, int n):  input error!!" << std::endl;
            exit(-1);
        }
    };

    inline const double &ma(int xohlcv, int n) {
        if (in == nullptr) {
            if (xohlcv == OHLCV::O1) {
                in = this->OO;
            } else if (xohlcv == OHLCV::H1) {
                in = this->unit->HH;
            } else if (xohlcv == OHLCV::L1) {
                in = this->LL;
            } else if (xohlcv == OHLCV::C1) {
                in = this->CC;
            } else if (xohlcv == OHLCV::V1) {
                in = this->unit->VV; // volume => from int to double
            } else {
                std::cout << "MA() input error !  EMA<> x(O,10) \n";
            }
            N_ = n;
            PeriodBase<N...>::func_signal->Connect(this, &MA_t<N...>::_ma);
        } else {
            if (xohlcv == OHLCV::O1) {
                if (in != this->OO) {
                    std::cout << "MA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else if (xohlcv == OHLCV::H1) {
                if (in != this->unit->HH) {
                    std::cout << "MA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else if (xohlcv == OHLCV::L1) {
                if (in != this->LL) {
                    std::cout << "MA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else if (xohlcv == OHLCV::C1) {
                if (in != this->CC) {
                    std::cout << "MA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else if (xohlcv == OHLCV::V1) {
                if (in != this->unit->VV) {
                    std::cout << "MA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else {
                std::cout << "MA() input error !  EMA<> x(O,10) \n";
            }
        }
        return uBEE::SEE_MA(this->x, this->x, in, N_, this->data);
    };

    template <typename... Args> inline auto MA(Args &&...args) -> decltype(ma(std::forward<Args>(args)...)) { return ma(std::forward<Args>(args)...); }

  private:
    inline void _update() {
        if (this->x >= this->repeat_x) {
            if (din != nullptr) {
                in[this->x - this->repeat_x] = in[this->x];
            }
        }
    }
};

// EMA #############################################################################################
template <int... N> class EMA_t : public FutureSerial<N...>, public OhlcvSerial<N...> {
  public:
    int N_;

  private:
    double *in;           // 用于计算EMA的输入的数据。
                          // 可以定义计算所需要临时变量等。
                          // --
    double *din{nullptr}; // 在 ema(double,int) 中使用

  private:
    // 构造函数继承、等号运算符继承
    using FutureSerial<N...>::FutureSerial;
    using FutureSerial<N...>::operator=;

  public:
    EMA_t() {
        std::cout << "B:constructor !! EMA() --------------------*****" << std::endl;
        in = nullptr;
        din = nullptr;
    };

    EMA_t(int xohlcv, int n) {
        std::cout << "constructor !! EMA() : input OHLCV::X N ! " << std::endl;
        //  PeriodBase<N...>::UnitCheck();
        PeriodBase<N...>::func_signal->Connect(this, &EMA_t<N...>::_ema);
        N_ = n;
        if (xohlcv == OHLCV::O1) {
            in = this->OO;
        } else if (xohlcv == OHLCV::H1) {
            in = this->HH;
        } else if (xohlcv == OHLCV::L1) {
            in = this->LL;
        } else if (xohlcv == OHLCV::C1) {
            in = this->CC;
        } else if (xohlcv == OHLCV::V1) {
            in = this->unit->VV; // volume => from int to double
        } else {
            std::cout << "EMA() input error !  EMA<> x(int,10) \n";
        }
        _ema();
    }

    EMA_t(char xohlcv, int n) {
        std::cout << "constructor !! EMA() : input OHLCV::X N ! " << std::endl;
        //  PeriodBase<N...>::UnitCheck();
        PeriodBase<N...>::func_signal->Connect(this, &EMA_t<N...>::_ema);
        N_ = n;
        if (xohlcv == 'O' || xohlcv == 'o') {
            in = this->OO;
        } else if (xohlcv == 'H' || xohlcv == 'h') {
            in = this->HH;
        } else if (xohlcv == 'L' || xohlcv == 'l') {
            in = this->LL;
        } else if (xohlcv == 'C' || xohlcv == 'c') {
            in = this->CC;
        } else if (xohlcv == 'V' || xohlcv == 'v') {
            in = this->VV; // volume => from int to double
        } else {
            std::cout << "EMA() input error !  EMA<> x(char,10) \n";
        }
        _ema();
    }

    ~EMA_t() {
        if (din != nullptr) {
            delete[] din;
        }
        std::cout << " EMA_t release ---- 2 !" << std::endl;
    };

    // 如果是静态变量定义，比如：EMA_T<8, 9> D3(K3, B2 / 2);
    // 在onBar中，只会执行一次，所以下面的 _ema()只会在初始化时，执行一次。
    // 但 func_signal 槽中的_ema()会在每次onBar之前，执行一次。
    // 如果要在onBar中每次都执行，则必须明确调用  DEA3.ema(X3, M3);

    // /* 目前不再提供这种构造函数 2023-11-22, 所有的写法变成 EMA_t<8,9> X3;  X3.ema(RSV3,12);
    // EMA_t(FutureSerial<N...> &p, int n) {
    //     N_ = n;
    //     in = p.data;
    //     _ema();
    // };
    // */

  private:
    inline void _ema() { uBEE::SEE_EMA(this->x, this->x, in, N_, this->data); };

  public:
    inline const double &ema() {
        if (nullptr == in) {
            std::cout << "ema() data need to be initial !!" << std::endl;
            exit(-1);
        }
        return uBEE::SEE_EMA(this->x, this->x, in, N_, this->data);
    };

    inline const double &ema(FutureSerial<N...> &p, int n) {
        if (nullptr == p.data) {
            std::cout << "ema(p,n) data need to be initial !!" << std::endl;
            exit(-1);
        }
        if (in == nullptr) {
            in = p.data;
            N_ = n;
        } else {
            if (in != p.data) {
                std::cout << " error ! ema(FutureSerial<N...> &p, N): another input serial is asigned !! " << std::endl;
                exit(-1);
            }
        }
        return uBEE::SEE_EMA(this->x, this->x, in, N_, this->data);
    };

    inline const double &ema(double d, int n) {
        if (din == in && in != nullptr) {
            in[this->x] = d;
            return uBEE::SEE_EMA(this->x, this->x, in, N_, this->data);
        } else if (in == nullptr) {
            in = new double[this->unit->ohlcv_len];
            for (int i = 0; i < this->unit->ohlcv_len; i++) {
                in[i] = NAN;
            }
            N_ = n;
            din = in;
            in[this->x] = d;

            PeriodBase<N...>::func_signal_end->Connect(this, &EMA_t<N...>::_update);
            return uBEE::SEE_EMA(this->x, this->x, in, N_, this->data);
        } else {
            std::cout << " ema(double d, int n):  another input serial is asigned !! " << std::endl;
            exit(-1);
        }
    };

    inline const double &ema(char xohlcv, int n) {
        if (in != nullptr) {
            if (xohlcv == 'O' || xohlcv == 'o') {
                if (in != this->OO) {
                    std::cout << "EMA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else if (xohlcv == 'H' || xohlcv == 'h') {
                if (in != this->HH) {
                    std::cout << "EMA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else if (xohlcv == 'L' || xohlcv == 'l') {
                if (in != this->LL) {
                    std::cout << "EMA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else if (xohlcv == 'C' || xohlcv == 'c') {
                if (in != this->CC) {
                    std::cout << "EMA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else if (xohlcv == 'V' || xohlcv == 'v') {
                if (in != this->VV) {
                    std::cout << "EMA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else {
                std::cout << "EMA() input error !  EMA<> x(O,10) \n";
            }
        } else {
            if (xohlcv == 'O' || xohlcv == 'o') {
                in = this->OO;
            } else if (xohlcv == 'H' || xohlcv == 'h') {
                in = this->HH;
            } else if (xohlcv == 'L' || xohlcv == 'l') {
                in = this->LL;
            } else if (xohlcv == 'C' || xohlcv == 'c') {
                in = this->CC;
            } else if (xohlcv == 'V' || xohlcv == 'v') {
                in = this->VV; // volume => from int to double
            } else {
                std::cout << "EMA() input error !  EMA<> x(O,10) \n";
            }
            N_ = n;
            PeriodBase<N...>::func_signal->Connect(this, &EMA_t<N...>::_ema);
        }
        return uBEE::SEE_EMA(this->x, this->x, in, N_, this->data);
    };

    inline const double &ema(int xohlcv, int n) {
        if (in != nullptr) {
            if (xohlcv == OHLCV::O1) {
                if (in != this->OO) {
                    std::cout << "EMA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else if (xohlcv == OHLCV::H1) {
                if (in != this->HH) {
                    std::cout << "EMA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else if (xohlcv == OHLCV::L1) {
                if (in != this->LL) {
                    std::cout << "EMA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else if (xohlcv == OHLCV::C1) {
                if (in != this->CC) {
                    std::cout << "EMA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else if (xohlcv == OHLCV::V1) {
                if (in != this->VV) {
                    std::cout << "EMA() input error !  EMA<> x(O,10) \n";
                    exit(-1);
                };
            } else {
                std::cout << "EMA() input error !  EMA<> x(O,10) \n";
            }
        } else {
            if (xohlcv == OHLCV::O1) {
                in = this->OO;
            } else if (xohlcv == OHLCV::H1) {
                in = this->HH;
            } else if (xohlcv == OHLCV::L1) {
                in = this->LL;
            } else if (xohlcv == OHLCV::C1) {
                in = this->CC;
            } else if (xohlcv == OHLCV::V1) {
                in = this->VV; // volume => from int to double
            } else {
                std::cout << "EMA() input error !  EMA<> x(O,10) \n";
            }
            N_ = n;
            PeriodBase<N...>::func_signal->Connect(this, &EMA_t<N...>::_ema);
        }
        return uBEE::SEE_EMA(this->x, this->x, in, N_, this->data);
    };

    template <typename... Args> inline auto EMA(Args &&...args) -> decltype(ema(std::forward<Args>(args)...)) { return ema(std::forward<Args>(args)...); }

  private:
    inline void _update() {
        if (this->x >= this->repeat_x) {
            if (din != nullptr) {
                in[this->x - this->repeat_x] = in[this->x];
            }
        }
    }
};

// SMA #############################################################################################
template <int... N> class SMA_t : public FutureSerial<N...>, public OhlcvSerial<N...> {
  public:
    int N_;
    int M_;

  private:
    double *in{nullptr};
    double *din{nullptr};

    using FutureSerial<N...>::FutureSerial;
    using FutureSerial<N...>::operator=;

  public:
    SMA_t() { in = nullptr; };

    SMA_t(const SMA_t<N...> &p) = delete;

    // SMA_t(FutureSerial<N...> &p, int n, int m) {
    //     std::cout << "constructor !! SMA_t() -------------------------------------------------*****" << std::endl;
    //     PeriodBase<N...>::UnitCheck();
    //     //   PeriodBase<N...>::func_signal->Connect(this, &SMA_t<N...>::_sma);
    //     N_ = n;
    //     M_ = m;
    //     in = p.data;
    //     _sma();
    // };

    SMA_t(int xohlcv, int n, int m) {
        std::cout << "constructor !! SMA_t() -------------------------------------------------*****" << std::endl;
        PeriodBase<N...>::UnitCheck();
        PeriodBase<N...>::func_signal->Connect(this, &SMA_t<N...>::_sma);
        N_ = n;
        M_ = m;
        if (xohlcv == OHLCV::O1) {
            in = this->OO;
        } else if (xohlcv == OHLCV::H1) {
            in = this->HH;
        } else if (xohlcv == OHLCV::L1) {
            in = this->LL;
        } else if (xohlcv == OHLCV::C1) {
            in = this->CC;
        } else {
            // todo  V is int[], how to convert to double[] ?
            std::cout << "SMA_t() input error !  SMA_t<> x(O,10) \n";
        }
        _sma();
    }

    SMA_t(char xohlcv, int n, int m) {
        std::cout << "constructor !! SMA_t() ------------------------------------------*****" << std::endl;
        PeriodBase<N...>::UnitCheck();
        PeriodBase<N...>::func_signal->Connect(this, &SMA_t<N...>::_sma);
        N_ = n;
        M_ = m;
        if (xohlcv == 'O' || xohlcv == 'o') {
            in = this->OO;
        } else if (xohlcv == 'H' || xohlcv == 'h') {
            in = this->HH;
        } else if (xohlcv == 'L' || xohlcv == 'l') {
            in = this->LL;
        } else if (xohlcv == 'C' || xohlcv == 'c') {
            in = this->CC;
        } else {
            // todo  V is int[], how to convert to double[] ?
            std::cout << "SMA_t() input error !  SMA_t<> x(O,10) \n";
        }

        _sma();
    }

    ~SMA_t() {
        if (din != nullptr) {
            delete[] din;
        }
        std::cout << " SMA_t release 1!" << std::endl;
    };

  private:
    inline void _sma() { uBEE::SEE_SMA(this->x, this->x, in, N_, M_, this->data); };

  public:
    inline const double &sma() {
        if (nullptr == in) {
            std::cout << "sma() input data need to be initial !!" << std::endl;
            exit(-1);
        }
        return uBEE::SEE_SMA(this->x, this->x, in, N_, M_, this->data);
    };

    inline const double &sma(FutureSerial<N...> &p, int n, int m) {
        if (nullptr == p.data) {
            std::cout << "sma(p,n,m) data need to be initial !!" << std::endl;
            exit(-1);
        }
        if (in == nullptr) {
            in = p.data;
            N_ = n;
            M_ = m;
        } else {
            if (in != p.data) { // 是为了防止用别的方法初始化的对象，又来调用这个函数。
                std::cout << " error ! sma(FutureSerial<>, N,M): another input serial is asigned !! " << std::endl;
                exit(-1);
            }
        }
        return uBEE::SEE_SMA(this->x, this->x, in, N_, M_, this->data);
    };

    inline const double &sma(double d, int n, int m) {
        if (din == in && in != nullptr) {
            in[this->x] = d;
            return uBEE::SEE_SMA(this->x, this->x, in, N_, M_, this->data);
        } else if (in == nullptr) {
            in = new double[this->unit->ohlcv_len];
            for (int i = 0; i < this->unit->ohlcv_len; i++) {
                in[i] = NAN;
            }
            N_ = n;
            M_ = m;
            din = in; // din 是为了防止用别的方法初始化的对象，又来调用这个函数。
            in[this->x] = d;

            PeriodBase<N...>::func_signal_end->Connect(this, &SMA_t<N...>::_update);
            return uBEE::SEE_SMA(this->x, this->x, in, N_, M_, this->data);
        } else {
            std::cout << " sma(double d, int n, int m):  another input serial is asigned !! " << std::endl;
            exit(-1);
        }
        std::cout << " sma(double,N,M) end " << std::endl;
    };

    template <typename... Args> inline auto SMA(Args &&...args) -> decltype(sma(std::forward<Args>(args)...)) { return sma(std::forward<Args>(args)...); }

  private:
    inline void _update() {
        if (this->x >= this->repeat_x) {
            if (din != nullptr) {
                in[this->x - this->repeat_x] = in[this->x];
            }
        }
    }
};

// RSV #############################################################################################
/* R:=(CLOSE-LLV(LOW,N))/(HHV(HIGH,N)-LLV(LOW,N))*100; */
template <int... N> class RSV_t : public FutureSerial<N...>, public OhlcvSerial<N...> {
  public:
    int N_;
    //  int &x = this->unit->index;

  private:
    double *in{nullptr};

    // 下面三个值必须初始化。
    double preH;
    double preL;
    int preF; // 涨跌停标志位

    using FutureSerial<N...>::FutureSerial;
    using FutureSerial<N...>::operator=;

  public:
    RSV_t() {
        in = nullptr;
        N_ = -1;

        preH = NAN; // 必须初始化
        preL = NAN; // 必须初始化
        preF = 0;   // 必须初始化
    }

    RSV_t(int xohlcv, int n) {
        std::cout << "constructor !! SMA_t() -------------------------------------------------*****" << std::endl;
        PeriodBase<N...>::UnitCheck();
        PeriodBase<N...>::func_signal->Connect(this, &RSV_t<N...>::_rsv);
        N_ = n;

        if (xohlcv == OHLCV::O1) {
            in = this->OO;
        } else if (xohlcv == OHLCV::H1) {
            in = this->HH;
        } else if (xohlcv == OHLCV::L1) {
            in = this->LL;
        } else if (xohlcv == OHLCV::C1) {
            in = this->CC;
        } else {
            // todo  V is int[], how to convert to double[] ?
            std::cout << "RSV_t() input error !  RSV_t<> x(OHLC,N) \n";
        }

        preH = NAN; // 必须初始化
        preL = NAN; // 必须初始化
        preF = 0;   // 必须初始化

        _rsv();
    }

    RSV_t(char xohlcv, int n) {
        std::cout << "constructor !! SMA_t() -------------------------------------------------*****" << std::endl;
        PeriodBase<N...>::UnitCheck();
        PeriodBase<N...>::func_signal->Connect(this, &RSV_t<N...>::_rsv);
        N_ = n;

        if (xohlcv == 'O' || xohlcv == 'o') {
            in = this->OO;
        } else if (xohlcv == 'H' || xohlcv == 'h') {
            in = this->HH;
        } else if (xohlcv == 'L' || xohlcv == 'l') {
            in = this->LL;
        } else if (xohlcv == 'C' || xohlcv == 'c') {
            in = this->CC;
        } else {
            // todo  V is int[], how to convert to double[] ?
            std::cout << "RSV_t() input error !  RSV_t<> x(OHLC,N) \n";
        }

        preH = NAN; // 必须初始化
        preL = NAN; // 必须初始化
        preF = 0;   // 必须初始化

        _rsv();
    }

    ~RSV_t() { std::cout << " RSV_t release ^^ 3 !" << std::endl; };

    RSV_t(int n) {
        std::cout << "constructor !! RSV_t() -------------------------------------------------*****" << std::endl;
        if (n <= 0) {
            std::cout << "error!  RSV_t  N is less 0 !! " << std::endl;
            exit(-1);
        }
        in = this->CC;
        N_ = n;

        preH = NAN; // 必须初始化
        preL = NAN; // 必须初始化
        preF = 0;   // 必须初始化

        PeriodBase<N...>::UnitCheck();
        PeriodBase<N...>::func_signal->Connect(this, &RSV_t<N...>::_rsv);

        _rsv();
    };

  private:
    void _rsv() {
        uBEE::SEE_RSV(this->x, this->x, this->HH, this->LL, this->CC, &preH, &preL, &preF, N_, this->data);

        /*
        std::cout << " rsv() : O:" << this->OO[x] << "  ";
        std::cout << " H:" << this->HH[x] << "  ";
        std::cout << " L:" << this->LL[x] << "  ";
        std::cout << " C:" << this->CC[x] << "  ";
        std::cout << " V:" << this->unit->VV[x] << "  ";
        std::cout << " RSV_t:" << this->data[x] << "  ";
        std::cout << " index:" << x << "\n ";
        */
    };

  public:
    inline const double &rsv() {
        if (N_ <= 0) {
            std::cout << "  error!  RSV_t : N is not corect  !! " << std::endl;
            exit(-1);
        }
        return uBEE::SEE_RSV(this->x, this->x, this->HH, this->LL, this->CC, &preH, &preL, &preF, N_, this->data);
    };

    inline const double &rsv(int n) {
        if (n > 0) {
            if (N_ < 0) {
                in = this->CC;
                N_ = n;
            } else {
                if (N_ != n) {
                    std::cout << "  error!  RSV_t : N is not corect  !! " << std::endl;
                    exit(-1);
                }
            }
        } else {
            std::cout << "  error!  RSV_t : N is not corect  !! " << std::endl;
            exit(-1);
        }
        return uBEE::SEE_RSV(this->x, this->x, this->HH, this->LL, this->CC, &preH, &preL, &preF, N_, this->data);
    };

    inline const double &rsv(FutureSerial<N...> &p, int n) {
        if (n > 0) {
            if (N_ < 0) {
                N_ = n;
            } else {
                if (N_ != n) {
                    std::cout << "  error!  RSV_t : N is not corect  !! " << std::endl;
                    exit(-1);
                }
            }
        } else {
            std::cout << "  error!  RSV_t : N is not corect  !! " << std::endl;
            exit(-1);
        }

        if (nullptr == p.data) {
            std::cout << "  error!  RSV_t  p.data is nullptr , need to be initial !!" << std::endl;
            exit(-1);
        }
        if (in == nullptr) {
            in = p.data;
        } else {
            if (in != p.data) {
                std::cout << "   error!  RSV_t   : another input serial is asigned !! " << std::endl;
                exit(-1);
            }
        }
        return uBEE::SEE_RSV(this->x, this->x, this->HH, this->LL, in, &preH, &preL, &preF, N_, this->data);
    };

    // todo 如何让 一个函数拥有两个函数名: 下面的实现
    template <typename... Args> inline auto RSV(Args &&...args) -> decltype(rsv(std::forward<Args>(args)...)) { return rsv(std::forward<Args>(args)...); }
};

// BOLL #############################################################################################

// RSV #############################################################################################

// x.out 是大家公用的数组空间。
// todo  要检查 start = finish 时，MA等计算是否有优化动作。
template <int... N> double D_EMA(FutureSerial<N...> &p, int n) {
    // todo , x.out如何使用调用者的空间？
    return uBEE::SEE_EMA(p.unit->index, p.unit->index, p.data, n, p.out);
};

template <int... N> double D_EMA(FutureSerial<N...> &x, double *o, int n) { return uBEE::SEE_EMA(x.unit->index, x.unit->index, o, n, x.data); }

template <int... N> double D_MA(FutureSerial<N...> &x, int n) { return uBEE::SEE_MA(x.unit->index, x.unit->index, x.data, n, x.out); }

template <int... N> double D_RSV(FutureSerial<N...> &x, int n) {
    // 下面这些玩意，移到 FutureSerial里去。 todo  用的是 &x(输入的，相当于用的是别人家的)的
    // preH，是不是会有问题？ double preH; double preL; int preF; todo 这里的 preH , preL, preF
    // 是否有问题？
    uBEE::SEE_RSV(x.unit->index, x.unit->index, x.unit->HH, x.unit->LL, x.unit->CC, &x.preH, &x.preL, &x.preF, n, x.out);
    return 0;
};

// int bars_last(bool x) {
//     int count = 0;
//     if (x) {
//         count++;
//     } else {
//         count = 0;
//     }
//     return count;
// }

// // template <class T = double, int... N> class TEST {
// //   public:
// //     T *x;
// //     T x1[100];
// //     TEST(T n) {
// //         x = x1;
// //         x[0] = n;
// //     }
// //     T get() { return x; }
// // };

// /*
// int SEE_MA(int start, int finish, const double in[], int N, double out[]);
// int SEE_EMA(int start, int finish, const double in[], int N, double out[]);
// int SEE_SMA(int start, int finish, const double in[], int N, int M, double out[]);
// */

// int ReadTick(const char *file_name) {
//     char indata[1000];
//     char outdata[2048];

//     struct libdeflate_decompressor *decompressor;
//     decompressor = libdeflate_alloc_decompressor();

//     size_t decsize;

//     int iRc = 0;
//     int fd;
//     int retry;
//     char ca_errmsg1[8192];
//     size_t tick_len = sizeof(CThostFtdcDepthMarketDataField);
//     int16_t len;
//     int rtn;

//     retry = 0;
//     while ((fd = open(file_name, O_RDONLY, 0660)) == -1) {
//         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//         if ((retry++) > 10) {
//             printf("File.cpp:  file_name:  %s\n", file_name);
//             printf("File.cpp: fatal error occured !!! error_no is %d\n", errno);
//             return -1;
//         }
//     }

//     while (rtn = read(fd, &len, sizeof(int16_t))) {
//         int in_len = read(fd, indata, len);

//         // get compressed data from file to indata;
//         // uncompressed to outdata;
//         // tick_len should be the same with decsize; decsize是解压后的长度。
//         libdeflate_deflate_decompress(decompressor, indata, in_len, outdata, tick_len, &decsize);
//         std::cout << "rtn: " << rtn << "   len:" << len << "    in_len: " << in_len << "  " << decsize << std::endl;

//         CThostFtdcDepthMarketDataField *tick = (CThostFtdcDepthMarketDataField *)outdata;

//         snprintf(ca_errmsg1, 8192, "A:%s %s %s T:%s O:%g H:%g L:%g C:%g V:%d \n", tick->ActionDay, tick->InstrumentID, tick->TradingDay, tick->UpdateTime, tick->LastPrice, tick->AskPrice1, tick->BidPrice1, tick->AskPrice2, tick->Volume);
//         std::cout << ca_errmsg1 << std::endl;
//     }

//     close(fd);
//     libdeflate_free_decompressor(decompressor);

//     return 0;
// };
} // namespace uBEE