#include "Base.h"
#include <iostream>
#include <thread>
#include <unistd.h>

namespace uGG
{
Base::Base():cs(4,nullptr)       // constructor  new thread fot getting data APIs.
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
  mainHub.onMessage([this](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {

    message[length-1] = 0;
    std::cout << message << std::endl;
    this->onTickHandler(message,length);
    switch(message[0]) {
    case  ON_TICK:
      this->onTickHandler(message,length);
      break;
    case  ON_BARS:
      this->onBarsHandler(message,length);
      break;
    }

  });
}

void Base::MainHubInit()
{
  std::cout << "enter into MainHubInit !!\n";
  mainHub.onConnection([this](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
    switch((long) ws->getUserData()) {
    case 1:
      this->cs[1] = ws;
      break;
    case 2:
      this->cs[2] = ws;
      break;
    case 3:
      this->cs[3] = ws;
      break;
    default:
      std::cout << "FAILURE: " << ws->getUserData() << " should not connect!" << std::endl;
      exit(-1);
    }
    ws->send("hhhhhhhaaaaaaaaaa!!");
  });

  // 客户端打印接收到的消息
  Base::onMessageInit();
  /*
    mainHub.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[256];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        printf("Client receive: %s\n", tmp);
        ws->send("Torkkk===");
        usleep(1000000);
        ws->send("----new-----");
        usleep(1);

    });
  */

  mainHub.onDisconnection([this](uWS::WebSocket<uWS::CLIENT> *ws, int code, char *message, size_t length) {
    this->mainHub.getDefaultGroup<uWS::SERVER>().close();
    this->mainHub.getDefaultGroup<uWS::CLIENT>().close();
  });

  mainHub.connect("ws://localhost:3000",(void *) 1);  //  web server
  mainHub.connect("ws://localhost:4000",(void *) 2);  //  data server
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
      break;
    default:
      std::cout << "FAILURE: " << ws->getUserData() << " should not connect!" << std::endl;
      exit(-1);
    }
  });

  assiHub.onMessage([this](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
    char *tmp = new char[length+1];
    //char tmp[256];
    memcpy(tmp, message, length);
    tmp[length] = 0;
    //usleep(1000000);
    //printf("Client receive: %s\n", tmp);
    this->buf.push(tmp);     //将收到的数据，传给主线程的get_tick() get_bars()之类的函数。
    this->cv.notify_all();   //唤醒get_tick() get_bars()
    //ws->send("-------fro assiHub ===");
    //usleep(1000000);

  });
  assiHub.connect("ws://localhost:4000",(void *) 0); //传入 (void *) 0), onConnection会收到，再保存ws.
  assiHub.run();
}

void Base::getTick()
{
  if(cs[0] == nullptr) {
    std::cout<< " not init !!\n";
    exit(-1);
  }
  cs[0]->send("----------from gettick -----------");

  //std::cout<< " go to sleep!! \n";
  std::unique_lock <std::mutex> l(mtx);
  //while(!ready)  // 如果标志位不为 true, 则等待...
  cv.wait(l); // 这里要改成 timeout时间。
  //std::cout<< " waked!! \n";
  char * tmp = buf.front();
  buf.pop();
  //std::cout<< tmp << std::endl;
  delete [] tmp;
}

}
