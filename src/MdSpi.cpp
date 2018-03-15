//#include "../ctp/ThostFtdcMdApi.h"
#include "FuList.h"
#include "MdSpi.h"
#include "Bars.h"
#include "Psqlpool.h"
#include "PsqlFunc.h"
#include <uWS/uWS.h>
#include <string.h>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <map>

namespace uBEE
{
using namespace std;

//------- from MdCtp.cpp ----------------begin ----------
extern CThostFtdcMdApi* pUserApi;
extern uWS::Group<uWS::SERVER> * sg;
//------- from MdCtp.cpp ---------------- end ----------

TThostFtdcBrokerIDType  BROKER_ID = "9999";         // ���͹�˾����
TThostFtdcInvestorIDType INVESTOR_ID = "059979";        // Ͷ���ߴ���
TThostFtdcPasswordType  PASSWORD = "123456";            // �û�����

char *ppInstrumentID[FUTURE_NUMBER];                             // �ڻ�ID
int iInstrumentID;                                      // ���ĵ��ڻ�����
int iRequestID;

std::map<std::string,uBEE::FuBlock> FuBlockMap;     // ÿ���ڻ�һ�� FuBlock������һ��MAP
std::map<std::string,uBEE::FuBo>    M_FuBo;         // ÿ���ڻ�һ�� FuBlock������һ��MAP

std::shared_ptr<uBEE::DBPool> dbpool;
uBEE::TradingTime             *tt;
//uBEE::TimeBlock               *tmbo;
uBEE::FuList                  *fl;
uBEE::TimeBlock               *tb;
//------- ----------------- ----------------  ----------

CMdSpi::CMdSpi()
{
  Init();
}

void CMdSpi::Init()
{
  // ��ȡ���� .......................................................
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

  // ���� future list ...............................................
  fl = new uBEE::FuList();
  int rtn = fl->Init(y,m,d);
  if(rtn < 0) {
    std::cout << "fl->Init error!!!!!!" << std::endl;
    exit(-1);
  }

  // ��ʼ�� �ڻ��б� ... ppInstrumentID .................begin.......
  for(int i = 0; i< FUTURE_NUMBER; i++) {
    ppInstrumentID[i] = nullptr ;
  }
  for(int i = 0; i< FUTURE_NUMBER; i++) {
    if(fl->pc_futures[i] == nullptr) {
      iInstrumentID = i;                         // ����ĺ�Լ��
      break ;
    }
    ppInstrumentID[i] = fl->pc_futures[i] ;
  }

  // ---- for testing begin ---------------------------------------
  for(int i = 0; i< FUTURE_NUMBER; i++) {
    if(ppInstrumentID[i] == nullptr) {
      break ;
    }
    std::cout << "=============:" << ppInstrumentID[i] << std::endl;
  }
  // ---- for testing end  ---------------------------------------

  // ...... ��ʼ�� ����ʱ����� ...................................
  tt = new uBEE::TradingTime() ;
  tb = new uBEE::TimeBlock();

  // ---- for testing begin ---------------------------------------
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
  // ---- for testing end  ---------------------------------------


  // ...... ��ʼ�� �ڻ� block FuBlockMap ... .......................
  dbpool = std::make_shared<uBEE::DBPool>();
  for(int i = 0; i< FUTURE_NUMBER; i++) {
    if(fl->pc_futures[i] == nullptr) {
      break ;
    }
    //uBEE::FuBlock fb;
    uBEE::FuBlock *fb = new uBEE::FuBlock();
    fb->dbpool = dbpool;
    fb->Init(&fb->Block, fl->pc_futures[i], &tt->t_hours[0]);
    fb->Block.pTimeType = & tb->TT[fb->Block.pt_hour->i_hour_type];
    std::cout << " befor fb->Init  + map hahah3 ------------\n" ;
    //uBEE::createTickTable(dbpool,fl->pc_futures[i]);
    std::cout << " befor fb->Init  + map hahah4 ------------\n" ;
    // !!! map ��Ϊ��Ա���������⣬���Ըĳ���ȫ�ֱ�����
    FuBlockMap.insert(std::pair<std::string,uBEE::FuBlock>(fl->pc_futures[i], *fb));
    std::cout << " after fb->Init  + map hahah ------------\n" ;

    int fr[5] = {19,60,180,300,600};
    uBEE::FuBo *fubo = new uBEE::FuBo(fl->pc_futures[i],tb,&fr[0], 5); 
    M_FuBo.insert(std::pair<std::string,uBEE::FuBo>(fl->pc_futures[i], *fubo));

  }
  exit(0);
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
  /*
  map<std::string,uBEE::FuBlock>::iterator it;
  it = FuBlockMap.begin();
  while(it != FuBlockMap.end()) {
    std::cout << "......:" << it->first << ":"<< it->second.Block.i_hour_type << std::endl;
    //it->first;
    //it->second;
    it ++;
  }
  //exit(-1);
  */


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
  //int iResult = pUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
  int iResult = pUserApi->SubscribeMarketData(fl->pc_futures, iInstrumentID);
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

void CMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *tick)
{
  time_t t = time(0);
  char currentTime[25];
  strftime(currentTime, sizeof(currentTime), "%Y/%m/%d %X",localtime(&t));


  map<std::string,uBEE::FuBlock>::iterator it;
  it=FuBlockMap.find(tick->InstrumentID);
  if(it==FuBlockMap.end())
    std::cout<<"we do not find :"<< tick->InstrumentID <<std::endl;
  else {
    cout << "DateTime " << currentTime <<
         " ID is " << tick->InstrumentID <<
         " Lastprice is " << tick->LastPrice <<
         " time_type is " << it->second.Block.i_hour_type << endl;
    see_handle_bars(&(it->second.Block), tick);
    see_handle_bars(&(it->second.Block), tick);
  }

  map<std::string,uBEE::FuBo>::iterator iter;
  iter=M_FuBo.find(tick->InstrumentID);  
  if(iter==M_FuBo.end())
    std::cout<<"we do not find :"<< tick->InstrumentID <<std::endl;
  else {
    DealBar(&(iter->second), tick,2);
  }
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
