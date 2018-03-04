#include "../ctp/ThostFtdcMdApi.h"
#include <uWS/uWS.h>
#include "MdSpi.h"
#include "Bars.h"
#include <map>
#include <string>

namespace uBEE
{

CThostFtdcMdApi* pUserApi; // UserApi对象

char FRONT_ADDR[] = "tcp://180.168.146.187:10011";		// 前置地址
TThostFtdcBrokerIDType	BROKER_ID = "9999";			// 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "059979";		// 投资者代码
TThostFtdcPasswordType  PASSWORD = "123456";			// 用户密码
//char *ppInstrumentID[] = {"ru1805", "ag1806"};			// 行情订阅列表
char aa[] = "ru1805";
char bb[] = "ag1806";
char *ppInstrumentID[100];			// 行情订阅列表
int iInstrumentID = 2;						// 行情订阅数量
int iRequestID = 0;                                     // 请求编号
uWS::Group<uWS::SERVER> * sg;
uWS::Group<uWS::CLIENT> * cg;

void MdCtp(uWS::Group<uWS::SERVER> * new_sg)
{
  sg = new_sg;
  ppInstrumentID[0] = &aa[0];
  ppInstrumentID[1] = &bb[0];
  /*
  while(1) {
    sg->broadcast("hahaha", 6, uWS::OpCode::TEXT);
    sleep(1);
  }
  */

  uBEE::TradingTime tt ;
  std::map<std::string,uBEE::FuBlock> fb_map;
  uBEE::FuBlock fb1 ;
  uBEE::FuBlock fb2 ;
  fb_map.insert(std::pair<std::string,uBEE::FuBlock>("root",fb1)); 
  fb_map.insert(std::pair<std::string,uBEE::FuBlock>("boot",fb1)); 
  

  pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// 创建UserApi

  //CThostFtdcMdSpi* pUserSpi = new CMdSpi();
  CMdSpi * pUserSpi = new CMdSpi();
  pUserSpi->Init(1001);
  pUserApi->RegisterSpi(pUserSpi);						// 注册事件类
  pUserApi->RegisterFront(FRONT_ADDR);					// connect
  pUserApi->Init();
  pUserApi->Join();
  pUserApi->Release();
}

} // end namespace uBEE
