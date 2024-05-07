#ifndef UBEE_GLOBAL_H
#define UBEE_GLOBAL_H

#include <stdio.h>
#include <string.h>
#include <time.h>

#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "Bars.h"
#include "base/error_log.h"
#include "base/ini_reader.h"
#include "base/spmc_queue.h"
#include "ctp/ThostFtdcMdApi.h"
#include "ctp/ThostFtdcTraderApi.h"
#include "ctp_DataCollect.h"
#include "ctp_traderApi.h"
#include "ctp_traderSpi.h"
#include "libdeflate.h"

namespace uBEE {
#define T________ 1

#define FUTRUE_ID_LEN 81

typedef char FrontAddr[128];
typedef char FrontMdAddr[128];

// ------------------------------------------------------------
extern uBEE::TimeBlock *g_time_block;

// 每个future有一个 future_block: uBEE::FutureBlock
extern std::map<std::string, uBEE::FutureBlock *> map_futures_block;
// extern uWS::Group<uWS::SERVER> *sg;
extern int InitAll();
extern int ConfigInit(const char *config_ini);
extern int InitFuturesBlock();

extern FILE *logfile;
extern std::string g_file_instruments;

extern std::atomic<size_t> g_count;

extern struct libdeflate_compressor *g_compressor;

using TickQueue = SPMCQueue<CThostFtdcDepthMarketDataField, 1024>;
extern TickQueue *g_tick_queue;
// ------------------------------------------------------------

extern CThostFtdcReqUserLoginField g_reqUserLogin;     // 用户登录请求
extern CThostFtdcReqAuthenticateField g_authenticate;  //  客户端认证请求

extern FrontAddr g_front_addr;
extern FrontMdAddr g_front_mdaddr;

// 报单录入操作是否完成的标志
// Create a manual reset event with no signal
// HANDLE g_hEvent = CreateEvent(NULL, false, false, NULL);
/// 会员代码
extern TThostFtdcBrokerIDType g_chBrokerID;
/// 交易用户代码
extern TThostFtdcUserIDType g_chUserID;
/// 交易用户密码
extern TThostFtdcPasswordType g_chPassword;
/// 交易所代码
extern TThostFtdcExchangeIDType g_chExchangeID;
/// 合约代码
extern TThostFtdcInstrumentIDType g_chInstrumentID;
/// 投资者代码
extern TThostFtdcInvestorIDType g_chInvestorID;
/// 预埋撤单编号
extern TThostFtdcParkedOrderActionIDType g_chParkedOrderActionID1;
/// 预埋报单编号
extern TThostFtdcParkedOrderIDType g_chParkedOrderID1;
/// 报单引用
extern TThostFtdcOrderRefType g_chOrderRef;
/// 前置编号
extern TThostFtdcFrontIDType g_chFrontID;
/// 会话编号
extern TThostFtdcSessionIDType g_chSessionID;
/// 报单编号
extern TThostFtdcOrderSysIDType g_chOrderSysID;
/// 止损价
extern TThostFtdcPriceType g_chStopPrice;
/// 报价引用
extern TThostFtdcOrderRefType g_chQuoteRef;
extern int FrontID;
extern int SessionID;
extern int Limitprice;
extern int nRequestID;
extern int chioce_action;  // 为0则全部报
extern int OrderRef_num;

extern std::vector<std::string> vector_OrderSysID;
extern std::vector<std::string> vector_ExchangeID;
extern std::vector<std::string> vector_InstrumentID;
extern std::vector<std::string> vector_OrderRef;
extern std::vector<int> vector_FrontID;
extern std::vector<int> vector_SessionID;
extern std::vector<std::string> md_InstrumentID;  // 合约vector
extern int action_number;

/// 执行宣告引用
extern TThostFtdcOrderRefType g_NewExecOrderRef;
/// 执行宣告编号
extern TThostFtdcExecOrderSysIDType g_NewExecOrderSysID;
/// 前置编号
extern TThostFtdcFrontIDType g_NewFrontID;
/// 会话编号
extern TThostFtdcSessionIDType g_NewSessionID;

// 期权自对冲响应通知
/// 期权自对冲编号
extern TThostFtdcOrderSysIDType g_chOptionSelfCloseSysID;
/// 期权自对冲引用
extern TThostFtdcOrderRefType g_chOptionSelfCloseRef;
/// 用户端产品信息
extern TThostFtdcProductInfoType g_chUserProductInfo;
/// 认证码
extern TThostFtdcAuthCodeType g_chAuthCode;
/// App代码
extern TThostFtdcAppIDType g_chAppID;

}  // namespace uBEE

#endif  // UBEE_GLOBAL_H
