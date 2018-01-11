#ifndef UBEE_HUBBCK_H
#define UBEE_HUBBCK_H

#include <uWS/uWS.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>

namespace uBEE
{

struct HubBck {
  char URL[256];
  int port;
  uWS::Hub   h;
public:
  HubBck();
  void Init();
  void Start();
  void Run();
private:
  void S_onDisconnection();
  void S_onConnection();
  void S_onMessage();
  void S_onPong();
  void S_Listen();
};

} //namespace

#endif // UBEE_HUBBCK_H
