
#ifndef UBEE_FUTURE_PERIOD_H
#define UBEE_FUTURE_PERIOD_H
// 基类，由PeriodSerial继承。

#include "../base/base.h"
#include <glog/logging.h>

#include <vector>
namespace uBEE {

// Future,FutureSerial的基类
// 变长参数模板，

// 这个类由Future类继承，在Future对象初始化时，将base的数据与这里的静态成员变量进行映射，完成对这里的静态变量的初始化。
// 当base类的数据变化时，所有这个类的子类的数据都会变化。比如对OHLCV进行赋值操作，是由base类完成的。
template <int... N> class PeriodBase {
  public:
  public:
    static char instrumentID[81];
    static Unit *unit; // 一个future的一个period，有一个unit，由 Base::FutureInit()初始化
                       // 由 Future<M,N> fu(&base); 将其与 base里的 unit 进行绑定。
    static int *ohlcv_len;
    static int *index;           //  OHLCV 数组下标，指向当前最新添加的 OHLCV 数组下标。
    static int *repeat_index;    //  当 index > repeat_index时，要将数据向前复制。
    static int *period_value;    //  周期，以秒计， 1(1S) 15(15S)  60(1F) 300(5F)
    static int *period_index;    // 周期的 数组下标 [0-49]
    static char period_name[16]; // 周期名
    static double *OO;           // 等于 double O[];
    static double *HH;
    static double *LL;
    static double *CC;
    static double *VV;
    static double *out; // 用于 new_talib.h中的 DEMA(FutureSerial<8,4> &x, 20)中调用
                        // SEE_EMA时，做为out[]入参。

    //  double *data;
    //  int *idata;

    // 按照 <M,N>对 来说的话，这里只需要一个 Signal<void()>就可以了，
    // 因为它可以连接所有与M这个合约N这个周期的所有 function。
    // 这里初始化了1个 Signal<void()>， 每个都可以connect 多个function。
    static Signal<void()> *func_signal;     // onbar 前置处理
    static Signal<void()> *func_signal_end; // onbar 前置处理

    PeriodBase() {
        std::cout << std::endl;
        std::cout << "B:construtor !! PeriodBase" << std::endl;
        std::cout << "E:construtor !! PeriodBase" << std::endl;
        //  data = nullptr;
        //  idata = nullptr;
    }

    PeriodBase(PeriodBase<N...> &p) = delete;

    template <int N1> int getOne() { return N1; };
    template <int M1, int N1> int getFirst() { return M1; }
    template <int M1, int N1> int getSecond() { return N1; }

    void UnitCheck() {
        std::cout << "B: UnitCheck(); " << std::endl;
        int future_idx{-1};
        int period_idx{-1};

        // 通过在if语句中使用constexpr关键字就可以在编译期计算if语句中的表达式，然后决定if语句走到哪个分支
        if constexpr (0 == sizeof...(N)) {
        } else if constexpr (1 == sizeof...(N)) {
            period_idx = getOne<N...>();

        } else if constexpr (2 == sizeof...(N)) {
            future_idx = getFirst<N...>();
            period_idx = getSecond<N...>();
        } else {
            std::cout << " template <int ...N> 里面的参数N必须小于等2 ！" << std::endl;
            exit(0);
        }

        if (PeriodBase<N...>::unit == nullptr) {
            std::cout << " unit没有绑定！ unit is nullptr !!" << std::endl;
            if (future_idx == -1 && period_idx == -1) {
                std::cout << " 请先执行 Future<>  Please!!!!!!!!" << std::endl;
                exit(-1);
            } else if (future_idx == -1) {
                std::cout << " 请先执行 Future<" << period_idx << "> Please !!!!!!!!" << std::endl;
                exit(-1);
            } else {
                std::cout << " 请先执行 Future<" << future_idx << "," << period_idx << "> Please !!!!!!!!" << std::endl;
                exit(-1);
            }
        }
    }
    // std::function<void()> handler;
    // static std::vector<std::function<void()>> ffnn;
    // 派生类的执行列表 还没有搞定。

  public:
    ~PeriodBase() = default;
}; // end class

// 下面这一堆玩意， 必须要， 不然的话，前面【 Future<N...>::unit = b->unit_array[0];
// 】这种操作会出问题。

template <int... N>                  // 这里很神奇啊！！！！   由M和N确定的数据，在Future内必须定义为 static,
int *PeriodBase<N...>::index = 0;    // 然后在这里进行初始化。
template <int... N>                  // 这里很神奇啊！！！！   由M和N确定的数据，在Future内必须定义为 static,
int *PeriodBase<N...>::repeat_index; //
template <int... N>                  // 这里很神奇啊！！！！
int *PeriodBase<N...>::period_value = 0;
template <int... N> // 这里很神奇啊！！！！
int *PeriodBase<N...>::period_index = 0;
template <int... N> // 这里很神奇啊！！！！
Unit *PeriodBase<N...>::unit = nullptr;
template <int... N> // 这里很神奇啊！！！！
int *PeriodBase<N...>::ohlcv_len = KSIZE;
template <int... N> // 这里很神奇啊！！！！
double *PeriodBase<N...>::OO = nullptr;
template <int... N> // 这里很神奇啊！！！！
double *PeriodBase<N...>::HH = nullptr;
template <int... N> // 这里很神奇啊！！！！
double *PeriodBase<N...>::LL = nullptr;
template <int... N> // 这里很神奇啊！！！！
double *PeriodBase<N...>::CC = nullptr;
template <int... N> // 这里很神奇啊！！！！
double *PeriodBase<N...>::VV = nullptr;
template <int... N> // 这里很神奇啊！！！！
double *PeriodBase<N...>::out = nullptr;
template <int... N> // 这里很神奇啊！！！！
Signal<void()> *PeriodBase<N...>::func_signal = nullptr;
template <int... N>                                          // 这里很神奇啊！！！！
Signal<void()> *PeriodBase<N...>::func_signal_end = nullptr; // onbar后置处理！

/*
template <int... N>                                   // 这里很神奇啊！！！！
std::array<double, KSIZE0> PeriodBase<N...>::o;      //
OHLCV是某一组交易基础数据。它由M、N二者一起才能唯一确定。 template <int... N> //
这里很神奇啊！！！！ std::array<double, KSIZE> PeriodBase<N...>::h;      //
这里的数组的长度应该怎么搞？？？？ 固定吗? template <int... N>                                   //
这里很神奇啊！！！！ std::array<double, KSIZE> PeriodBase<N...>::l;      //
这里的数组的长度应该怎么搞？？？？ 固定吗? template <int... N>                                   //
这里很神奇啊！！！！ std::array<double, KSIZE> PeriodBase<N...>::c;      //
这里的数组的长度应该怎么搞？？？？ 固定吗? template <int... N>                                   //
这里很神奇啊！！！！ std::array<double, KSIZE> PeriodBase<N...>::v;      //
这里的数组的长度应该怎么搞？？？？ 固定吗?
*/

// two types of data_structure:
/*   [type 1:] ********
// *   1 [futureID1 ] ---------------------------------------------------------------------------
//                 0  1   2   3   4    5    6    7    8    9   10  11  13  14 ...  ...
//                 x  1F  x   x  15F   x    x    1H   x    x   4H
//                    O           O              O             O
//                    O           O              O             O
//                                O
// *   2 [futureID1 ] ---------------------------------------------------------------------------
//                 0  1   2   3   4    5    6    7    8    9   10  11  13  14 ...  ...
//                 x  1F  x   x  15F   x    x    1H   x    x   4H
//                    O           O              O             O
//                    O           O              O             O
//                                O
//
//      "O": means: functtion like MACD(1), MACD(2), RSI(), KDJ()...
//      each <futureID,1F>( <M,N>pair below)   pair has a function_list !!!!
//
//      [type 2:] <M,N>  ********
//       1  <futureID1, 1F >  O O ........
//       2  <futureID1, 15F>  O O O O ........
//       3  <futureID1, 1H >  O O ........
//
//       4  <futureID2, 1F >  O O ........
//       5  <futureID2, 10F>  O O O O ........
//       6  <futureID2, 2H >  O O ........
//       7   ... ...
*/

// ################################# SectionsBase ###################################################
template <int... N> class SectionsBase : public PeriodBase<N...> {
    // -------------------------segments record ----------------------------

  public:
    int &x = PeriodBase<N...>::unit->index;
    int &repeat_x = PeriodBase<N...>::unit->repeat_index;
    int &period_val = PeriodBase<N...>::unit->period_value; //  周期，以秒计， 1(1S) 15(15S)  60(1F) 300(5F)
    int &period_idx = PeriodBase<N...>::unit->period_index; //  周期的 数组下标 [0-49]
    double *&oo = PeriodBase<N...>::unit->OO;
    double *&hh = PeriodBase<N...>::unit->HH;
    double *&ll = PeriodBase<N...>::unit->LL;
    double *&cc = PeriodBase<N...>::unit->CC;
    double *&vv = PeriodBase<N...>::unit->VV;

  public:
    std::vector<Section> sections_;

    // -----------new B----------
    // std::vector<Section> new_sections_;
    // -----------new E----------

  private:
    int ref_type_;
    int ref_flag_;

    bool is_set;

    bool plotflag_;
    int idx{0}; // vector的index

    Section cur_section_; // 用于恢复 防止在onBar中多次调用，

    // ------------- new B------------
    // bool is_new;
    // Section new_cur_section_; // 用于恢复 防止在onBar中多次调用，
    // Section new_nxt_section_;
    // ------------- new E-------------

  public:
    SectionsBase() {
        std::cout << " SectonsBase construction !! begin ! " << std::endl;
        PeriodBase<N...>::UnitCheck();

        plotflag_ = false;
        is_set = false;

        ref_type_ = INT_MIN; // 前一个section ID  INT_MIN 表示这个序列没有用过section
        ref_flag_ = INT_MIN; // 当前 section ID
        cur_section_.type = INT_MIN;
        cur_section_.flag = INT_MIN;
        cur_section_.B = INT_MIN;
        cur_section_.E = INT_MIN;
        cur_section_.len = INT_MIN;

        //------------- new B -----------
        // is_new = false;
        // new_cur_section_.type = INT_MIN;
        // new_cur_section_.flag = INT_MIN;
        // new_cur_section_.B = INT_MIN;
        // new_cur_section_.E = INT_MIN;
        // new_cur_section_.len = INT_MIN;

        // new_nxt_section_.type = INT_MIN;
        // new_nxt_section_.flag = INT_MIN;
        // new_nxt_section_.B = INT_MIN;
        // new_nxt_section_.E = INT_MIN;
        // new_nxt_section_.len = INT_MIN;
        //-------------- new E ----------

        idx = -1;

        PeriodBase<N...>::func_signal_end->Connect(this, &SectionsBase<N...>::_update);
        std::cout << " SectonsBase construction !! end !  " << std::endl;
    }

    ~SectionsBase() {
        sections_.clear();
        sections_.shrink_to_fit();
    }

  public:
    // set_section() 是幂等的，在同一个切片中，可以多次执行，结果相同。

    // 在同一onbar中，可以多次执行 set_section
    //  type :      5     |  5   =   6   =  6   =  700  =  6   =   5   = 5   = MIN   = MIN =  5   |
    //  flag :      100   | 100  =  MAX  = 105  =  MAX  = MAX  =  100  = 109 = MIN   = MIN = 100  |
    // set_flag:                    105                           109           99
    // 1. 设置了type后，flag要重设置。
    // 2. 如果 type 和 前一个bar相同，则flag与前一个flag相同，除非重新设置flag
    // 3. 在同一个onbar中，当 type 一直变化时，每次变化会导致flag清除，清除的方式是：新type的flag为 INT_MIN，type和前一个onbar一样时，flag也和前一个flag一样。
    // 4. 当在一个onbar中，type经过一些变化，稳定后，要重设置flag，否则，会因为上面第3条规则，导致flag异常。

    // 2020-12-18 在onbar内的小循环。可以多次调用 set_section()。如果发现type又给设置回来了，和ref_type一样了，那就要将flag也设置回去。
    // 如果type一直设置为新的type，则flag = INT_MIN。
    void set_section(int type) {
        is_set = true;
        if (cur_section_.type != type) { // type有变化才更新 cur_section_;
            cur_section_.type = type;
            if (type == ref_type_) { // 如果 type 和 前一个onbar的type相同，则flag 要改回。// 改回以前的flag !  在 seg_section 中，可以重设这个值。
                cur_section_.flag = ref_flag_;
            } else { //  其它所有type的更改，都将flag初始化为 INT_MIN 。
                cur_section_.flag = INT_MIN;
            }
        }
    }

    // --------------- new  B---------------- todo ----------------------------------
    // void new_set_section(int type) {
    //     if (type = !INT_MIN) { //
    //         is_new = true;
    //         if (new_cur_section_.type == type) { // to E
    //             recover_nxt_section();
    //         } else { //  to C'  or  C
    //             set_nxt_section(type);
    //         }

    //     } else { //  to A or B
    //         is_new = false;
    //         recover_nxt_section();
    //     }
    // }

    // void inline recover_nxt_section() {
    //     if (new_nxt_section_.type != INT_MIN) {
    //         new_cur_section_.type = INT_MIN;
    //         new_cur_section_.flag = INT_MIN;
    //         // new_cur_section_.B = INT_MIN;
    //         // new_cur_section_.E = INT_MIN;
    //         // new_cur_section_.len = INT_MIN;
    //     }
    // }

    // void inline recover_cur_section() {
    //     if (new_cur_section_.type != INT_MIN) {
    //         new_cur_section_.type = INT_MIN;
    //         new_cur_section_.flag = INT_MIN;
    //         new_cur_section_.B = INT_MIN;
    //         new_cur_section_.E = INT_MIN;
    //         new_cur_section_.len = INT_MIN;
    //     }
    // }
    // void inline set_nxt_section(int type) {
    //     new_nxt_section_.type = type;
    //     // new_nxt_section_.B = this->x;
    //     // new_nxt_section_.E = this->x;
    //     // new_nxt_section_.len = 1;
    //     new_nxt_section_.flag = INT_MIN;
    // }
    // --------------- new E ---------------- todo ----------------------------------

  private:
    // --------------- new  B ---------------- todo ----------------------------------
    // inline void _new_update() {
    //     if (new_cur_section_.type == new_nxt_section_.type) // is INT_MIN
    //     {
    //         return; // A - A
    //     } else {
    //         if (new_nxt_section_.type != INT_MIN) {
    //             if (new_cur_section_.type != INT_MIN) { // C'  ==> close + push;
    //                 new_sections_[idx].E = this->x - 1; // close
    //             } else {
    //                 //  C ==> push
    //             }
    //             new_cur_section_.type = new_nxt_section_.type;
    //             new_cur_section_.flag = new_nxt_section_.flag;
    //             new_cur_section_.B = this->x;
    //             new_cur_section_.E = INT_MIN;
    //             new_cur_section_.len = 1;
    //             new_sections_.push_back(new_cur_section_);
    //             idx++;
    //             recover_nxt_section();
    //         } else {
    //             if (is_new) { // E to B
    //                 // new_cur_section_.E = this->x;
    //                 // new_cur_section_.len += 1;
    //                 new_sections_[idx].len += 1;
    //                 new_sections_[idx].flag = new_cur_section_.flag;
    //             } else { // B to A
    //                 recover_cur_section();
    //             }
    //         }
    //         is_new = false;
    //     }
    // }
    // --------------- new  E ---------------- todo ----------------------------------

    // 2020-12-18 多个不同的onbar执行，_update()和set_section() 一起形成一个大的循环。
    inline void _update() { // 这个方法是在onbar结束后进行的，但在send之前调用。
        if (is_set == false) {
            if (cur_section_.type == INT_MIN) {
                return;
            } else {
                cur_section_.type = INT_MIN;
                cur_section_.flag = INT_MIN;
            }
        }
        if (cur_section_.type != ref_type_) {
            // if (idx >= 0) { // 最后才更新长度和结束 .E   // 改成这个判断 idx >= 0 , 可以记录 type=INT_MIN.  //不记录 ref_type_ != INT_MIN
            if (ref_type_ != INT_MIN) { //  不记录默认段 ref_type_ != INT_MIN 。 如果前一个section不是INT_MIN, 就完成前一个section收尾。
                sections_[idx].E = this->x - 1;
                sections_[idx].len = this->x - sections_[idx].B;
            }
            if (cur_section_.type != INT_MIN) { // 去掉这个判断，就会记录 type=INT_MIN. 如果当前section不是INT_MIN，就新push一个section。
                cur_section_.B = this->x;
                cur_section_.E = INT_MIN;
                sections_.push_back(cur_section_); // todo 根据 type，push到不同的vector。 循环数组。
                idx++;
            }
            ref_type_ = cur_section_.type;
            ref_flag_ = cur_section_.flag;
        } else {
            if (ref_flag_ != cur_section_.flag) {
                sections_[idx].flag = cur_section_.flag;
                ref_flag_ = cur_section_.flag;
            }
        }
        is_set = false;
    }

    // 下面为不记录默认section的写法。 下面 【】 三处修改！！
    //  同时在 base.cpp中，要改上传方式为：  if (sections->back().E == INT_MIN)
    // inline void _update() { // 这个方法是在onbar结束后进行的，但在send之前调用。
    //     if (is_set == false) {
    //         if (cur_section_.type == INT_MIN) {
    //             return;
    //         } else {
    //             cur_section_.type = INT_MIN;
    //             cur_section_.flag = INT_MIN;
    //         }
    //     }
    //     if (cur_section_.type != ref_type_) {
    //  【】   if (ref_type_ != INT_MIN) { // 最后才更新长度和结束 .E   // 改成这个判断 idx >= 0 , 可以记录 type=INT_MIN.  // ref_type_ != INT_MIN
    //             sections_[idx].E = this->x - 1;
    //             sections_[idx].len = this->x - sections_[idx].B;
    //         }
    //  【】   if (cur_section_.type != INT_MIN) { // 去掉这个判断，就会记录 type=INT_MIN.
    //             cur_section_.B = this->x;
    //             cur_section_.E = INT_MIN;
    //             sections_.push_back(cur_section_);
    //             idx++;
    //             ref_type_ = cur_section_.type;
    //             ref_flag_ = cur_section_.flag;
    //  【】   }
    //     } else {
    //         if (ref_flag_ != cur_section_.flag) {  // 如果不记录默认type的话，不能出现修改flag的情况，否则会修改前一个section的flag。
    //             sections_[idx].flag = cur_section_.flag;
    //             ref_flag_ = cur_section_.flag;
    //         }
    //     }
    //     is_set = false;
    // }

  public:
    int cur_section() { return is_set ? cur_section_.type : INT_MIN; };
    int ref_section() {
        return 0; // todo!
    };

    // ------------------------------------------------------------------------------------
    inline bool is_section_begin() { return (cur_section_.type != ref_type_); }
    inline bool is_section_continue() { return (cur_section_.type == ref_type_); }
    inline bool is_section_end() { return (cur_section_.type != ref_type_); }

    int size() { return sections_.size(); }

    // -------------------------- begin -----------标志-------------------------------------------------------
    // todo need to be tested !!
    void set_section_flag(int flag) {
        if (!is_set) { // 不能在没有设置section的情况设置flag。   // std::cout << " set_section() first !" << std::endl;
            return;
        }
        cur_section_.flag = cur_section_.type == INT_MIN ? INT_MIN : flag;
    }
    int cur_section_flag() {
        if (!is_set) { // 不能在没有设置section的情况设置flag。// std::cout << " set_section() first !" << std::endl;
            return INT_MIN;
        }
        return cur_section_.type == INT_MIN ? INT_MIN : cur_section_.flag;
    }
    // -------------------------- section 信息 --------------------------------------------------------------
    // tested ok 2020-12-21
    int cur_section_len() {
        if (!is_set) { // 不能在没有设置section的情况设置flag。
            return INT_MIN;
        }
        if (cur_section_.type == ref_type_) {
            return ref_type_ == INT_MIN ? INT_MIN : this->x - sections_[idx].B + 1;
        } else {
            return cur_section_.type == INT_MIN ? INT_MIN : 1;
        }
    }
    // tested ok 2020-12-21
    int cur_section_begin() {
        if (!is_set) { // 不能在没有设置section的情况设置flag。
            return INT_MIN;
        }
        if (cur_section_.type == ref_type_) {
            return ref_type_ == INT_MIN ? INT_MIN : sections_[idx].B;
        } else {
            return cur_section_.type == INT_MIN ? INT_MIN : this->x;
        }
    }
    // -------------------------- mark end ------------------------------------------------------------------

  public:
    virtual void plot(std::string name, int color) {
        if (plotflag_ == false) {
            std::tuple<std::string, std::vector<Section> *, int> temp = std::make_tuple(name, &sections_, color);
            this->unit->sectionslist_output.push_back(temp);
            plotflag_ = true;
        }
    }

}; // end SectionsBase<>

// #################### BoolBase #####################################################################
// BoolBase 不存储序列数据
// BoolBase 主要的功能是 重载bool运算。
template <int... N> class BoolBase : public SectionsBase<N...> {
    // template <int... M> friend class StopsegsList; // 让StopsegsList 可以访问 下面的 私有成员
    // template <int... M> friend class BoolSerial;
    // template <int... M> friend class PointsList;

  public:
    bool value_;

  public:
    BoolBase() {
        std::cout << "B:constructor() !!   BoolBase" << std::endl;

        value_ = false;

        PeriodBase<N...>::UnitCheck();
        std::cout << "E:constructor() !! BoolBase " << std::endl;
    }

    BoolBase(BoolBase<N...> &p) = delete;

    // 适用于 if( obj ) 这种判断形式
    operator bool() const { return value_; }

    // 重载等号 【一】 S1 = true;
    BoolBase &operator=(bool b) {
        value_ = b;
        return *this;
    }

    // 重载等号 【二】 S1 = S2;
    // 因为序列化操作，是每个切片都会执行，所以只是赋值当前index的值。不会整个序列copy一遍。
    BoolBase &operator=(const BoolBase &p) {
        value_ = p.value_;
        return *this;
    }

    friend inline bool operator&&(const BoolBase &a, bool b) { return b && a.value_; }
    friend inline bool operator&&(bool b, const BoolBase &a) { return b && a.value_; }

    friend inline bool operator||(const BoolBase &a, bool b) { return b || a.value_; }
    friend inline bool operator||(bool b, const BoolBase &a) { return b || a.value_; }

    friend inline bool operator&&(const BoolBase &a, const BoolBase &b) { return a.value_ && b.value_; }
    friend inline bool operator||(const BoolBase &a, const BoolBase &b) { return a.value_ || b.value_; }

    friend inline bool operator!(const BoolBase &a) { return !a.value_; }

    friend inline bool operator==(const BoolBase &a, const BoolBase &b) { return (a.value_ == b.value_); }
    friend inline bool operator==(bool a, const BoolBase &b) { return (a == b.value_); }
    friend inline bool operator==(const BoolBase &a, bool b) { return (a.value_ == b); }

    friend inline bool operator!=(const BoolBase &a, const BoolBase &b) { return (a.value_ != b.value_); }
    friend inline bool operator!=(bool a, const BoolBase &b) { return (a != b.value_); }
    friend inline bool operator!=(const BoolBase &a, bool b) { return (a.value_ != b); }

    // friend inline bool operator!(bool b) { return !b }
    // =====================================================================
    int get_ref(int x) { return -1; }

    int get_num_in(int x) { return 0; }

    int get_num_between(int b, int e) { return 0; }

    // = delete;
    ~BoolBase() { std::cout << "BoolBase 析构！！！！" << std::endl; }
};

// #### BoolSerial #########################################################################################
//  存储序列数据
template <int... N> class BoolSerial : public BoolBase<N...> {
    template <int... M> friend class StopsegsList;
    template <int... M> friend class BoolsegsList;

  public:
    bool *data;
    // 构造函数继承、等号运算符继承
    // using BoolBase<N...>::BoolBase;

    // 必须要加这一行
    // using BoolBase<N...>::operator=;

  private:
    bool plot_flag_ = false; // 用于表示是否要将这个序列数据 传给前端进行显示。
    int mark_;               // 用于记录前一次index的值 (在同一次onbar中，多次赋值时，只记录一次)

  public:
    BoolSerial() {
        std::cout << "B:constructor() !! BoolSerial  " << std::endl;
        this->value_ = false;
        this->plot_flag_ = false;

        PeriodBase<N...>::UnitCheck();
        data = new bool[this->unit->ohlcv_len];
        for (int i = 0; i < this->unit->ohlcv_len; i++) {
            data[i] = false;
        }

        PeriodBase<N...>::func_signal_end->Connect(this, &BoolSerial<N...>::_update);
        std::cout << "E:constructor() !! BoolSerial " << std::endl;
    };

    // 不提供这个，否则会一直重新分配？ // 不会，一个对象只会构造一次
    BoolSerial(bool b) {
        std::cout << "B: BoolSerial(bool)  constructor" << std::endl;
        this->plot_flag_ = false;

        PeriodBase<N...>::UnitCheck();
        // if (this->data == nullptr) {
        data = new bool[this->unit->ohlcv_len];
        for (int i = 0; i < this->unit->ohlcv_len; i++) {
            data[i] = false;
        }
        // }
        data[this->x] = b;
        this->value_ = b;

        PeriodBase<N...>::func_signal_end->Connect(this, &BoolSerial<N...>::_update);
        std::cout << "E: BoolSerial (bool)  constructor" << std::endl;
    }

    BoolSerial &operator=(bool b) {
        data[this->x] = b;
        this->value_ = b;
        return *this;
    }

    // 重载等号 【二】 S1 = S2;
    // 因为序列化操作，是每个切片都会执行，所以只是赋值当前index的值。不会整个序列copy一遍。
    BoolSerial &operator=(const BoolSerial &p) {
        this->data[this->x] = p.value_;
        this->value_ = p.value_;
        return *this;
    }

    virtual bool ref(int x) {
        if (x >= 0 && x <= this->x) {
            return this->data[this->x - x];
        } else {
            //  std::cout << " ref(x): x超出范围！" << std::endl;
            return this->value_;
        }
    }

    virtual bool cur() { return this->value_; }

  public:
    void plot(std::string name, int color) {
        if (this->plot_flag_ == false) {
            // std::tuple<std::string, std::vector<BoolSeg> *, int> temp = std::make_tuple(name, &segments_, color);
            // this->unit->segmentslist_output.push_back(temp);
            this->plot_flag_ = true;
        }
    }

    ~BoolSerial() {
        if (this->data != nullptr) {
            std::cout << " ~BoolSerial  !!  ---------------------------?????????????? " << std::endl;
            delete[] this->data;
        }
    }

  private:
    // 向前复制数据
    inline void _update() {
        if (this->x >= this->repeat_x) {
            this->data[this->x - this->repeat_x] = this->data[this->x];
            this->data[this->x - this->repeat_x + 1] = this->data[this->x + 1]; // for  BoolsegsList and StopsegsList: _update()
        }
    }

}; // end  BoolSerial

// StopsegsList #########################################################################################
template <int... N> class StopsegsList : public BoolSerial<N...> {
  public:
    std::vector<BoolSeg> segments_;

  private:
    BoolSeg cur_segment_;

    bool ref_value_;
    bool cur_value_;
    int ref_flag_;
    int idx; // int idx = segments_.size() - 1; 表示 segments_ 的index.下标。

    bool is_used; // 记录这个序列是否被使用。
    int is_set;

  public:
    StopsegsList() {
        std::cout << " StopsegsList constructor begin !" << std::endl;

        is_used = false;

        ref_value_ = false;
        this->value_ = false;
        cur_value_ = false;

        ref_flag_ = INT_MIN;
        cur_segment_.flag = INT_MIN;

        cur_segment_.B = INT_MIN;
        cur_segment_.E = INT_MIN;
        cur_segment_.len = 1;

        idx = -1; // 在 set_segment 和 update中，用来判断是否第一次使用。

        PeriodBase<N...>::func_signal_end->Connect(this, &StopsegsList<N...>::_update); // 设置后置处理
        std::cout << " StopsegsList constructor end !" << std::endl;
    };

    // 重载等号 【一】
    StopsegsList &operator=(bool value) {
        set_segment(value, 0);
        return *this;
    }

    // 重载等号 【二】
    StopsegsList &operator=(const StopsegsList &p) {
        set_segment(p.value_, 0);
        return *this;
    }

  private:
    // 思路：在同一个onbar中，无论调用多少次set_segment，只要与前一次onbar不同，就将flag设置为INT_MIN。
    // 思路：只要值是前一次onbar的值相同，就将flag改为前一次onbar的flag。

    // set_segment是可以多次调用的。所以，在当前onbar中,形成一个 小循环。
    //  在当前onbar中循环，首先，this->value_是上一个onbar的值,然后改成set_segment()的值
    //  当下一次set_segment()到来时，它去比较上一次的this->value_是否有更改，没有就什么也不做。
    //  有更改就改，改完后，再看这个值是不是上一个onbar的值，是就恢复flag，不是就将flag设置成INT_MIN。
    //  注意this->data, this->value_是继承自 BoolSerial，cur() 和 ref() 是在 BoolSerial中定义的。
    void set_segment(bool b, int iset) {
        this->data[this->x] = b;
        this->value_ = b;
        is_set = iset;

        if (cur_value_ != b) {
            cur_value_ = b;                                            // 有改变，就改成当前 b
            cur_segment_.flag = b == ref_value_ ? ref_flag_ : INT_MIN; // 如果 b 和 前一个onbar的value相同，则flag 要改回以前的flag !
        }

        if (idx == -1) {
            ref_value_ = !cur_value_; // 第一次这两个值必须不一样，以保证在后置update时，push一个segment到vector中。
            is_used = true;
        }
    }

  private:
    // 思路： set_segment和update形成大循环 onbar内 + 和onbar后。。
    // 1. onbar内：set_segment() 修改 this->value_  , set_segflag() 修改 flag。
    // 2. onbar后：update来更新或产生新的segment。
    // 3. update 只有两种情况：和前值相比， 值发生变化，就update旧的，生成新的segment。
    // 4. 值没有发生变化：如果flag发生变化，就更新flag，否则什么也不做。
    inline void _update() { // 这个方法是在onbar结束后进行的，但在send之前调用。
        if (!is_used) {
            return;
        }
        // --------------------------------- begin -------------
        // 用户每次 给序列赋值时，会将is_set置为0。如果为1，表示这是第一次没有赋值，要置反。
        // 在onbar中如何调用了 set_segment(value, 0); 则 is_set 被置为0，表示onbar中有赋值操作，当is_set == 1时，意味着 onbar中没有调用。
        if (is_set == 1) {
            set_segment(!cur_value_, 1);
        }
        // is_set >1 表示后继仍没有给序列赋值。不需要再置反。
        if (is_set > 1) {
            this->data[this->x] = cur_value_;
            return;
        }
        // --------------------------------- end ---------------
        if (cur_value_ == ref_value_) {
            if (ref_flag_ != cur_segment_.flag) {
                segments_[idx].flag = cur_segment_.flag;
                ref_flag_ = cur_segment_.flag;
            }
        } else {
            if (idx >= 0) { // 每个段在最后结束时更新长度和结束点.E  如果小于0是第一次，还没有push，不能更新。
                segments_[idx].E = this->x - 1;
                segments_[idx].len = this->x - segments_[idx].B;
            }
            cur_segment_.B = this->x;
            // cur_segment_.E = INT_MIN;
            cur_segment_.value = cur_value_;
            segments_.push_back(cur_segment_);
            idx++;
            ref_value_ = cur_value_;
            ref_flag_ = cur_segment_.flag;
        }
        // --------------------------------- begin ------------
        // 下一下onbar，要置反。
        if (is_set == 0) { // 在 StopsegsList &operator=(bool value) 中调用 set_segment(value, 0); 改为了 0
            this->value_ = !this->value_;
            this->data[this->x + 1] = this->value_; // 重写 cur(),去掉这一句 !  todo 循环使用数组时，向前复制数据，不会复制 this->x+1 的数据，会出错。 todo !!!
        }
        // 只需要>1就不需要再++了。
        if (is_set <= 1) {
            is_set++;
        }
        // --------------------------------- end --------------
    }

  public:
    // 用于将某对象的数据传给前端显示，在base.cpp的sendTradingData()中会处理
    // 在unit中有一个vector: pointslist_output。
    // 每个对象在调用这个plot时，会传入自已的对象名、要前端显示的颜色及方式。【talib_define.h: #define PLOT(obj, aa) obj.plot(#obj, aa) 】
    // 这个plot会将本对象的 data指针放到这个vector中。
    void plot(std::string name, int color) {
        if (this->plot_flag_ == false) {
            SectionsBase<N...>::plot(name, color);
            std::tuple<std::string, std::vector<BoolSeg> *, int> temp = std::make_tuple(name, &segments_, color);
            this->unit->segmentslist_output.push_back(temp);
            this->plot_flag_ = true;
        }
    }

  public:
    ~StopsegsList() {
        segments_.clear();
        segments_.shrink_to_fit();
        std::cout << "StopsegsList 析构！！！！" << std::endl;
    }

  public:
    // inline bool is_begin() { return (this->value_ && !ref_value_); }  todo!!
    // inline bool is_continue() { return (this->value_ && ref_value_); }
    // inline bool is_end() { return (!this->value_ && ref_value_); }

    // int size() { return segments_.size(); }

    // -------------------------- begin -----------每个段 有 8 个标志位可供 使用 -----------------------------
    void set_segflag(int flag) {
        if (!is_used) {
            return;
        }
        cur_segment_.flag = is_set == 0 ? flag : INT_MIN;
    }
    int cur_segflag() { return is_set == 0 ? cur_segment_.flag : INT_MIN; }

    // -------------------------- mark end ------------------------------------------------------------------

    // segment的长度.
    int cur_seglen() {
        if (!is_used) {
            return INT_MIN;
        }
        return this->value_ == ref_value_ ? this->x - segments_[idx].B + 1 : 1;
    }
    // segment的起始index.
    int cur_segbegin() {
        if (!is_used) {
            return INT_MIN;
        }
        return this->value_ == ref_value_ ? segments_[idx].B : this->x;
    }
    int cur_segend() {
        if (!is_used) {
            return INT_MIN;
        }
        return this->x;
    }
    int cur_segvalue() { return this->cur(); } // todo ! cur() 要重写 override, 在update中不需要为 this->+1  赋值。
    // -------------------------- mark end ------------------------------------------------------------------

    // 在n个周期内，有多少个段， b=true时，计算 value_为ture的段， b=false时，计算 value_ 为false的段。
    // 例如，用 value_为true，表示MA5线上涨，false表示下跌。get_count(100,true) 表示在最近100个周期内 MA5上涨有多少个段。
    // get_count(100,false) 表示在最近100个周期内，MA5下跌有多少个段。
    // 如果 n 落在某个段上，这个段会计算在内。如下：
    //           4     5 6       7 8       9 10    11
    // ......... xxxxxxx ooooooooo xxxxxxxxx oooooooo
    //             2        3          4         5
    // -------------------- n -------- n ------ n -->

    int seg_count(bool b, int n) { // todo !!
        return 10;
    }

    // 在n个周期内，出现 true to false转变的次数  todo !!
    int totrue_count(int n) { return 0; }
    // 在n个周期内，出现 false to true转变的次数
    int tofalse_count(int n) { return 0; }

    // =================== test ok ================================================================
    // 最近一次由true to false时到现在的周期数。  todo : 没有测试
    int tofalse_last() { return 0; }

    // =================== test ok ================================================================
    // 最近一次由false to true时到现在的周期数。 从0开始计算， 例如： ref() = false, this->value_ = true, 则 ftot_last() = 0 ;
    int totrue_last() { //  todo : 没有测试
        return 0;
    }
    // =============================================================================================

    // todo 返回 引用 或 指针 ？
    BoolSeg segcur() { return this->segments_.back(); }

    //   todo 返回 引用 或 指针 ？  如果本段为false ， 则segref(true,1),为本段前一个value为true的段; segref(false,1),则为本false段前一个false段。
    BoolSeg segref(bool b, int n) {
        if (n <= idx) {
            return this->segments_[idx - n];
        } else {
            return cur_segment_;
        }
    }

    // 最近一次满足条件b, 当前除外
    // 上一次满足条件b 到现在的周期数。======================================================
    // 如果 b = x; 则：
    //  xxxxxxxxx: return 1 【一】
    //  xxxoooxxx: return 1 【一】
    //  xxxxoooxx: return 1 【一】
    //  xxxxxooox: return 4 【二】.1
    //  oooooooox: return -1  【二】.2
    //  xxxxo: return 1 【三】
    //  xxxxoo: return 2 【三】
    //  xxxxooo: return 3 【三】.1
    //  ooooooo: return -1; 【三】.2
    int barslast(bool b) {
        if (b == this->value_) {
            // b = x
            // xxxxooooxxxxxxx
            if (this->ref() == b) { //  【一】
                return 1;
            } else { // xxxxoooox  【二】
                if (segments_.size() > 2) {
                    return this->x - (segments_[idx - 3].E);
                } else {
                    return -1;
                }
            }
        } else { // 【三】
            int rtn = this->x - this->segments_.back().B + 1;
            return rtn > this->x ? -1 : rtn;
        }
    }

}; // end StopsegsList<>

// BoolsegsList #########################################################################################
template <int... N> class BoolsegsList : public BoolSerial<N...> {
  public:
    std::vector<BoolSeg> segments_;

  private:
    BoolSeg cur_segment_;

    bool ref_value_;
    bool cur_value_;
    int ref_flag_;
    int idx; // int idx = segments_.size() - 1; 表示 segments_ 的index.下标。

    bool is_used; // 记录这个序列是否被使用。

  public:
    BoolsegsList() {
        std::cout << " BoolsegsList constructor begin !" << std::endl;

        is_used = false;

        ref_value_ = false;
        this->value_ = false;
        cur_value_ = false;

        ref_flag_ = INT_MIN;
        cur_segment_.flag = INT_MIN;

        cur_segment_.B = INT_MIN;
        cur_segment_.E = INT_MIN;
        cur_segment_.len = 1;

        idx = -1; // 在 set_segment 和 update中，用来判断是否第一次使用。

        PeriodBase<N...>::func_signal_end->Connect(this, &BoolsegsList<N...>::_update); // 设置后置处理
        std::cout << " BoolsegsList constructor end !" << std::endl;
    };

    // 重载等号 【一】
    BoolsegsList &operator=(bool value) {
        set_segment(value);
        return *this;
    }

    // 重载等号 【二】
    BoolsegsList &operator=(const BoolsegsList &p) {
        set_segment(p.value_);
        return *this;
    }

  private:
    // 思路：在同一个onbar中，无论调用多少次set_segment，只要与前一次onbar不同，就将flag设置为INT_MIN。
    // 思路：只要值是前一次onbar的值相同，就将flag改为前一次onbar的flag。

    // set_segment是可以多次调用的。所以，在当前onbar中,形成一个 小循环。
    //  在当前onbar中循环，首先，this->value_是上一个onbar的值,然后改成set_segment()的值
    //  当下一次set_segment()到来时，它去比较上一次的this->value_是否有更改，没有就什么也不做。
    //  有更改就改，改完后，再看这个值是不是上一个onbar的值，是就恢复flag，不是就将flag设置成INT_MIN。
    //  注意this->data, this->value_是继承自 BoolSerial，cur() 和 ref() 是在 BoolSerial中定义的。
    void set_segment(bool b) {
        this->data[this->x] = b;

        if (this->value_ != b) {
            this->value_ = b;                                          // 有改变，就改成当前 b
            cur_segment_.flag = b == ref_value_ ? ref_flag_ : INT_MIN; // 如果 b 和 前一个onbar的value相同，则flag 要改回以前的flag !
        }

        if (idx == -1) {
            ref_value_ = !this->value_; // 第一次这两个值必须不一样，以保证在后置update时，push一个segment到vector中。
            is_used = true;
        }
    }

  private:
    // 思路： set_segment和update形成大循环 onbar内 + 和onbar后。。
    // 1. onbar内：set_segment() 修改 this->value_  , set_segflag() 修改 flag。
    // 2. onbar后：update来更新或产生新的segment。
    // 3. update 只有两种情况：和前值相比， 值发生变化，就update旧的，生成新的segment。
    // 4. 值没有发生变化：如果flag发生变化，就更新flag，否则什么也不做。
    inline void _update() { // 这个方法是在onbar结束后进行的，但在send之前调用。
        if (!is_used) {
            return;
        }
        if (this->value_ == ref_value_) {
            if (ref_flag_ != cur_segment_.flag) {
                segments_[idx].flag = cur_segment_.flag;
                ref_flag_ = cur_segment_.flag;
            }
        } else {
            if (idx >= 0) { // 每个段在最后结束时更新长度和结束点.E  如果小于0是第一次，还没有push，不能更新。
                segments_[idx].E = this->x - 1;
                segments_[idx].len = this->x - segments_[idx].B;
            }
            cur_segment_.B = this->x;
            // cur_segment_.E = INT_MIN;
            cur_segment_.value = this->value_;
            segments_.push_back(cur_segment_);
            idx++;
            ref_value_ = this->value_;
            ref_flag_ = cur_segment_.flag;
        }
        this->data[this->x + 1] = this->value_; // 下一个自动延续   // 如果循环使用数组，这个这方有问题 todo!!
    }

  public:
    // 用于将某对象的数据传给前端显示，在base.cpp的sendTradingData()中会处理
    // 在unit中有一个vector: pointslist_output。
    // 每个对象在调用这个plot时，会传入自已的对象名、要前端显示的颜色及方式。【talib_define.h: #define PLOT(obj, aa) obj.plot(#obj, aa) 】
    // 这个plot会将本对象的 data指针放到这个vector中。
    void plot(std::string name, int color) {
        if (this->plot_flag_ == false) {
            SectionsBase<N...>::plot(name, color);
            std::tuple<std::string, std::vector<BoolSeg> *, int> temp = std::make_tuple(name, &segments_, color);
            this->unit->segmentslist_output.push_back(temp);
            this->plot_flag_ = true;
        }
    }

  public:
    ~BoolsegsList() {
        segments_.clear();
        segments_.shrink_to_fit();
        std::cout << "BoolsegsList 析构！！！！" << std::endl;
    }

  public:
    // inline bool is_begin() { return (this->value_ && !ref_value_); }  todo!!
    // inline bool is_continue() { return (this->value_ && ref_value_); }
    // inline bool is_end() { return (!this->value_ && ref_value_); }

    // int size() { return segments_.size(); }

    // -------------------------- begin ----------- ----------------------------
    void set_segflag(int flag) {
        if (!is_used) {
            return;
        }
        cur_segment_.flag = flag;
    }
    int cur_segflag() { return cur_segment_.flag; }

    // -------------------------- mark end ------------------ --------------------

    // segment的长度.
    int cur_seglen() {
        if (!is_used) {
            return INT_MIN;
        }
        return this->value_ == ref_value_ ? this->x - segments_[idx].B + 1 : 1;
    }
    // segment的起始index.
    int cur_segbegin() {
        if (!is_used) {
            return INT_MIN;
        }
        return this->value_ == ref_value_ ? segments_[idx].B : this->x;
    }
    int cur_segend() {
        if (!is_used) {
            return INT_MIN;
        }
        return this->x;
    }
    int cur_segvalue() { return this->value_; }
    // -------------------------- mark end ------------------------------------------------------------------

    // 在n个周期内，有多少个段， b=true时，计算 value_为ture的段， b=false时，计算 value_ 为false的段。
    // 例如，用 value_为true，表示MA5线上涨，false表示下跌。get_count(100,true) 表示在最近100个周期内 MA5上涨有多少个段。
    // get_count(100,false) 表示在最近100个周期内，MA5下跌有多少个段。
    // 如果 n 落在某个段上，这个段会计算在内。如下：
    //           4     5 6       7 8       9 10    11
    // ......... xxxxxxx ooooooooo xxxxxxxxx oooooooo
    //             2        3          4         5
    // -------------------- n -------- n ------ n -->

    int seg_count(bool b, int n) { // todo !!
        return 10;
    }

    // 在n个周期内，出现 true to false转变的次数  todo !!
    int totrue_count(int n) { return 0; }
    // 在n个周期内，出现 false to true转变的次数
    int tofalse_count(int n) { return 0; }

    // =================== test ok ================================================================
    // 最近一次由true to false时到现在的周期数。  todo : 没有测试
    int tofalse_last() { return 0; }

    // =================== test ok ================================================================
    // 最近一次由false to true时到现在的周期数。 从0开始计算， 例如： ref() = false, this->value_ = true, 则 ftot_last() = 0 ;
    int totrue_last() { //  todo : 没有测试
        return 0;
    }
    // =============================================================================================

    // todo 返回 引用 或 指针 ？
    BoolSeg segcur() { return this->segments_.back(); }

    //   todo 返回 引用 或 指针 ？  如果本段为false ， 则segref(true,1),为本段前一个value为true的段; segref(false,1),则为本false段前一个false段。
    BoolSeg segref(bool b, int n) {
        if (n <= idx) {
            return this->segments_[idx - n];
        } else {
            return cur_segment_;
        }
    }

    // 最近一次满足条件b, 当前除外
    // 上一次满足条件b 到现在的周期数。======================================================
    // 如果 b = x; 则：
    //  xxxxxxxxx: return 1 【一】
    //  xxxoooxxx: return 1 【一】
    //  xxxxoooxx: return 1 【一】
    //  xxxxxooox: return 4 【二】.1
    //  oooooooox: return -1  【二】.2
    //  xxxxo: return 1 【三】
    //  xxxxoo: return 2 【三】
    //  xxxxooo: return 3 【三】.1
    //  ooooooo: return -1; 【三】.2
    int barslast(bool b) {
        if (b == this->value_) {
            // b = x
            // xxxxooooxxxxxxx
            if (this->ref() == b) { //  【一】
                return 1;
            } else { // xxxxoooox  【二】
                if (segments_.size() > 2) {
                    return this->x - (segments_[idx - 3].E);
                } else {
                    return -1;
                }
            }
        } else { // 【三】
            int rtn = this->x - this->segments_.back().B + 1;
            return rtn > this->x ? -1 : rtn;
        }
    }

}; // end BoolsegsList<>

// ##################### PointsList ###########################################################################
template <int... N> class PointsList : public BoolBase<N...> {
  public:
    std::vector<int> points_;

  private:
    bool plot_flag_ = false; // 用于表示是否要将这个序列数据 传给前端进行显示。
    int mark_;               // 用于记录前一次index的值 (在同一次onbar中，多次赋值时，只记录一次)

  public:
    PointsList() { this->mark_ = -1; }
    PointsList(PointsList<N...> &p) = delete;

    // 重载等号 【一】  针对  MM = true ;这种情况。
    PointsList &operator=(bool b) {
        modify_points(b);
        return *this;
    }

    // 重载等号 【二】  针对  MM = NN ; 这种情况
    PointsList &operator=(const PointsList &p) {
        modify_points(p.value_);
        return *this;
    }

    // = delete;
    ~PointsList() {
        points_.clear();
        points_.shrink_to_fit();
        std::cout << "PointsList 析构！！！！" << std::endl;
    }

  private:
    inline void modify_points(bool b) {
        this->value_ = b;
        if (this->value_ == true) {
            if (this->mark_ != this->unit->index) {
                points_.push_back(this->unit->index);
                this->mark_ = this->unit->index;
            }
        } else { // 在同一次onbar调用中，有可能存在多次赋值的情况，当第一次为true时，会记录，但第二次如果为false，则要把已经记录的pop出来。
            if (this->mark_ == this->unit->index) {
                points_.pop_back();
                this->mark_ = -1;
            }
            // 一般情况下在onBar中，应该只操作一次。
            // 在同一次onBar()中，多次赋值的情况处理。
            // 已经存进去的，要取出来。
        }
    }

  public:
    // 用于将某对象的数据传给前端显示，在base.cpp的sendTradingData()中会处理
    // 在unit中有一个vector: pointslist_output。
    // 每个对象在调用这个plot时，会传入自已的对象名、要前端显示的颜色及方式。【talib_define.h: #define PLOT(obj, aa) obj.plot(#obj, aa) 】
    // 这个plot会将本对象的 data指针放到这个vector中。
    void plot(std::string name, int color) {
        if (this->plot_flag_ == false) {
            std::tuple<std::string, std::vector<int> *, int> temp = std::make_tuple(name, &points_, color);
            this->unit->pointslist_output.push_back(temp);
            this->plot_flag_ = true;
        }
    }

}; // end LinkedList

// #########################################################################################
// template <int... N> class FutureSerial : public PeriodBase<N...> {
template <int... N> class FutureSerial : public SectionsBase<N...> {
    template <int... M> friend class Future;
    template <int... M> friend class Trader; // 让 trader 可以使用 plot_flag_

  public:
    double *data; // 为每个序列保存数据。在创造序列对象时，要初始化，并分配空间

  private:
    // 用于表示是否要将这个序列数据 传给前端进行显示。
    bool plot_flag_ = false;
    bool flag_ohlcv_ = false;

  public:
    // 参数为空， 默认为double，分配空间。

    FutureSerial() {
        std::cout << "B:constructor() !! FutureSerial" << std::endl;
        plot_flag_ = false;
        flag_ohlcv_ = false;
        PeriodBase<N...>::UnitCheck();
        this->data = new double[this->unit->ohlcv_len];
        for (int i = 0; i < this->unit->ohlcv_len; i++) {
            this->data[i] = NAN;
        }

        PeriodBase<N...>::func_signal_end->Connect(this, &FutureSerial<N...>::_update);
        std::cout << "E:constructor() !! FutureSerial" << std::endl;
    };

  private:
    // 这里的参数 bool x 是为了让 FutureSerial 不为data分类内存。
    // FutureSerial(bool x) {
    //     std::cout << "B: FutureSerial(bool)  constructor" << std::endl;
    //     plot_flag_ = false;
    //     flag_ohlcv_ = true;
    //     std::cout << "E: FutureSerial(bool)  constructor" << std::endl;
    // }

  public:
    // 参数为字符，付给OHLCV
    FutureSerial(char x) {
        std::cout << "B: FutureSerial(char)  constructor" << std::endl;
        plot_flag_ = false;
        flag_ohlcv_ = true;
        PeriodBase<N...>::UnitCheck();
        if (x == 'o' || x == 'O') {
            this->data = this->unit->OO;
        } else if (x == 'h' || x == 'H') {
            this->data = this->unit->HH;
        } else if (x == 'l' || x == 'L') {
            this->data = this->unit->LL;
        } else if (x == 'c' || x == 'C') {
            this->data = this->unit->CC;
        } else if (x == 'v' || x == 'V') {
            this->data = this->unit->VV;
            // todo  需要将 this->unit->VV 改成 int类型
            // this->idata = this->unit->VV;  // int 类型。
        } else {
            std::cout << " FutureSerial(char) input error !! input should be 'o','O','h','L','l','L','v','V' !\n";
            flag_ohlcv_ = false;
            exit(-1);
        }
        std::cout << "E: FutureSerial(char)  constructor" << std::endl;
    }

    // //  todo
    // // boo类型 单独出去
    // // int类型 也单独出去
    // FutureSerial(bool x) {
    //     std::cout << "B: FutureSerial(bool)  constructor" << std::endl;
    //     plot_flag_ = false;
    //     PeriodBase<N...>::UnitCheck();
    //     this->value = new bool[this->unit->ohlcv_len];
    //     this->value[this->x] = x;
    //     std::cout << " FutureSerial input error !! \n";
    //     std::cout << "E: FutureSerial(bool)  constructor" << std::endl;
    // }

    // 不提供这个，否则会一直重新分配？ // 不会，一个对象只会构造一次
    FutureSerial(double value) {
        std::cout << "B: FutureSerial(double)  constructor" << std::endl;
        plot_flag_ = false;
        flag_ohlcv_ = false;
        PeriodBase<N...>::UnitCheck();
        // if (this->data == nullptr) {
        this->data = new double[this->unit->ohlcv_len];
        for (int i = 0; i < this->unit->ohlcv_len; i++) {
            this->data[i] = NAN;
        }
        // }
        this->data[this->x] = value;

        PeriodBase<N...>::func_signal_end->Connect(this, &FutureSerial<N...>::_update);
        std::cout << "E: FutureSerial(double)  constructor" << std::endl;
    }

    //  构造函数
    //  支持： static FutureSerial<8, 9> dtta(3);
    //  支持： static FutureSerial<8, 9> dtta{3};
    FutureSerial(int value) {
        std::cout << "B: FutureSerial(int)  constructor" << std::endl;
        plot_flag_ = false;
        flag_ohlcv_ = false;
        PeriodBase<N...>::UnitCheck();
        // if (this->data == nullptr) {
        data = new double[this->unit->ohlcv_len];
        for (int i = 0; i < this->unit->ohlcv_len; i++) {
            data[i] = NAN;
        }
        // }
        // this->data[this->x] = (double)value;
        data[this->x] = static_cast<double>(value);

        PeriodBase<N...>::func_signal_end->Connect(this, &FutureSerial<N...>::_update);
        std::cout << "E: FutureSerial(int)  constructor" << std::endl;
    }

    // 重载等号 【一】  S1 = 3.14;
    FutureSerial &operator=(double x) {
        /// std::cout << "赋值 double\n";
        // is_onbar 暂时不需要。 is_onbar 作用是，凡是 通过=号赋值的 serial 表示是在 onBar中
        // 赋值的。 标记为 is_onbar。 其它的EMA要用这个serial做为参数使用时，只能在onbar中 执行一下
        // X2.ema();
        // 否则后台通过信号槽运行时X2.ema()时，这里的serial值还没有在onbar中运行，没有计算出来。
        // if (!is_onbar) is_onbar = true;
        data[this->x] = x;
        return *this;
    }

    // 重载等号 【二】 S1 = S2;
    // 因为序列化操作，是每个切片都会执行，所以只是赋值当前index的值。不会整个序列copy一遍。
    FutureSerial &operator=(const FutureSerial &p) {
        /// std::cout << "赋值 p\n";
        data[this->x] = p.data[this->x];
        return *this;
    }

    // 重载加号
    friend inline double operator+(const FutureSerial &p1, const FutureSerial &p2) {
        /// std::cout << "p1 + p2  " << std::endl;
        /// std::cout << "p1.x: " << p1.x << "  p2.x: " << p2.x << std::endl;
        return p1.data[p1.x] + p2.data[p2.x];
        // return p1.m_A + p2.m_A;
    }
    friend inline double operator+(double val, const FutureSerial &p) {
        /// std::cout << "double + p2  " << std::endl;
        return val + p.data[p.x];
    }
    friend inline double operator+(const FutureSerial &p, double val) {
        /// std::cout << "p2 + double  " << std::endl;
        return p.data[p.x] + val;
    }

    // 重载减法
    friend inline double operator-(const FutureSerial &p1, const FutureSerial &p2) {
        // std::cout << "p1 - p2  " << p1.x << "  " << p1.data[p1.x] << "  " <<
        // p2.data[p2.x] << std::endl; std::cout << "p1.x: " << p1.x
        // << "  p2.x: " << p2.x << std::endl;
        return p1.data[p1.x] - p2.data[p2.x];
        // return p1.m_A + p2.m_A;
    }
    friend inline double operator-(double val, const FutureSerial &p) {
        /// std::cout << "double - p2  " << std::endl;
        return val - p.data[p.x];
    }
    friend inline double operator-(const FutureSerial &p, double val) {
        /// std::cout << "p2 - double  " << std::endl;
        return p.data[p.x] - val;
    }

    // 重载乘法
    friend inline double operator*(const FutureSerial &p1, const FutureSerial &p2) {
        /// std::cout << "p1 x p2  " << std::endl;
        /// std::cout << "p1.x: " << p1.x << "  p2.x: " << p2.x << std::endl;
        return p1.data[p1.x] * p2.data[p2.x];
        // return p1.m_A + p2.m_A;
    }
    friend inline double operator*(double val, const FutureSerial &p) {
        /// std::cout << "double x p2  " << std::endl;
        return val * p.data[p.x];
    }
    friend inline double operator*(const FutureSerial &p, double val) {
        /// std::cout << "p2 x double  " << std::endl;
        return p.data[p.x] * val;
    }

    // 重载除法
    friend inline double operator/(const FutureSerial &p1, const FutureSerial &p2) {
        /// std::cout << "p1 / p2  " << std::endl;
        /// std::cout << "p1.x: " << p1.x << "  p2.x: " << p2.x << std::endl;
        return p1.data[p1.x] / p2.data[p2.x];
        // return p1.m_A + p2.m_A;
    }
    friend inline double operator/(double val, const FutureSerial &p) {
        /// std::cout << "double / p2  " << std::endl;
        return val / p.data[p.x];
    }
    friend inline double operator/(const FutureSerial &p, double val) {
        /// std::cout << "p2 / double  " << std::endl;
        return p.data[p.x] / val;
    }

    //  >=
    friend inline bool operator>=(const FutureSerial &p1, const FutureSerial &p2) {
        /// std::cout << "p1 >= p2  " << std::endl;
        /// std::cout << "p1.x: " << p1.x << "  p2.x: " << p2.x << std::endl;
        return p1.data[p1.x] >= p2.data[p2.x];
        // return p1.m_A + p2.m_A;
    }
    friend inline bool operator>=(double val, const FutureSerial &p) {
        /// std::cout << "double >= p2  " << std::endl;
        return val >= p.data[p.x];
    }
    friend inline bool operator>=(const FutureSerial &p, double val) {
        /// std::cout << "p1 >= double  " << std::endl;
        return p.data[p.x] >= val;
    }

    // <=
    friend inline bool operator<=(const FutureSerial &p1, const FutureSerial &p2) {
        /// std::cout << "p1 <= p2  " << std::endl;
        /// std::cout << "p1.x: " << p1.x << "  p2.x: " << p2.x << std::endl;
        return p1.data[p1.x] <= p2.data[p2.x];
    }
    friend inline bool operator<=(double val, const FutureSerial &p) {
        /// std::cout << "double <= p2  " << std::endl;
        return val <= p.data[p.x];
    }
    friend inline bool operator<=(const FutureSerial &p, double val) {
        /// std::cout << "p1 <= double  " << std::endl;
        return p.data[p.x] <= val;
    }

    //  >
    friend inline bool operator>(const FutureSerial &p1, const FutureSerial &p2) {
        /// std::cout << "p1 > p2  " << std::endl;
        /// std::cout << "p1.x: " << p1.x << "  p2.x: " << p2.x << std::endl;
        return p1.data[p1.x] > p2.data[p2.x];
    }
    friend inline bool operator>(double val, const FutureSerial &p) {
        /// std::cout << "double > p2  " << std::endl;
        return val > p.data[p.x];
    }
    friend inline bool operator>(const FutureSerial &p, double val) {
        /// std::cout << "p1 > double  " << std::endl;
        return p.data[p.x] > val;
    }

    // <
    friend inline bool operator<(const FutureSerial &p1, const FutureSerial &p2) {
        /// std::cout << "p1 < p2  " << std::endl;
        /// std::cout << "p1.x: " << p1.x << "  p2.x: " << p2.x << std::endl;
        return p1.data[p1.x] < p2.data[p2.x];
    }
    friend inline bool operator<(double val, const FutureSerial &p) {
        /// std::cout << "double < p2  " << std::endl;
        return val < p.data[p.x];
    }
    friend inline bool operator<(const FutureSerial &p, double val) {
        /// std::cout << "p1 < double  " << std::endl;
        return p.data[p.x] < val;
    }

    double ref(int x) {
        if (x >= 0 && x <= this->x) {
            return this->data[this->x - x];
        } else {
            // return NAN;
            // return 0; // 这里不能返回 NAN！
            return this->data[this->x]; // 返回当前值。 这样最合理。
        }
    }

    double cur() { return this->data[this->x]; }

    // 用于将某对象的数据传给前端显示，在base.cpp的sendTradingData()中会处理
    // 在unit中有一个vector: output。
    // 每个对象在调用这个plot时，会传入自已的对象名、要前端显示的颜色及方式。
    // 这个plot会将本对象的 data指针放到这个vector中。
    virtual void plot(std::string name, int color) override {
        if (plot_flag_ == false) {
            SectionsBase<N...>::plot(name, color);
            std::tuple<std::string, double *, int> temp = std::make_tuple(name, this->data, color);
            this->unit->output.push_back(temp);
            plot_flag_ = true;
        }
    }

  public:
    ~FutureSerial() {
        if (this->data != nullptr) {
            // std::cout << " ~FutureSerial !!  ---------------------------?????????????? " << std::endl;
            if (!flag_ohlcv_) {
                delete[] this->data;
            } else {
                // std::cout << " ~FutureSerial !!  -----------------------?????????????? is ohlcv, do not delete ! " << std::endl;
            }
        }
    }

  private:
    // 如果在本onbar中,没有对本序列做处理，则在后置处理中，将其设置为前一值。
    // 目前暂不处理，要求只要是序列，必须在每次onbar调用中，都要给此序列赋值。
    // 在后置处理中再给此序列赋值，只能对下一次onbar起作用，对本次onbar并不起作用，
    //  如果本次onbar中，此序列在赋值前，有其它地方使用这个序列，依然会出错。所以即使在update中处理了，对本次onbar也不起作用。
    // void _update() {
    //     if (!std::isnan(data[this->x])) {
    //         return;
    //     } else if (this->x > 0 && !std::isnan(data[this->x - 1])) {
    //         data[this->x] = data[this->x - 1];
    //     }
    // }

  private:
    // 向前复制数据。
    inline void _update() {
        if (this->x >= this->repeat_x) {
            data[this->x - this->repeat_x] = data[this->x];
        }
    }

}; // end FutureSerial<>

// ====================================================== future class =============================================================
template <int... N> class OhlcvSerial {
  public:
    FutureSerial<N...> O{'o'};
    FutureSerial<N...> H{'h'};
    FutureSerial<N...> L{'l'};
    FutureSerial<N...> C{'c'};
    FutureSerial<N...> V{'v'};

    FutureSerial<N...> o{'o'};
    FutureSerial<N...> h{'h'};
    FutureSerial<N...> l{'l'};
    FutureSerial<N...> c{'c'};
    FutureSerial<N...> v{'v'};
};

// ====================================================== future class =============================================================
// Future类，实际上是每个future的每个period有一个Future对象。这里的Future，应该改名为
// FuturePeriod更好。 Future是继承 PeriodBase<M,N> 这里<M,N>是实例化了 #define 5F 300 Future<M,N>(
// base* bb, "ru2303", 5F)

// 在main()里，要定义 这个策略是一个品种一个period，还是一个品种多个period，还是多个品种多个period.
// Future<> 表示只有一个品种，一个period 进行测试。
// Future<5>  Future<300> 表示只有一个品种，多个period
// Future<1,5> Future<2,10> 表示有多个品牌，多个preiod
template <int... N> class Future : public PeriodBase<N...> {
  public:
    Base *b;
    int future_index_; // M 策略 future 数组下标
    int period_index_; // N 策略 future period 下标

  public:
    /*
     Future(Base* base, std::string s, int period) {
         // 这里要做几件事情：
         // 【一】根据<M,N>计算出 它的号，可以根据初始化的顺序，直接采用 0,1,2,3,4,5......
         //  比如   <ru2305,5>  0
         //        <ru2306,10> 1
         //        <au2306,5>  2
         //        <au2307,15> 3
         // 【二】 把 OHLCV数组以及索引号（当前数组内容的长度）， 传给 Base ;
         // 【三】 把 function_list 传给Base ;
         //  完成以上事情后，Base在收到message时，会自动计算OHLCV，索引号+1，并放在相应的
     Future所需的地方。然后调用 func_list。

         this->b = base;
         // todo 这里要根据相应的<M,N> 到 i的应对关系 ，挂接到不同的  fun_list[i] 上去。
         // 后面的执行只能是 fun_list[i]0]();
         this->b->fun_list[0] = this->future_fun_list;
         // todo 这里为什么不能& sig ?
         // this->b->Update[0] = &this->sig;

         // 把Future 强塞给 b->bmap里了。
         std::pair<std::vector<int>, void*> kkk = {{N...}, (void*)this};
         this->b->bmap.insert(kkk);
         // b->unit_array[0] = &this->unit;
         std::cout << " befffffffffff !----------------------------------------" << std::endl;
         // todo m n M N

         init(base);

         if constexpr (0 == sizeof...(N)) {
             std::cout << " no input in template <> !!  " << std::endl;
         } else if constexpr (1 == sizeof...(N)) {
             std::cout << " one input in template <> !!  " << std::endl;
             int tt = getOne<N...>();
             std::cout << tt << "   hhhhhhhhhhhhh -----one ------" << std::endl;

         } else if constexpr (2 == sizeof...(N)) {
             std::cout << " two input in template <> !!  " << std::endl;
             int first = getFirst<N...>();
             int second = getSecond<N...>();
             std::cout << tt << "   hhhhhhhhhhhhh --- two --------" << std::endl;
         } else {
             std::cout << "M N 参数错误" << std::endl;
         }
     }
     */
    template <int N1> int getOne() { return N1; };
    template <int M1, int N1> int getFirst() { return M1; }
    template <int M1, int N1> int getSecond() { return N1; }

    // --- https://blog.tartanllama.xyz/if-constexpr/
    // With if constexpr
    // /*
    // template <int N1, int N2, int... Ns>
    // int getone() {
    //     return N2;
    // }
    // */

    // 下面的构造函数是针对单个  static Future<8, period_1F> x(&bb); 对象进行初始化
    // 在base对象中，有多个 Unit(OHLCV)，在这里Future 初始化时，要找到对应的那一个Unit.
    Future(Base *base) {
        if (nullptr == base) {
            std::cout << " Base has not init yet! " << std::endl;
            exit(-1);
        }

        b = base;

        if constexpr (0 == sizeof...(N)) {
            std::cout << " Future<> constructor !\n";
            // 形式：【Future<> fu(&base) ;】
            // 使用第0个 future： this->future_index_ = 0;
            // period的下标，从0到50(PeriodNum),使用第1个被初始化的period下标: this->period_index_ =
            // i;
            this->future_index_ = 0;
            int i = 0;
            for (i = 0; i < PeriodNum; i++) {
                if (base->unit_array_[0][i] != nullptr) {
                    this->period_index_ = i;
                    break;
                }
            }
            if (i == PeriodNum && base->unit_array_[0][i] == nullptr) {
                std::cout << "future<M,N>  M(future_index): " << this->future_index_ << "  N(period_index): " << this->period_index_ << " not init! 没有初始化, 请先调用 Base::FutureInit() ! \n";
                exit(-1);
            }

        } else if constexpr (1 == sizeof...(N)) {
            // 形式：【 Future<N> : Future<period_1F> fu(&base) ; 】
            // 使用第0个 future： this->future_index_ = 0;
            // period下标，使用 <period_1F> 里的 period_1F
            std::cout << " Future<N> constructor !\n";
            this->future_index_ = 0;
            this->period_index_ = getOne<N...>();
            if (base->unit_array_[0][this->period_index_] == nullptr) {
                std::cout << "future<M,N>  M(future_index): " << this->future_index_ << "  N(period_index): " << this->period_index_ << " not init! 没有初始化, 请先调用 Base::FutureInit() ! \n";
                exit(-1);
            }

        } else if constexpr (2 == sizeof...(N)) {
            // 形式：【 Future<M,N> :  Future<2, period_1H> fu(&base) ; 】
            std::cout << " Future<M,N> constructor !\n";
            this->future_index_ = getFirst<N...>();
            this->period_index_ = getSecond<N...>();
            if (base->unit_array_[this->future_index_][this->period_index_] == nullptr) {
                std::cout << "future<M,N>  M(future_index): " << this->future_index_ << "  N(period_index): " << this->period_index_ << " not init! 没有初始化, 请先调用 Base::FutureInit() ! \n";
                exit(-1);
            }
        } else {
            std::cout << "Future<M,N> M N 参数错误" << std::endl;
        }

        std::cout << "future_index: " << this->future_index_ << "  period_index: " << this->period_index_ << std::endl;
        // 这里要根据相应的<M,N> 到 i的应对关系 ，挂接到不同的  fun_list[i] 上去。
        // 每个unit,即每个<M,N>有自己的信号槽,

        init();
    }

    ~Future() { std::cout << " Futrue release !! haha ------------------------------------------------" << std::endl; };

    void init() {
        std::cout << "init future !!" << std::endl;
        Future<N...>::unit = b->unit_array_[this->future_index_][this->period_index_];
        Future<N...>::index = &this->unit->index;
        Future<N...>::repeat_index = &this->unit->repeat_index;
        Future<N...>::period_value = &this->unit->period_value;
        Future<N...>::period_index = &this->unit->period_index;
        Future<N...>::func_signal = &this->unit->func_signal;
        Future<N...>::func_signal_end = &this->unit->func_signal_end;
        Future<N...>::OO = this->unit->OO;
        Future<N...>::HH = this->unit->HH;
        Future<N...>::LL = this->unit->LL;
        Future<N...>::CC = this->unit->CC;
        Future<N...>::VV = this->unit->VV;
        Future<N...>::out = this->unit->out;
        // Future<N...>::period_name = &b->unit_array_[0][0]->period_name;

        std::cout << Future<N...>::unit->ohlcv_len << std::endl;
        std::cout << Future<N...>::unit->index << std::endl;
        std::cout << *Future<N...>::index << std::endl;
    }

    //   public:
    //     Base *b;
    //     int future_index_; // M 策略 future 数组下标
    //     int period_index_; // N 策略 future period 下标

    // https://www.zhihu.com/question/329974084
    // FutureSerial<N...> o{true};
    // FutureSerial<N...> h{true};
    // FutureSerial<N...> l{true};
    // FutureSerial<N...> c{true};
    // FutureSerial<N...> v{true};

    // FutureSerial<N...> O{'o'};
    // FutureSerial<N...> H{'h'};
    // FutureSerial<N...> L{'l'};
    // FutureSerial<N...> C{'c'};
    // FutureSerial<N...> V{'v'};
};
} // namespace uBEE
#endif // UBEE_FUTURE_PERIOD_H
