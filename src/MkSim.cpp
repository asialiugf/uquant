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
//barSG  * KBuf;

//---

// --- FuSim 每个期货一个FuSim,用于处理 模拟交易产生相应的tick ... bar 等.
FuSim::FuSim(char *Future, const char *pFile)
{
  see_memzero(File,1024);
  see_memzero(Table,512);
  see_memzero(InstrumentID,31);
  snprintf(InstrumentID,31,"%s",Future) ;
  snprintf(File,1024,"%s",pFile) ;

  iLineNum = CountLines(pFile) ;
  iCurLine = 1;
  if(Future !=nullptr && strlen(Future) <= 31) {
    memcpy(InstrumentID,Future,strlen(Future));
  }

}
TICK * FuSim::MkTickF()             // make tick from tick file
{
  char          TradingDay[9];          ///交易日
  char          InstrumentID[31];       ///合约代码
  double        LastPrice;              ///最新价
  double        OpenPrice;              ///今开盘
  double        HighestPrice;           ///最高价
  double        LowestPrice;            ///最低价
  int           Volume;                 ///数量
  double        OpenInterest;           ///持仓量
  char          UpdateTime[9];          ///最后修改时间
  int           UpdateMillisec;         ///最后修改毫秒
  double        BidPrice1;              ///申买价一
  int           BidVolume1;             ///申买量一
  double        AskPrice1;              ///申卖价一
  int           AskVolume1;             ///申卖量一
  char          ActionDay[9];           ///业务日期
  int ss;
  if(iLineNum<=0) {
    return nullptr ;
  }
  if(iCurLine <= iLineNum) {
    std::string TickLine =  ReadLine(File,iCurLine,iLineNum) ;
    std::cout << " iCurLine:" << iCurLine << " iLineNum:" << iLineNum <<" " << TickLine << std::endl;
    if(TickLine.empty()) {
      return nullptr ;
    }

    char Ttemp[15] ;
    char Atemp[15] ;

    see_memzero(Ttemp,15);
    see_memzero(Atemp,15);

    see_memzero(TradingDay,9);
    see_memzero(ActionDay,9);
    see_memzero(UpdateTime,9);
    see_memzero(InstrumentID,31);
    sscanf(TickLine.c_str(), "T:%s %s %d S:%d A:%s H:%lf L:%lf LP:%lf AP:%lf AV:%d BP:%lf BV:%d OI:%lf V:%d",
           Ttemp, UpdateTime, &UpdateMillisec, &ss, Atemp,
           &HighestPrice, &LowestPrice, &LastPrice,
           &AskPrice1, &AskVolume1,
           &BidPrice1, &BidVolume1,
           &OpenInterest, &Volume);
    see_memzero(Tick.InstrumentID,31);

    /*
    memcpy(Tick.TradingDay,Ttemp,4) ;
    memcpy(Tick.TradingDay+4,Ttemp+5,2) ;
    memcpy(Tick.TradingDay+6,Ttemp+8,2) ;

    memcpy(Tick.ActionDay,Atemp,4) ;
    memcpy(Tick.ActionDay+4,Atemp+5,2) ;
    memcpy(Tick.ActionDay+6,Atemp+8,2) ;
    */
    memcpy(Tick.TradingDay,Ttemp,8) ;
    memcpy(Tick.ActionDay,Atemp,8) ;

    memcpy(Tick.UpdateTime,UpdateTime,9) ;
    Tick.UpdateMillisec = UpdateMillisec/1000;
    Tick.HighestPrice = HighestPrice;
    Tick.LowestPrice = LowestPrice;
    Tick.LastPrice = LastPrice;
    Tick.AskPrice1 = AskPrice1;
    Tick.AskVolume1 = AskVolume1;
    Tick.BidPrice1 = BidPrice1;
    Tick.BidVolume1 = BidVolume1;
    Tick.OpenInterest = OpenInterest;
    Tick.Volume = Volume;

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
    uBEE::ErrLog(1000,"MkSim(): enter!!",1,0,0) ;
  }

  //KBuf = new barSG() ;
  SimSG = new_sg;

  std::cout << "sssssssssssssssssssss\n" ;
  for(int j=0; j<7; j++) {
    int i = 0;
    while(i<SGM_NUM &&tb->TT[j].aSgms[i].iI !=-1) {
      std::cout << "----:"<< tb->TT[j].aSgms[i].cB ;
      std::cout << "----:"<< tb->TT[j].aSgms[i].cE ;
      std::cout << "----:"<< tb->TT[j].aSgms[i].iB ;
      std::cout << "----:"<< tb->TT[j].aSgms[i].iE ;
      std::cout << "----:"<< tb->TT[j].aSgms[i].iI << std::endl;
      i++;
    }
    std::cout << std::endl;
  }
  std::cout << "sssssssssssssssssssss\n" ;

  //exit(0);


  //M_SimFuFile.insert(std::pair<std::string,std::string>("ag1606","../Sim/tick/ag1606.tick.ss"));
  M_SimFuFile.insert(std::pair<std::string,std::string>("ru1805","../Sim/tick/ru1805.20180330.tick.txt"));
  M_SimFuFile.insert(std::pair<std::string,std::string>("zn1805","../Sim/tick/zn1805.20180328.tick.txt"));
  //M_SimFuFile.insert(std::pair<std::string,std::string>("bu1606","../Sim/tick/bu1606.tick.ss"));
  //M_SimFuFile.insert(std::pair<std::string,std::string>("cu1603","../Sim/tick/cu1603.tick.ss"));
  //M_SimFuFile.insert(std::pair<std::string,std::string>("m1605","../Sim/tick/m1605.tick.ss"));
  //M_SimFuFile.insert(std::pair<std::string,std::string>("MA605","../Sim/tick/MA605.tick.ss"));


  // ------------------------------初始化 FuSim ， 每个 future  一个 FuSim ... 保存在  M_FuSim 这个map中。
  for(auto iter = M_SimFuFile.begin(); iter != M_SimFuFile.end(); ++iter) {
    if(T________) {
      sprintf(ca_errmsg,"MkSim(): Future:%s file:%s",iter->first.c_str(),iter->second.c_str()) ;
      uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
    }
    char* p = (char*)iter->first.c_str();
    char* f = (char*)iter->second.c_str();

    // 用户自定义 交易周期
    int fr[5] = {19,14401,9900,300,600};
    uBEE::FuBo *fubo = new uBEE::FuBo(p,tb,SimSG, &fr[0], 5);
    M_SimFuBo.insert(std::pair<std::string,uBEE::FuBo>(p, *fubo));

    uBEE::FuSim *fusim = new uBEE::FuSim(p, f);
    M_FuSim.insert(std::pair<std::string,uBEE::FuSim>(p, *fusim));
  }

  // ----------------  test ----------------------------------------------begin
  for(auto it = M_SimFuBo.begin(); it != M_SimFuBo.end(); ++it) {
    uBEE::ErrLog(1000,"rrrrrrrrrr",1,0,0);
    uBEE::FuBo *fubo = &(it->second);

    for(int i=0; i<50; ++i) {
      if(fubo->pBaBo[i] == nullptr) {
        continue;
      }
      for(int j=0; j<fubo->pBaBo[i]->iSegNum; ++j) {
        Segment *seg = fubo->pBaBo[i]->seg[j] ;
        sprintf(ca_errmsg,"rrrrrrrrr:%s i:%d iF:%d id:%d:%d, mk:%d  sn:%d segBE:%s-%s barBE:%s--%s sgiBE:%d--%d  bariBE:%d--%d barBxEx:%d--%d",
                fubo->InstrumentID,
                i,fubo->pBaBo[i]->iF,j,fubo->pBaBo[i]->iSegNum,seg->mark,seg->sn,
                seg->cB,seg->cE,seg->barB,seg->barE,
                seg->iB,seg->iE,
                seg->bariB,seg->bariE,seg->barBx,seg->barEx);
        uBEE::ErrLog(1000,ca_errmsg,1,0,0);
      }
    }

    uBEE::ErrLog(1000,"rrrrrrrrrr",1,0,0);
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
      memcpy(tick->InstrumentID,fubo->InstrumentID,strlen(fubo->InstrumentID)) ;

      if(fubo==nullptr || tick==nullptr) {
        continue;
      }
      HandleTick(fubo,tick);
      usleep(1000000);
      /*
      SendBar(fubo, tick, 1);
      SaveBar(fubo, tick, 1);
      DealBar(fubo, tick, 1);
      */
      /*
      for(int i=0; i<50; ++i) {
        if(fubo->pBaBo[i] == nullptr) {
          continue;
        }
        DealBar(fubo, tick, i);
      }
      */
    }
  }

}

} // end namespace uBEE
