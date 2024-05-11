#ifndef UBEE_BARS_H
#define UBEE_BARS_H

#include "ctp/ThostFtdcMdApi.h"
// #include "Psqlpool.h"
// #include "PsqlFunc.h"
// #include <uWS/uWS.h>

#include <condition_variable>
#include <functional>
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "base/see_talib.h"

// #include "global.h"

namespace uBEE {
// 交易品种 对应 交易时间类型
static const std::map<std::string, int> M_FuTime = {
    //  czce 郑商所 -------801 4位------------
    {"AP", 2}, // 苹果
    {"CF", 2}, // 棉花
    {"CY", 2}, // 棉纱
    {"FG", 2}, // 玻璃
    {"JR", 0}, // 粳稻
    {"LR", 0}, // 晚籼稻
    {"MA", 2}, // 甲醇N
    {"OI", 2}, // 菜籽油
    {"PM", 0}, // 普麦
    {"RI", 0}, // 早籼稻
    {"RM", 2}, // 菜籽粕
    {"RS", 0}, // 油菜籽
    {"SF", 0}, // 硅铁
    {"SM", 0}, // 锰硅
    {"SR", 2}, // 白糖
    {"TA", 2}, // PTA
    {"WH", 0}, // 强麦
    {"ZC", 2}, // 新动力煤
    {"PF", 2}, //  短纤  todo
    {"SA", 2}, //  纯碱  todo
    {"UR", 2}, //  尿素  todo 2 or 3?
    {"CJ", 2}, //  红枣  todo 2 or 3?
    // {"TC",  2   }, // 动力煤
    // {"ME",  0   }, // 甲醇
    //  dce 大商所 --- 16 --- 20180109 ----------- 1801
    //  4---------------------------------------------
    {"a", 2},  //   豆一
    {"b", 2},  //   豆二
    {"bb", 0}, //   胶合板
    {"c", 0},  //   玉米
    {"cs", 0}, //   玉米淀粉
    {"fb", 0}, //   纤维板
    {"i", 2},  //   铁矿石
    {"j", 2},  //   焦炭
    {"jd", 0}, //   鸡蛋
    {"jm", 2}, //   焦煤
    {"l", 0},  //   聚乙烯
    {"m", 2},  //   豆粕
    {"p", 2},  //   棕榈油
    {"pp", 0}, //   聚丙烯
    {"v", 0},  //   聚氯乙烯
    {"y", 2},  //   豆油
    {"rr", 2}, //   粳米 todo
    // shfe  上期所--- 14 --- 20180109 -----------------------
    {"cu", 3}, //   铜
    {"bc", 3}, //   铜(BC)  // todo
    {"al", 3}, //   铝
    {"zn", 3}, //   锌
    {"pb", 3}, //   铅
    {"ni", 3}, //   镍
    {"sn", 3}, //   锡
    {"au", 4}, //   黄金
    {"ag", 4}, //   银
    {"rb", 1}, //   螺纹钢
    {"wr", 0}, //   线材
    {"hc", 1}, //   热轧卷板
    {"fu", 2}, //   燃料油
    {"bu", 1}, //   石油沥青
    {"ru", 1}, //   天然橡胶
    // cffe 中金所 --- 5 --- 20180109 -------------------------
    {"IF", 5}, // 沪深300
    {"IC", 5}, // 中证500
    {"IH", 5}, // 上证50
    {"TF", 6}, // 国债5年期
    {"T", 6},  // 国债10年期

};

#define SAVE_ALL 1
#define SAVE_BAR 2
#define SAVE_TICK 3

#define SEND_BAR 4
#define SEND_ALL 5
#define SEND_TICK 6

#define SEND_SAVE_ALL 7
#define SEND_SAVE_BAR 8
#define SEND_SAVE_TICK 9

// #define T________  1

#define see_memzero(buf, n) (void)memset(buf, 0, n)
// #define SEE_NULL -2147483648
#define SEE_OK 0

#define BAR_SECOND 's'
#define BAR_MINUTE 'm'
#define BAR_HOUR 'h'
#define BAR_DAY 'D'
#define BAR_WEEK 'W'
#define BAR_MONTH 'M'
#define BAR_SEASON 'J'
#define BAR_YEAR 'Y'
#define BAR_TICKC 't'

#define FUTRUE_ID_LEN 81
#define SEE_SGM_NUM 50
#define SEE_HOUR_TYPE_NUM 10
// #define  TRADE_TIME         "../etc/tbl/see_trade_time"
// #define  FUTURE_DAYS        "../etc/tbl/see_future_days"
// #define  FUTURE_TIME        "../etc/tbl/see_future_time"

#define TICK struct CThostFtdcDepthMarketDataField
constexpr int TICK_LEN = sizeof(TICK);

/*
   注意：
    下面的定义，与数组下标是严格一致的。
    block->bar_block[0]  = block->bar_block[period_tick]
    block->bar_block[13]  = block->bar_block[period_10m]
    各种函数的 period 也用的是下面的定义。

*/

// period_index here
// period_value 是指 周期的数值，比如 5分钟的交易周期
// 【 period_5m = 12 , 其 period_index: 12数组下标， period_value: 300秒】
#define period_tick 0
#define period_1s 1
#define period_2s 2
#define period_3s 3
#define period_5s 4
#define period_10s 5
#define period_15s 6
#define period_20s 7
#define period_30s 8
#define period_1m 9
#define period_2m 10
#define period_3m 11
#define period_5m 12
#define period_10m 13
#define period_15m 14
#define period_20m 15
#define period_30m 16
#define period_1h 17
#define period_2h 18
#define period_3h 19
#define period_4h 20
#define period_5h 21
#define period_6h 22
#define period_8h 23
#define period_10h 24
#define period_12h 25
#define period_1D 26
#define period_1W 27
#define period_1M 28
#define period_1J 29
#define period_1Y 30

// 标准周期
//   0   1   2   3   4   5    6    7    8    9    10    11    12    13    14 15
//   16 0S  1S  2S  3S  5S  10S  15S  20S  30S  1F   2F    3F    5F    10F   15F
//   20F    30F 0,  1,  2,  3,  5,  10,  15,  20,  30,  60,  120,  180,  300,
//   600,  900,  1200,  1800 0S是tick。 17    18    19     20     21      22 23
//   24   25   26   27   28   29  30 1H    2H    3H     4H     5H      6H   8H
//   10   12   1D   1W   1M   1J  1Y 3600, 7200, 10800, 14400, 18000,  0,   0,
//   0,   0,   0,   0,   0,   0,  0

// 用户自定义 交易周期 不能超过20个 不能和已有的周期重复！
//                    31  32   33   34   35
// const int fr[5] = {19,14401,9900,350,6600};

// -- 前面加上 100 101 ... 是为了排序需要.
// M_FF是为 HubCtp
// HubSim根据tick生成kbar用的，如果不需要，可以将后面的值改为-1即可。
// 如果想要定义自己的级别，可以在后面的131_cu 添加，值以秒计.
// 日 周 月 季 年 todo!!
// 下面不为 -1的，表示要计算 kbar的 周期 下面这种做法，不太好？todo 改成配置文件?
static const std::map<std::string, int> M_FF = {
    {"100_T", 0},    // 0 tick!!!
    {"101_1S", 1},   // 1 1
    {"102_2S", -1},  // 2 2
    {"103_3S", -1},  // 3 3
    {"104_5S", 5},   // 4 5
    {"105_10S", -1}, // 5 10
    {"106_15S", -1}, // 6 15
    {"107_20S", -1}, // 7 20
    {"108_30S", -1}, // 8 30
    {"109_1F", 60},  // 9 60
    {"110_2F", -1},  // 10 120
    {"111_3F", -1},  // 11 180
    {"112_5F", 300}, // 12 300
    {"113_10F", -1}, // 13 600
    {"114_15F", -1}, // 14 900
    {"115_20F", -1}, // 15 1200
    {"116_30F", -1}, // 16 1800
    {"117_1H", -1},  // 17 3600
    {"118_2H", -1},  // 18 7200
    {"119_3H", -1},  // 19 10800
    {"120_4H", -1},  // 20 14400
    {"121_5H", -1},  // 21 18000
    {"122_6H", -1},  // 22 21600
    {"123_8H", -1},  // 23 28800
    {"124_10H", -1}, // 24 36000
    {"125_12H", -1}, // 25 43200
    {"126_1D", -1},  // 26
    {"127_1W", -1},  // 27
    {"128_1M", -1},  // 28
    {"129_1J", -1},  // 29
    {"130_1Y", -1},  // 30
    //---------- for custom define 自定义周期---------------
    {"131_cu", -1},   // 31
    {"132_cu", -1},   // 32
    {"133_cu", -1},   // 33
    {"134_cu", -1},   // 34
    {"135_xp", 3456}, // 35
    {"136_cu", -1},   // 36
    {"137_cu", -1},   // 37
    {"138_cu", -1},   // 38
    {"139_cu", -1},   // 39
    {"140_cu", -1},   // 40
    {"141_cu", -1},   // 41
    {"142_cu", -1},   // 42
    {"143_cu", -1},   // 43
    {"144_cu", -1},   // 44
    {"145_cu", -1},   // 45
    {"146_cu", -1},   // 46
    {"147_cu", -1},   // 47
    {"148_cu", -1},   // 48
    {"149_cu", -1},   // 49
    // 不能超过50个周期！！ 在 base.h <struct Future> 中 写死了。
};

#define SAME_SEG_8 8
#define SAME_SEG_9 9

#define SAME_NO_SEG_0 -1
#define SAME_NO_SEG_1 -1
#define SAME_NO_SEG_2 -2
#define SAME_NO_SEG_3 -3
#define SAME_NO_SEG_4 -4
#define SAME_NO_SEG_5 -5
#define SAME_NO_SEG_6 -6
#define SAME_NO_SEG_7 -7
#define SAME_NO_SEG_8 -8
#define SAME_NO_SEG_9 -9

#define SEE_MKT_OPEN 10000  /*  market openning */
#define SEE_MKT_CLOSE 10001 /*  market closed   */
#define SEE_SAME_SEG 10002
#define SEE_DIFF_SEG 10003
#define SEE_SAME_NO_SEG 10004
#define SEE_DIFF_NO_SEG 10005
#define SEE_SAME_KBAR 10006
#define SEE_DIFF_KBAR 10007

#define SEE_START_TICK 10008 // 开机后第一个交易时间段内的tick

#define UPDATE_B1                                                                                                      \
    b1->c = tick->LastPrice;                                                                                           \
    if (b1->h < tick->LastPrice) {                                                                                     \
        b1->h = tick->LastPrice;                                                                                       \
    }                                                                                                                  \
    if (b1->l > tick->LastPrice) {                                                                                     \
        b1->l = tick->LastPrice;                                                                                       \
    }                                                                                                                  \
    b1->vsum = tick->Volume;                                                                                           \
    b1->v = tick->Volume - b1->vold;
/*
#define NEW_B1         memcpy(b1->ActionDay,tick->ActionDay,9) ; \
                       memcpy(b1->TradingDay,tick->TradingDay,9) ; \
*/
#define NEW_B1                                                                                                         \
    b1->iX = period_index;                                                                                             \
    b1->period_value_ = future_block->pBarBlock[period_index]->period_value_;                                          \
    b1->o = tick->LastPrice;                                                                                           \
    b1->h = tick->LastPrice;                                                                                           \
    b1->l = tick->LastPrice;                                                                                           \
    b1->c = tick->LastPrice;                                                                                           \
    b1->vold = b1->vsum;                                                                                               \
    b1->vsum = tick->Volume;                                                                                           \
    b1->v = tick->Volume - b1->vold;                                                                                   \
    b1->sent = 0;

// -----Begin ----------- 交易时间定义 ----------------------------------------
#define SGM_NUM 10

// 7 种交易时间类型
static const std::map<int, std::string> M_TimeType = {
    {0, "{\"time\":[\"09:00-10:15\",\"10:30-11:30\",\"13:30-15:00\"]}"},
    {1, "{\"time\":[\"21:00-23:00\",\"09:00-10:15\",\"10:30-11:30\",\"13:30-15:00\"]}"},
    {2, "{\"time\":[\"21:00-23:30\",\"09:00-10:15\",\"10:30-11:30\",\"13:30-15:00\"]}"},
    {3, "{\"time\":[\"21:00-24:00\",\"00:00-01:00\",\"09:00-10:15\",\"10:30-11:30\",\"13:30-15:00\"]}"},
    {4, "{\"time\":[\"21:00-24:00\",\"00:00-02:30\",\"09:00-10:15\",\"10:30-11:30\",\"13:30-15:00\"]}"},
    {5, "{\"time\":[\"09:30-11:30\",\"13:00-15:00\"]}"},
    {6, "{\"time\":[\"09:15-11:30\",\"13:00-15:15\"]}"},
};

// 7 种交易时间类型
static const std::map<int, std::string> m_time_types = {
    {0, "{\"time\":[\"09:00-10:15\",\"10:30-11:30\",\"13:30-15:00\"]}"},
    {1, "{\"time\":[\"21:00-23:00\",\"09:00-10:15\",\"10:30-11:30\",\"13:30-15:00\"]}"},
    {2, "{\"time\":[\"21:00-23:30\",\"09:00-10:15\",\"10:30-11:30\",\"13:30-15:00\"]}"},
    {3, "{\"time\":[\"21:00-24:00\",\"00:00-01:00\",\"09:00-10:15\",\"10:30-11:30\",\"13:30-15:00\"]}"},
    {4, "{\"time\":[\"21:00-24:00\",\"00:00-02:30\",\"09:00-10:15\",\"10:30-11:30\",\"13:30-15:00\"]}"},
    {5, "{\"time\":[\"09:30-11:30\",\"13:00-15:00\"]}"},
    {6, "{\"time\":[\"09:15-11:30\",\"13:00-15:15\"]}"},
};

// ----- End ----------- 交易时间定义 ----------------------------------------

// time_type用到这个segment结构，
// bar_block中也用到这个结构。从mark以后，是bar_block专用的，time_type中用不到。
struct Segment {
    char cB[9]; // char Begin   字串类型    交易时段起始
    char cE[9]; // char End     字串类型    交易时段结束
    int iB;     // int型 Begin  字串类型    交易时段起始
    int iE;     // int型 End    字串类型    交易时段结束
    int iI;     // 和前一个 segment之间的间隔。如果是第一个segment， iI = 0;
    int mark; // 0 表示 seg 包含 bar。 // 1.2.3. 表示 一个bar 包含多个 seg。用于记录一个bar是否跨时间的segment。
    int sn;
    char barB[9];
    char barE[9];
    int bariB;
    int bariE;
    int barBx; // 记录 起始barB所在的 seg[]的 index .
    int barEx; // 记录 结束barE所在的 seg[]的 index .
  public:
    Segment();
};

struct TimeType {
    int iType;   /* 不同的交易时间类型 */
    int iSegNum; /* 多少个segment */
    Segment segments_[SGM_NUM];
};

// time block ----------
struct TimeBlock {
    TimeType time_types_[7]; // 有7种交易时间类型。参见 M_TimeType
  public:
    TimeBlock();

  private:
    int Init(TimeType time_types_[]);
};

// ----- End ----------- 时间结构定义 ----------------------------------------

struct stBar {
    int iX;            // 索引号  0:TICK  1:2S 2:3S 4:5S ...   100:tick=0;
    int period_value_; // 周期  600 300 ...：:w
    char cB[9];        // begin time BAR K柱 的开始时间
    char cE[9];        // end time
    double o;          // open
    double h;          // high
    double l;          // low
    double c;          // close
    int v;             // volume
    int vsum;          // keep volume sum
    int vold;          // 前一个K柱的结束时的量
    int sent;          // 有没有sent 或者写入  ==2 已写 ==1 已sent 但没有写 ==0 没发没写
};

struct BarBlock {
    stBar bar1;
    stBar *b1;
    char curB[9]; // 记录当前tick所在的段
    char curE[9]; //
    int curiB;    // 记录当前tick所在的段
    int curiE;
    int curiX;          // 记录当前tick所在的段的下标
    int iBidx;          // 此bar1的起始点所在的 segment idx，
    int iEidx;          // 此bar1的结束点所在的 segment idx，
    int period_value_;  // 0:tick 1:2s, 60:1F ---- 周期 ： 以秒计
    int iH;             // 将周期转成 H M S, 比如：周期为 97 秒 转成： iPeriodH=0 ;
    int iM;             // iPeriodM = 1;
    int iS;             // iPeriodS = 37;  需要初始化！！
    char cF[10];        // frequency ; "1S" "2S" ...
    char ca_table[128]; /* database table name */
    int iSegNum;        // segment 数量
    Segment *seg[100];  // segment array
  public:
    BarBlock(const char *pF, int fr, TimeType *p_time_type);
    // int MakeTime(char *caTime, int T) ;
};

struct FutureBlock {
    // std::shared_ptr<uBEE::DBPool> dbpool;
    // uWS::Group<uWS::SERVER> *SG;
    // uWS::WebSocket<uWS::SERVER> *ws;  // HubBck 需要。
    int iChange; // Tick changed "20:59:??" to "21:00:00"
    char InstrumentID[81];
    char ActionDay[9];
    char TradingDay[9];
    char UpdateTime[9];      // for saving "20:59:??" .....
    char caFileName[1024];   // 用于记录"/home/rabbit/see/dat/rcv_dat/au/au1801",要组合
                             // period
    int iTickValid;          // 用于记录收到tick时，是否有效
    TimeType *p_time_type;   // TimeType
    BarBlock *pBarBlock[50]; // 1s 2s 3s ... 1f 2f 3f 5f ... 1h 5h ... 1y tick
  public:
    // FutureBlock(char *fuID, uBEE::TimeBlock *tmbo, uWS::Group<uWS::SERVER> *sg);
    FutureBlock(const char *fuID, uBEE::TimeBlock *tmbo);
};

// -------------------- for sending -----------------

struct sTick { // tick for send !!
    int iType; // type :  0:tick  1 2 3 ... for other ....
    char InstrumentID[81];
    char ActionDay[9];
    char TradingDay[9];
    // int     iX;              // 索引号  0:1S  1:2S 2:3S 4:5S ... 100:tick=0;
    // int     iF;              // 周期  600 300 ...：:w
    char UpdateTime[9];  /// 最后修改时间
    double OpenPrice;    /// 今开盘
    double HighestPrice; /// 最高价
    double LowestPrice;  /// 最低价
    double LastPrice;    /// 最新价
    double OpenInterest; /// 持仓量
    int UpdateMillisec;  /// 最后修改毫秒
    double BidPrice1;    /// 申买价一
    int BidVolume1;      /// 申买量一
    double AskPrice1;    /// 申卖价一
    int AskVolume1;      /// 申卖量一
    int Volume;          /// 数量
};

struct sKbar {  // Kbar for send !!
    int iX;     // 索引号  0:1S  1:2S 2:3S 4:5S ...   100:tick=0;
    int iF;     // 周期  600 300 ...：:w
    char cB[9]; // begin time BAR K柱 的开始时间
    char cE[9]; // end time
    double o;   // open
    double h;   // high
    double l;   // low
    double c;   // close
    int v;      // volume
    int vsum;   // keep volume sum
};

struct sData {
    int iType; // type :  0:tick  1 2 3 ... for other ....  1:nomal 2:update
    char InstrumentID[81];
    char ActionDay[9];
    char TradingDay[9];
    int iN; // number of KK below !!
    sKbar KK[50];
};

static const int hLen = sizeof(sData) - 50 * sizeof(sKbar); // head length
static const int tLen = sizeof(sTick);                      // tick length
static const int bLen = sizeof(sKbar);                      // bar length
static const int oLen = hLen + bLen;

// --- define for sData iType
#define T_TICK 0
#define T_BARS 1
#define T_UPDATE 2

// ----- End ----------- 时间结构定义 ----------------------------------------

int MakeTime(char *caT, int T);
int HhmmssToSec(const char *str);

int ReadTick(const char *file_name);
int SendTick(uBEE::FutureBlock *future_block, TICK *tick);
int SaveTick(uBEE::FutureBlock *future_block, TICK *tick);
int SaveTick(TICK *tick);
int HandleTick(uBEE::FutureBlock *future_block, TICK *tick, int flag);
int MarkBar(uBEE::FutureBlock *future_block, TICK *tick, int period);
int SendBar(uBEE::FutureBlock *future_block, int period, int flag);
int SaveBar(uBEE::FutureBlock *future_block, sKbar *KK, int period);
int DealBar(uBEE::FutureBlock *future_block, TICK *tick, int period, int flag);

int Display(uBEE::FutureBlock *future_block, TICK *tick, int period, const char *msg);
int DispBar(uBEE::FutureBlock *future_block, TICK *tick, int period, const char *msg);
int DispKbar(const char *InstrumentID, const char *TradingDay, const char *ActionDay, sKbar *bar);
int GetFrequencyIdx(int f);

//--------------------------------------------------

struct X_OHLC {
    char cB[9];
    char cE[9];
    std::vector<double> O;
    std::vector<double> H;
    std::vector<double> L;
    std::vector<double> C;
    std::vector<int> V;
    int x;     // index !! O[0]... O[1]... O[x] ...
    int u;     // update bar  u:=0 表示真正结束的bar， u:=1
               // 表示这是一个没有结束的bar。 u:=-1 表示第一个，新开始。
    int iCall; // callbacks数量.
    // void (*callbacks[256])();
    std::function<void()> callbacks[256];

  public:
    X_OHLC();
    int Insert(sKbar *bar);
    int Update(sKbar *bar);
};

} // namespace uBEE
#endif // UBEE_BARS_H
