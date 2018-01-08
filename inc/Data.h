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

struct Data {
  uWS::Hub assiHub;   // assitant Hub linked to data server for getTick,getBar ...
  uWS::Hub mainHub;   // main     Hub callback for onTick() onBars() ...

}

}

#endif // UGG_DATA_H
