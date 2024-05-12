#include "ctp_make_trader.h"

#include <unistd.h>

#include <iostream>
#include <thread>
#include <vector>

#include "base/ini_reader.h"
#include "ctp_mduser_spi.h"
#include "ctp_trader_spi.h"
#include "global.h"

namespace uBEE {
int ctp_make_trader() {
    std::cout << "【获取前置机地址：】" << std::endl;
    cout << "g_chFrontaddr = " << g_front_addr << "\n" << endl;

    // 创建 API 对象。
    std::cout << "【创建 API 对象：】" << std::endl;
    CTraderApi *trader_api = new CTraderApi;
    trader_api->CreateFtdcTraderApi(".");
    printf("\napi版本: \n%s", trader_api->GetApiVersion());
    cout << endl;

    // 创建 SPI 对象。
    std::cout << "【创建 SPI 对象：】" << std::endl;
    CSimpleHandler trader_spi(trader_api);

    // 向API对象里注入SPI对象。
    std::cout << "【向API对象里注入SPI对象：】" << std::endl;
    trader_api->RegisterSpi(&trader_spi);
    trader_api->SubscribePrivateTopic(THOST_TERT_QUICK);
    trader_api->SubscribePublicTopic(THOST_TERT_QUICK);
    std::cout << "【向API对象里注入Front前置机地址：】" << std::endl;

    trader_api->RegisterFront(g_front_addr);
    std::cout << "【API INIT() 初始化：】" << std::endl;

    trader_api->Init();
    // usleep(200000000);

    usleep(2000000);

    std::cout << "【用户认证：】" << std::endl;
    trader_spi.ReqAuthenticate();

    usleep(200000);
    std::cout << "【用户登录：】" << std::endl;
    trader_spi.ReqUserLogin();

    // 这里需要等待2秒,否则后面的查询不成功。
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    g_count = 0;
    trader_spi.ReqQryInstrument();
    while (g_count == 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 100毫秒
    }

    // std::cout << "【查证市场数据：】" << std::endl;
    // sh.ReqQryDepthMarketData();
    // usleep(2000000);
    return 0;
}

} // namespace uBEE