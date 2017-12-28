#ifndef UGG_BASE_H
#define UGG_BASE_H

#include <uWS/uWS.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>

namespace uGG
{

struct Base {

    uWS::Hub assiHub;   // assitant Hub linked to data server for getTick,getBar ...
    uWS::Hub mainHub;   // main     Hub callback for onTick() onBars() ...
    uWS::WebSocket<uWS::CLIENT> *cw;  // (mainHub) client to web server
    uWS::WebSocket<uWS::CLIENT> *cd;  // (mainHub) client to data server
    uWS::WebSocket<uWS::CLIENT> *ct;  // (mainHub) client to trading server
    uWS::WebSocket<uWS::CLIENT> *ca;  // (assiHub) assitant client to data server for getTick,getBar ...
    std::vector<uWS::WebSocket<uWS::CLIENT>*>  cs;
	std::queue<char*> buf ;

    std::mutex mtx; 					// 全局互斥锁.
    std::condition_variable cv; 		// 全局条件变量.
    bool ready = false; 				// 全局标志位.

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
    void onTick();
    void onBars();
    void MainHubInit();
private:
    void AssiHubInit();
};

}

#endif // UGG_BASE_H
