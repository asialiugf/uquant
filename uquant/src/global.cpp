#include "global.h"

#include "base/timestamp.h"

// #include "Bars.h"

namespace uBEE {

uBEE::TmBo *g_time_block;
std::map<std::string, uBEE::FuBo *> map_futures_block;

FILE *logfile;
std::string g_file_instruments;

std::atomic<size_t> g_count{0};
struct libdeflate_compressor *g_compressor;
TickQueue *g_tick_queue;

CThostFtdcReqUserLoginField g_reqUserLogin;
CThostFtdcReqAuthenticateField g_authenticate;
FrontAddr g_front_addr;
FrontMdAddr g_front_mdaddr;

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
int chioce_action = 0; // 为0则全部报
int OrderRef_num = 0;

std::vector<std::string> vector_OrderSysID;
std::vector<std::string> vector_ExchangeID;
std::vector<std::string> vector_InstrumentID;
std::vector<std::string> vector_OrderRef;
std::vector<int> vector_FrontID;
std::vector<int> vector_SessionID;
std::vector<std::string> md_InstrumentID;
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

int ConfigInit(const char *config_ini) {
    std::cout << "【enter】 ConfigInit() \n";
    INIReader reader(config_ini);
    if (reader.ParseError() < 0) {
        std::cout << "open 【config.ini】 file failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    strcpy(g_reqUserLogin.BrokerID, reader.Get("config", "BrokerID", "").c_str());
    strcpy(g_reqUserLogin.UserID, reader.Get("config", "UserID", "").c_str());
    strcpy(g_reqUserLogin.Password, reader.Get("config", "Password", "").c_str());

    std::cout << g_reqUserLogin.BrokerID << std::endl;
    std::cout << g_reqUserLogin.UserID << std::endl;
    std::cout << g_reqUserLogin.Password << std::endl;

    strcpy(g_authenticate.BrokerID, reader.Get("config", "BrokerID", "").c_str());
    strcpy(g_authenticate.UserID, reader.Get("config", "UserID", "").c_str());
    strcpy(g_authenticate.AppID, reader.Get("config", "AppID", "").c_str());
    strcpy(g_authenticate.AuthCode, reader.Get("config", "AuthCode", "").c_str());

    strcpy(g_front_addr, reader.Get("config", "FrontAddr", "").c_str());
    strcpy(g_front_mdaddr, reader.Get("config", "FrontMdAddr", "").c_str());

    std::cout << "【outer】 ConfigInit() \n";
    return 0;
}

int InitFuturesBlock() {
    if (uBEE::md_InstrumentID.size() == 0)
        return -1;
    for (auto it = uBEE::md_InstrumentID.begin(); it != uBEE::md_InstrumentID.end(); it++) {
        cout << *it << " iiiiiiiiiii\n";
        char *p = (char *)it->c_str(); // char *Future, const char *pFile
        cout << p << " ---------\n";
        // todo new 抛出异常，需要处理！
        uBEE::FuBo *fubo = new uBEE::FuBo(p, g_time_block);
        // uBEE::FuBo *fubo = new uBEE::FuBo(it->c_str(), g_time_block);
        cout << p << " 8888888\n";
        map_futures_block.insert(std::pair<std::string, uBEE::FuBo *>(p, fubo));
        cout << p << " 99999999\n";
    }
    return 0;
}

int InitAll() {
    g_tick_queue = new TickQueue;
    g_time_block = new uBEE::TmBo(); // 初始化time_block
    g_compressor = libdeflate_alloc_compressor(9);
    g_file_instruments = "instruments_" + getCurrentSystemTime();

    return 0;
}

} // namespace uBEE
