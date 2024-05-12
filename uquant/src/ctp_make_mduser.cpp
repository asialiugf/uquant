#include <unistd.h>

#include <iostream>
#include <thread>
#include <vector>

#include "base/ini_reader.h"
#include "ctp_mduser_spi.h"
#include "ctp_trader_spi.h"
#include "global.h"

namespace uBEE {

int ctp_make_mduser() {
    printf("g_front_mdaddr = %s\n", g_front_mdaddr);

    CThostFtdcMdApi *mduser_api = CThostFtdcMdApi::CreateFtdcMdApi(".", false, false);
    CSimpleMdHandler mduser_spi(mduser_api);
    mduser_api->RegisterSpi(&mduser_spi);
    mduser_api->RegisterFront(g_front_mdaddr);
    mduser_api->Init();
    //  INIT后，生成三个线程，一个是主线程，一个是 Spi
    //  用于接收行情等信息

    // 这里需要等待线程准备好。 否则下面的ash.ReqUserLogin()
    // 会失败。
    usleep(200000);

    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "thread  in make_mduser : --------- : " << this_id << "\n";

    // 这里需要ReqUserLogin() 否则后面无法订阅行情
    mduser_spi.ReqUserLogin();
    usleep(2000000);
    mduser_spi.SubscribeMarketData(); // 订阅行情
    usleep(2000000);

    std::cout << "运行到这里了！ after SubscribeMarketData" << std::endl;
    // spi.SubscribeForQuoteRsp();//订阅询价
    // spi.UnSubscribeMarketData();//退订行情
    // spi.UnSubscribeForQuoteRsp();//退订询价
    // spi.ReqQryMulticastInstrument();//请求查询组播合约
    // WaitForSingleObject(xinhao, INFINITE);

    mduser_api->Join();
    std::cout << "运行到这里了！ after Join befor Release SubscribeMarketData" << std::endl;
    mduser_api->Release();
    std::cout << "运行到这里了！ after Join befor Release SubscribeMarketData" << std::endl;
    return 0;
}

/*
int ctp_make_trader() {
    std::cout << "【获取前置机地址：】" << std::endl;
    cout << "g_chFrontaddr = " << g_front_addr << "\n" << endl;

    // 创建 API 对象。
    std::cout << "【创建 API 对象：】" << std::endl;
    CTraderApi *p_trader_api = new CTraderApi;
    p_trader_api->CreateFtdcTraderApi(".");
    printf("\napi版本: \n%s", p_trader_api->GetApiVersion());
    cout << endl;

    // 创建 SPI 对象。
    std::cout << "【创建 SPI 对象：】" << std::endl;
    CSimpleHandler spi(p_trader_api);

    // 向API对象里注入SPI对象。
    std::cout << "【向API对象里注入SPI对象：】" << std::endl;
    p_trader_api->RegisterSpi(&spi);
    p_trader_api->SubscribePrivateTopic(THOST_TERT_QUICK);
    p_trader_api->SubscribePublicTopic(THOST_TERT_QUICK);
    std::cout << "【向API对象里注入Front前置机地址：】" << std::endl;

    p_trader_api->RegisterFront(g_front_addr);
    std::cout << "【API INIT() 初始化：】" << std::endl;

    p_trader_api->Init();
    // usleep(200000000);

    usleep(2000000);

    std::cout << "【用户认证：】" << std::endl;
    spi.ReqAuthenticate();

    usleep(200000);
    std::cout << "【用户登录：】" << std::endl;
    spi.ReqUserLogin();

    // 这里需要等待2秒,否则后面的查询不成功。
    usleep(2000000);
    g_count = 0;
    spi.ReqQryInstrument();
    while (g_count == 0) {
        usleep(2000000);
        std::cout << "while 1!!!! " << std::endl;
    }

    // std::cout << "【查证市场数据：】" << std::endl;
    // sh.ReqQryDepthMarketData();
    usleep(2000000);
    return 0;
}
*/

} // namespace uBEE