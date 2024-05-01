#include "base.h"

#include <fmt/core.h>

#include "timestamp.h"
#include <glog/logging.h>
#include <thread>

namespace uBEE {
using lSignal::Connection;
using lSignal::Signal;
using lSignal::Slot;

Base::Base() {
    std::cout << "base  initial !!  haha ============!" << std::endl;
    for (int i = 0; i < FutureNum; i++) {
        for (int j = 0; j < PeriodNum; j++) {
            this->unit_array_[i][j] = nullptr;
        }
    }

    this->web_ws_ = nullptr;

} //

Base::~Base() {
    for (int i = 0; i < FutureNum; i++) {
        for (int j = 0; j < PeriodNum; j++) {
            if (this->unit_array_[i][j] != nullptr) {
                delete[] this->unit_array_[i][j]->OO;
                delete[] this->unit_array_[i][j]->HH;
                delete[] this->unit_array_[i][j]->LL;
                delete[] this->unit_array_[i][j]->CC;
                delete[] this->unit_array_[i][j]->VV;
                delete this->unit_array_[i][j];
                std::cout << "base release haha ============! i:" << i << " j:" << j << std::endl;
            }
        }
    }
    std::cout << "base release haha ============!" << std::endl;
};

void Base::MainHubOnMessageInit() {
    main_hub_->onMessage([this](uWSclient *ws, char *data, size_t length, uWS::OpCode opCode) {
        char tmp[1600];
        memcpy(tmp, data, length);
        tmp[length] = 0;
        struct ttff *msg1 = (struct ttff *)data;
        printf("Client receive message length: %ld  \n", length);
        std::cout << data << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // ws->send(data);
    });
}

void Base::MainHubConnection() { // 这里是进行实际TCP连接
    if (forweb_) {
        main_hub_->connect("ws://localhost:7001", (void *)6); //    连接显示服务进程，将数据转发给web端。
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    if (remote_) {
        switch (this->mode_) {
        case Mode::BACK_TEST:
            std::cout << " Base::MainHubConnection()   Mode::BACK_TEST" << std::endl;
            // 后面这个  (void *)2 ， 可以通过 (long)ws->getUserData() 来读取，见 Base::SaveWebSock() !!
            main_hub_->connect("ws://localhost:9001", (void *)2); //  data server HubBck //回测
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        case Mode::REAL_CTP:
            main_hub_->connect("ws://localhost:3003", (void *)3); //  data server HubCtp  //实盘
            break;
        case Mode::SIMULATION:
            main_hub_->connect("ws://localhost:3004", (void *)4); //  data server HubSim  //模拟
            break;
        default:
            main_hub_->connect("ws://localhost:3004", (void *)5); //  data server HubSim  //模拟
            break;
        }
    }
}

void Base::MainHubOnConnectInit() {
    main_hub_->onConnection([this](uWSclient *ws, uWS::HttpRequest req) {
        // 建立连接后，才可以调用 onInit,从websocket取数据。
        // 在onInit里 getData();
        // 重新连接时，需要重新设定 start_day, finish_day,
        printf("main hub onConnection B -- \n");
        this->SaveWebSock(ws, req);

        // 采用新的线程来处理策略程序，需要修改成：接收到 web端的反馈后，再进行下一个切片处理。 todo 2023-11-26
        if ((long)ws->getUserData() == 6) {
            std::thread th1([&]() { this->onMessages(); });
            th1.detach();
        }

        // todo 针对不同的连接，做不同的事情，比如  this->onInitHandler();
        // 同一个loop里可以有多个不同的连接，要不要分成不同mainhub ？
    });
}
void Base::MainHubOnDisconnInit() {
    main_hub_->onDisconnection([this](uWSclient *ws, int code, char *message, size_t length) {
        auto result = std::find(this->ws_.begin(), this->ws_.end(), ws);
        if (result == this->ws_.end()) {
            std::cout << "Not found" << std::endl;
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "YesYes!!" << std::endl; // 找到了
            (*result) = nullptr;
            for (;;) {
                // 重新连接！
                printf("reconnect in onDisconnection!!\n");
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                this->MainHubConnection(); // 这里所有的连接都要重新来过一次吗?
                main_hub_->run();          // 这里所有的连接都要重新来过一次吗? 这里会不会有问题?
            }
            // ws->close();
        }
        std::cout << "code:" << code << std::endl;
        // this->main_hub_->getDefaultGroup<uWS::SERVER>().close();
        // this->main_hub_->getDefaultGroup<uWS::CLIENT>().close();
        switch ((long)ws->getUserData()) {
        case 1:
            break;
        case 5:
            main_hub_->connect("ws://localhost:3004",
                               (void *)4); //  data server HubSim  //模拟
            break;
        }
    });
}

void Base::MainHubOnErrorInit() {
    main_hub_->onError([this](void *user) {
        printf("Error: %s, errno:%d\n", strerror(errno), errno);
        std::cout << "FAILURE: Connection failed! Timeout?" << std::endl;
        for (;;) {
            // 重新连接！
            printf("reconnect in onError !!\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            this->MainHubConnection();
            main_hub_->run();
        }
        // exit(-1);
        switch ((long)user) {
        case 1:
            std::cout << "Client emitted error on invalid URI" << std::endl;
            break;
        case 2:
            std::cout << "Client emitted error on resolve failure" << std::endl;
            break;
        default:
            std::cout << "FAILURE: " << user << " should not emit error!" << std::endl;
            exit(-1);
        }
        exit(-1);
    });
}
void Base::MainHubInit() {
    printf("B: Base::MainHubInit () ");
    // this->mode_ = Mode::BACK_TEST;
    main_hub_ = new uWS::Hub;
    this->MainHubOnConnectInit(); // 设置
    this->MainHubOnMessageInit(); // 设置
    this->MainHubOnDisconnInit(); // 设置
    this->MainHubOnErrorInit();   // 设置
    this->MainHubConnection();    // 这里是真正建立连接,可能会建立多个不同的连接，
                                  // 建立完成后，onConnection设置的函数就会被调用：Base::MainHubOnConnectInit()

    // 这里执行 main_hub_->run();  通过上面的conect() 与相应的server进行 信息交互。
    // 通过 onMessage，接收来自 SERVER 的 tick \ bars数据。
    // main_hub_->run();
    // 程序何时结束 ？
    // 如果是backtest的话，可以让 backtest SERVER 在请求结束后，发送消息过来。
    // 或者策略程序 在 测试的时间段结束后，自己调用 close()，结束与
    // SERVER的连接。
    // } else {
    // 本地循环 Queue
    // 本地循环分两种情况，一种是通过CTP连接获取数据进行，还有一种情况是直接读取本地数据。

    // 情形一、连接CTP等，进行交易
    {
        // todo
    }
    // 情形二、直接读取本地数据。
    // this->onMessages();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    printf("E: ------------- Base::MainHubInit () \n ");
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Base::Run() {

    // main_hub_->run();
    // 程序何时结束 ？
    // 如果是backtest的话，可以让 backtest SERVER 在请求结束后，发送消息过来。
    // 或者策略程序 在 测试的时间段结束后，自己调用 close()，结束与
    // SERVER的连接。

    //   main_hub_

    if (remote_ || forweb_) {
        this->MainHubInit();
        main_hub_->run();
    } else {
        switch (this->mode_) {
        case Mode::BACK_TEST:
            // this->MainHubInit();
            // main_hub_->run();
            this->onMessages();
            std::cout << "Mode::BACK_TEST" << std::endl;
            break;
        case Mode::REAL_CTP:
            // 二、CTP连接
            break;
        case Mode::SIMULATION:
            // 三、直接读取本地数据(数据库，或文件)
            break;
        case Mode::CHOOSING: // 选股
            std::cout << "Mode::CHOOSING ((((((((((((((((((((()))))))))))))))))))))" << std::endl;
            // 三、直接读取本地数据(数据库，或文件)
            // 如何读取本地文件呢？
            this->onMessages();
            break;
        default:
            break;
        }
    }

    printf("Base::Run() E --\n");
    // exit(0);
}

void Base::onInit(MoveOnlyFunction<void()> handler) { Base::onInitHandler = std::move(handler); }
void Base::onBars(MoveOnlyFunction<void(int)> handler) { Base::onBarsHandler = std::move(handler); }

// 【from trade/main.cpp】 bb.FutureInit("./tbl/trade.json");
int Base::FutureInit(const std::string &tradejson) {
    LOG(INFO) << __FUNCTION__;
    // 对于选股策略来说，暂时先用 <8,9> <8,12> <8,14> 这几个位置分别表示1分钟，5分钟，15分钟
    if (mode_ == Mode::CHOOSING) {
        if (!remote_) {
            Unit *unitx = new Unit();
            unitx->OO = new double[KSIZE];
            unitx->HH = new double[KSIZE];
            unitx->LL = new double[KSIZE];
            unitx->CC = new double[KSIZE];
            unitx->VV = new double[KSIZE];
            unitx->out = new double[KSIZE];
            unitx->ohlcv_len = KSIZE;
            unitx->index = 0; // 策略切片执行的index
            unitx->repeat_index = REPEAT;
            unitx->period_value = 9;
            unitx->period_index = 9;
            unitx->future_index = 8;
            unit_array_[8][9] = unitx;

            unitx = new Unit();
            unitx->OO = new double[KSIZE];
            unitx->HH = new double[KSIZE];
            unitx->LL = new double[KSIZE];
            unitx->CC = new double[KSIZE];
            unitx->VV = new double[KSIZE];
            unitx->out = new double[KSIZE];
            unitx->ohlcv_len = KSIZE;
            unitx->index = 0; // 策略切片执行的index
            unitx->repeat_index = REPEAT;
            unitx->period_value = 12;
            unitx->period_index = 12;
            unitx->future_index = 8;
            unit_array_[8][12] = unitx;
        }
        return 0;
    }

    std::vector<int> period_vec;
    // return 0;
    // https://github.com/ibireme/yyjson
    // https://ibireme.github.io/yyjson/doc/doxygen/html/index.html
    // https://github.com/asialiugf/CPP_yyjson
    yyjson_read_flag flg = YYJSON_READ_ALLOW_COMMENTS | YYJSON_READ_ALLOW_TRAILING_COMMAS;
    yyjson_read_err err;
    std::cout << tradejson << std::endl;
    yyjson_doc *doc = yyjson_read_file(tradejson.c_str(), flg, NULL, &err);
    if (doc) {
        yyjson_val *root = yyjson_doc_get_root(doc);

        yyjson_val *trading_mode = yyjson_obj_get(root, "trading_mode");
        if (yyjson_is_uint(trading_mode)) {
            switch (yyjson_get_uint(trading_mode)) {
            case 1: {
                this->mode_ = Mode::BACK_TEST; //  从本地文件或数据库取数据，或者 从远端取数据
                break;
            }
            case 2: {
                this->mode_ = Mode::REAL_CTP; // 本地建立连接，或者 从remote取数据，相当于是实盘，也有两种方式。
                break;
            }
            case 3: {
                this->mode_ = Mode::SIMULATION; // 本地文件或数据库， 远端连接获取数据
                break;
            }
            case 4: {
                this->mode_ = Mode::CHOOSING;
                break;
            }
            default: {
                printf("trading_mode seting error! in file trading.json \n");
            }
            }
        }

        yyjson_val *futures_array = yyjson_obj_get(root, "futures");
        for (int i = 0; i < yyjson_arr_size(futures_array); i++) {
            period_vec.clear();
            period_vec.push_back(i);
            yyjson_val *future = yyjson_arr_get(futures_array, i);
            yyjson_val *instrument_id = yyjson_obj_get(future, "instrument_id");
            yyjson_val *periods = yyjson_obj_get(future, "periods");
            for (int j = 0; j < yyjson_arr_size(periods); j++) {
                yyjson_val *period = yyjson_arr_get(periods, j);
                // printf("%s %s\n", yyjson_get_str(instrument_id), yyjson_get_str(period));

                auto iter = PeriodMap.find(yyjson_get_str(period));
                if (iter != PeriodMap.end()) {
                    int x = iter->second[0];
                    // printf(" %d \n", x);
                    period_vec.push_back(x);
                } else {
                    printf("period: %s is not defined!\n", yyjson_get_str(period));
                }
            }
            this->future_map_.emplace(yyjson_get_str(instrument_id), period_vec);
        }
    }

    yyjson_doc_free(doc);

    //   std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    if (this->future_map_.empty()) {
        std::cout << " future map is empty !" << std::endl;
        return -1;
    }

    //  memset(future_list, 0, sizeof(future_list));

    int i = 0;
    for (auto it = (this->future_map_).begin(); it != (this->future_map_).end(); ++it) { // for strategy ... future
        if (it->second.size() < 2) {
            std::cout << " period is not set !" << std::endl;
            return -1;
        }

        //  strncpy(future_list[i], it->first.c_str(), it->first.length());

        auto iter = it->second.cbegin();
        //   std::cout << it->first << "    " << *iter << " \t ";
        int m = *iter; // 第一值，是future_index;

        iter++;

        // todo

        int j = 0;
        for (; iter != it->second.cend(); iter++) {
            //   std::cout << "  period_index: " << *iter << " \t ";
            Unit *unitx = new Unit();
            if (!this->remote_) {
                // todo 本地数据
                unitx->OO = new double[KSIZE];
                unitx->HH = new double[KSIZE];
                unitx->LL = new double[KSIZE];
                unitx->CC = new double[KSIZE];
                unitx->VV = new double[KSIZE];
                unitx->out = new double[KSIZE];
            } else {
                //  远端数据
                // todo  这里的数据是谁来分配，如何传递到这里来？
                // x->OO = ??
                // x->HH ==??

                std::cout << " Base::FutureInit()  remote_ == true , so  need to get data from websocket !!  " << std::endl;
                // exit(-1);
                // 下面这一段暂时分先分配内存： 不退出程序。
                {
                    unitx->OO = new double[KSIZE];
                    unitx->HH = new double[KSIZE];
                    unitx->LL = new double[KSIZE];
                    unitx->CC = new double[KSIZE];
                    unitx->VV = new double[KSIZE];
                    unitx->out = new double[KSIZE];
                }
            }
            unitx->ohlcv_len = KSIZE;
            unitx->index = 0; // 策略切片执行的index
            unitx->repeat_index = REPEAT;

            unitx->period_value = *iter;
            unitx->period_index = *iter;
            unitx->future_index = m;

            unit_array_[m][*iter] = unitx;
            j++;
        }
        i++;
    }

    return 0;
}

void Base::SaveWebSock(uWSclient *ws, uWS::HttpRequest req) {
    long xx = (long)ws->getUserData();
    std::cout << "ppppppppppppp:  " << (long)ws->getUserData() << std::endl;
    printf("here %ld\n", xx);
    switch ((long)ws->getUserData()) {
    case 1:
        // this->ws_[0] = ws;
        this->ws_.push_back(ws);
        break;
    // case 2: 表示是 backtest SERVER 。 这里需要发送相应的请求。比如：
    // 策略程序 请求的期货名称，时间段，测试级别是 tick ? 1F ? 5F
    // ?等信息。
    // 注意：策略程序在初始化时，应该提供这些信息。这里能够看到这些信息，
    // 并 通过 ws->send 发送给 backtest SERVER.
    // 这里的请求是否可以通过gRPC来完成呢？留个作业。
    // 本质上是一个 沟通协议。
    case 2: {
        // todo 这里有问题 ？ ws_有问题？
        // this->ws_[1] = ws;  // backtest
        std::cout << " 和 回测服务进程 建立连接。" << std::endl;
        printf("befor push\n");
        this->ws_.push_back(ws);
        this->ws_.data()[2] = ws;
        this->dat_ws_ = ws;
        printf("after push\n");
        ws->send(" simulation !!");

        // onInitHandler will get data from server via ws!
        // 当所有的连接建立完成后可以对 策略程序中的 onInit进行处理了。
        this->onInitHandler();

        break;
    }
    case 3:
        this->ws_[3] = ws; // real_ctp
        break;
    case 4:
        this->ws_[4] = ws; // simulate
        break;
    case 5:
        this->ws_[5] = ws; // simulate
        break;
    case 6:
        this->web_ws_ = ws; // forweb_ 将数据传给 显示进程，由显示进程转给web
        std::cout << " 和 web显示服务进程 建立连接。" << std::endl;
        break;
    default:
        std::cout << "FAILURE: " << ws->getUserData() << " should not connect!" << std::endl;
        exit(-1);
    }
}

void Base::sendTradingData() {
    // this->dat_ws_->send("{\"action\":\"sub\", \"share\":\"GOOG\"}");
    char desc[1024];

    char datetime[100];
    size_t ret;
    memset(desc, '\0', 1024);
    memset(datetime, '\0', 100);

    ret = snprintf(datetime, 100, "%s-%s",
                   this->unit_array_[8][9]->ActionDay, //
                   this->unit_array_[8][9]->Time);     //
    long long tt = EpochConverter2(std::string(datetime));

    strncpy(datetime, this->unit_array_[8][9]->ActionDay, 4);
    strncpy(datetime + 5, this->unit_array_[8][9]->ActionDay + 4, 2);
    strncpy(datetime + 8, this->unit_array_[8][9]->ActionDay + 6, 2);

    strncpy(datetime + 11, this->unit_array_[8][9]->Time, 2);
    strncpy(datetime + 14, this->unit_array_[8][9]->Time + 2, 2);
    // "2018-06-25T10:00:00.000Z",
    datetime[4] = '-';
    datetime[7] = '-';
    datetime[13] = ':';
    datetime[10] = 'T';
    strncpy(datetime + 16, ":00.000Z", 8);
    std::cout << tt << ": time !!!!!!!!!!!!! :  " << datetime << std::endl;

    // 要注意数据文件里面的汉字！！
    // 方式二： datetime = "2023-05-19T11:00:00.000Z" ;
    ret = snprintf(desc, 1024, "{\"time\":\"%s\",\"open\":\"%f\",\"high\":\"%f\",\"low\":\"%f\",\"close\":\"%f\"",
                   //  ret = snprintf(desc, 1024, "{t:%s-%s,o:%f,h:%f,l:%f,c:%f}",
                   datetime,                                                    //
                   this->unit_array_[8][9]->OO[this->unit_array_[8][9]->index], //
                   this->unit_array_[8][9]->HH[this->unit_array_[8][9]->index], //
                   this->unit_array_[8][9]->LL[this->unit_array_[8][9]->index], //
                   this->unit_array_[8][9]->CC[this->unit_array_[8][9]->index]);

    // 方式一： tt = 1684494000 ;
    // ret = snprintf(desc, 1024, "{\"time\":\"%lld\",\"open\":\"%f\",\"high\":\"%f\",\"low\":\"%f\",\"close\":\"%f\"}",
    //                //  ret = snprintf(desc, 1024, "{t:%s-%s,o:%f,h:%f,l:%f,c:%f}",
    //                tt,                                                          //
    //                this->unit_array_[8][9]->OO[this->unit_array_[8][9]->index], //
    //                this->unit_array_[8][9]->HH[this->unit_array_[8][9]->index], //
    //                this->unit_array_[8][9]->LL[this->unit_array_[8][9]->index], //
    //                this->unit_array_[8][9]->CC[this->unit_array_[8][9]->index]);

    //  this->web_ws_->send(desc);

    char temp[1024];
    std::string happy;

    // --------------- 从output中取出 name :  ---------------- 序列化数据 ---------比如 ma5,ma55 K2,D2之类 -----
    for (auto tp : this->unit_array_[8][9]->output) {
        memset(temp, '\0', 1024);
        std::string name; // 名称
        double *serial;   // double数组，即某序列的数据
        int color;
        auto tp2 = std::make_tuple(std::ref(name), std::ref(serial), std::ref(color)) = tp;
        //   double *serial = std::get<1>(tp); // 取出数组
        LOG(INFO) << " from base.cpp      hahaha :: is ok ? :: " << name << " " << serial[this->unit_array_[8][9]->index];
        ret = snprintf(temp, 1024, ",\"%s\":\"%f\"",            //
                       name.c_str(),                            //
                       serial[this->unit_array_[8][9]->index]); //
        std::string temps(temp);
        happy = happy + temps;
    }

    // sections output to web ----------------------------------------------------
    for (auto tp : this->unit_array_[8][9]->sectionslist_output) {
        memset(temp, '\0', 1024);
        std::string name;               //  1、名称
        std::vector<Section> *sections; //  2、是一个vector<int> 里面存储是index位置信息
        int color;                      //  3、颜色 ？？
        auto tp2 = std::make_tuple(std::ref(name), std::ref(sections), std::ref(color)) = tp;
        if (!sections->empty()) {
            //  if (sections->back().type != -1) {                       // -1是自定义section_id的默认ID。不必上传
            //     if (sections->back().type != INT_MIN) {                  // INT_MIN 是自定义section_id的默认ID。不必上传
            if (sections->back().E == INT_MIN) {                     // 这个段处于结束状态，不再上传。
                ret = snprintf(temp, 1024, ",\"%s_section\":\"%d\"", //
                               name.c_str(),                         //
                               sections->back().type);               //
                std::string temps(temp);
                happy = happy + temps;
            }
        }
    }

    // ----------------从 pointslist_output 取出交易信号 -------------------------------- 每个index,每个变量只有一个值 ----
    // 对应的是 trading策略中的
    // PointsList<8, 9> ICO132_B; // 定义了一个买信号，类似一个bool类，如果在某个 index处，出现了买点，则会记录这个index在它自已的 vector 成员变量中。
    // PointsList<8, 9> ICO132_S; //
    // PLOT(ICO132_B, 0);  // 在这里， 信号 ICO132_B和ICO132_S的各自的成员vector的指针，被 push 到了 unit_array_[][]中的 pointslist_output中，
    // PLOT(ICO132_S, 0);  //  pointslist_output是一个vector,它用于记录所有要显示到前端的 信号的vector指针。
    // 每个 PointsList<8, 9>类型的变量，有一个vector<int>， pointslist_output会把他们都收集起来。
    for (auto tp : this->unit_array_[8][9]->pointslist_output) {
        memset(temp, '\0', 1024);
        std::string name;         //  1、名称
        std::vector<int> *points; //  2、是一个vector<int> 里面存储是index位置信息
        int color;                //  3、颜色 ？？
        auto tp2 = std::make_tuple(std::ref(name), std::ref(points), std::ref(color)) = tp;

        if (!points->empty() && points->back() == this->unit_array_[8][9]->index) {
            ret = snprintf(temp, 1024, ",\"%s\":\"true\"", //
                           name.c_str());                  //
            std::string temps(temp);
            happy = happy + temps;
        }
    }

    // segments_ output to web ----------------------------------------------------
    for (auto tp : this->unit_array_[8][9]->segmentslist_output) {
        memset(temp, '\0', 1024);
        std::string name;               //  1、名称
        std::vector<BoolSeg> *segments; //  2、是一个vector<int> 里面存储是index位置信息
        int color;                      //  3、颜色 ？？
        auto tp2 = std::make_tuple(std::ref(name), std::ref(segments), std::ref(color)) = tp;
        if (!segments->empty()) {
            // ------------ 画一条直线 ---------------------
            if (segments->back().value == true) {
                ret = snprintf(temp, 1024, ",\"%s\":\"1\"", //
                               name.c_str());               //
            } else {
                ret = snprintf(temp, 1024, ",\"%s\":\"0\"", //
                               name.c_str());               //
            }
            std::string temps(temp);
            happy = happy + temps;
            // ------------ 画一条直线 ---------------------

            // std::cout << " segments name: " << name << "  size: " << segments->size() << std::endl;
            std::string bbb = name + "_begin";
            std::string eee = name + "_end";
            if (segments->back().B == this->unit_array_[8][9]->index && segments->back().value == true) {
                // if (segments->back().B == this->unit_array_[8][9]->index) {
                ret = snprintf(temp, 1024, ",\"%s\":\"true\"", //
                               bbb.c_str());                   //
                std::string temps(temp);
                happy = happy + temps;
            }
        }
    }

    // 回测试结果输出 ---------------------------------------------------------------
    for (auto tp : this->unit_array_[8][9]->orderslist_output) {
        memset(temp, '\0', 1024);
        std::string name;           // 名称
        std::vector<Order> *orders; // pointslist类型，它所存储的数据，是一个vector<int> 里面存储是index位置信息
        int color;
        auto tp2 = std::make_tuple(std::ref(name), std::ref(orders), std::ref(color)) = tp;

        if (!orders->empty() && orders->back().idx == this->unit_array_[8][9]->index) {
            ret = snprintf(temp, 1024, ",\"%s\":\"%d\"", //
                           name.c_str(),                 //
                           orders->back().buyposition);  //
            std::string temps(temp);
            happy = happy + temps;
        }
    }
    // 回测试结果输出 ---------------------------------------------------------------

    std::string forsend;
    forsend = std::string(desc) + happy + "}";

    std::cout << forsend << std::endl;

    this->web_ws_->send(forsend.c_str());
}

// 初始化时，会将 ohlcv数据文件名 赋值给 this->kbarfile_
// onMessages会读取这个文件，进行策略处理，【this->onBarsHandler(i);】
// 每个切片处理完成后，会传给前端显示。 【this->senTradingData();】
void Base::onMessages() {
    std::cout << "B: onMessages! " << std::endl;
    char cBE[30]; // "xx:xx:xx--xx:xx:xx"
    char ActionDay[30];
    char Time[30];
    int tt;
    double jprice;
    std::string temp;
    std::fstream file;
    //  const char *BarF = "~/xquant/uquant/tests/mock/fu2309_1F.text";
    //  const char *filename = "/home/rabbit/xquant/uquant/tests/mock/trader_test/CF2405_1F.txt";
    // file.open(BarF, std::ios::in);
    if (this->kbarfile_.empty()) {
        std::cout << "base.kbarfile_ has not init ! " << std::endl;
        exit(-1);
    }
    file.open(this->kbarfile_);

    if (!file.is_open()) { // 检查文件是否成功打开
        std::cerr << "Error: " << strerror(errno);
        std::cerr << this->kbarfile_ << " onMessages() file open error !! " << std::endl;
        exit(0);
    }
    int i = 0;
    char datebefor[100];
    memset(datebefor, '\0', 100);

    while (std::getline(file, temp)) {
        memcpy(datebefor, this->unit_array_[8][9]->ActionDay, 8);
        sscanf(temp.c_str(), "%s %s %lg %lg %lg %lg %lg %d %lg", //
               unit_array_[8][9]->ActionDay,                     //
               unit_array_[8][9]->Time,                          //
               &unit_array_[8][9]->OO[i],                        //
               &unit_array_[8][9]->HH[i],                        //
               &unit_array_[8][9]->LL[i],                        //
               &unit_array_[8][9]->CC[i],                        //
               &unit_array_[8][9]->VV[i],                        //
               &tt,                                              //
               &jprice                                           //
        );

        // 下面这两个if 是将交易日改成正常actionday，否则前端日期显示有问题！
        if (strcmp(this->unit_array_[8][9]->Time, "2059") < 0) {
            //  memcpy(datebefor, this->unit_array_[8][9]->ActionDay, 8);
        }
        if (strcmp(this->unit_array_[8][9]->Time, "2059") > 0) {
            memcpy(this->unit_array_[8][9]->ActionDay, datebefor, 8);
        }

        unit_array_[8][9]->index = i;

        // std::cout << "  i: " << i << "  ";
        // std::cout << "  O: " << unit_array_[8][9]->OO[i] << "  ";
        // std::cout << "  H: " << unit_array_[8][9]->HH[i] << "  ";
        // std::cout << "  L: " << unit_array_[8][9]->LL[i] << "  ";
        // std::cout << "  C: " << unit_array_[8][9]->CC[i] << "  ";
        // std::cout << "  V: " << unit_array_[8][9]->VV[i] << "  ";

        // 只与OHLCV相关的函数调用，可以前置处理。比如 MA(C,55); 这里收盘价的55均线，
        // 当C序列有新的数据时，就可以在这里先计算，再调用onBarsHandler();
        unit_array_[8][9]->func_signal();     // todo 这是前置处理。是否还要加后置处理。
        this->onBarsHandler(i);               // todo 这个参数 i 应该是没有在trader里用到。
        unit_array_[8][9]->func_signal_end(); //   这是后置处理。

        if (i >= unit_array_[8][9]->repeat_index) { // 向前复制数据。
            unit_array_[8][9]->OO[i - unit_array_[8][9]->repeat_index] = unit_array_[8][9]->OO[i];
            unit_array_[8][9]->HH[i - unit_array_[8][9]->repeat_index] = unit_array_[8][9]->HH[i];
            unit_array_[8][9]->LL[i - unit_array_[8][9]->repeat_index] = unit_array_[8][9]->LL[i];
            unit_array_[8][9]->CC[i - unit_array_[8][9]->repeat_index] = unit_array_[8][9]->CC[i];
            unit_array_[8][9]->VV[i - unit_array_[8][9]->repeat_index] = unit_array_[8][9]->VV[i];
        }

        // 【发送到web !!】
        if (forweb_ && this->web_ws_ != nullptr) {
            if (i > 5000) {
                std::this_thread::sleep_for(std::chrono::milliseconds(20)); // 500
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
            this->sendTradingData();
        }
        // if (i == 10) {
        //     // file.close();
        //     break;
        //     //     exit(0);
        // }

        i++;
        if (i == KSIZE - 1) { // 数组移到从 KSIZE - REPEAT 开始。
            i = KSIZE - REPEAT - 1;
        }
    } //--while

    file.close();
    std::cout << "E: onMessages! " << std::endl;
    if (forweb_ && this->web_ws_ != nullptr) {
        // this->main_hub_->getDefaultGroup<uWS::SERVER>().close();
        this->web_ws_->terminate();
    }
    // todo 2023-11-26 在线程里面执行到这里时，如何退出 loop ？   请看 76行 新线程： main_hub_->onConnection([this](uWSclient *ws, uWS::HttpRequest req)
};

void Base::GetData(FUNCTIONS x, const char *para) {
    if (this->dat_ws_ == nullptr) {
        printf("websocket need to be init !!\n");
        exit(0);
    }
    if (this->future_map_.empty()) {
        printf("future_map is empty! need to be init !!\n");
        exit(0);
    }
    // 如果断线重连的话，para里的start_day, finish_day, 要更新！
    // todo !
    // first_get! second_get!,
    // 所以参数需要保存
    // 参数里会带 Future<M,N>，所以，根据M，N找到

    int first_get = true;

    switch (x) {
    case FUNCTIONS::FUN_GET_HISTORY_KBAR: {
        char msg[512];
        yyjson_doc *para_doc = yyjson_read(para, strlen(para), 0);
        yyjson_val *para_root = yyjson_doc_get_root(para_doc);
        //
        yyjson_val *future_list = yyjson_obj_get(para_root, "future_list");
        int m = 0; // need to get from para json
        int n = 1; // need to get from para json
        if (this->unit_array_[m][n] == nullptr) {
            printf("future: %d, period: %d need to be initialed! \n", m, n);
            yyjson_doc_free(para_doc);
            return;
        } else if (this->unit_array_[m][n]->is_first_get == true) {
            memcpy(this->unit_array_[m][n]->start_day, "20200808", 8);
            memcpy(this->unit_array_[m][n]->finish_day, "20230808", 8);
            memcpy(this->unit_array_[m][n]->start_time, "09:00:00", 8);
            memcpy(this->unit_array_[m][n]->finish_time, "23:00:00", 8);
            this->unit_array_[m][n]->is_first_get = false;
            this->dat_ws_->send(para);
        } else {
            memcpy(msg, "20200808 09:00:00 20230808 023:00:00", 35);
            this->dat_ws_->send(msg);
        }
        yyjson_doc_free(para_doc);
        this->dat_ws_->send("{\"action\":\"sub\", \"share\":\"GOOG\"}");
        // this->dat_ws_->send("ddd");
        break;
    }
    case FUNCTIONS::FUN_GET_HISTORY_TICK: {
        printf("2");
        break;
    }
    default:
        break;
    }
}

} // namespace uBEE