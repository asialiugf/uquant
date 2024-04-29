
#pragma once
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <functional>
#include <iostream>
#include <ranges>
#include <vector>

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

// ====================== Trader ===========================================================
template <int... N> class Trader : public FutureSerial<N...> {
  private:
    // 用于记录
    std::vector<Order> orders_;

    int cur_buy_position_;  // 当前bar的买多仓位   今天
    int cur_sell_position_; // 当前bar的卖空仓位

    int ref1_buy_position_;  // 前一个bar的买多仓位 昨天
    int ref1_sell_position_; // 前一个bar的卖空仓位

    int ref2_buy_position_;  // 前一个bar的买多仓位 前天
    int ref2_sell_position_; // 前一个bar的卖空仓位

    int open_mount;  // 总的开仓数量，用于计算手续费
    int close_mount; // 总的平仓数量，用于计算手续费

  public:
    // 构造函数继承、等号运算符继承
    using FutureSerial<N...>::FutureSerial;
    using FutureSerial<N...>::operator=;

  public:
    Trader() {
        std::cout << "B:constructor !! Trader --------------------*****" << std::endl;
        this->plot_flag_ = false;
        cur_buy_position_ = 0;   //  今天持仓
        cur_sell_position_ = 0;  //  今天持仓
        ref1_buy_position_ = 0;  //  昨天持仓
        ref1_sell_position_ = 0; //  昨天持仓
        ref2_buy_position_ = 0;  //  前天持仓
        ref2_sell_position_ = 0; //  前天持仓
        open_mount = 0;          // 总的开仓数量，用于计算手续费
        close_mount = 0;         // 总的平仓数量，用于计算手续费
        PeriodBase<N...>::func_signal_end->Connect(this, &Trader<N...>::_earnings);
    };

    ~Trader() { std::cout << " Trader release ---- !" << std::endl; };

  public:
    inline const void buyopen(int x) { // 开多仓 open表示开仓，buy表示多仓
        cur_buy_position_ += x;
        open_mount += x;
    };
    inline const void buyclose(int x) { // 平多仓，close表示平仓
        if (cur_buy_position_ > x) {
            cur_buy_position_ -= x;
            close_mount += x; // 平仓的次数增加，用于计算手续费
        } else {              // 如果提交的平仓数据，比现有的买单还要多，那就平掉现有所有买单，但不增加卖单。
            close_mount += cur_buy_position_;
            cur_buy_position_ = 0;
        }
    };
    inline const void sellopen(int x) { //  开空仓 sell表示空仓
        cur_sell_position_ += x;
        open_mount += x; // 开仓数量+x, 用于计算手续费
    };
    inline const void sellclose(int x) { // 卖出的单（空单）， 进行平仓，平空仓
        if (cur_sell_position_ > x) {
            cur_sell_position_ -= x;
            close_mount += x;
        } else { // 如果提交的平仓数量x,比现有的 cur_sell_position_ 仓位数量还要大，那就把现有的 cur_sell_position_平掉，但不增加反向买单
            close_mount += cur_sell_position_;
            cur_sell_position_ = 0;
        }
    };
    //  inline const double &cancel(){};

    inline const int &buyposition() { return this->cur_buy_position_; }; // 含今天的开仓
    inline const int &sellposition() { return this->cur_sell_position_; };

    inline const int &Bposition() { return ref1_buy_position_; }; // 不含今天的开仓
    inline const int &Sposition() { return ref1_sell_position_; };

  private:
    // 简单计算 以当前 kbar开盘价为准，计算前一个kbar的下单。
    // 真实的下单，要看ctp是如何确认交易是否成功，再确定如何计算。

    inline void _earnings() { // 这个方法是在onbar结束后进行的，但在send之前调用。

        // 计算收益
        // 0. 本算法，暂时只是针对回测，对于实时的计算方法，需要根据CTP重写。
        // 1. 本算法的逻辑是：以当前切片计算买卖点，以下一个切片的开盘价为成交价格，所以当前切片的order不计算，要在下一个切片中计算
        // 2. 即，当前切片的postion，不计算当前切片的order。
        // 2. 当前切片的收益，是以当前切片的收盘价作为最后的价格，乘以 position 持仓。

        // 计算方法：分为两个方向计算：买多，卖空。
        //  今天的收益 = 昨天order数量(ref1_buy -ref2_buy) * ( 今天C - 今天O ) + 前天总仓位 ref2 * ( 今天C - 昨天REF(C,1) ) + 昨天的收益。
        if (this->x > 0) {
            int idx = this->x;

            // 今天的收益：前天的仓位*(close - close.ref) + 昨天的order * (close-open)  ==>  多头与空头 两个方向。
            double buy_ref2 = (this->CC[this->x] - this->CC[this->x - 1]) * this->ref2_buy_position_;               // 前天的仓位 * 收盘价差。
            double buy_delta = (this->CC[this->x] - this->OO[this->x]) * (ref1_buy_position_ - ref2_buy_position_); // 昨天的order数量 = ref1_buy_position_ - ref2_buy_position_
            double sell_ref2 = (this->CC[this->x - 1] - this->CC[this->x]) * this->ref2_sell_position_;
            double sell_delta = (this->OO[this->x] - this->CC[this->x]) * (ref1_sell_position_ - ref2_sell_position_);

            // 总收益 = 昨天的总收益 + 今天的收益
            this->data[this->x] = this->data[this->x - 1] + buy_ref2 + buy_delta + sell_ref2 + sell_delta;

            // 开平仓测试！ ==============
            // std::cout << std::endl << std::endl;
            // std::cout << " 开仓数量： open_mount:" << this->open_mount << " 平仓数量： close_mount:" << this->close_mount << "  -------  ";
            // std::cout << "  this->data[this->x] : " << this->data[this->x] << std::endl;
            // std::cout << "index: " << this->x;
            // std::cout << " buy 前天仓位 ref2: " << ref2_buy_position_ << " 昨天仓位 ref1: " << ref1_buy_position_ << " 今天仓位 cur: " << cur_buy_position_;
            // std::cout << " sell 前天仓位 ref2: " << ref2_sell_position_ << " 昨天仓位 ref1: " << ref1_sell_position_ << " 今天仓位 cur: " << cur_sell_position_ << std::endl;

            // std::cout << " buy 昨天新增仓位: " << (ref1_buy_position_ - ref2_buy_position_) << " * (close-open): " << (this->CC[idx] - this->OO[idx]) << " : " << buy_delta << std::endl;
            // std::cout << "buy 前天仓位 ref2: " << ref2_buy_position_ << " * ( close - ref(close,1) ): " << (this->CC[idx] - this->CC[idx - 1]) << " : " << buy_ref2 << std::endl;
            // std::cout << " sell 昨天新增仓位: " << (ref1_sell_position_ - ref2_sell_position_) << " * (close-open): " << (this->OO[idx] - this->CC[idx]) << " : " << sell_delta << std::endl;
            // std::cout << "sell 前天仓位 ref2: " << ref2_sell_position_ << " * ( close - ref(close,1) ): " << (this->CC[idx - 1] - this->CC[idx]) << " : " << sell_ref2 << std::endl;
            // std::cout << " 昨天收益： " << this->data[idx - 1] << " 今天收益：  this->data[idx - 1] + buy_ref2 + buy_delta + sell_ref2 + sell_delta ：  " << this->data[idx] << std::endl;
            // std::cout << "   CC[idx-1] : " << this->CC[idx - 1] << " CC[idx]: " << this->CC[idx] << "  OO[idx]: " << this->OO[idx] << std::endl;
            // 开平仓测试！ ==============
        } else {
            this->data[this->x] = 0;
        }

        // 如果当前kbar有下单，则要记录到orders_中！！ todo 记录的内容有待定！！
        if ((this->ref1_buy_position_ != this->cur_buy_position_) || (this->ref1_sell_position_ != this->cur_sell_position_)) {
            Order order;
            order.idx = this->x;
            order.buyposition = cur_buy_position_;
            order.sellposition = cur_sell_position_;
            this->orders_.push_back(order);
        }

        this->ref2_buy_position_ = this->ref1_buy_position_; // 平移切片仓位。 前天=昨天， 昨天=今天 的全仓位。
        this->ref2_sell_position_ = this->ref1_sell_position_;

        this->ref1_buy_position_ = this->cur_buy_position_;
        this->ref1_sell_position_ = this->cur_sell_position_;
    };

  public:
    // 用于将某对象的数据传给前端显示，在base.cpp的sendTradingData()中会处理
    // 在unit中有一个vector: pointslist_output。
    // 每个对象在调用这个plot时，会传入自已的对象名、要前端显示的颜色及方式。【talib_define.h: #define PLOT(obj, aa) obj.plot(#obj, aa) 】
    // 这个plot会将本对象的 data指针放到这个vector中。
    void plot(std::string name, int color) override {
        // FutureSerial<N...>::plot(name, color);
        if (this->plot_flag_ == false) {
            // 这里的data保存的交易收益金额，每个kbar保留一个值，所以是一个data序列，上传到web时，plot(name,color);
            std::tuple<std::string, double *, int> temp = std::make_tuple(name, this->data, color);
            this->unit->output.push_back(temp);

            // 这里的orders_是一个vector,保留每个order, 在一个切片，即每个index，可能会有多个定单。
            // 所以在上传时(程序是在base.cpp中的send...函数中)，记录成这个切片的数组 {[{},{},{}]} 正常情况下，一个index应该只有一个order
            std::string ordername = name + "_order";
            std::tuple<std::string, std::vector<Order> *, int> porder = std::make_tuple(ordername, &orders_, color);
            this->unit->orderslist_output.push_back(porder);
            this->plot_flag_ = true;
        }
    }
};

} // namespace uBEE

// 前一个kbar切片有买卖，要重新计算position以及收益。
// 计算了前一个kbar提交的买卖order之后的position作为当前kbar的position。
// for (auto it = this->orders_.rbegin(); it != this->orders_.rend(); it++) {
//     if ((*it).idx < this->x - 1) {
//         break;
//     }
//     // 重新计算position !
//     switch ((*it).type) {
//     case 1: { // buyopen
//         printf("1");
//         this->buy_position_ += (*it).mount;
//         break;
//     }
//     case 2: { //   buyclose
//         printf("2");
//         this->buy_position_ -= (*it).mount;
//         break;
//     }
//     case 3: { //  sellopen
//         printf("3");
//         this->sell_position_ += (*it).mount;
//         break;
//     }
//     case 4: { //   sellclose
//         printf("4");
//         this->sell_position_ -= (*it).mount;
//         break;
//     }
//     default:
//         break;
//     }
// }

// Order order;
// order.idx = this->x;
// order.type = 4;
// order.mount = x;
// this->orders_.push_back(order);