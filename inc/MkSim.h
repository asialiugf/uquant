#ifndef UBEE_MKSIM_H
#define UBEE_MKSIM_H

#include <uWS/uWS.h>
#include "Bars.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>

namespace uBEE
{
struct FuSim {
  TICK Tick;
  sData  Data ;
  char File[1024];
  char BarF[1024];
  char Table[512];
  char InstrumentID[31];
  int  iLineNum ;
  int  iCurLine ;
public:
  FuSim(char *Future, const char *Filename);
  int SetBarF(const char *Filename);
  TICK * MkTickF();         // make tick from tick file
  int MkBarsF(uBEE::FuBo *fubo,int Fr);      // make bars from bars file
  int MkTickBarsF(int Fr);  // make bars from tick file
  int MkTickT();            // make tick from database tick table
  int MkBarsT(int Fr);      // make bars from database bars table
  int MkTickBarsT(int Fr);  // make bars from database tick table
private:
};

void MkSim(uWS::Group<uWS::SERVER> * new_sg) ;

} //namespace

#endif // UBEE_MKSIM_H
