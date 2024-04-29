#include "future_env.h"
namespace uBEE {

// #define fu2305 7
// #define au2306 8
// #define xu1801 0
// #define tu1801 1
// #define ru1805 2
// #define ru1809 3
// #define xu1807 4
// #define zz1805 5
// #define ag1912 6
// #define fu2305 7
// #define fu2309 8
// #define LOCAL_DATA false // 是否使用本地数据

int Prepare_env(Base *bb) { //  static Base bb;
    int rtn{0};
    bb->mode_ = Mode::BACK_TEST;
    bb->mode_ = Mode::CHOOSING;
    bb->remote_ = false;

    // const char *path
    std::string sHome = std::getenv("HOME");
    if (sHome.empty()) {
        LOG(ERROR) << " HONE 环境变量不存在 ! ";
        rtn = 9001;
    }

    std::string filename = sHome + "/xquant/uquant/tests/mock/tbl/trade.json";
    LOG(INFO) << filename;

    // bb为static 这里还需要 再次FutureInit吗,  index是否从0开始？ OHLCV如何？
    bb->FutureInit(filename);
    bb->onInit([&]() { bb->GetData(FUNCTIONS::FUN_GET_HISTORY_KBAR, "kkkk"); });

    return rtn;
}
} // namespace uBEE
