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

struct Future {
  char    InstrumentID[31];
  int     iP[50];  //period
public:
  Future();
};

struct Base {
  int Mode;
  std::map<std::string,Future>    M_Fu;

  sData  DT;  // Data for send !!
  sData *data;   //
  char  *InstrumentID;
  char  *TradingDay;
  char  *ActionDay;
  sKbar *bars[50] ;

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
  void FuInit(const std::map<std::string,std::vector<int>> *M,const int aFr[],int len);
  // ------------------------------- API ---------------------------------
  void getFutureTick(char *start_date, char *end_date);
  void getFutureBars(const char *period, const char *start_date, const char *end_date);
  void getStockBars(const char *period, const char *start_date, const char *end_date);
private:
  void AssiHubInit();
};

} // namespace ---

#endif // UBEE_BASE_H
