#ifndef UBEE_BASE_H
#define UBEE_BASE_H

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


struct Base {

  uWS::Hub assiHub;   				// assitant Hub linked to data server for getTick,getBar ...
  uWS::Hub mainHub;   				// main     Hub callback for onTick() onBars() ...
  uWS::WebSocket<uWS::CLIENT> *cw;  // (mainHub) client to web server
  uWS::WebSocket<uWS::CLIENT> *cd;  // (mainHub) client to data server
  uWS::WebSocket<uWS::CLIENT> *ct;  // (mainHub) client to trading server
  uWS::WebSocket<uWS::CLIENT> *ca;  // (assiHub) assitant client to data server for getTick,getBar ...
  std::vector<uWS::WebSocket<uWS::CLIENT>*>  cs;
  std::queue<char*> buf ;

  std::mutex mtx; 					// 全局互斥锁.
  std::condition_variable cv; 		// 全局条件变量.
  //bool ready = false; 			// 全局标志位.

  std::function<void(char *, size_t)> onBarsHandler;
  std::function<void(char *, size_t)> onTickHandler;

public:
  Base();
  void Init();
  void Start();
  void Stop();
  void Restart();
  void Pause();
  void Continue();
  void getTick();
  void getBars();
  void onTick(std::function<void(char *, size_t)> handler);
  void onBars(std::function<void(char *, size_t)> handler);
  //void onTick(std::function<void(uWS::WebSocket<uWS::CLIENT> *, char *, size_t, uWS::OpCode)> handler);
  //void onBars(std::function<void(uWS::WebSocket<uWS::CLIENT> *, char *, size_t, uWS::OpCode)> handler);
  void onMessageInit();
private:
  void AssiHubInit();
};

}

#endif // UBEE_BASE_H
