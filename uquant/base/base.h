#ifndef UBEE_BASE_H
#define UBEE_BASE_H
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <uWS/uWS.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include <glog/logging.h>

#include "../base/move_only_function.h"
#include "../base/sig_slot.h"
#include "../base/yyjson.h"

namespace uBEE {
using lSignal::Connection;
using lSignal::Signal;
using lSignal::Slot;
using uWSclient = uWS::WebSocket<uWS::CLIENT>;
using uWSserver = uWS::WebSocket<uWS::SERVER>;

enum class FUNCTIONS {
    FUN_GET_TICK,
    FUN_GET_KBAR,
    FUN_GET_HISTORY_TICK,
    FUN_GET_HISTORY_KBAR,
};

struct FUN_GET_HISTORY_KBAR_PARA {
    int fun_id{1};
    char start_day[9];
    char start_time[9];
    char finish_day[9];
    char finish_time[9];
};

#define period_TK 0
#define period_1S 1
#define period_2S 2
#define period_3S 3
#define period_5S 4
#define period_10S 5
#define period_15S 6
#define period_20S 7
#define period_30S 8
#define period_1F 9
#define period_2F 10
#define period_3F 11
#define period_5F 12
#define period_10F 13
#define period_15F 14
#define period_20F 15
#define period_30F 16
#define period_1H 17
#define period_2H 18
#define period_3H 19
#define period_4H 20
#define period_5H 21
#define period_6H 22
#define period_8H 23
#define period_10H 24
#define period_12H 25
#define period_1D 26
#define period_1W 27
#define period_1M 28
#define period_1J 29
#define period_1Y 30

#define YES 1
#define NO -1
// std::vector<int> {index,是否要交易，period秒}
static const std::map<std::string, std::vector<int>> PeriodMap = {
    {"period_TK", {0, -1, 0}},       // 0 tick!!!
    {"period_1S", {1, -1, 1}},       // 1
    {"period_2S", {2, -1, 2}},       // 2
    {"period_3S", {3, -1, 3}},       // 3
    {"period_5S", {4, YES, 5}},      // 4
    {"period_10S", {5, -1, 10}},     // 5
    {"period_15S", {6, -1, 15}},     // 6
    {"period_20S", {7, -1, 20}},     // 7
    {"period_30S", {8, -1, 30}},     // 8
    {"period_1F", {9, YES, 60}},     // 9
    {"period_2F", {10, -1, 120}},    // 10
    {"period_3F", {11, -1, 180}},    // 11
    {"period_5F", {12, -1, 300}},    // 12
    {"period_10F", {13, -1, 600}},   // 13
    {"period_15F", {14, -1, 900}},   // 14
    {"period_20F", {15, -1, 1200}},  // 15
    {"period_30F", {16, -1, 1800}},  // 16
    {"period_1H", {17, -1, 3600}},   // 17
    {"period_2H", {18, -1, 7200}},   // 18
    {"period_3H", {19, -1, 10800}},  // 19
    {"period_4H", {20, -1, 14400}},  // 20
    {"period_5H", {21, -1, 18000}},  // 21
    {"period_6H", {22, -1, 21600}},  // 22
    {"period_8H", {23, -1, 28800}},  // 23
    {"period_10H", {24, -1, 36000}}, // 24
    {"period_12H", {25, -1, 43200}}, // 25
    {"period_1D", {26, -1, -1}},     // 26
    {"period_1W", {27, -1, -1}},     // 27
    {"period_1M", {28, -1, -1}},     // 28
    {"period_1J", {29, -1, -1}},     // 29
    {"period_1Y", {30, -1, -1}},     // 30
    //---------- for custom define 自定义周期---------------
    {"131_cu", {31, -1, -1}},   //
    {"132_cu", {32, -1, -1}},   //
    {"133_cu", {33, -1, -1}},   //
    {"134_cu", {34, -1, -1}},   //
    {"135_xp", {35, -1, 3456}}, //
    {"136_cu", {36, -1, -1}},   //
    {"137_cu", {37, -1, -1}},   //
    {"138_cu", {38, -1, -1}},   //
    {"139_cu", {49, -1, -1}},   //
    {"140_cu", {40, -1, -1}},   //
    {"141_cu", {41, -1, -1}},   //
    {"142_cu", {42, -1, -1}},   //
    {"143_cu", {43, -1, -1}},   //
    {"144_cu", {44, -1, -1}},   //
    {"145_cu", {45, -1, -1}},   //
    {"146_cu", {46, -1, -1}},   //
    {"147_cu", {47, -1, -1}},   //
    {"148_cu", {48, -1, -1}},   //
    {"149_cu", {49, -1, -1}},   // 不能超过50个周期！！ 在 base.h <struct Future> 中 写死了。
};

constexpr int KSIZE = 8000;
constexpr int REPEAT = 4100; // 要求 repeat > ksize/2 ; 同时， ksize - repeat 要比指标需要的数量要大。
constexpr int FutureNum = 50;
constexpr int PeriodNum = 50;

enum class Mode {
    BACK_TEST,  // 回测       // remote  : 数据从websocket来   local : 本地数据，文件或数据库
    REAL_CTP,   // CTP实盘    // remote  : 数据从websocket来   local : 本地CTP连接
    SIMULATION, // 模拟交易   // remote  : 数据从websocket来   local : 本地数据，文件或数据库
    CHOOSING    // 选股       // remote  : 数据从websocket来   local : 本地数据，文件或数据库
};

// trade_fun.h 中使用的有关交易的信息
typedef struct Order {
    int idx;          // 位置数组下标
    int type;         // buyopen, buyclose, sellopen, sellclose, cancel
    int mount;        // 交易数量
    int buyposition;  // 买多持仓，买多头寸
    int sellposition; // 卖空持仓，卖空头寸
} Order;

// future_period.h 中 SegmentsList类 使用的分段信息
typedef struct BoolSeg {
    bool value; // true or false;  // 2023-12-09 增加。 用于记录此段是上涨还是下跌
    int B;      // begin index;  开始index值
    int E;      // end index;  结束index值
    int len;    // 本 BoolSeg 长度
    int flag;   // 标识
                //   bool boolarray[8]; // 标识位
    //  int distance;
    // 距离前一个 BoolSeg的长度。 2023-12-09: 不用了，因为同时记录上涨段和下跌段，所以：距离前一个上涨段的长度，实际上是前面下跌段的长度
} BoolSeg;

typedef struct Section {
    int type; // 段的类型。由用户自已定义处理。 -1表示没有处理，用户不能用-1这个值。其它都可以。
    int B;    // begin index;  开始index值
    int E;    // end index;  结束index值
    int len;  // 本 BoolSeg 长度
    int flag; // 针对本section的标识

} Section;

typedef struct Unit {
    char instrumentID[81];
    char ActionDay[30];
    char Time[30];

    // 用于否是第一次获取数据，如果是断线连，则需要重新设定 start_day finish_day
    // start_time finish_time ....
    bool is_first_get{true};
    char start_day[9];
    char finish_day[9];
    char start_time[9];
    char finish_time[9];

    int ohlcv_len;
    int index;

    // 当index > repeat_index时，将数据向前复制。比如 ohlcv_len = 100000;
    // repeat_index = 90000; 当程序运行到 index =  repeat_index时，这个点的数据就会被复制到 index 0;
    // index = repeat_index+1的数据，被复制到 index 1;依此类推，当index = 99999时,数据被复制到 index 9999，下一个index从(ohlcv_len - repeat_index)开始。

    int repeat_index; // 当index > repeat_index时，将数据向前复制。
    int future_index; // Future<M,N> 的 M  => 数组下标
    int period_value; // 用秒计的period
    int period_index; // Future<M,N> 的 N  => 数组下标
    char period_name[16];
    double *OO;
    double *HH;
    double *LL;
    double *CC;
    double *VV;
    double *out; // 初始化时要和OHLCV一样分配置空间，用于talib计算时，做为出参。
                 // 由于 new_talib.h中的D_EMA()函数的调用方式是 FutureSeriod<8,4> x =
                 // D_EMA(K3,100); 这里的DEMA()返回值是double， 它没有办法使用 x序列的
                 // data[]作为 tallib中的 SEE_EMA()的 out[]入参。
                 // 所以需要在这里先申请一个double数组。
                 // 在onBar里的计算都是串行的，所以，所有的D_MA，D_EMA，D_KDJ可以用它。
                 // 没有并行计算的要求，所以整个 Future<8,4> 均使用这一个out

    // todo 按照 <M,N>对 来说的话，这里只需要一个 Signal<void()>就可以了，
    // 因为它可以连接所有与M这个合约N这个周期的所有 function。
    // 一个 sig 可以 connect 多个functions.
    // sig(); 这样调用，与之相联的所有functions都会执行一遍.
    // Signal<void()> future_fun_list[1];  // 这里初始化了50个 Signal<void()>，
    // 每个都可以connect 多个function。
    Signal<void()> func_signal;
    Signal<void()> func_signal_end;

    // 记录每个序列对象输出的data指针，用于FutureSerial plot()，让base.cpp 可以传到前端显示这些数据。
    // std::string 对象名
    // double * 表示 序列的data数组
    // int  表示color
    std::vector<std::tuple<std::string, double *, int>> output;                            // plot 记录序列是否要上传到web
    std::vector<std::tuple<std::string, std::vector<int> *, int>> pointslist_output;       // plot记录 诸如 cross(ma5,ma10) 这种信号
    std::vector<std::tuple<std::string, std::vector<BoolSeg> *, int>> segmentslist_output; // segments 记录
    std::vector<std::tuple<std::string, std::vector<Section> *, int>> sectionslist_output; // sections 记录  sections是用来记录某个序列根据某些条件形成的分段。
    // 比如MACD指标上涨下跌，在0轴之上之下，共有4种类型的sections， 可以 用这个序列 S.set_section(1); S.set_section(2);... 来记录它。
    std::vector<std::tuple<std::string, std::vector<Order> *, int>> orderslist_output; // plot记录 交易记录

} Unit;

// 每个策略进程会有一个Base对象
class Base {
  public:
    Mode mode_{Mode::BACK_TEST};  // 方式
    bool remote_{false};          // 是从本地还是远端取数据，如果是从远端取，则需要启用 mainHub
    bool forweb_{false};          // 是否要将执行过程中的数据送到web端进行显示。 // 在策略主程序中赋值 bb.forweb_= true;
    std::string kbarfile_;        // 本地kbar文件 要初始化
    uWS::Hub *main_hub_{nullptr}; // (mainHub) callback for onTick() onBars() ...
    uWSclient *dat_ws_{nullptr};  // (mainHub) client to dat server
    uWSclient *web_ws_{nullptr};  // (mainHub) client to web server
    // uWSclient* ws_[4];             // (mainHub) client to data server
    // uWs::WebSocket<uWS::CLIENT>* ws[4];     // (mainHub) client to data server
    std::vector<uWSclient *> ws_; // (mainHub) client to data server

    Unit *unit_array_[FutureNum][PeriodNum];             // index by future_period_index_
    std::map<std::string, std::vector<int>> future_map_; // futureInit() !

    /*
    //   vector 第一个值是序号，每个品种分配一个，不能重复，从0开始， 在后面的
    Future<序号，周期> 时必须使用这个序号。

    //   std::map<std::string, std::vector<int>> fuMap;
    //   fuMap["xu1801"] = {0, period_TK, period_1S, period_1F, period_2H};
    //   fuMap["tu1801"] = {1, period_TK, period_30F, period_2H};
    //   fuMap["ru1805"] = {2, period_1S, period_5F, period_2H};
    //   fuMap["ru1809"] = {3, period_TK, period_15S, period_1F, period_5F};
    //   fuMap["xu1807"] = {4, period_TK, period_1S, period_1F, period_2H};
    //   fuMap["zz1805"] = {5, period_TK, period_1S, period_1F, period_2H};
    //   fuMap["ag1912"] = {6, period_TK, period_1S, period_1F, period_2H};
    */

    Base();
    ~Base();

    // int FutureInit(const std::map<std::string, std::vector<int>>&, bool);
    int FutureInit(const std::string &);
    // 请在onInit()里调用 GetData() !
    void onInit(MoveOnlyFunction<void()> handler);
    void onBars(MoveOnlyFunction<void(int)> handler);
    void onMessages();
    void sendTradingData();

    // 所有的功能都用这个函数来调用，para 是一个json字串
    void GetData(FUNCTIONS x, const char *para);

    void Run();

  public:
    MoveOnlyFunction<void()> onInitHandler = nullptr;
    MoveOnlyFunction<void(int)> onBarsHandler = nullptr;

  private:
    void MainHubInit();
    void MainHubConnection();
    void SaveWebSock(uWSclient *ws, uWS::HttpRequest req);
    void MainHubOnMessageInit();
    void MainHubOnConnectInit();
    void MainHubOnDisconnInit();
    void MainHubOnErrorInit();
};

// static Base bb;

// void Init();
// void onInit(std::function<void()> handler);
// void onInit(MoveOnlyFunction<void()> handler);
// void onBars(std::function<void(int)> handler);
// void Run();

} // namespace uBEE

#endif