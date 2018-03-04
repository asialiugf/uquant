#ifndef UBEE_BARS_H
#define UBEE_BARS_H

#include <uWS/uWS.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>

namespace uBEE
{
#define see_memzero(buf, n)         (void) memset(buf, 0, n)
#define SEE_NULL    -2147483648
#define  SEE_OK          0

#define  BAR_SECOND        's'
#define  BAR_MINUTE        'f'
#define  BAR_HOUR          'h'
#define  BAR_DAY           'd'
#define  BAR_WEEK          'w'
#define  BAR_MONTH         'm'
#define  BAR_SEASON        'j'
#define  BAR_YEAR          'y'
#define  BAR_TICKC         't'

#define  FUTRUE_ID_LEN     31
#define  SEE_SGM_NUM       50
#define  SEE_HOUR_TYPE_NUM 10
#define  TRADE_TIME         "../etc/tbl/see_trade_time"
#define  FUTURE_DAYS        "../etc/tbl/see_future_days"
#define  FUTURE_TIME        "../etc/tbl/see_future_time"

typedef struct  {
  char c_oc_flag ;    /* 'o':open   ;c':close */
  char ca_b[9] ;      /* ca_begin             */
  char ca_e[9] ;      /* ca_end               */

  char ca_15F_start[9] ;
  char ca_20F_start[9] ;
  char ca_30F_start[9] ;
  char ca_1H_start[9] ;
  char ca_2H_start[9] ;
  char ca_3H_start[9] ;
  char ca_4H_start[9] ;
  char ca_5H_start[9] ;
  char ca_1D_start[9] ;

  char ca_15F_end[9] ;
  char ca_20F_end[9] ;
  char ca_30F_end[9] ;
  char ca_1H_end[9] ;
  char ca_2H_end[9] ;
  char ca_3H_end[9] ;
  char ca_4H_end[9] ;
  char ca_5H_end[9] ;
  char ca_1D_end[9] ;
} see_segment_t ;   // 用于记录时间段，目前每个交易时间段为15分钟



typedef struct {
  char ca_begin[9];
  char ca_end[9];
} see_begin_end_t;

typedef struct {
  int             i_hour_type;  /* 不同的交易时间类型 */
  int             period;
  see_begin_end_t * pt_BEs[SEE_SGM_NUM];
} see_BE_t;

typedef struct  {
  int             i_hour_type;  /* 不同的交易时间类型 */
  see_segment_t  *pt_segments[SEE_SGM_NUM] ;
} see_hours_t ;     // 交易时间，用于记录一天的所有的交易时间段  每个期货品种有一个 see_fut_block_t，这个结构中会包含


// class TradingTime -----------------------

struct TradingTime {
  see_hours_t t_hours[10] ;   // 有10种交易时间类型。
public:
  TradingTime();
private:
  int Init(see_hours_t t_hours[]) ;

};
// class TradingTime  end  -----------------------


typedef struct {
//    char    InstrumentID[31];
  char    TradingDay[9];
  char    ActionDay[9];
  char    ca_btime[9];   //begin time
  char    ca_etime[9];  //end time
  double  o ;             // open
  double  c ;             // close
  double  h ;             // high
  double  l ;             // low
  int     v ;             // volume
  int     vsum ;         // keep volume sum
} see_bar_t ;

typedef struct {
  see_bar_t           bar0 ;
  see_bar_t           bar1 ;
  char                c_save ;                    /* 's' 表示 save  'n' 表示 不需要save */
  int                 i_bar_type ;                // 1 2 3 5 10 15   这个值可以用来计算 新来的tick是不是在同一个K
  char                c_bar_type ;                // S F H D W M J Y  BAR_SECOND BAR_MINUTE ...
  char                ca_table[128];                 /* database table name */
  char                ca_home[512];              /* for txt ohlc saving */
  char                ca_file[512];
} see_bar_block_t ;


typedef struct  {
  char                InstrumentID[31];
  char                ca_home[512];                   // 用于记录"/home/rabbit/see/dat/rcv_dat/au" 需要初始化
  int                 i_hour_type ;                   // 每个品种的交易时间类型不一样，有的到23:00结束，有的到 01:00
  char                c_oc_flag ;                     //  'o' 'c' 用于记录 收到的tick是不是在交易时间段内 每收到一个记一次
  int                 i_sgm_idx ;                     // 用于记录收到tick时，是在哪个交易时间段内 每收到一个记一次
  see_hours_t         *pt_hour ;                      // 每个品种的交易时间类型 不一样
  see_bar_block_t     bar_block[31] ;                 // 1s 2s 3s ... 1f 2f 3f 5f ... 1h 5h ... 1y tick
  //see_shm_t           shm ;                    /* 用于记录sharememory, 每个future有一个shmem */
} see_fut_block_t ;

typedef struct {
  char                InstrumentID[31];
  char                TradingDay[9];
  char                ActionDay[9];
  char                UpdateTime[9];
  double              o ;             // open
  double              c ;             // close
  double              h ;             // high
  double              l ;             // low
  int                 v ;             // volume
} see_bar_save_t ;


struct FuBlock {
  see_fut_block_t Block ;
public:
  FuBlock();
  int Init(see_fut_block_t * p_block, char * pc_future, see_hours_t t_hours[]);
private:
};


int string_split(char *s,char _cmd[SEE_SGM_NUM][20]);


} //end namespace

#endif // UBEE_BARS_H
