#ifndef UBEE_MKSIM_H
#define UBEE_MKSIM_H

#include <uWS/uWS.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>

namespace uBEE
{
struct FuSim {
  char File[1024];
  char Table[512];
  char InstrumentID[31];
public:
  FuSim(const char *Filename, char *Future);
  int MkTickF();            // make tick from tick file 
  int MkBarsF(int Fr);      // make bars from bars file
  int MkTickBarsF(int Fr);  // make bars from tick file
  int MkTickT();            // make tick from database tick table
  int MkBarsT(int Fr);      // make bars from database bars table
  int MkTickBarsT(int Fr);  // make bars from database tick table
private:
};

void MkSim(uWS::Group<uWS::SERVER> * new_sg) ;

} //namespace

#endif // UBEE_MKSIM_H
