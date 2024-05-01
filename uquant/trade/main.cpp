#include <algorithm>
#include <array>
#include <cfloat>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fmt/core.h>
#include <functional>
#include <glog/logging.h>
#include <iostream>
#include <map>
#include <set>
#include <string.h>
#include <string_view>
#include <thread>
#include <unistd.h>
#include <vector>

#include "../base/base.h"
#include "../base/error_log.h"
#include "../base/future_period.h"
#include "../base/ini_loader.h"
#include "../base/new_talib.h"
#include "../base/timestamp.h"
#include "../base/trade_fun.h"
#include "../umath/umath.h"
#include "./common/trade_config.h"
// 这里将MA 变成 static MA
#include "../base/almost_equal.h"
#include "../base/talib_define.h"

#include "./indicator/kd_macd.h"
#include "./indicator/ma.h"
#include "./indicator/rsi.h"

using namespace uBEE;

#define fu2305 7
#define au2306 8
#define xu1801 0
#define tu1801 1
#define ru1805 2
#define ru1809 3
#define xu1807 4
#define zz1805 5
#define ag1912 6
#define fu2305 7
#define fu2309 8

/*
    // ohlcv::CC 是在 new_talib.h中定义：  enum ohlcv { OO, HH, LL, CC, VV };
    // EMA_T<8, 12> EMA_812(ohlcv::CC, 10);
    // 也可以用下面的写法，直接用序列做构造函数入参。 C8_12见前面的定义，指future<8,12>的 close序列。

*/
// 实现了从 指标中取值进行处理！！
template <int... N> bool buyarea(IND_KD_MACD<N...> &kd) { return kd.ICO137_B; }

int main_01(const std::string &kbarfile) {

    auto start = std::chrono::system_clock::now();

    Base bb;
    bb.mode_ = Mode::BACK_TEST;
    //   bb.mode_ = Mode::CHOOSING;
    // bb.remote_ = true;

    bb.forweb_ = true;       // 需要将数据送到前端显示
    bb.remote_ = false;      // 使用本地数据   // 这里为true时， coredump了 todo !!！
    bb.kbarfile_ = kbarfile; // 设置本地文件

    // FutureInit() 为策略OHLCV等分配内存
    bb.FutureInit("./tbl/trade.json");

    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    bb.onInit([&]() {
        printf("B: onInit() !!\n");
        //       bb.GetData(FUNCTIONS::FUN_GET_HISTORY_KBAR, "kkkkkk");
        printf("E: onInit() !!\n");
    });

    // todo 2023-11-14
    // Future<8, period_1F>需要解决前面这个合约序号8问题，最好自动生成？

    Future<8, period_1F> x(&bb); //  Future<8, 9> x(&bb);
    Future<8, period_5F> y(&bb); //  Future<8, 12> y(&bb);

    StopsegsList<8, 9> segs;

    // ----------------------------------------------
    // 交易处理 Trader<> 这里要改成 localCTP ?
    Trader<8, 9> trader;
    PLOT(trader, 100);
    // ###########################################################

    // 这里可以同时运行多个指标，如果循环处理多个合约，则这里不能是static
    // IND_MA<8, 9> ind_ma(5, 13);
    IND_MA<8, 9> ind_ma;
    IND_KD_MACD<8, 9> kd;
    IND_RSI<8, 9> RSI;

    int iii = 0;
    bb.onBars([&](int e) {
        iii++;
        ind_ma.run();
        kd.run();
        RSI.run();

        // 开平仓测试！ ==================================================================
        if (kd.ICO132_B) {
            if (trader.sellposition() > 4) {
                trader.sellclose(1);
            } else {
                trader.buyopen(1);
            }
            if (trader.sellposition() > 8) {
                trader.sellclose(1009);
            }
        }
        if (kd.ICO132_S) {
            if (trader.buyposition() > 4) {
                trader.buyclose(1);
            } else {
                trader.sellopen(1);
            }

            if (trader.buyposition() > 8) {
                trader.buyclose(1009);
            }
        }
        // 开平仓测试！ =====================================================================
        if (kd.H_KPB5.cur_section() == 1) {
            if (kd.H_KPB4.cur_section() == 1) {
                if (kd.H_KPB3.cur_section() == 1) {
                }

                if (kd.H_KPB3.cur_section() == 0) {
                }
            }

            if (kd.H_KPB4.cur_section() == 0) {
            }
        }

        if (kd.H_KPB5.cur_section() == 0) {
        }

        // 开平仓测试！ =====================================================================

        if (buyarea(kd)) {
            //  LOG(ERROR) << x.unit->ActionDay << " hello ----【绿桃心】 绿80  " << x.unit->Time << " " << x.C.cur() << " " << x.O.cur();
        }

        // if (iii == 10) {
        //    exit(-1);
        // }
    }); // end onBar() ;

    std::cout << "pppppppppppppppppppppppp qqqqqqqqqqqqqqqqqqqqqqqqqqqq !" << std::endl;

    bb.Run();

    for (auto ix : kd.H_KB3.segments_) {
        std::cout << "charmi  "
                  << " B: " << ix.B << " E: " << ix.E << " value: " << ix.value << " len:" << ix.len << std::endl;
    }

    auto end = std::chrono::system_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "花费了" << double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den << "秒" << std::endl;
    return 0;
}

int main(int argc, char **argv) {

    google::InitGoogleLogging("argv[0]"); // 初始化

    FLAGS_minloglevel = google::INFO; // 只记录大于ERROR等级的日志
    FLAGS_log_dir = "./log/";         // 设置日志存放路径
                                      // FLAGS_alsologtostderr = 0; // 日志同时输出到stderr

    std::string home_dir = std::getenv("HOME");
    if (home_dir.empty()) {
        LOG(ERROR) << " HONE 环境变量不存在 ! ";
        return 9001;
    }

    // std::string path = home_dir + "/tdx_data";
    std::string path = home_dir + "/tdx_data";
    LOG(INFO) << path;

    // if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
    std::string kf;
    if (kf.empty()) {
        std::cout << "字串为空" << std::endl;
    }

    if (!std::filesystem::is_directory(path)) {
        std::cout << "指定路径不是一个目录" << std::endl;
        exit(-1);
    }

    if (std::filesystem::begin(std::filesystem::directory_iterator(path)) == std::filesystem::end(std::filesystem::directory_iterator(path))) {
        std::cout << "目录为空" << std::endl;
        exit(-1);
    }

    for (const auto &file : std::filesystem::directory_iterator(path)) {

        std::cout << file.path() << "  ==================" << std::endl;
        main_01(file.path());
    }

    // for (int i = 0; i < 1; i++) {
    //     main_01();
    // }

    return 0;
}