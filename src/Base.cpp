#include "Base.h"
#include "Bars.h"
#include "ApiFun.h"
#include <cjson/cJSON.h>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <algorithm>
#include <vector>

namespace uBEE
{

static barSG  KBuf1 ;
static barSG  * KBuf = &KBuf1 ;
static int  kLen = sizeof(Kline);

Base::Base():cs(100,nullptr)       // constructor  new thread fot getting data APIs.
{
  std::thread t(&Base::AssiHubInit,this);
  t.detach();
  usleep(1000000); // should wait for thread ready
}

void Base::Init()
{

}

void Base::onTick(std::function<void(char *, size_t)> handler)
{
  Base::onTickHandler = handler;
}

void Base::onBars(std::function<void(char *, size_t)> handler)
{
  Base::onBarsHandler = handler;
}

void Base::onMessageInit()
{
  mainHub.onMessage([this](uWS::WebSocket<uWS::CLIENT> *ws, char *data, size_t length, uWS::OpCode opCode) {

    memcpy((char *)KBuf,data,length);
    /*
    std::cout << KBuf->InstrumentID << " " << KBuf->ActionDay<<" "<< KBuf->iN  << std::endl ;
    for(int i = 0; i< KBuf->iN ; ++i ) {
      std::cout << KBuf->KK[i].cK << std::endl;
    }
    */
    //char * buffer = new char(length);
    //std::cout << std::string(message, length) << std::endl;
    //message[length-1] = 0;
    //std::cout << "kkkkkkkkk\n" << std::endl;
    //std::cout << std::string(message, length) << std::endl;
    this->onTickHandler((char*)KBuf,length);

    /* 
     case : weekend ==> change kkk;
     case : monthend ==> do something;
    */

    /*
    char msg[200];
    memcpy(msg,message,length);
    this->onTickHandler(msg,length);
    switch(message[0]) {
    case  ON_TICK:
      this->onTickHandler(msg,length);
      break;
    case  ON_BARS:
      this->onBarsHandler(msg,length);
      break;
    }
    */

  });
}

void Base::Start()
{
  std::cout << "enter into Start !!\n";
  mainHub.onConnection([this](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
    switch((long) ws->getUserData()) {
    case 1:
      this->cs[1] = ws;
      this->cw = ws;
      break;
    case 2:
      this->cs[2] = ws;
      this->cd = ws;
      break;
    case 3:
      this->cs[3] = ws;
      this->ct = ws;
      break;
    case 4:
      this->cs[4] = ws;
      this->c_ctp = ws;
      break;
    case 5:
      this->cs[5] = ws;
      this->c_sim = ws;
      break;
    default:
      std::cout << "FAILURE: " << ws->getUserData() << " should not connect!" << std::endl;
      exit(-1);
    }
    ws->send("hhhhhhhaaaaaaaaaa!!");
  });

  // 客户端打印接收到的消息
  Base::onMessageInit();

  mainHub.onDisconnection([this](uWS::WebSocket<uWS::CLIENT> *ws, int code, char *message, size_t length) {
    auto result = find(this->cs.begin(), this->cs.end(), ws);     //查找 ws
    if(result == this->cs.end()) {    //没找到
      std::cout << "Not found" << std::endl;
    } else {
      std::cout << "YesYes!!" << std::endl;  //找到了
      (*result) = nullptr ;
      //ws->close();
    }
    std::cout << "code:"<< code << std::endl;
    //this->mainHub.getDefaultGroup<uWS::SERVER>().close();
    //this->mainHub.getDefaultGroup<uWS::CLIENT>().close();
    switch((long) ws->getUserData()) {
    case 1:
      break;
    case 5:
      mainHub.connect("ws://localhost:3004",(void *) 5);  //  data server HubSim  //模拟
      break;
    }
  });

  mainHub.connect("ws://localhost:3000",(void *) 1);  //  web server
  mainHub.connect("ws://localhost:4000",(void *) 2);  //  data server
  mainHub.connect("ws://localhost:3003",(void *) 4);  //  data server HubCtp  //实盘
  mainHub.connect("ws://localhost:3004",(void *) 5);  //  data server HubSim  //模拟
  mainHub.connect("ws://localhost:5000",(void *) 3);  //  trading server
  std::cout << "-------------- !!\n";
  mainHub.run();
  std::cout << "after run \n";
}

void Base::AssiHubInit()
{
  assiHub.onConnection([this](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
    switch((long) ws->getUserData()) {
    case 0:
      this->cs[0] = ws;
      this->ca = ws;
      break;
    default:
      std::cout << "FAILURE: " << ws->getUserData() << " should not connect!" << std::endl;
      exit(-1);
    }
  });

  assiHub.onMessage([this](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
    char *tmp = new char[length+1];
    char tmp1[256];
    memcpy(tmp1, message, length);
    tmp1[length] = 0;
    //usleep(1000000);
    printf("Client receive:%s\n", message);
    this->m_Qbuf.push(tmp);     //将收到的:数据，传给主线程的get_tick() get_bars()之类的函数。
    this->cv.notify_all();   //唤醒get_tick() get_bars()
    //ws->send("-------fro assiHub ===");
    //usleep(1000000);

  });
  assiHub.connect("ws://localhost:3001",(void *) 0); //传入 (void *) 0), onConnection会收到，再保存ws.
  assiHub.run();
}

//void Base::getFuTick(char *start_date, char *end_date)
void Base::getFutureTick(char *start_date, char *end_date)
{
  // cs[0] 与 DataServer: HubAPI 相联系。
  if(cs[0] == nullptr) {
    std::cout<< " assistant Hub may not be initialed !!\n";
    exit(-1);
  }

  // 将请求发给 DataServer: HubAPI。
  // 这里的请求，有很多种，需要定义相关协议。
  char cmd[512];
  memset(cmd,'\0',512);
  int iCode = API_GET_FUTURE_TICKS ;
  sprintf(cmd,"%4d{\"Sdate\":\"%s\",\"Edate\":\"%s\"}",API_GET_FUTURE_TICKS,start_date,end_date);
  std::cout << cmd << std::endl;
  cs[0]->send(cmd);


  //  等待 HubApi.cpp Dataserver 返回数据。
  std::cout<< " go to sleep!! \n";
  std::unique_lock <std::mutex> l(m_mtx);
  cv.wait(l); // 这里要改成 timeout时间。
  std::cout<< " waked!! \n";
  char * tmp = m_Qbuf.front();
  m_Qbuf.pop();
  delete [] tmp;
}

void Base::getFutureBars(const char *period, const char *start_date, const char *end_date)
{
}
void Base::getStockBars(const char *period, const char *start_date, const char *end_date)
{
}


} //namespace
