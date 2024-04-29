#include <iostream>

#include "Bars.h"
#include "global.h"

namespace uBEE {

// todo
//  这里需要重新处理要参考以前的  MdSpi.cpp

// std::map<std::string, uBEE::FuBo *> M_CtpFuBo;  // 每个期货一个 FuBo，future block 构成一个MAP

// 行情类
class CSimpleMdHandler : public CThostFtdcMdSpi {
   public:
    // 构造函数，需要一个有效的指向CThostFtdcMduserApi实例的指针
    CSimpleMdHandler(CThostFtdcMdApi *pUserApi) : m_pUserMdApi(pUserApi) {}
    ~CSimpleMdHandler() {}
    // 当客户端与交易托管系统建立起通信连接，客户端需要进行登录
    void deletemyself() { delete this; }

    virtual void OnFrontConnected() {
        INIReader reader("./config.ini");
        if (reader.ParseError() < 0) {
            std::cout << "open ini file failed." << std::endl;
        }
        strcpy(g_chBrokerID, reader.Get("config", "BrokerID", "").c_str());
        strcpy(g_chUserID, reader.Get("config", "UserID", "").c_str());
        strcpy(g_chPassword, reader.Get("config", "Password", "").c_str());

        std::cout << g_chBrokerID << std::endl;
        std::cout << g_chUserID << std::endl;
        std::cout << g_chPassword << std::endl;

        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "CThostFtdcMdSpi thread : ---------  " << this_id
                  << " sleeping...OnFrontConnected\n";

        // SetEvent(xinhao);
        printf("<OnFrontConnected>\n");
        printf("</OnFrontConnected>\n");

        // SetEvent(xinhao);
        // ReqUserLogin();
    }

    void RegisterFensUserInfo() {
        INIReader reader("./config.ini");

        // strcpy(g_chBrokerID, getConfig("config", "BrokerID").c_str());
        // strcpy(g_chUserID, getConfig("config", "UserID").c_str());
        CThostFtdcFensUserInfoField pFens = {0};
        // strcpy(pFens.BrokerID, g_chBrokerID);
        // strcpy(pFens.UserID, g_chUserID);

        strcpy(pFens.BrokerID, reader.Get("config", "BrokerID", "").c_str());
        strcpy(pFens.UserID, reader.Get("config", "UserID", "").c_str());

        pFens.LoginMode = THOST_FTDC_LM_Trade;
        m_pUserMdApi->RegisterFensUserInfo(&pFens);
    }

    void ReqUserLogin() {
        std::cout << "【enter】 ctp_mduser_spi.h  ReqUserLogin() \n";

        std::cout << g_reqUserLogin.BrokerID << std::endl;
        std::cout << g_reqUserLogin.UserID << std::endl;
        std::cout << g_reqUserLogin.Password << std::endl;

        int num = m_pUserMdApi->ReqUserLogin(&g_reqUserLogin, 1);

        printf("\tlogin num = %d\n", num);

        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "thread in ReqUserLogin : --------- :  " << this_id << "\n";
    }

    void ReqUserLogout() {
        CThostFtdcUserLogoutField a = {0};
        strcpy(a.BrokerID, g_chBrokerID);
        strcpy(a.UserID, g_chUserID);
        int num = m_pUserMdApi->ReqUserLogout(&a, 1);
        printf("\tlogout num = %d\n", num);
    }

    virtual void OnHeartBeatWarning(int nTimeLapse) {
        printf("<OnHeartBeatWarning>\n");
        printf("\tnTimeLapse [%d]\n", nTimeLapse);
        printf("</OnHeartBeatWarning>\n");
    }

    // 当客户端与交易托管系统通信连接断开时，该方法被调用
    virtual void OnFrontDisconnected(int nReason) {
        // 当发生这个情况后，API会自动重新连接，客户端可不做处理
        printf("<OnFrontDisconnected>\n");
        printf("\tnReason= = [%d]", nReason);
        printf("</OnFrontDisconnected>\n");
    }

    // 当客户端发出登录请求之后，该方法会被调用，通知客户端登录是否成功
    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                                CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        printf("<OnRspUserLogin>\n");
        if (pRspUserLogin) {
            printf("\tTradingDay [%s]\n", pRspUserLogin->TradingDay);
            printf("\tLoginTime [%s]\n", pRspUserLogin->LoginTime);
            printf("\tBrokerID [%s]\n", pRspUserLogin->BrokerID);
            printf("\tUserID [%s]\n", pRspUserLogin->UserID);
            printf("\tSystemName [%s]\n", pRspUserLogin->SystemName);
            printf("\tMaxOrderRef [%s]\n", pRspUserLogin->MaxOrderRef);
            printf("\tSHFETime [%s]\n", pRspUserLogin->SHFETime);
            printf("\tDCETime [%s]\n", pRspUserLogin->DCETime);
            printf("\tCZCETime [%s]\n", pRspUserLogin->CZCETime);
            printf("\tFFEXTime [%s]\n", pRspUserLogin->FFEXTime);
            printf("\tINETime [%s]\n", pRspUserLogin->INETime);
            printf("\tFrontID [%d]\n", pRspUserLogin->FrontID);
            printf("\tSessionID [%d]\n", pRspUserLogin->SessionID);
        }
        if (pRspInfo) {
            printf("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
            printf("\tErrorID [%d]\n", pRspInfo->ErrorID);
        }
        printf("\tnRequestID [%d]\n", nRequestID);
        printf("\tbIsLast [%d]\n", bIsLast);

        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "thread OnRspUserLogin : --------- : " << this_id << "\n";

        printf("</OnRspUserLogin>\n");
        if (pRspInfo->ErrorID != 0) {
            // 端登失败，客户端需进行错误处理
            printf(
                "\tFailed to login, errorcode=%d errormsg=%s requestid=%d "
                "chain = %d",
                pRspInfo->ErrorID, pRspInfo->ErrorMsg, nRequestID, bIsLast);
            std::cin.get();
            std::cin.ignore();
            exit(-1);
        }
        // SetEvent(xinhao);
    }

    /// 登出请求响应
    virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,
                                 CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
        printf("<OnRspUserLogout>\n");
        if (pUserLogout) {
            printf("\tBrokerID [%s]\n", pUserLogout->BrokerID);
            printf("\tUserID [%s]\n", pUserLogout->UserID);
        }
        if (pRspInfo) {
            printf("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
            printf("\tErrorID [%d]\n", pRspInfo->ErrorID);
        }
        printf("\tnRequestID [%d]\n", nRequestID);
        printf("\tbIsLast [%d]\n", bIsLast);
        printf("</OnRspUserLogout>\n");
        // SetEvent(xinhao);
        // pUserApi->Release();
    }

    void UnSubscribeMarketData() {
        int md_num = 0;
        char **ppInstrumentID = new char *[5000];
        for (int count1 = 0; count1 <= md_InstrumentID.size() / 500; count1++) {
            if (count1 < md_InstrumentID.size() / 500) {
                int a = 0;
                for (a = 0; a < 500; a++) {
                    ppInstrumentID[a] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
                    md_num++;
                }
                int result = m_pUserMdApi->UnSubscribeMarketData(ppInstrumentID, a);
                printf((result == 0) ? "退订行情请求1......发送成功\n"
                                     : "退订行情请求1......发送失败，错误序号=[%d]\n",
                       result);
            } else if (count1 == md_InstrumentID.size() / 500) {
                int count2 = 0;
                for (count2 = 0; count2 < md_InstrumentID.size() % 500; count2++) {
                    ppInstrumentID[count2] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
                    md_num++;
                }
                int result = m_pUserMdApi->UnSubscribeMarketData(ppInstrumentID, count2);
                printf((result == 0) ? "退订行情请求2......发送成功\n"
                                     : "退订行情请求2......发送失败，错误序号=[%d]\n",
                       result);
            }
        }
    }

    virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                      CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                                      bool bIsLast) {
        printf("<OnRspUnSubMarketData>\n");
        if (pSpecificInstrument) {
            printf("\tInstrumentID [%s]\n", pSpecificInstrument->InstrumentID);
        }
        if (pRspInfo) {
            printf("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
            printf("\tErrorID [%d]\n", pRspInfo->ErrorID);
        }
        printf("\tnRequestID [%d]\n", nRequestID);
        printf("\tbIsLast [%d]\n", bIsLast);
        printf("</OnRspUnSubMarketData>\n");
        if (bIsLast) {
            // SetEvent(xinhao);
        }
    };

    /*
    void SubscribeMarketData()  // 收行情
    {
        char **ppInstrumentID = new char *[10];
        for (size_t x{0}; x < 10; x++) {
            ppInstrumentID[x] = nullptr;
        }
        ppInstrumentID[0] = const_cast<char *>("fu2305");
        // ppInstrumentID[1] = const_cast<char *>("fu2305");

        uBEE::FuBo *fubo = new uBEE::FuBo("fu2305", tb);  // every future has a fubo: future block !
        M_CtpFuBo.insert(std::pair<std::string, uBEE::FuBo *>("fu2305", fubo));

        int result = m_pUserMdApi->SubscribeMarketData(ppInstrumentID, 1);
        printf((result == 0) ? "订阅行情请求2......发送成功\n" :
    "订阅行情请求2......发送失败，错误序号=[%d]\n", result);
    }
    */

    void SubscribeMarketData()  // 收行情
    {
        int md_num = 0;
        char **ppInstrumentID = new char *[5000];
        for (int count1 = 0; count1 <= md_InstrumentID.size() / 500; count1++) {
            if (count1 < md_InstrumentID.size() / 500) {
                int a = 0;
                for (a = 0; a < 500; a++) {
                    ppInstrumentID[a] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
                    md_num++;
                }
                int result = m_pUserMdApi->SubscribeMarketData(ppInstrumentID, a);
                printf((result == 0) ? "订阅行情请求1......发送成功\n"
                                     : "订阅行情请求1......发送失败，错误序号=[%d]\n",
                       result);
            } else if (count1 == md_InstrumentID.size() / 500) {
                int count2 = 0;
                for (count2 = 0; count2 < md_InstrumentID.size() % 500; count2++) {
                    ppInstrumentID[count2] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
                    md_num++;
                }
                int result = m_pUserMdApi->SubscribeMarketData(ppInstrumentID, count2);
                printf((result == 0) ? "订阅行情请求2......发送成功\n"
                                     : "订阅行情请求2......发送失败，错误序号=[%d]\n",
                       result);
            }
        }
    }

    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                    CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                                    bool bIsLast) {
        printf("<OnRspSubMarketData>\n");
        if (pSpecificInstrument) {
            printf("\tInstrumentID [%s]\n", pSpecificInstrument->InstrumentID);
        }
        if (pRspInfo) {
            printf("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
            printf("\tErrorID [%d]\n", pRspInfo->ErrorID);
        }
        printf("\tnRequestID [%d]\n", nRequestID);
        printf("\tbIsLast [%d]\n", bIsLast);
        printf("</OnRspSubMarketData>\n");
        if (bIsLast) {
            usleep(2000000);
            // SetEvent(xinhao);
        }
    };

    /// 深度行情通知
    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
        // 获取系统时间
        // SYSTEMTIME sys;
        // GetLocalTime(&sys);
        // printf("%02d:%02d:%02d.%03d\t", sys.wHour, sys.wMinute, sys.wSecond,
        // sys.wMilliseconds);
        // printf("<OnRtnDepthMarketData> before !");

        // std::thread::id this_id = std::this_thread::get_id();
        // std::cout << " CThostFtdcMdSpi thread OnRtnDepthMarketData :" << this_id << "\n";

        if (pDepthMarketData) {
            g_tick_queue->push([&pDepthMarketData](CThostFtdcDepthMarketDataField &msg) {
                memcpy(&msg, pDepthMarketData, sizeof(CThostFtdcDepthMarketDataField));
            });
            // SaveTick(pDepthMarketData);
            // printf("\tTradingDay [%s]  ", pDepthMarketData->TradingDay);
            // printf("\tInstrumentID [%s]  ", pDepthMarketData->InstrumentID);
            // printf("\tExchangeID [%s] ", pDepthMarketData->ExchangeID);
            // printf("\tExchangeInstID [%s]\n", pDepthMarketData->ExchangeInstID);
            // printf("\tUpdateTime [%s]  ", pDepthMarketData->UpdateTime);
            // printf("\tActionDay [%s]  ", pDepthMarketData->ActionDay);
            /*
            printf("\tVolume [%d]  ", pDepthMarketData->Volume);
            printf("\tUpdateMillisec [%d]  ", pDepthMarketData->UpdateMillisec);
            printf("\tBidVolume1 [%d]  ", pDepthMarketData->BidVolume1);
            printf("\tAskVolume1 [%d]  ", pDepthMarketData->AskVolume1);
            printf("\tBidVolume2 [%d]  ", pDepthMarketData->BidVolume2);
            printf("\tAskVolume2 [%d]  ", pDepthMarketData->AskVolume2);
            printf("\tBidVolume3 [%d]  ", pDepthMarketData->BidVolume3);
            printf("\tAskVolume3 [%d]  ", pDepthMarketData->AskVolume3);
            printf("\tBidVolume4 [%d]  ", pDepthMarketData->BidVolume4);
            printf("\tAskVolume4 [%d]  ", pDepthMarketData->AskVolume4);
            printf("\tBidVolume5 [%d]  ", pDepthMarketData->BidVolume5);
            printf("\tAskVolume5 [%d]  ", pDepthMarketData->AskVolume5);
            printf("\tLastPrice [%.2lf]  ", (pDepthMarketData->LastPrice > 10000000) ? 0 :
            pDepthMarketData->LastPrice); printf("\tPreSettlementPrice [%.8lf]\n",
                   (pDepthMarketData->PreSettlementPrice > 10000000) ? 0 :
            pDepthMarketData->PreSettlementPrice); printf("\tPreClosePrice
                       [% .8lf]\n ", (pDepthMarketData->PreClosePrice > 10000000) ? 0 :
                   pDepthMarketData->PreClosePrice);
            printf("\tPreOpenInterest
                       [% .8lf]\n ", (pDepthMarketData->PreOpenInterest > 10000000) ? 0 :
                   pDepthMarketData->PreOpenInterest);
            printf("\tOpenPrice [%.8lf]\n", (pDepthMarketData->OpenPrice > 10000000) ? 0 :
            pDepthMarketData->OpenPrice); printf("\tHighestPrice [%.8lf]\n",
            (pDepthMarketData->HighestPrice > 10000000) ? 0 : pDepthMarketData->HighestPrice);
            printf("\tLowestPrice [%.8lf]\n", (pDepthMarketData->LowestPrice > 10000000) ? 0 :
            pDepthMarketData->LowestPrice); printf("\tTurnover [%.8lf]\n",
            (pDepthMarketData->Turnover > 10000000) ? 0 : pDepthMarketData->Turnover);
            printf("\tOpenInterest [%.8lf]\n", (pDepthMarketData->OpenInterest > 10000000) ? 0 :
            pDepthMarketData->OpenInterest); printf("\tClosePrice [%.8lf]\n",
            (pDepthMarketData->ClosePrice > 10000000) ? 0 : pDepthMarketData->ClosePrice);
            printf("\tSettlementPrice [%.8lf]\n", (pDepthMarketData->SettlementPrice > 10000000) ? 0
            : pDepthMarketData->SettlementPrice); printf("\tUpperLimitPrice
                       [% .8lf]\n ", (pDepthMarketData->UpperLimitPrice > 10000000) ? 0 :
                   pDepthMarketData->UpperLimitPrice);
            printf("\tLowerLimitPrice
                       [% .8lf]\n ", (pDepthMarketData->LowerLimitPrice > 10000000) ? 0 :
                   pDepthMarketData->LowerLimitPrice);
            printf("\tPreDelta [%.8lf]\n", (pDepthMarketData->PreDelta > 10000000) ? 0 :
            pDepthMarketData->PreDelta); printf("\tCurrDelta [%.8lf]\n",
            (pDepthMarketData->CurrDelta > 10000000) ? 0 : pDepthMarketData->CurrDelta);
            printf("\tBidPrice1 [%.8lf]\n", (pDepthMarketData->BidPrice1 > 10000000) ? 0 :
            pDepthMarketData->BidPrice1); printf("\tAskPrice1 [%.8lf]\n",
            (pDepthMarketData->AskPrice1 > 10000000) ? 0 : pDepthMarketData->AskPrice1);
            printf("\tBidPrice2 [%.8lf]\n", (pDepthMarketData->BidPrice2 > 10000000) ? 0 :
            pDepthMarketData->BidPrice2); printf("\tAskPrice2 [%.8lf]\n",
            (pDepthMarketData->AskPrice2 > 10000000) ? 0 : pDepthMarketData->AskPrice2);
            printf("\tBidPrice3 [%.8lf]\n", (pDepthMarketData->BidPrice3 > 10000000) ? 0 :
            pDepthMarketData->BidPrice3); printf("\tAskPrice3 [%.8lf]\n",
            (pDepthMarketData->AskPrice3 > 10000000) ? 0 : pDepthMarketData->AskPrice3);
            printf("\tBidPrice4 [%.8lf]\n", (pDepthMarketData->BidPrice4 > 10000000) ? 0 :
            pDepthMarketData->BidPrice4); printf("\tAskPrice4 [%.8lf]\n",
            (pDepthMarketData->AskPrice4 > 10000000) ? 0 : pDepthMarketData->AskPrice4);
            printf("\tBidPrice5 [%.8lf]\n", (pDepthMarketData->BidPrice5 > 10000000) ? 0 :
            pDepthMarketData->BidPrice5); printf("\tAskPrice5 [%.8lf]\n",
            (pDepthMarketData->AskPrice5 > 10000000) ? 0 : pDepthMarketData->AskPrice5);
            printf("\tAveragePrice [%.8lf]\n", (pDepthMarketData->AveragePrice > 10000000) ? 0 :
            pDepthMarketData->AveragePrice);
            */
            /* 处理k_bar !!
            std::map<std::string, uBEE::FuBo *>::iterator iter;
            iter = M_CtpFuBo.find(pDepthMarketData->InstrumentID);
            if (iter == M_CtpFuBo.end())
                std::cout << "we do not find :" << pDepthMarketData->InstrumentID << std::endl;
            else {
                HandleTick(iter->second, pDepthMarketData, SEND_SAVE_ALL);
            }
            */
        }  // if(pDepthMarketData)
        // printf("</OnRtnDepthMarketData> after !\n");
    };

    /// 订阅询价请求
    void SubscribeForQuoteRsp() {
        int md_num = 0;
        char **ppInstrumentID = new char *[5000];
        for (int count1 = 0; count1 <= md_InstrumentID.size() / 500; count1++) {
            if (count1 < md_InstrumentID.size() / 500) {
                int a = 0;
                for (a = 0; a < 500; a++) {
                    ppInstrumentID[a] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
                    md_num++;
                }
                int result = m_pUserMdApi->SubscribeForQuoteRsp(ppInstrumentID, a);
                printf((result == 0) ? "订阅询价请求1......发送成功\n"
                                     : "订阅询价请求1......发送失败，错误序号=[%d]\n",
                       result);
            } else if (count1 == md_InstrumentID.size() / 500) {
                int count2 = 0;
                for (count2 = 0; count2 < md_InstrumentID.size() % 500; count2++) {
                    ppInstrumentID[count2] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
                    md_num++;
                }
                int result = m_pUserMdApi->SubscribeForQuoteRsp(ppInstrumentID, count2);
                printf((result == 0) ? "订阅询价请求2......发送成功\n"
                                     : "订阅询价请求2......发送失败，错误序号=[%d]\n",
                       result);
            }
        }
    }

    virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                     CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                                     bool bIsLast) {
        printf("<OnRspSubForQuoteRsp>\n");
        if (pSpecificInstrument) {
            printf("\tInstrumentID [%s]\n", pSpecificInstrument->InstrumentID);
        }
        if (pRspInfo) {
            printf("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
            printf("\tErrorID [%d]\n", pRspInfo->ErrorID);
        }
        printf("\tnRequestID [%d]\n", nRequestID);
        printf("\tbIsLast [%d]\n", bIsLast);
        printf("</OnRspSubForQuoteRsp>\n");
        if (bIsLast) {
            // SetEvent(xinhao);
        }
    };

    void UnSubscribeForQuoteRsp() {
        int md_num = 0;
        char **ppInstrumentID = new char *[5000];
        for (int count1 = 0; count1 <= md_InstrumentID.size() / 500; count1++) {
            if (count1 < md_InstrumentID.size() / 500) {
                int a = 0;
                for (a = 0; a < 500; a++) {
                    ppInstrumentID[a] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
                    md_num++;
                }
                int result = m_pUserMdApi->UnSubscribeForQuoteRsp(ppInstrumentID, a);
                printf((result == 0) ? "退订询价请求1......发送成功\n"
                                     : "退订询价请求1......发送失败，错误序号=[%d]\n",
                       result);
            } else if (count1 == md_InstrumentID.size() / 500) {
                int count2 = 0;
                for (count2 = 0; count2 < md_InstrumentID.size() % 500; count2++) {
                    ppInstrumentID[count2] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
                    md_num++;
                }
                int result = m_pUserMdApi->UnSubscribeForQuoteRsp(ppInstrumentID, count2);
                printf((result == 0) ? "退订询价请求2......发送成功\n"
                                     : "退订询价请求2......发送失败，错误序号=[%d]\n",
                       result);
            }
        }
    }

    virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                       CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                                       bool bIsLast) {
        printf("<OnRspUnSubForQuoteRsp>\n");
        if (pSpecificInstrument) {
            printf("\tInstrumentID [%s]\n", pSpecificInstrument->InstrumentID);
        }
        if (pRspInfo) {
            printf("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
            printf("\tErrorID [%d]\n", pRspInfo->ErrorID);
        }
        printf("\tnRequestID [%d]\n", nRequestID);
        printf("\tbIsLast [%d]\n", bIsLast);
        printf("</OnRspUnSubForQuoteRsp>\n");
        if (bIsLast) {
            // SetEvent(xinhao);
        }
    };

    /// 询价通知
    virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
        printf("<OnRtnForQuoteRsp>\n");
        if (pForQuoteRsp) {
            printf("\tTradingDay [%s]\n", pForQuoteRsp->TradingDay);
            printf("\tInstrumentID [%s]\n", pForQuoteRsp->InstrumentID);
            printf("\tForQuoteSysID [%s]\n", pForQuoteRsp->ForQuoteSysID);
            printf("\tForQuoteTime [%s]\n", pForQuoteRsp->ForQuoteTime);
            printf("\tActionDay [%s]\n", pForQuoteRsp->ActionDay);
            printf("\tExchangeID [%s]\n", pForQuoteRsp->ExchangeID);
        }
        printf("</OnRtnForQuoteRsp>\n");
    }

    void ReqQryMulticastInstrument() {
        std::string new_TopicID;
        printf("请输入TopicID的值:\n");
        std::cin >> new_TopicID;

        CThostFtdcQryMulticastInstrumentField a = {0};
        a.TopicID = atoi(new_TopicID.c_str());
        // strcpy(a.InstrumentID, "");
        int b = m_pUserMdApi->ReqQryMulticastInstrument(&a, nRequestID++);
        printf((b == 0) ? "请求查询组播合约......发送成功\n"
                        : "请求查询组播合约......发送失败，序号=[%d]\n",
               b);
    }

    virtual void OnRspQryMulticastInstrument(
        CThostFtdcMulticastInstrumentField *pMulticastInstrument, CThostFtdcRspInfoField *pRspInfo,
        int nRequestID, bool bIsLast) {
        printf("<OnRspQryMulticastInstrument>\n");
        if (pMulticastInstrument) {
            printf("\tInstrumentID [%s]\n", pMulticastInstrument->InstrumentID);
            printf("\tTopicID [%d]\n", pMulticastInstrument->TopicID);
            printf("\tInstrumentNo [%d]\n", pMulticastInstrument->InstrumentNo);
            printf("\tVolumeMultiple [%d]\n", pMulticastInstrument->VolumeMultiple);
            printf("\tCodePrice [%.8lf]\n", (pMulticastInstrument->CodePrice > 10000000)
                                                ? 0
                                                : pMulticastInstrument->CodePrice);
            printf("\tPriceTick [%.8lf]\n", (pMulticastInstrument->PriceTick > 10000000)
                                                ? 0
                                                : pMulticastInstrument->PriceTick);
        }
        if (pRspInfo) {
            printf("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
            printf("\tErrorID [%d]\n", pRspInfo->ErrorID);
        }
        printf("\tnRequestID [%d]\n", nRequestID);
        printf("\tbIsLast [%d]\n", bIsLast);
        printf("</OnRspQryMulticastInstrument>\n");
    };

   private:
    // 指向CThostFtdcMduserApi实例的指针
    CThostFtdcMdApi *m_pUserMdApi;
};
}  // namespace uBEE