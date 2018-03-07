#include "../ctp/ThostFtdcMdApi.h"
#include <uWS/uWS.h>
#include "MdSpi.h"
#include "Bars.h"
#include "FuList.h"
#include <map>
#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

namespace uBEE
{

char FRONT_ADDR[] = "tcp://180.168.146.187:10011";		// 前置地址
CThostFtdcMdApi* pUserApi; // UserApi对象
uWS::Group<uWS::SERVER> * sg;

void MdCtp(uWS::Group<uWS::SERVER> * new_sg)
{
  sg = new_sg;
  //ppInstrumentID[0] = &aa[0];
  //ppInstrumentID[1] = &bb[0];

  /*
  // 获取日期 .......................................................
  int y,m,d;
  time_t rawtime;
  struct tm *ptminfo;
  time(&rawtime);
  ptminfo = localtime(&rawtime);

  printf("current: %02d-%02d-%02d %02d:%02d:%02d\n",
         ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday,
         ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);

  y = ptminfo->tm_year + 1900 ;
  m = ptminfo->tm_mon + 1 ;
  d = ptminfo->tm_mday ;

  // 生成 future list ...............................................
  uBEE::FuList fl;
  int rtn = fl.Init(y,m,d);
  if(rtn < 0) {
    exit(-1);
  }

  // 初始化 期货列表 ... ppInstrumentID .................begin.......
  for(int i = 0; i< FUTURE_NUMBER; i++) {
    ppInstrumentID[i] = nullptr ;
    if(fl.pc_futures[i] == nullptr) {
      iInstrumentID = i;                         // 最大订阅合约数
      break ;
    }
    ppInstrumentID[i] = fl.pc_futures[i] ;
  }
  for(int i = 0; i< FUTURE_NUMBER; i++) {
    if(ppInstrumentID[i] == nullptr) {
      break ;
    }
    std::cout << "=============:" << ppInstrumentID[i] << std::endl;
  }

  /
  for(int i = 0; i< DCE_NUMBER; i++) {
    ppInstrumentID[i] = nullptr ;
    if(fl.pShfeList[i] == nullptr) {
      iInstrumentID = i;
      break ;
    }
    ppInstrumentID[i] = fl.pShfeList[i] ;
  }
  for(int i = 0; i< DCE_NUMBER; i++) {
    if(ppInstrumentID[i] == nullptr) {
      break ;
    }
    std::cout << "=============:" << ppInstrumentID[i] << std::endl;
  }
  /
  // 初始化 期货列表 ... ppInstrumentID .................end........


  // for testing !!
  /
  while(1) {
    sg->broadcast("hahaha", 6, uWS::OpCode::TEXT);
    sleep(1);
  }
  /
  


  // ...... 初始化 交易时间对象 ...................................
  uBEE::TradingTime tt ;

  // ...... 初始化 期货 block FuBlockMap ..........................
  for(int i = 0; i< FUTURE_NUMBER; i++) {
    if(fl.pc_futures[i] == nullptr) {
      break ;
    }
    uBEE::FuBlock fb;
    fb.Init(&fb.Block, fl.pc_futures[i], &tt.t_hours[0]);
    FuBlockMap.insert(std::pair<std::string,uBEE::FuBlock>(fl.pc_futures[i],fb));
  }
  */

  // ......  创建 pUserApi 并初始化................................
  pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();

  // ......  创建 pUserSpi 并初始化................................
  //CThostFtdcMdSpi* pUserSpi = new CMdSpi();
  CMdSpi * pUserSpi = new CMdSpi();
  //pUserSpi->Init(1001);
  pUserSpi->set_SG(new_sg);

  // ..............................................................
  pUserApi->RegisterSpi(pUserSpi);						// 注册事件类
  pUserApi->RegisterFront(FRONT_ADDR);					// connect
  pUserApi->Init();
  pUserApi->Join();
  pUserApi->Release();
}

} // end namespace uBEE
