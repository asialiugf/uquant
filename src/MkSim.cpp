#include "../ctp/ThostFtdcMdApi.h"
#include <uWS/uWS.h>
#include "Bars.h"
#include "MkSim.h"
#include "Global.h"
#include <map>
#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

namespace uBEE
{

//---
uWS::Group<uWS::SERVER> * SimSG;
std::map<std::string,uBEE::FuBo>    M_SimFuBo;         // 每个期货一个 FuBlock，构成一个MAP
//std::shared_ptr<uBEE::DBPool> dbpool;
//---

FuSim::FuSim(const char *Filename, char *Future)
{
  char File[1024];
  char Table[512];
  char InstrumentID[31];
  see_memzero(File,1024);
  see_memzero(Table,512);
  see_memzero(InstrumentID,31);
  memcpy(InstrumentID,Future,strlen(Future));
  memcpy(File,Filename,strlen(Filename));
}
int FuSim::MkTickF()             // make tick from tick file
{
}
int FuSim::MkBarsF(int Fr)       // make bars from bars file
{
}
int FuSim::MkTickBarsF(int Fr)   // make bars from tick file
{

  
  return 0;
}

int FuSim::MkTickT()             // make tick from database tick table
{
}
int FuSim::MkBarsT(int Fr)       // make bars from database bars table
{
}
int FuSim::MkTickBarsT(int Fr)   // make bars from database tick table
{
}

void MkSim(uWS::Group<uWS::SERVER> * new_sg)
{
  SimSG = new_sg;

}

} // end namespace uBEE
