#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <unistd.h>

#include <iostream>
#include <thread>

#include "ctp_make_mduser.h"
#include "ctp_make_trader.h"
#include "global.h"
#include "queue_read.h"

// #include <uWS/uWS.h>

#include "Bars.h"

extern char **environ;

int Menu();

int main(int argc, char **argv) {

    // daemon(1,0) : 1表示 不改目录， 第二个参数 0 表示 将 0,1,2 标准输入输出错误，改为 /dev/null
    if (daemon(1, 0) == -1)
        exit(EXIT_FAILURE);

    using namespace uBEE;
    int rtn;
    int pid;
    // uWS::Hub kk;
    // int iFunc = Menu();
    ConfigInit("./config.ini");
    InitAll();

    int iFunc = 3;

    // uBEE::Daemon(1, 0);

    for (int j = 0; j < 7; j++) {
        int i = 0;
        while (i < SGM_NUM && uBEE::g_time_block->TT[j].aSgms[i].iI != -1) {
            std::cout << "----:" << uBEE::g_time_block->TT[j].aSgms[i].cB;
            std::cout << "----:" << uBEE::g_time_block->TT[j].aSgms[i].cE;
            std::cout << "----:" << uBEE::g_time_block->TT[j].aSgms[i].iB;
            std::cout << "----:" << uBEE::g_time_block->TT[j].aSgms[i].iE;
            std::cout << "----:" << uBEE::g_time_block->TT[j].aSgms[i].iI << std::endl;
            i++;
        }
        std::cout << std::endl;
    }

    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "main thread : --------- :  " << this_id << "\n";

    TickWrite();

    KbarHandle();

    //  登录，获取 交易品种代码 ctp_traderSpi.cpp: CTraderSpi::OnRspQryDepthMarketData() ;
    //  trader: 认证，登录后，调用 spi.ReqQryInstrument(); 获取所有合约
    rtn = uBEE::ctp_make_trader();

    // 为每个合约分配一个  future_block uBEE:FuBo
    rtn = uBEE::InitFuturesBlock();
    if (rtn < 0) {
        exit(-1);
    }

    // testing !
    for (auto it = uBEE::md_InstrumentID.begin(); it != uBEE::md_InstrumentID.end(); it++) {
        cout << *it << "\n";
    }

    // 订阅所有行情
    rtn = uBEE::ctp_make_mduser();

    //  hb.Init();
    //  hb.Start();

    pid = getpid();

    ///    uBEE::SaveArgv(argc, argv);
    ///     uBEE::InitSetProcTitle();
    ///    uBEE::SetProcTitle("master ", "DataServ: ");

    /*  20230214
    std::cout << "befor fork api !!\n";
    rtn = ForkApi();
    sleep(1);
    std::cout << "after fork api !!\n";
      20230214 */

    // for back test!!! 回测
    if (iFunc == 2 || iFunc == 6 || iFunc == 7 || iFunc == 8) {
        for (int i = 0; i < 5; i++) {
            // rtn = ForkBck();
            sleep(1);
        }
    }

    // for simulation !!! 仿真
    if (iFunc == 4 || iFunc == 5 || iFunc == 7 || iFunc == 8) {
        // rtn = ForkSim();
        sleep(1);
    }

    // for CTP 实情
    if (iFunc == 3 || iFunc == 5 || iFunc == 6 || iFunc == 8) {
        // rtn = ForkCtp();
        sleep(1);
    }

    if (iFunc < 2 || iFunc > 8) {
        std::cout << "Input Error !! \n";
        exit(-1);
    }

    while (true) {
        sleep(1000);
    }
}

int ForkCtp() {
    int rc;
    int pid;
    pid = fork();

    switch (pid) {
    case -1:
        return -1;
    case 0: {
        // uBEE::HubCtp hub;  // ------- for test
        /*
        std::cout << " 99999 enter fork ForkCtp !" << std::endl;
        uBEE::HubCtp hub;
        std::cout << " 99999 enter fork ForkCtp !" << std::endl;
        pid = getpid();
        uBEE::InitSetProcTitle();
        uBEE::SetProcTitle("HubCtp:", "DataServ: ");

        std::cout << "befor HubCtp.Init!" << std::endl;
        hub.Init();
        sleep(2);
        std::cout << "after HubCtp.Init!" << std::endl;

        std::thread t([&hub] { uBEE::MkCtp(hub.sg); });
        t.detach();
        hub.Start();
        */
        std::cout << "end hub.Start!!" << std::endl;
    } break;
    default:
        break;
    }

    return 0;
}

int Menu() {
    int tt;
    std::cout << std::endl;
    std::cout << "            \033[31m Input type description: \033[0m" << std::endl;
    std::cout << "            \033[35m 2: \033[35mBck\033[0m only\033[0m" << std::endl;
    std::cout << "            \033[31m 3: \033[31mCtp\033[0m only\033[0m" << std::endl;
    std::cout << "            \033[32m 4: \033[32mSim\033[0m only\033[0m" << std::endl;
    std::cout << "            \033[31m 5: \033[31mCtp\033[0m + \033[32mSim\033[0m" << std::endl;
    std::cout << "            \033[31m 6: \033[31mCtp\033[0m + \033[35mBck\033[0m" << std::endl;
    std::cout << "            \033[32m 7: \033[32mSim\033[0m + \033[35mBck\033[0m" << std::endl;
    std::cout << "            \033[31m 8: \033[31mCtp\033[0m + "
                 "\033[32mSim\033[0m + \033[35mBck\033[0m"
              << std::endl;
    std::cout << "            \033[31m Please Input type: \033[0m";
    std::cin >> tt;
    return tt;
}
