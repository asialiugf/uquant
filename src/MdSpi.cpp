#include "MdSpi.h"
#include "Bars.h"
#include <uWS/uWS.h>
#include <string.h>
#include <iostream>
#include <ctime>

namespace uBEE
{
using namespace std;

extern CThostFtdcMdApi* pUserApi;
extern char FRONT_ADDR[];
extern TThostFtdcBrokerIDType	BROKER_ID;
extern TThostFtdcInvestorIDType INVESTOR_ID;
extern TThostFtdcPasswordType	PASSWORD;
extern char* ppInstrumentID[];
extern int iInstrumentID;
extern int iRequestID;
extern uWS::Group<uWS::SERVER> * sg;
//extern uWS::Group<uWS::CLIENT> * cg;
extern std::map<std::string,uBEE::FuBlock> FuBlockMap;

void CMdSpi::Init(int a)
{
  x = a;
}

void CMdSpi::set_SG(uWS::Group<uWS::SERVER> * sg)
{
  m_SG = sg ;
}

void CMdSpi::set_InstrumentID(char *pp[])
{
  // ��Ҫ�޸ģ�
  //m_ppInstrumentID = pp ;
}

void CMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo,
                        int nRequestID, bool bIsLast)
{
  cerr << "--->>> "<< "OnRspError" << endl;
  IsErrorRspInfo(pRspInfo);
}

void CMdSpi::OnFrontDisconnected(int nReason)
{
  cerr << "--->>> " << "OnFrontDisconnected" << endl;
  cerr << "--->>> Reason = " << nReason << endl;
}

void CMdSpi::OnHeartBeatWarning(int nTimeLapse)
{
  cerr << "--->>> " << "OnHeartBeatWarning" << endl;
  cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
}

void CMdSpi::OnFrontConnected()
{
  cerr << "--->>> " << "OnFrontConnected" << endl;
  // �û���¼����
  // --- testing ----------------------------------
  std::cout << "uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu:" << x << std::endl;
  map<std::string,uBEE::FuBlock>::iterator it;
  it = FuBlockMap.begin();
  while(it != FuBlockMap.end()) {
    std::cout << "......:" << it->first << ":"<< it->second.Block.i_hour_type << std::endl;
    //it->first;
    //it->second;
    it ++;
  }
  //exit(-1);
  // --- testing ----------------------------------

  ReqUserLogin();
}

void CMdSpi::ReqUserLogin()
{
  CThostFtdcReqUserLoginField req;
  memset(&req, 0, sizeof(req));
  strcpy(req.BrokerID, BROKER_ID);
  strcpy(req.UserID, INVESTOR_ID);
  strcpy(req.Password, PASSWORD);
  int iResult = pUserApi->ReqUserLogin(&req, ++iRequestID);
  cerr << "--->>> �����û���¼����: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
  /*
  while(1) {
    sg->broadcast("hahaha", 7, uWS::OpCode::TEXT);
    sleep(1);
  }
  */
}

void CMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  cerr << "--->>> " << "OnRspUserLogin" << endl;
  if(bIsLast && !IsErrorRspInfo(pRspInfo)) {
    ///��ȡ��ǰ������
    cerr << "--->>> ��ȡ��ǰ������ = " << pUserApi->GetTradingDay() << endl;
    // ����������
    SubscribeMarketData();
  }
}

void CMdSpi::SubscribeMarketData()
{
  int iResult = pUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
  cerr << "--->>> �������鶩������: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void CMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  cout << "OnRspSubMarketData instrumentId is " << pSpecificInstrument->InstrumentID << endl;
}

void CMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
  cerr << "OnRspUnSubMarketData" << endl;
}

void CMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
  time_t t = time(0);
  char currentTime[25];
  strftime(currentTime, sizeof(currentTime), "%Y/%m/%d %X",localtime(&t));
  cout << "OnRtnDepthMarketData " << currentTime <<
       "instrumentId is " << pDepthMarketData->InstrumentID <<
       " Lastprice is " << pDepthMarketData->LastPrice << endl;
}

bool CMdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
  // ���ErrorID != 0, ˵���յ��˴������Ӧ
  bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
  if(bResult)
    cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
  return bResult;
}
} //end namespace
