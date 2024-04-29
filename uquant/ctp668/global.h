#pragma once
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

#include "DataCollect.h"
#include "base/gb_x_utf8.h"
#include "base/ini_reader.h"
#include "ctp/ThostFtdcMdApi.h"
#include "ctp/ThostFtdcTraderApi.h"
// #include "getconfig.h"
#include "time.h"
#include "traderApi.h"
#include "traderSpi.h"

using namespace std;
FILE *logfile;

char ErrMsg[1024];

// 报单录入操作是否完成的标志
// Create a manual reset event with no signal
// HANDLE g_hEvent = CreateEvent(NULL, false, false, NULL);
/// 会员代码
TThostFtdcBrokerIDType g_chBrokerID;
/// 交易用户代码
TThostFtdcUserIDType g_chUserID;
/// 交易用户密码
TThostFtdcPasswordType g_chPassword;
/// 交易所代码
TThostFtdcExchangeIDType g_chExchangeID;
/// 合约代码
TThostFtdcInstrumentIDType g_chInstrumentID;
/// 投资者代码
TThostFtdcInvestorIDType g_chInvestorID;
/// 预埋撤单编号
TThostFtdcParkedOrderActionIDType g_chParkedOrderActionID1;
/// 预埋报单编号
TThostFtdcParkedOrderIDType g_chParkedOrderID1;
/// 报单引用
TThostFtdcOrderRefType g_chOrderRef;
/// 前置编号
TThostFtdcFrontIDType g_chFrontID;
/// 会话编号
TThostFtdcSessionIDType g_chSessionID;
/// 报单编号
TThostFtdcOrderSysIDType g_chOrderSysID;
/// 止损价
TThostFtdcPriceType g_chStopPrice;
/// 报价引用
TThostFtdcOrderRefType g_chQuoteRef;
int FrontID = 0;
int SessionID = 0;
int Limitprice = 0;
int nRequestID = 0;
int chioce_action = 0;  // 为0则全部报
int OrderRef_num = 0;

vector<string> vector_OrderSysID;
vector<string> vector_ExchangeID;
vector<string> vector_InstrumentID;
vector<string> vector_OrderRef;
vector<int> vector_FrontID;
vector<int> vector_SessionID;
vector<string> md_InstrumentID;
int action_number;

/// 执行宣告引用
TThostFtdcOrderRefType g_NewExecOrderRef;
/// 执行宣告编号
TThostFtdcExecOrderSysIDType g_NewExecOrderSysID;
/// 前置编号
TThostFtdcFrontIDType g_NewFrontID;
/// 会话编号
TThostFtdcSessionIDType g_NewSessionID;

// 期权自对冲响应通知
/// 期权自对冲编号
TThostFtdcOrderSysIDType g_chOptionSelfCloseSysID;
/// 期权自对冲引用
TThostFtdcOrderRefType g_chOptionSelfCloseRef;
/// 用户端产品信息
TThostFtdcProductInfoType g_chUserProductInfo;
/// 认证码
TThostFtdcAuthCodeType g_chAuthCode;
/// App代码
TThostFtdcAppIDType g_chAppID;

// HANDLE xinhao = CreateEvent(NULL, false, false, NULL);

CTraderApi *pUserApi = new CTraderApi;
