#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <unistd.h>

#include <iostream>
#include <thread>

#include "base/CLI11.hpp"
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
    // if (daemon(1, 0) == -1)
    //     exit(EXIT_FAILURE);

    //======================================================================================================
    CLI::App app{"xquant good luck! charmi and miao !"};         // 软件描述出现在第一行打印
    app.footer("my footer xquant good luck! charmi and miao !"); // 最后一行打印
    app.get_formatter()->column_width(40);                       // 列的宽度
    app.require_subcommand(1);                                   // 表示运行命令需要且仅需要一个子命令

    auto sub1 = app.add_subcommand("sub1", "subcommand1");
    auto sub2 = app.add_subcommand("sub2", "subcommand1");
    sub1->fallthrough(); // 当出现的参数子命令解析不了时,返回上一级尝试解析
    sub2->fallthrough();

    // 定义需要用到的参数
    string filename;
    int threads = 10;
    int mode = 0;
    vector<int> barcodes;
    bool reverse = false;
    string outPath;
    string type;
    string password;
    if (sub1) {
        // 第一个参数不加-, 表示位置参数,位置参数按出现的顺序来解析
        // 这里还检查了文件是否存在,已经是必须参数
        sub1->add_option("file", filename, "Position paramter")->check(CLI::ExistingFile)->required();

        // 检查参数必须大于0
        sub1->add_option("-n,-N", threads, "Set thread number")->check(CLI::PositiveNumber);
    }
    if (sub2) {
        // 设置范围
        sub2->add_option("-e,-E", mode, "Set mode")->check(CLI::Range(0, 3));
        // 将数据放到vector中,并限制可接受的长度
        sub2->add_option("-b", barcodes, "Barcodes info:start,len,mismatch")->expected(3, 6);
    }
    // 添加flag,有就是true
    app.add_flag("-r,-R", reverse, "Apply reverse");
    // 检查目录是否存在
    app.add_option("-o", outPath, "Output path")->check(CLI::ExistingDirectory);

    app.add_option("-t,--type", type, "running type");
    app.add_option("-p,--password", password, "running type");

    CLI11_PARSE(app, argc, argv);

    // 判断哪个子命令被使用
    if (sub1->parsed()) {
        cout << "Got sub1" << endl;
        cout << "filename:" << filename << endl;
        cout << "threads:" << threads << endl;
    } else if (sub2->parsed()) {
        cout << "Got sub2" << endl;
        cout << "mode:" << mode << endl;
        cout << "barcodes:";
        for (auto &b : barcodes)
            cout << b << " ";
        cout << endl;
    }
    cout << endl << "Comman paras" << endl;
    cout << "reverse:" << reverse << endl;
    cout << "outPath:" << outPath << endl;
    std::cout << "running type:" << type << std::endl;
    std::cout << "password:" << password << std::endl;
    exit(1);
    // ./xquant sub1 ddd -o test -t rrr -p wqeqwer  // 文件 ddd要存在 ， 目录 test要存在
    //======================================================================================================

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
        while (i < SGM_NUM && uBEE::g_time_block->time_types_[j].segments_[i].iI != -1) {
            std::cout << "----:" << uBEE::g_time_block->time_types_[j].segments_[i].cB;
            std::cout << "----:" << uBEE::g_time_block->time_types_[j].segments_[i].cE;
            std::cout << "----:" << uBEE::g_time_block->time_types_[j].segments_[i].iB;
            std::cout << "----:" << uBEE::g_time_block->time_types_[j].segments_[i].iE;
            std::cout << "----:" << uBEE::g_time_block->time_types_[j].segments_[i].iI << std::endl;
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
