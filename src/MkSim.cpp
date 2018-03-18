#include "../ctp/ThostFtdcMdApi.h"
#include <uWS/uWS.h>
#include "Bars.h"
#include "MkSim.h"
#include "Global.h"
#include "ErrLog.h"
#include "File.h"
#include <map>
#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <vector>

namespace uBEE
{
#define LOG_FUNC()    do { cout << __FUNCTION__ << endl; } while (0)
//---
uWS::Group<uWS::SERVER> * SimSG;
std::map<std::string,uBEE::FuSim>    M_FuSim;         // 每个期货一个 FuSim  构成一个MAP
std::map<std::string,uBEE::FuBo>     M_SimFuBo;         // 每个期货一个 FuBlock，构成一个MAP
std::vector<std::string>             V_Future(10);
std::map<std::string,std::string>    M_SimFuFile;         // 每个期货一个 FuBlock，构成一个MAP

//---

// --- FuSim 每个期货一个FuSim,用于处理 模拟交易产生相应的tick ... bar 等.
FuSim::FuSim(char *Future, const char *pFile)
{
  see_memzero(File,1024);
  see_memzero(Table,512);
  see_memzero(InstrumentID,31);
  memcpy(File,pFile,strlen(pFile));

  iLineNum = CountLines(pFile) ;
  iCurLine = 1;
  if(Future !=nullptr && strlen(Future) <= 31) {
    memcpy(InstrumentID,Future,strlen(Future));
  }

}
TICK * FuSim::MkTickF()             // make tick from tick file
{
  if(iLineNum<=0) {
    return nullptr ;
  }
  if(iCurLine <= iLineNum) {
    std::cout << " iCurLine:" << iCurLine << " iLineNum:" << iLineNum << std::endl;
    std::string TickLine =  ReadLine(File,iCurLine) ;
    std::cout << TickLine << std::endl;
    iCurLine++ ;
  }
  if(iCurLine>iLineNum) {
    iCurLine = 1;
  }
  return &Tick ;
}
int FuSim::MkBarsF(int Fr)       // make bars from bars file
{
}


int FuSim::MkTickBarsF(int Fr)   // make bars from tick file
{
  if(iLineNum ==0) {
    return -1;
  }

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

  if(T________) {
    sprintf(ca_errmsg,"MkSim(): enter!!") ;
    uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
  }

  SimSG = new_sg;

  M_SimFuFile.insert(std::pair<std::string,std::string>("ag1606","../Sim/tick/ag1606.tick.ss"));
  M_SimFuFile.insert(std::pair<std::string,std::string>("bu1606","../Sim/tick/bu1606.tick.ss"));
  M_SimFuFile.insert(std::pair<std::string,std::string>("cu1603","../Sim/tick/cu1603.tick.ss"));
  M_SimFuFile.insert(std::pair<std::string,std::string>("m1605","../Sim/tick/m1605.tick.ss"));
  M_SimFuFile.insert(std::pair<std::string,std::string>("MA605","../Sim/tick/MA605.tick.ss"));


  // ------------------------------初始化 FuSim ， 每个 future  一个 FuSim ... 保存在  M_FuSim 这个map中。
  for(auto iter = M_SimFuFile.begin(); iter != M_SimFuFile.end(); ++iter) {
    cout << iter->first << " : " << iter->second << endl;
    if(T________) {
      sprintf(ca_errmsg,"MkSim(): Future:%s file:%s",iter->first.c_str(),iter->second.c_str()) ;
      uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
    }
    char* p = (char*)iter->first.c_str();
    char* f = (char*)iter->second.c_str();

    // 用户自定义 交易周期
    int fr[5] = {19,14401,180,300,600};
    uBEE::FuBo *fubo = new uBEE::FuBo(p,tb,&fr[0], 5);
    M_SimFuBo.insert(std::pair<std::string,uBEE::FuBo>(p, *fubo));

    uBEE::FuSim *fusim = new uBEE::FuSim(p, f);
    M_FuSim.insert(std::pair<std::string,uBEE::FuSim>(p, *fusim));
  }


  // ----------------  test ----------------------------------------------begin
  for(auto it = M_SimFuBo.begin(); it != M_SimFuBo.end(); ++it) {
    sprintf(ca_errmsg,"rrrrrrrrr");
    uBEE::ErrLog(1000,ca_errmsg,1,0,0);
    uBEE::ErrLog(1000,ca_errmsg,1,0,0);
    uBEE::FuBo *fubo = &(it->second);

    for(int i=0; i<50; ++i) {
      if(fubo->pBaBo[i] == nullptr) {
        continue;
      }
      for(int j=0;j<fubo->pBaBo[i]->iSegNum;++j) {
        stSegment *seg = fubo->pBaBo[i]->seg[j] ;
        sprintf(ca_errmsg,"rrrrrrrrr:future:%s  i:%d iF:%d  segid:%d, mark:%d  segB segE:%s--%s  barB barE:%s--%s",
          fubo->InstrumentID,
          i,fubo->pBaBo[i]->iF,j,seg->mark,
                      seg->cB,seg->cE,seg->barB,seg->barE);
        uBEE::ErrLog(1000,ca_errmsg,1,0,0);
      }
    }

    sprintf(ca_errmsg,"rrrrrrrrr");
    uBEE::ErrLog(1000,ca_errmsg,1,0,0);
    uBEE::ErrLog(1000,ca_errmsg,1,0,0);
  }
  // ----------------  test ----------------------------------------------end

  // -------------- 从 M_FuSim 这个map中取出 future 以及 fusim ，再 从 M_SimFuBo中 找出 这个future的 fobo--->
  // -------------- fusim 生成tick ,  fobo 用来生成 K柱 .
  while(1) {
    for(auto it = M_FuSim.begin(); it != M_FuSim.end(); ++it) {
      //char * fu = it->first ;
      uBEE::FuSim *fusim = &(it->second) ;
      // 从 M_SimFuBo 这个map中找到相应的 fubo， 然后将其传给 DearBars() ;
      std::map<std::string,uBEE::FuBo>::iterator iter;
      iter = M_SimFuBo.find(it->first);
      if(iter == M_SimFuBo.end()) {
        sprintf(ca_errmsg,"MkSim not find: %s",it->first.c_str()) ;
        uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
        continue ;
      }

      uBEE::FuBo *fubo = &(iter->second);

      TICK *tick = fusim->MkTickF();
      for(int i=0; i<50; ++i) {
        if(fubo->pBaBo[i] == nullptr) {
          continue;
        }
        DealBar(fubo, tick, i);
      }
    }
  }

}

} // end namespace uBEE
