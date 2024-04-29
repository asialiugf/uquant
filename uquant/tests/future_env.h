#ifndef UBEE_FUTURE_ENV_H
#define UBEE_FUTURE_ENV_H

#include <string.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <cfloat>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string_view>
#include <thread>
#include <vector>

#include <cstdlib>
#include <iostream>

#include "../base/base.h"
#include "../base/error_log.h"
#include "../base/future_period.h"
#include "../base/ini_loader.h"
#include "../base/new_talib.h"
#include "../base/timestamp.h"
#include "../umath/umath.h"
#include "future_env.h"

#include <fmt/core.h>
#include <glog/logging.h>

// 这里将MA 变成 static MA
#include "../base/talib_define.h"

namespace uBEE {

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

#endif