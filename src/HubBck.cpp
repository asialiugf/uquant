#include "uBEE.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <algorithm>
#include <vector>

namespace uBEE
{

HubBck::HubBck()
{
}

void HubBck::Init()
{
  memset(URL,'\0',256);
  sprintf(URL,"3002");
  port = 3002;
}

void HubBck::S_onMessage()
{
  h.onMessage([this](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
    switch(*((int*)message)) {
    case 0: {
      BckMsg *bckmsg = (BckMsg *)message ;
      std::cout << bckmsg->iType <<" " << bckmsg->iN << std::endl;
      break;
    }
    case 1:
      ws->send(message, length, opCode);
      break;
    }
  });
}

void HubBck::S_onConnection()
{
  h.onConnection([this](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
    //ws->send("--server--");
    //todo ----
    // save ws....
    long user_data = (long) ws->getUserData();
    std::cout <<"BackTest Server onConnection :"<< user_data << "pid:" << getpid() << std::endl;
  });
}

void HubBck::S_onDisconnection()
{
  h.onDisconnection([this](uWS::WebSocket<uWS::SERVER> *ws, int code, char *message, size_t length) {
    std::cout << "onDisconnection !!" << std::endl;
    std::cout << message << std::endl;
  });
}

void HubBck::S_onPong()
{
  h.onPong([this](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length) {
    std::cout<< "ok ping\n";
  });
  h.getDefaultGroup<uWS::SERVER>().startAutoPing(2000);
}

void HubBck::S_Listen()
{
  //bool k = h.listen(port) ;
  bool k = h.listen(port, nullptr, uS::REUSE_PORT);
  if(!k) {
    std::cout << " listen error !!" << std::endl;
    exit(-1);
  }
}
void HubBck::Run()
{
  h.run();
}

void  HubBck::Start()
{
  HubBck::S_onDisconnection();
  HubBck::S_onConnection();
  HubBck::S_onMessage();
  HubBck::S_onPong();
  HubBck::S_Listen();
  //HubBck::Run();
}

} // namespace
