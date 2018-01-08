#ifndef UGG_DATA_H
#define UGG_DATA_H

#include <uWS/uWS.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>

namespace uBEE
{

struct ApiHub {
  uWS::Hub   h;
public:
  ApiHub();
  void Start();

};

struct CtpHub {
  uWS::Hub   h;
public:
  CtpHub();
  void Start();

};

struct SimHub {
  uWS::Hub   h;
public:
  SimHub();
  void Start();

};

struct BckHub {
  uWS::Hub   h;
public:
  BckHub();
  void Start();

};

} //namespace

#endif // UGG_DATA_H
