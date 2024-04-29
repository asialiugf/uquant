#include <stdio.h>
#include <unistd.h>

#include <thread>

#include "base/ini_reader.h"
#include "handle_mkdata_spi.h"
#include "handle_trader_spi.h"

#define my_clear() printf("\033[H\033[J")

vector<string> split(const string &str, const string &pattern) {
    // const char* convert to char*
    char *strc = new char[strlen(str.c_str()) + 1];
    strcpy(strc, str.c_str());
    vector<string> resultVec;
    char *tmpStr = strtok(strc, pattern.c_str());
    while (tmpStr != NULL) {
        resultVec.push_back(string(tmpStr));
        tmpStr = strtok(NULL, pattern.c_str());
    }

    delete[] strc;

    return resultVec;
}

int main() {
    // system("COLOR 0A");
    logfile = fopen("syslog.txt", "w");

    int pp;

    INIReader reader("./config.ini");
    if (reader.ParseError() < 0) {
        std::cout << "open config.ini file failed." << std::endl;
        return -1;
    }

    while (true) {
        printf("请选择连接行情/交易:\n");
        printf("1.连接交易\n");
        printf("2.连接行情\n");
        int trade_md;
        cin >> trade_md;
        switch (trade_md) {
            case 2: {
                // string g_chFrontMdaddr = getConfig("config", "FrontMdAddr");
                string g_chFrontMdaddr = reader.Get("config", "FrontMdAddr", "");
                printf("g_chFrontMdaddr = %s\n", g_chFrontMdaddr.c_str());

                CThostFtdcMdApi *pUserMdApi = CThostFtdcMdApi::CreateFtdcMdApi(".", false, false);
                CSimpleMdHandler ash(pUserMdApi);
                pUserMdApi->RegisterSpi(&ash);
                pUserMdApi->RegisterFront(const_cast<char *>(g_chFrontMdaddr.c_str()));
                pUserMdApi->Init();
                //  INIT后，生成三个线程，一个是主线程，一个是 Spi
                //  用于接收行情等信息

                // pUserMdApi->Join();
                // WaitForSingleObject(xinhao, INFINITE);

                // 这里需要等待线程准备好。 否则下面的ash.ReqUserLogin()
                // 会失败。
                usleep(100000);

                std::thread::id this_id = std::this_thread::get_id();
                std::cout << "thread : ---------  " << this_id << " sleeping...\n";

                ash.ReqUserLogin();
                // WaitForSingleObject(xinhao, INFINITE);
                // 开始获取合约
                md_InstrumentID.clear();
                string New_instrument;
                printf("请输入合约号，多个合约请以':'分隔:\n");
                cin >> New_instrument;
                md_InstrumentID = split(New_instrument, ":");

                ash.SubscribeMarketData();  // 订阅行情

                std::cout << "运行到这里了！ after SubscribeMarketData" << std::endl;
                // ash.SubscribeForQuoteRsp();//订阅询价
                // ash.UnSubscribeMarketData();//退订行情
                // ash.UnSubscribeForQuoteRsp();//退订询价
                // ash.ReqQryMulticastInstrument();//请求查询组播合约
                // WaitForSingleObject(xinhao, INFINITE);
                int i;
                std::cin >> i;
                cin.get();
                pUserMdApi->Release();
                return 0;
                exit(-1);
            }
            case 1: {
                // string g_chFrontaddr = getConfig("config", "FrontAddr");
                string g_chFrontaddr = reader.Get("config", "FrontAddr", "");
                cout << "g_chFrontaddr = " << g_chFrontaddr << "\n" << endl;
                CTraderApi *pUserApi = new CTraderApi;  //--------------------------
                pUserApi->CreateFtdcTraderApi(".");
                printf("\napi版本: \n%s", pUserApi->GetApiVersion());
                printf("\n采集库版本：\n%s", CTP_GetDataCollectApiVersion());
                cout << endl;
                CSimpleHandler sh(pUserApi);
            cir:
                pUserApi->RegisterSpi(&sh);
                pUserApi->SubscribePrivateTopic(THOST_TERT_QUICK);
                pUserApi->SubscribePublicTopic(THOST_TERT_QUICK);
                pUserApi->RegisterFront(const_cast<char *>(g_chFrontaddr.c_str()));
                pUserApi->Init();
                // WaitForSingleObject(g_hEvent, INFINITE);

                while (true) {
                    printf("请确定连接模式:\n");
                    printf("1.直连模式\n");
                    printf("2.中继服务器操作员模式(一对多模式)\n");
                    printf("3.中继服务器非操作员模式(多对多模式)\n");
                    int mode_num;
                    cin >> mode_num;
                    switch (mode_num) {
                        case 1:  // 直连模式
                        {
                            std::cout << " befor ReqAuthenticate : ==------------------ \n";
                            sh.ReqAuthenticate();
                            // WaitForSingleObject(g_hEvent, INFINITE);
                            usleep(2000000);
                            std::cout << " befor ReqAuthenticate : ==------------------ \n";
                            sh.ReqUserLogin();
                            // WaitForSingleObject(g_hEvent, INFINITE);
                            break;
                        }
                        case 2:  // 操作员模式
                        {
                            sh.ReqAuthenticate();
                            // WaitForSingleObject(g_hEvent, INFINITE);
                            sh.ReqUserLogin();
                            // WaitForSingleObject(g_hEvent, INFINITE);
                            sh.SubmitUserSystemInfo();
                            break;
                        }
                        case 3:  // 非操作员模式
                        {
                            sh.ReqAuthenticate();
                            // WaitForSingleObject(g_hEvent, INFINITE);
                            sh.RegisterUserSystemInfo();
                            sh.ReqUserLogin();
                            // WaitForSingleObject(g_hEvent, INFINITE);
                            break;
                        }
                        default:
                            printf("选择的模式有误，请重新输入！\n");
                            cin.get();
                            // system("clear");
                            my_clear();
                            printf("\x1b[H\x1b[2J");
                            continue;
                    }
                    break;
                }

                cin.get();

                printf("日期:");
                // printf(pUserApi->GetTradingDay());
                std::cout << pUserApi->GetTradingDay() << std::endl;
                cout << endl;
                while (true) {
                loop:
                    int input1;
                    // system("clear");
                    my_clear();
                    printf("103.请求登出\n");
                    printf("1.结算单确认请求\n");
                    printf("2.用户口令更新请求\n");
                    printf("3.资金账户口令更新请求\n");
                    printf("/////////////报单////////////\n");
                    printf("4.报单模块\n");
                    printf("////////////查询/////////////\n");
                    printf("5.查询模块\n");
                    printf("/////////////行权&做市商////////////\n");
                    printf("6.行权&做市商\n");
                    printf("///////////出入金/////////////\n");
                    printf("7.转账指令\n");
                    printf("///////////铜期权测试////////////\n");
                    printf("8.铜期权测试\n");
                    printf("9.版本6.6.5新加接口\n");
                    printf("0.清空界面\n");
                    printf("100.退出程序\n");
                    printf("请输入你需要的操作序号：\n");
                    cin >> input1;
                    switch (input1) {
                        case 103: {
                            sh.ReqUserLogout();
                            cin.get();
                            break;
                            // goto cir;
                        }
                        case 1:  // 结算单确认请求
                        {
                            sh.ReqSettlementInfoConfirm();  // 结算单确认请求
                            // WaitForSingleObject(g_hEvent, INFINITE);
                            cin.get();
                            // system("clear");
                            my_clear();
                            break;
                        }
                        case 2:  // 用户口令更新请求
                        {
                            sh.ReqUserPasswordUpdate();  // 用户口令更新请求
                            // WaitForSingleObject(g_hEvent, INFINITE);
                            cin.get();
                            // system("clear");
                            my_clear();
                            break;
                        }
                        case 3:  // 资金账户口令更新请求
                        {
                            sh.ReqTradingAccountPasswordUpdate();  // 资金账户口令更新请求
                            // WaitForSingleObject(g_hEvent, INFINITE);
                            cin.get();
                            // system("clear");
                            my_clear();
                            break;
                        }
                        case 4:  // 报单录入请求
                        {
                        orderinsert:
                            // system("clear");
                            my_clear();
                            int orderinsert_num;
                            printf("3.大商所市价止损单\n");
                            printf("4.报入一笔立即单\n");
                            printf("5.撤销上一笔报单\n");
                            printf("6.报入预埋单-限价单立即单\n");
                            printf("7.撤销预埋单-(上一个预埋单)\n");
                            printf("8.报入预埋撤单\n");
                            printf("9.撤销预埋撤单-(上一个预埋撤单)\n");
                            printf("10.报入条件单\n");
                            printf("11.撤销条件单-(上一个条件单)\n");
                            printf("25.大商所止损单\n");
                            printf("26.大商所止盈单\n");
                            printf("27.FOK全成全撤\n");
                            printf("28.FAK部成部撤\n");
                            printf("29.市价单\n");
                            printf("30.套利指令\n");
                            printf("31.互换单\n");
                            printf("32.申请组合\n");
                            printf("0.返回上一层\n");
                            cin >> orderinsert_num;
                            switch (orderinsert_num) {
                                case 0:
                                    goto loop;
                                case 3: {
                                    sh.ReqOrderInsert_dce();
                                    cin.get();
                                    break;
                                }
                                case 4:  // 报入普通立即单
                                {
                                    sh.ReqOrderInsert_Ordinary();
                                    cin.get();
                                    break;
                                }
                                case 5:  // 撤销上一笔报单
                                {
                                    sh.ReqOrderAction_Ordinary();  // 撤销上一笔报单
                                    cin.get();
                                    break;
                                }
                                case 6:  // 报入预埋单
                                {
                                    sh.ReqParkedOrderInsert();  // 报入预埋单
                                    cin.get();
                                    break;
                                }
                                case 7:  // 删除预埋单
                                {
                                    sh.ReqRemoveParkedOrder();  // 删除预埋单
                                    cin.get();
                                    break;
                                }
                                case 8:  // 报入预埋撤单
                                {
                                    sh.ReqParkedOrderAction();  // 报入预埋撤单
                                    cin.get();
                                    break;
                                }
                                case 9:  // 删除预埋单撤单
                                {
                                    sh.ReqRemoveParkedOrderAction();  // 删除预埋单撤单
                                    cin.get();
                                    break;
                                }
                                case 10:  // 报入条件单
                                {
                                it:
                                    printf("1.最新价大于条件价\n");
                                    printf("2.最新价大于等于条件价\n");
                                    printf("3.最新价小于条件价\n");
                                    printf("4.最新价小于等于条件价\n");
                                    printf("5.卖一价大于条件价\n");
                                    printf("6.卖一价大于等于条件价\n");
                                    printf("7.卖一价小于条件价\n");
                                    printf("8.卖一价小于等于条件价\n");
                                    printf("9.买一价大于条件价\n");
                                    printf("10.买一价大于等于条件价\n");
                                    printf("11.买一价小于条件价\n");
                                    printf("12.买一价小于等于条件价\n");
                                    printf("13.返回上一层\n");
                                    printf("请输入你需要报入的条件单类型:\n");
                                    int num;
                                    cin >> num;
                                    if (num < 1 || num > 13) {
                                        printf("输入的序号有误,请重新输入.\n");
                                        cin.get();
                                        goto it;
                                    } else if (num == 13) {
                                        goto orderinsert;
                                    } else {
                                        sh.ReqOrderInsert_Condition(num);  // 报入条件单
                                        cin.get();
                                        break;
                                    }
                                }
                                case 11:  // 报入条件单撤单
                                {
                                    sh.ReqOrderAction_Condition();  // 报入条件单撤单
                                    cin.get();
                                    break;
                                }

                                case 25:  // 大商所止损单
                                {
                                    sh.ReqOrderInsert_Touch();
                                    cin.get();
                                    break;
                                }
                                case 26:  // 大商所止盈单
                                {
                                    sh.ReqOrderInsert_TouchProfit();
                                    cin.get();
                                    break;
                                }
                                case 27:  // FOK全成全撤
                                {
                                    sh.ReqOrderInsert_VC_CV();
                                    cin.get();
                                    break;
                                }
                                case 28:  // FAK部成部撤
                                {
                                    sh.ReqOrderInsert_VC_AV();
                                    cin.get();
                                    break;
                                }
                                case 29:  // 市价单
                                {
                                    sh.ReqOrderInsert_AnyPrice();
                                    cin.get();
                                    break;
                                }
                                case 30:  // 套利指令
                                {
                                    sh.ReqOrderInsert_Arbitrage();
                                    cin.get();
                                    break;
                                }
                                case 31:  // 互换单
                                {
                                    sh.ReqOrderInsert_IsSwapOrder();
                                    cin.get();
                                    break;
                                }
                                case 32:  // 申请组合
                                {
                                    sh.ReqCombActionInsert();
                                    cin.get();
                                    break;
                                }
                                default:
                                    printf("请输入正确的序号\n");
                                    cin.get();
                                    goto orderinsert;
                            }
                            goto orderinsert;
                        }
                        case 5:  // 查询界面
                        {
                        search:
                            // system("clear");
                            my_clear();
                            int choose_num;
                            printf("4.请求查询交易通知\n");
                            printf("5.请求查询客户通知\n");
                            printf("11.查询成交\n");
                            printf("12.查询预埋单\n");
                            printf("13.查询预埋撤单\n");
                            printf("14.查询报单\n");
                            printf("15.撤单对应查询编号\n");
                            printf("16.请求查询资金账户\n");              // ReqQryTradingAccount
                            printf("17.请求查询投资者持仓\n");            // ReqQryInvestorPosition
                            printf("18.请求查询投资者持仓明细\n");        // ReqQryInvestorPositionDetail
                            printf("19.请求查询交易所保证金率\n");        // ReqQryExchangeMarginRate
                            printf("20.请求查询合约保证金率\n");          // ReqQryInstrumentMarginRate
                            printf("21.请求查询合约手续费率\n");          // ReqQryInstrumentCommissionRate
                            printf("22.请求查询做市商合约手续费率\n");    // ReqQryMMInstrumentCommissionRate
                            printf("23.请求查询做市商期权合约手续费\n");  // ReqQryMMOptionInstrCommRate
                            printf("24.请求查询报单手续费\n");            // ReqQryInstrumentOrderCommRate
                            printf("25.请求查询期权合约手续费\n");        // ReqQryOptionInstrCommRate
                            printf("26.请求查询合约\n");                  // ReqQryInstrument
                            printf("27.请求查询投资者结算结果\n");        // ReqQrySettlementInfo
                            printf("28.请求查询转帐流水\n");              // ReqQryTransferSerial
                            printf("29.请求查询询价\n");
                            printf("30.请求查询报价\n");
                            printf("31.请求查询执行宣告\n");
                            printf("32.请求查询转帐银行\n");
                            printf("33.请求查询交易通知\n");
                            printf("34.请求查询交易编码\n");
                            printf("35.请求查询结算信息确认\n");
                            printf("36.请求查询产品组\n");
                            printf("37.请求查询投资者单元\n");
                            printf("38.期货发起查询银行余额请求\n");
                            printf("39.请求查询经纪公司交易参数\n");
                            printf("40.查询最大报单数量请求\n");
                            printf("41.请求查询分类合约\n");
                            printf("42.请求组合优惠比例\n");
                            printf("43.请求查询投资者品种/跨品种保证金\n");
                            printf("44.请求查询交易所调整保证金率\n");
                            printf("45.投资者风险结算持仓查询\n");
                            printf("46.风险结算产品查询\n");
                            printf("47.查询银期签约关系\n");
                            printf("48.请求查询签约银行\n");
                            printf("49.查询深度行情\n");
                            printf("0.返回上一层\n");
                            printf("请输入选择的序号:\n");
                            cin >> choose_num;
                            switch (choose_num) {
                                case 4: {
                                    sh.ReqQryTradingNotice();  // 请求查询交易通知
                                    cin.get();
                                    break;
                                }
                                case 5: {
                                    sh.ReqQryNotice();  // 请求查询客户通知
                                    cin.get();
                                    break;
                                }
                                case 11:  // 请求查询成交
                                {
                                    sh.ReqQryTrade();  // 请求查询成交
                                    cin.get();
                                    break;
                                }
                                case 12:  // 请求查询服务器预埋单
                                {
                                    sh.ReqQryParkedOrder();  // 请求查询服务器预埋单
                                    cin.get();
                                    break;
                                }
                                case 13:  // 请求查询服务器预埋撤单
                                {
                                    sh.ReqQryParkedOrderAction();  // 请求查询服务器预埋撤单
                                    cin.get();
                                    break;
                                }
                                case 14:  // 请求查询报单
                                {
                                    sh.ReqQryOrder();  // 请求查询报单
                                    cin.get();
                                    break;
                                }
                                case 15:  // 撤销查询的报单回报
                                {
                                action:
                                    int action_num;
                                    printf("请输入需要撤单的序号：\n");
                                    cin >> action_num;
                                    printf("%d\n", action_num);
                                    if (action_num < 1 || action_num > vector_OrderSysID.size()) {
                                        printf("输入的序号有误,请重新输入.\n");
                                        cin.get();
                                        goto action;
                                    }
                                    sh.ReqOrderAction_forqry(action_num);  // 撤销查询的报单回报
                                    cin.get();
                                    break;
                                }
                                case 16:  // 请求查询资金账户
                                {
                                    sh.ReqQryTradingAccount();  // 请求查询资金账户
                                    cin.get();
                                    break;
                                }
                                case 17:  // 请求查询投资者持仓
                                {
                                    sh.ReqQryInvestorPosition();  // 请求查询投资者持仓
                                    cin.get();
                                    break;
                                }
                                case 18:  // 请求查询投资者持仓明细
                                {
                                    sh.ReqQryInvestorPositionDetail();  // 请求查询投资者持仓明细
                                    cin.get();
                                    break;
                                }
                                case 19:  // 请求查询交易所保证金率
                                {
                                    sh.ReqQryExchangeMarginRate();  // 请求查询交易所保证金率
                                    cin.get();
                                    break;
                                }
                                case 20:  // 请求查询合约保证金率
                                {
                                    sh.ReqQryInstrumentMarginRate();  // 请求查询合约保证金率
                                    cin.get();
                                    break;
                                }
                                case 21:  // 请求查询合约手续费率
                                {
                                    sh.ReqQryInstrumentCommissionRate();  // 请求查询合约手续费率
                                    cin.get();
                                    break;
                                }
                                case 22:  // 请求查询做市商合约手续费率
                                {
                                    sh.ReqQryMMInstrumentCommissionRate();  // 请求查询做市商合约手续费率
                                    cin.get();
                                    break;
                                }
                                case 23:  // 请求查询做市商期权合约手续费
                                {
                                    sh.ReqQryMMOptionInstrCommRate();  // 请求查询做市商合约手续费率
                                    cin.get();
                                    break;
                                }
                                case 24:  // 请求查询报单手续费
                                {
                                    sh.ReqQryInstrumentOrderCommRate();  // 请求查询报单手续费
                                    cin.get();
                                    break;
                                }
                                case 25:  // 请求查询期权合约手续费
                                {
                                    sh.ReqQryOptionInstrCommRate();  // 请求查询期权合约手续费
                                    cin.get();
                                    break;
                                }
                                case 26:  // 请求查询合约
                                {
                                    sh.ReqQryInstrument();  // 请求查询合约
                                    cin.get();
                                    break;
                                }
                                case 27:  // 请求查询投资者结算结果
                                {
                                    sh.ReqQrySettlementInfo();  // 请求查询投资者结算结果
                                    cin.get();
                                    break;
                                }
                                case 28:  // 请求查询转帐流水
                                {
                                    sh.ReqQryTransferSerial();  // 请求查询投资者结算结果
                                    cin.get();
                                    break;
                                }
                                case 29:  // 请求查询询价
                                {
                                    sh.ReqQryForQuote();  // 请求查询询价
                                    cin.get();
                                    break;
                                }
                                case 30:  // 请求查询报价
                                {
                                    sh.ReqQryQuote();  // 请求查询报价
                                    cin.get();
                                    break;
                                }
                                case 31:  // 请求查询执行宣告
                                {
                                    sh.ReqQryExecOrder();  // 请求查询执行宣告
                                    cin.get();
                                    break;
                                }
                                case 32:  // 请求查询转帐银行
                                {
                                    sh.ReqQryTransferBank();
                                    cin.get();
                                    break;
                                }
                                case 33:  // 请求查询交易通知
                                {
                                    sh.ReqQryTradingNotice();
                                    cin.get();
                                    break;
                                }
                                case 34:  // 请求查询交易编码
                                {
                                    sh.ReqQryTradingCode();
                                    cin.get();
                                    break;
                                }
                                case 35:  // 请求查询结算信息确认
                                {
                                    sh.ReqQrySettlementInfoConfirm();
                                    cin.get();
                                    break;
                                }
                                case 36:  // 请求查询产品组
                                {
                                    sh.ReqQryProductGroup();
                                    cin.get();
                                    break;
                                }
                                case 37:  // 请求查询投资者单元
                                {
                                    sh.ReqQryInvestUnit();
                                    cin.get();
                                    break;
                                }
                                case 38:  // 期货发起查询银行余额请求
                                {
                                    sh.ReqQueryBankAccountMoneyByFuture();
                                    cin.get();
                                    break;
                                }
                                case 39:  // 请求查询经纪公司交易参数
                                {
                                    sh.ReqQryBrokerTradingParams();
                                    cin.get();
                                    break;
                                }
                                case 40:  // 查询最大报单数量请求
                                {
                                    sh.ReqQryMaxOrderVolume();
                                    cin.get();
                                    break;
                                }
                                case 41:  // 请求查询分类合约
                                {
                                    sh.ReqQryClassifiedInstrument();
                                    cin.get();
                                    break;
                                }
                                case 42:  // 请求组合优惠比例
                                {
                                    sh.ReqQryCombPromotionParam();
                                    cin.get();
                                    break;
                                }
                                case 43:  // 请求查询投资者品种/跨品种保证金
                                {
                                    sh.ReqQryInvestorProductGroupMargin();
                                    cin.get();
                                    break;
                                }
                                case 44:  // 请求查询交易所调整保证金率
                                {
                                    sh.ReqQryExchangeMarginRateAdjust();
                                    cin.get();
                                    break;
                                }
                                case 45: {
                                    sh.ReqQryRiskSettleInvstPosition();
                                    cin.get();
                                    break;
                                }
                                case 46: {
                                    sh.ReqQryRiskSettleProductStatus();
                                    cin.get();
                                    break;
                                }
                                case 47:  // 查询银期签约关系
                                {
                                    sh.ReqQryAccountregister();
                                    cin.get();
                                    break;
                                }
                                case 48: {
                                    sh.ReqQryContractBank();
                                    cin.get();
                                    break;
                                }
                                case 49: {
                                    sh.ReqQryDepthMarketData();
                                    cin.get();
                                    break;
                                }
                                case 50: {
                                    sh.ReqQryDepthMarketData();
                                    cin.get();
                                    break;
                                }
                                case 0: {
                                    goto loop;
                                }
                                default: {
                                    printf("请输入正确的序号\n");
                                    cin.get();
                                    goto search;
                                }
                            }
                            goto search;
                        }
                        case 6:  // 行权&做市商
                        {
                        Exec:
                            // system("clear");
                            my_clear();
                            int num_xingquan;
                            printf("32.执行宣告录入请求\n");
                            printf("33.执行宣告操作请求\n");
                            printf("34.放弃行权\n");
                            printf("35.询价录入请求\n");
                            printf("36.做市商报价录入请求\n");
                            printf("37.做市商报价撤销请求\n");
                            printf("0.返回上一层\n");
                            printf("请选择你需要的编码");
                            cin >> num_xingquan;
                            switch (num_xingquan) {
                                case 32:  // 执行宣告录入请求
                                {
                                    sh.ReqExecOrderInsert(0);
                                    cin.get();
                                    break;
                                }
                                case 33:  // 执行宣告操作请求
                                {
                                    sh.ReqExecOrderAction();
                                    cin.get();
                                    break;
                                }
                                case 34:  // 放弃行权
                                {
                                    sh.ReqExecOrderInsert(1);
                                    cin.get();
                                    break;
                                }
                                case 35:  // 询价录入请求
                                {
                                    // string g_chFrontMdaddr =
                                    // getConfig("config", "FrontMdAddr");
                                    string g_chFrontMdaddr = reader.Get("config", "FrontMdAddr", "");
                                    cout << "g_chFrontMdaddr = " << g_chFrontMdaddr << "\n" << endl;
                                    CThostFtdcMdApi *pUserMdApi = CThostFtdcMdApi::CreateFtdcMdApi();
                                    CSimpleMdHandler ash(pUserMdApi);
                                    pUserMdApi->RegisterSpi(&ash);
                                    pUserMdApi->RegisterFront(const_cast<char *>(g_chFrontMdaddr.c_str()));
                                    pUserMdApi->Init();
                                    // WaitForSingleObject(xinhao, INFINITE);
                                    ash.ReqUserLogin();
                                    // WaitForSingleObject(xinhao, INFINITE);
                                    ash.SubscribeMarketData();  // 行情订阅询价请求
                                    sh.ReqForQuoteInsert();     // 交易请求询价
                                    cin.get();
                                    pUserMdApi->Release();
                                    break;
                                }
                                case 36:  // 做市商报价录入请求
                                {
                                    sh.ReqQuoteInsert();
                                    cin.get();
                                    break;
                                }
                                case 37:  // 做市商报价撤销请求
                                {
                                    sh.ReqQuoteAction();
                                    cin.get();
                                    break;
                                }
                                case 0: {
                                    goto loop;
                                }
                                default:
                                    printf("输入的编码有误，请重新输入\n");
                                    cin.get();
                            }
                            goto Exec;
                        }
                        case 7:  // 期货资金转账
                        {
                        futrue:
                            // system("clear");
                            my_clear();
                            int num_future;
                            printf("38.期货发起银行资金转期货请求\n");
                            printf("39.期货发起期货资金转银行请求\n");
                            printf("0.返回上一层\n");
                            printf("请输入你需要的操作序号：");
                            cin >> num_future;
                            switch (num_future) {
                                case 38:  // 期货发起银行资金转期货请求
                                {
                                    sh.ReqFromBankToFutureByFuture();
                                    cin.get();
                                    break;
                                }
                                case 39:  // 期货发起期货资金转银行请求
                                {
                                    sh.ReqFromFutureToBankByFuture();
                                    cin.get();
                                    break;
                                }
                                case 0: {
                                    goto loop;
                                }
                                default:
                                    printf("输入的编码有误，请重新输入\n");
                                    cin.get();
                            }
                            goto futrue;
                        }
                        case 8:  // 铜期权测试
                        {
                        qiquan:
                            // system("clear");
                            my_clear();
                            int num_qiquan;
                            printf("//////////////铜期权测试////////////\n");
                            printf("1.期权自对冲录入请求\n");
                            printf("2.期权自对冲操作请求\n");
                            printf("3.请求查询期权自对冲\n");
                            printf("0.返回上一层\n");
                            printf("请选择你需要的编码:\n");
                            cin >> num_qiquan;
                            switch (num_qiquan) {
                                case 1: {
                                    sh.ReqOptionSelfCloseInsert();
                                    cin.get();
                                    break;
                                }
                                case 2: {
                                    sh.ReqOptionSelfCloseAction();
                                    cin.get();
                                    break;
                                }
                                case 3: {
                                    sh.ReqQryOptionSelfClose();
                                    cin.get();
                                    break;
                                }
                                case 0:
                                    goto loop;
                                    break;
                                default:
                                    printf("输入的序号有误，请重新输入。\n\n");
                                    cin.get();
                            }
                            goto qiquan;
                        }
                        case 9:  // 版本6.6.5新加接口
                        {
                        NewVersion:
                            // system("clear");
                            my_clear();
                            int num_Newversion;
                            printf("新版本测试\n");
                            printf("1.请求查询交易员报盘机\n");
                            printf("0.返回上一层\n");
                            printf("请选择你需要的编码:\n");
                            cin >> num_Newversion;
                            switch (num_Newversion) {
                                case 1:  // 查询用户当前支持的认证模式
                                {
                                    sh.ReqQryTraderOffer();
                                    cin.get();
                                    break;
                                }
                                case 0:
                                    goto loop;
                                    break;
                                default:
                                    printf("输入的序号有误，请重新输入。\n\n");
                                    cin.get();
                                    goto NewVersion;
                            }
                            goto NewVersion;
                        }
                        case 0:
                            // system("clear");
                            my_clear();
                            break;
                        case 100:
                            pUserApi->Release();
                            exit(-1);
                    }
                }
                return 0;
            }
            default: {
                printf("请输入正确的序号。/n");
                cin.get();
            }
        }
    }
}
