#ifndef UBEE_BASE_H
#define UBEE_BASE_H

#include "Bars.h"
#include <uWS/uWS.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>

namespace uBEE
{

#define ON_TICK      '1'
#define ON_BARS      '2'
#define ON_ERROR     '3'

// Future storage for  future and periods! 
// the memory image:
//  "ru1805"
//  iP[0] = -1;
//  ip[1] = -1;
//  ip[2] = -1;
//  ip[3] = -1;
//  ip[4] = 5;     // index 4 === period is 5 seconds.
//  ...
//  ip[x] = 60;    // index x === period is 60 seconds.
//  ...
//  ip[49] = -1;
// mainhub.onMessage will set bars[0] bars[1] 
// bars[0] ==> ip[4] = 5;
// bars[1] ==> ip[x] = 60; 
// ip[n] noused will be set to  -1 ;
// refer to FuInit() ! | index 0 for tick. index 1----30 basic periods.  index 31-49 for custom define .
/*
struct Future {
  char    InstrumentID[31];
  char    ID2[3] ;
  int     iP[50] ;  //period
  double  mDif ;   // 变动差 比如 橡胶变化是5元
  double  mLot ;   // 每手收益 比如 一手橡胶 是50元
  double  mOP ;    // money for open position 开仓手续费
  double  mCP ;    // money for close position 平仓手续费
public:
  Future();
};
*/

struct Base {
  int Mode;
  std::map<std::string,Future>    M_Fu;    // map <"ru1805",struct Future>

  // -------- 下面的变量只记录当前收到的 future的信息 --------------------
  // 如果是多合约策略，要在其它的地方保存更完整的每个合约的基础信息 ------ 
  sData  DT;                        // recieving DaTa for  Bars.cpp( SG.broadcast() ) !!
  sData *data;                      // recieving data from mainhub.onMessage 
  sTick  TK;                        // recieving DaTa for  Bars.cpp( SG.broadcast() ) !!
  sTick *tick;                      // recieving data from mainhub.onMessage 
  char  *InstrumentID;              // point to data->InstrumentID
  char  *TradingDay;                // point to data->TradingDay
  char  *ActionDay;                 // point to data->ActionDay
  sKbar *bars[50] ;                 // current bars! mainhub.onMessage will set bars[0] bars[1] ... and send it to onBars() !!
  Future * fu ;                     // current future block for strategy !! more fu, refer to M_Fu ......

  uWS::Hub assiHub;   				// assitant Hub linked to data server for getTick,getBar ...
  uWS::Hub mainHub;   				// main     Hub callback for onTick() onBars() ...
  uWS::WebSocket<uWS::CLIENT> *cw;  // (mainHub) client to web server
  uWS::WebSocket<uWS::CLIENT> *cd;  // (mainHub) client to data server
  uWS::WebSocket<uWS::CLIENT> *c_bck;  // (mainHub) client to data server HubBck   back test
  uWS::WebSocket<uWS::CLIENT> *c_ctp;  // (mainHub) client to data server HubCtp   ctp
  uWS::WebSocket<uWS::CLIENT> *c_sim;  // (mainHub) client to data server HubSim   simulation
  uWS::WebSocket<uWS::CLIENT> *ct;  // (mainHub) client to trading server
  uWS::WebSocket<uWS::CLIENT> *ca;  // (assiHub) assitant client to data server for getTick,getBar ...
  std::vector<uWS::WebSocket<uWS::CLIENT>*>  cs;
  std::queue<char*> m_Qbuf ;

  std::mutex m_mtx; 					// 全局互斥锁.
  std::condition_variable cv; 		// 全局条件变量.
  //bool ready = false; 			// 全局标志位.

  //std::function<void(char *, size_t)> onBarsHandler;
  //std::function<void(char *, size_t)> onTickHandler;
  std::function<void(sKbar *[],int)> onBarsHandler;
  std::function<void(sTick *)> onTickHandler;

public:
  Base();
  void Init();
  void Run();
  void Stop();
  void Restart();
  void Pause();
  void Continue();
  void onTick(std::function<void(sTick *)> handler);
  void onBars(std::function<void(sKbar *[],int)> handler);
  //void onTick(std::function<void(uWS::WebSocket<uWS::CLIENT> *, char *, size_t, uWS::OpCode)> handler);
  //void onBars(std::function<void(uWS::WebSocket<uWS::CLIENT> *, char *, size_t, uWS::OpCode)> handler);
  void onMessageInit();
  // ------------------------------- API ---------------------------------
  void FuInit(const std::map<std::string,std::vector<int>> *M);
  // ------------------------------- API ---------------------------------
  void getFutureTick(char *start_date, char *end_date);
  void getFutureBars(const char *period, const char *start_date, const char *end_date);
  void getStockBars(const char *period, const char *start_date, const char *end_date);
private:
  void AssiHubInit();
};

} // namespace ---

#endif // UBEE_BASE_H
