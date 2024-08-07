#include "future_env.h"

namespace uBEE {

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

int main_01() {
    int rtn;
    auto start = std::chrono::system_clock::now();

    Base bb;

    // Prepare_env();
    bb.mode_ = Mode::CHOOSING;
    //  使用本地数据 在base.cpp的onmessage()中，使用 tests/mock/中的fu2309.text 文件
    bb.remote_ = false;

    std::string sHome = std::getenv("HOME");
    if (sHome.empty()) {
        LOG(ERROR) << " HONE 环境变量不存在 ! ";
        rtn = 9001;
    }

    std::string filename = sHome + "/xquant/uquant/tests/mock/tbl/trader_macdkd.json";
    LOG(INFO) << filename;

    // bb为static 这里还需要 再次FutureInit吗,  index是否从0开始？ OHLCV如何？
    bb.FutureInit(filename);

    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    bb.onInit([&]() {
        printf("B: onInit() !!\n");
        bb.GetData(FUNCTIONS::FUN_GET_HISTORY_KBAR, "kkkk");
        printf("E: onInit() !!\n");
    });

    // todo 2023-11-14
    // Future<8, period_1F>需要解决前面这个合约序号8问题，最好自动生成？

    Future<8, period_1F> x(&bb); //  Future<8, 9> x(&bb);
    Future<8, period_5F> y(&bb); //  Future<8, 12> y(&bb);

    // FutureSerial<> O('o');
    FutureSerial<8, period_1F> O_1F('o');
    FutureSerial<8, period_1F> H_1F('h');
    FutureSerial<8, period_1F> L_1F('l');
    FutureSerial<8, period_1F> C_1F('c');
    FutureSerial<8, period_1F> V_1F('v');

    FutureSerial<8, period_5F> O_5F('o');
    FutureSerial<8, period_5F> H_5F('h');
    FutureSerial<8, period_5F> L_5F('l');
    FutureSerial<8, period_5F> C_5F('c');
    FutureSerial<8, period_5F> V_5F('v');

    // -------------------------------------------

    const static int A1 = 9;
    const static int B1 = 3;

    const static int V2 = 4;
    const static int A2 = 9 * V2;
    const static int B2 = 3 * V2;

    const static int V3 = 16;
    const static int A3 = 9 * V3;
    const static int B3 = 3 * V3;

    const static int V4 = 64;
    const static int A4 = 9 * V4;
    const static int B4 = 3 * V4;

    const static int V5 = 256;
    const static int A5 = 9 * V5;
    const static int B5 = 3 * V5;

    const static int V6 = 256 * 4;
    const static int A6 = 9 * V6;
    const static int B6 = 3 * V6;

    // -------------------------------------------
    RSV_t<8, 9> RSV1;
    EMA_t<8, 9> R1;
    SMA_t<8, 9> K1;

    RSV_t<8, 9> RSV2;
    EMA_t<8, 9> R2;
    SMA_t<8, 9> K2;
    EMA_t<8, 9> D2;
    SMA_t<8, 9> K22;
    EMA_t<8, 9> D22;
    SMA_t<8, 9> K23;
    EMA_t<8, 9> D23;

    RSV_t<8, 9> RSV3;
    EMA_t<8, 9> R3;
    SMA_t<8, 9> K3;
    EMA_t<8, 9> D3;
    SMA_t<8, 9> K32;
    EMA_t<8, 9> D32;
    SMA_t<8, 9> K33;
    EMA_t<8, 9> D33;

    RSV_t<8, 9> RSV4;
    EMA_t<8, 9> R4;
    SMA_t<8, 9> K4;
    EMA_t<8, 9> D4;
    SMA_t<8, 9> K42;
    EMA_t<8, 9> D42;
    SMA_t<8, 9> K43;
    EMA_t<8, 9> D43;

    RSV_t<8, 9> RSV5;
    EMA_t<8, 9> R5;
    SMA_t<8, 9> K5;
    EMA_t<8, 9> D5;
    SMA_t<8, 9> K52;
    EMA_t<8, 9> D52;
    SMA_t<8, 9> K53;
    EMA_t<8, 9> D53;

    const static int S2 = 12;
    const static int L2 = 26;
    const static int M2 = 9;

    const static int S3 = 12 * V2;
    const static int L3 = 26 * V2;
    const static int M3 = 9 * V2;

    const static int S4 = 12 * V3;
    const static int L4 = 26 * V3;
    const static int M4 = 9 * V3;

    const static int S5 = 12 * V4;
    const static int L5 = 26 * V4;
    const static int M5 = 9 * V4;

    const static int S6 = 12 * V5;
    const static int L6 = 26 * V5;
    const static int M6 = 9 * V5;

    // MACD 2
    FutureSerial<8, 9> DIF2;
    EMA_t<8, 9> X2;
    EMA_t<8, 9> DEA2;
    EMA_t<8, 9> EMA_S2(OHLCV::C1, S2);
    EMA_t<8, 9> EMA_L2(OHLCV::C1, L2);

    // MACD 3
    FutureSerial<8, 9> DIF3;
    EMA_t<8, 9> X3;
    EMA_t<8, 9> DEA3;
    EMA_t<8, 9> EMA_S3(OHLCV::C1, S3);
    EMA_t<8, 9> EMA_L3(OHLCV::C1, L3);

    // MACD 4
    FutureSerial<8, 9> DIF4;
    EMA_t<8, 9> X4;
    EMA_t<8, 9> DEA4;
    EMA_t<8, 9> EMA_S4(OHLCV::C1, S4);
    EMA_t<8, 9> EMA_L4(OHLCV::C1, L4);

    // MACD 5
    FutureSerial<8, 9> DIF5;
    EMA_t<8, 9> X5;
    EMA_t<8, 9> DEA5;
    EMA_t<8, 9> EMA_S5(OHLCV::C1, S5);
    EMA_t<8, 9> EMA_L5(OHLCV::C1, L5);

    PLOT(DEA5, 120);
    // DEA5.plot("DEA5", 120);

    // MACD 6
    FutureSerial<8, 9> DIF6;
    EMA_t<8, 9> X6;
    EMA_t<8, 9> DEA6;
    EMA_t<8, 9> EMA_S6(OHLCV::C1, S6);
    EMA_t<8, 9> EMA_L6(OHLCV::C1, L6);

    PointsList<8, 9> YB_32;
    PointsList<8, 9> YS_32;

    PointsList<8, 9> ICO132_B;
    PointsList<8, 9> ICO132_S;

    int iii = 0;
    bb.onBars([&](int e) {
        iii++;

        // KD 1
        {
            // 这里的RSV使用的是close, 不可变。
            // RSV_T<8,9> 相当于是一个type。 用其定义一个对象。 // 源代码参看：new_talib.h
            RSV1.rsv(A1); // RSV1:=(C-LLV(C,A1))/(HHV(C,A1)-LLV(C,A1))*100
            R1.ema(RSV1, 1);
            K1.sma(RSV1, B1, 1);
        }

        // KD 2
        {
            RSV2.rsv(A2);
            R2.ema(RSV2, 2);
            K2.sma(R2, B2, 1);
            D2.ema(K2, B2);
            K22.sma(R2, B1 * 2, 1);
            D22.ema(K22, 2);
            K23.sma(R2, B1, 1);
            D23.ema(K23, 2);
        }

        // KD 3
        {
            RSV3.rsv(A3);
            R3.ema(RSV3, 8);
            K3.sma(R3, B3, 1);
            D3.ema(K3, B3 / 2);
            K32.sma(R3, B2 * 2, 1);
            D32.ema(K32, B2);
            K33.sma(R3, B2, 1);
            D33.ema(K33, B2);
        }

        // KD 4
        {
            /*
            RSV_T<8, 9> RSV4(A4);
            RSV4.rsv();
            EMA_T<8, 9> R4(RSV4, 13);
            R4.ema();
            SMA_T<8, 9> K4(R4, B4, 55);
            K4.sma();
            EMA_T<8, 9> D4(K4, B4 / 2);
            D4.ema();
            SMA_T<8, 9> K42(R4, B3 * 2, 1);
            K42.sma();
            EMA_T<8, 9> D42(K42, 2);
            D42.ema();
            SMA_T<8, 9> K43(R4, B3, 1);
            K43.sma();
            EMA_T<8, 9> D43(K43, 2);
            D43.ema();
            */
            RSV4.rsv(A4);
            R4.ema(RSV4, 34);
            K4.sma(R4, B4, 1);
            D4.ema(K4, B4 / 2);
            K42.sma(R4, B3 * 2, 1);
            D42.ema(K42, B3);
            K43.sma(R4, B3, 1);
            D43.ema(K43, B3 / 2);
        }

        // KD 5
        {
            RSV5.rsv(A5);
            R5.ema(RSV5, 55);
            K5.sma(R5, B5, 1);
            D5.ema(K5, B4);
            K52.sma(R5, B4 * 2, 1);
            D52.ema(K52, B4);
            K53.sma(R5, B4, 1);
            D53.ema(K53, B4 / 2);
        }

        // KD 6
        {
            /*
            // KD 6
            RSV_T<8, 9> RSV6(A6);
            EMA_T<8, 9> R6(RSV6, 55);
            SMA_T<8, 9> K6(R6, B6, 1);
            EMA_T<8, 9> D6(K6, B6 / 2);
            SMA_T<8, 9> K62(R6, B4 * 2, 1);
            EMA_T<8, 9> D62(K62, B4);
            SMA_T<8, 9> K63(R6, B4, 1);
            EMA_T<8, 9> D63(K63, B4 / 2);
            */
        }

        // MACD 2
        {
            EMA_S2.ema();
            EMA_L2.ema();
            // EMA_S2.ema(C_1F, S2);
            //  EMA_L2.ema(C_1F, L2);
            DIF2 = EMA_S2 - EMA_L2;
            X2.EMA(DIF2, 1);
            DEA2.EMA(X2, M2);
        }

        // MACD 3
        {
            EMA_S3.ema();
            EMA_L3.ema();
            DIF3 = (EMA_S3.ema() - EMA_L3.ema()) / 1.5;
            X3.ema(DIF3, 55);
            DEA3.ema(X3, M3);
        }

        // MACD 4
        {
            EMA_S4.ema();
            EMA_L4.ema();
            DIF4 = (EMA_S4 - EMA_L4) / 1.5 / 1.5;
            X4.EMA(DIF4, 89);
            DEA4.EMA(X4, 144);
        }

        // MACD 5
        {
            EMA_S5.ema();
            EMA_L5.ema();
            DIF5 = (EMA_S5 - EMA_L5) / 1.5 / 1.5 / 1.5;
            X5.EMA(DIF5, 144);
            DEA5.EMA(X5, 144);
        }

        // MACD 6
        {
            EMA_S6.ema();
            EMA_L6.ema();
            DIF6 = (EMA_S6 - EMA_L6) / 1.5 / 1.5 / 1.5 / 1.5;
            X6.EMA(DIF6, 144);
            DEA6.EMA(X6, M6);
        }

        bool X_B32 = (X2 < 0 && X3 < 0 && X2 > X3);
        bool X_S32 = (X2 > 0 && X3 > 0 && X2 < X3);
        bool X_B43 = (X3 < 0 && X4 < 0 && X3 > X4);
        bool X_S43 = (X3 > 0 && X4 > 0 && X3 < X4);
        bool X_B54 = (X4 < 0 && X5 < 0 && X4 > X5);
        bool X_S54 = (X4 > 0 && X5 > 0 && X4 < X5);

        // PLOT(X_S54, 33);
        // PLOT(K3, 120);
        // PLOT(D3, 120);
        // PLOT(K32, 120);
        // PLOT(D32, 120);
        // PLOT(K33, 120);
        // PLOT(D33, 120);
        // DEA5.plot("DEA5", 120);

        bool m_line = C_1F >= O_1F;                                 // 阳线 收盘价大于开盘价
        bool f_line = C_1F <= O_1F;                                 // 阴线 收盘价小于开盘价
        bool m_pin = C_1F >= O_1F && (C_1F - L_1F) < (H_1F - C_1F); // 阳线 长影线
        bool f_pin = C_1F <= O_1F && (C_1F - L_1F) > (H_1F - C_1F); // 阴线 长影线

        bool BC = K1 > K1.ref(1) || C_1F > C_1F.ref(1) || m_line || f_pin;
        bool SC = K1 < K1.ref(1) || C_1F < C_1F.ref(1) || f_line || m_pin;

        bool YB1 = RSV1 > RSV1.ref(1) && RSV1.ref(1) < 6;
        bool YS1 = RSV1 < RSV1.ref(1) && RSV1.ref(1) > 94;
        bool YB2 = RSV2 > RSV2.ref(1) && RSV2.ref(1) < 6;
        bool YS2 = RSV2 < RSV2.ref(1) && RSV2.ref(1) > 94;
        bool YB3 = RSV3 > RSV3.ref(1) && RSV3.ref(1) < 6;
        bool YS3 = RSV3 < RSV3.ref(1) && RSV3.ref(1) > 94;
        bool YB4 = RSV4 > RSV4.ref(1) && RSV4.ref(1) < 6;
        bool YS4 = RSV4 < RSV4.ref(1) && RSV4.ref(1) > 94;
        bool YB5 = RSV5 > RSV5.ref(1) && RSV5.ref(1) < 6;
        bool YS5 = RSV5 < RSV5.ref(1) && RSV5.ref(1) > 94;

        //---------------------【红蓝绿粉】>>>
        //*****************************************************************************
        // static PointsList<8, 9> YB_32;
        // static PointsList<8, 9> YS_32;

        YB_32 = RSV2 >= RSV3 && RSV2.ref(1) >= RSV3.ref(1);      //*****
        bool YB_43 = RSV3 >= RSV4 && RSV3.ref(1) >= RSV4.ref(1); //*****
        bool YB_54 = RSV4 >= RSV5 && RSV4.ref(1) >= RSV5.ref(1); //*****
        YS_32 = RSV2 <= RSV3 && RSV2.ref(1) <= RSV3.ref(1);      //*****
        bool YS_43 = RSV3 <= RSV4 && RSV3.ref(1) <= RSV4.ref(1); //*****
        bool YS_54 = RSV4 <= RSV5 && RSV4.ref(1) <= RSV5.ref(1); //*****
                                                                 //------------------【5：RSV粉线到底为0】-------------------------------------------------------------------------------------------------------------------
        bool YB5_2 = YB2 && YB_32 && YB_43 && YB_54;             //*****
        bool YB5_3 = YB3 && YB_43 && YB_54;                      //*****
        bool YB5_4 = YB4 && YB_54;                               //*****
        bool YB5_5 = YB5;                                        //*****
        bool YS5_2 = YS2 && YS_32 && YS_43 && YS_54;             //*****
        bool YS5_3 = YS3 && YS_43 && YS_54;                      //*****
        bool YS5_4 = YS4 && YS_54;                               //*****
        bool YS5_5 = YS5;                                        //*****
                                                                 //------------------【4：RSV蓝线到底为0】------------------------------------------------
        bool YB4_2 = YB2 && YB_32 && YB_43;                      //  ->>>- //*****
        bool YB4_3 = YB3 && YB_43;                               //  -->>- //*****
        bool YB4_4 = YB4;                                        //*****
        bool YS4_2 = YS2 && YS_32 && YS_43;                      //*****
        bool YS4_3 = YS3 && YS_43;                               //*****
        bool YS4_4 = YS4;                                        //*****
                                                                 //------------------【3：RSV绿线到底为0】------------------------------------------------
        bool YB3_2 = YB2 && YB_32;                               //*****
        bool YB3_3 = YB3;                                        //*****
        bool YS3_2 = YS2 && YS_32;                               //*****
        bool YS3_3 = YS3;                                        //*****

        bool H_KPB2 = (K23 > K2 || K22 > K2);
        bool H_KPS2 = (K23 < K2 || K22 < K2);

        // static bool H_KPP2 = H_KPB2 && H_KPS2;        // 【重叠部分】
        // static bool H_KCB2 = BARSLAST(!(H_KPB2));   //  粉线上涨周期
        // static bool H_KCS2 = BARSLAST(!(H_KPS2));   // 粉线下跌周期
        // static bool H_KDB2 = COUNT(H_KPS2 && !(REF(H_KPS2, 1)),
        //                            H_KCB2 + 1);  // 粉线上涨周期内，有多少次  MACD 和 KD同时上涨
        // static bool H_KDS2 = COUNT(H_KPB2 && !(REF(H_KPB2, 1)), H_KCS2 + 1);
        // static bool H_KTB2 = (H_KPP2 && !(H_KDB2));  //  上涨的 头部
        // static bool H_KTS2 = (H_KPP2 && !(H_KDS2));
        // static bool H_KB2 = (H_KPB2 && !(H_KTS2));  //
        // static bool H_KS2 = (H_KPS2 && !(H_KTB2));  //

        bool H_XPB2 = (K23 > K2 || K22 > K2 || X2 > X2.ref(1));
        bool H_XPS2 = (K23 < K2 || K22 < K2 || X2 < X2.ref(1));

        // static bool H_XPP2 = H_XPB2 && H_XPS2;  // 【重叠部分】
        // static bool H_XCB2 = BARSLAST(!(H_XPB2));  //  粉线上涨周期
        // static bool H_XCS2 = BARSLAST(!(H_XPS2));  // 粉线下跌周期
        // static bool H_XDB2 = COUNT(H_XPS2 && !(REF(H_XPS2, 1)),
        //                            H_XCB2 + 1);  // 粉线上涨周期内，有多少次  MACD 和 KD同时上涨
        // static bool H_XDS2 = COUNT(H_XPB2 && !(REF(H_XPB2, 1)), H_XCS2 + 1);
        // static bool H_XTB2 = (H_XPP2 && !(H_XDB2));  //  上涨的 头部
        // static bool H_XTS2 = (H_XPP2 && !(H_XDS2));
        // static bool H_XB2 = (H_XPB2 && !(H_XTS2));  //
        // static bool H_XS2 = (H_XPS2 && !(H_XTB2));  //

        bool H_KPB3 = (K33 > K3 || K32 > K3 || X3 > REF(X3, 1));
        bool H_KPS3 = (K33 < K3 || K32 < K3 || X3 < REF(X3, 1));

        // static bool H_KPP3 = H_KPB3 && H_KPS3;       // 【重叠部分】
        // static bool H_KCB3 = BARSLAST(!(H_KPB3));  //  粉线上涨周期
        // static bool H_KCS3 = BARSLAST(!(H_KPS3));  // 粉线下跌周期
        // static bool H_KDB3 = COUNT(H_KPS3 && !(REF(H_KPS3, 1)),
        //                            H_KCB3 + 1);  // 粉线上涨周期内，有多少次  MACD 和 KD同时上涨
        // static bool H_KDS3 = COUNT(H_KPB3 && !(REF(H_KPB3, 1)), H_KCS3 + 1);
        // static bool H_KTB3 = (H_KPP3 && !(H_KDB3));  //  上涨的 头部
        // static bool H_KTS3 = (H_KPP3 && !(H_KDS3));
        // static bool H_KB3 = (H_KPB3 && !(H_KTS3));  //
        // static bool H_KS3 = (H_KPS3 && !(H_KTB3));  //

        bool H_KPB4 = (K43 > K4 || K42 > K4 || X4 > REF(X4, 1));
        bool H_KPS4 = (K43 < K4 || K42 < K4 || X4 < REF(X4, 1));

        // static bool H_KPP4 = H_KPB4 && H_KPS4;       // 【重叠部分】
        // static bool H_KCB4 = BARSLAST(!(H_KPB4));  //  粉线上涨周期
        // static bool H_KCS4 = BARSLAST(!(H_KPS4));  // 粉线下跌周期
        // static bool H_KDB4 = COUNT(H_KPS4 && !(REF(H_KPS4, 1)),
        //                H_KCB4 + 1);  // 粉线上涨周期内，有多少次 MACD
        // 和 KD同时上涨 //static bool H_KDS4 = COUNT(H_KPB4 && !(REF(H_KPB4, 1)), H_KCS4 + 1);
        // static bool H_KTB4 = (H_KPP4 && !(H_KDB4));  //  上涨的 头部
        // static bool H_KTS4 = (H_KPP4 && !(H_KDS4));
        // static bool H_KB4 = (H_KPB4 && !(H_KTS4));  //             || (H_KPP4
        //&&  K4>REF(K4,1)) static bool H_KS4 = (H_KPS4 && !(H_KTB4));  //           || (H_KPP4
        //&&  K4<REF(K4,1))

        bool H_KPB5 = (K53 > K5 || K52 > K5 || X5 > REF(X5, 1));
        bool H_KPS5 = (K53 < K5 || K52 < K5 || X5 < REF(X5, 1));

        // static bool H_KPP5 = H_KPB5 && H_KPS5;          // 【重叠部分】P
        // static bool H_KCB5 = BARSLAST(!(H_KPB5));     //  粉线上涨周期
        // static bool H_KCS5 = BARSLAST(!(H_KPS5));     // 粉线下跌周期
        // static bool H_KDB5 = COUNT(H_KPS5 && !(REF(H_KPS5, 1)),
        //                        H_KCB5 + 1);  // 粉线上涨周期内，有多少次  MACD 和 KD同时上涨
        // static bool H_KDS5 = COUNT(H_KPB5 && !(REF(H_KPB5, 1)), H_KCS5 + 1);
        // static bool H_KTB5 = (H_KPP5 && !(H_KDB5));  //  上涨的 头部
        // static bool H_KTS5 = (H_KPP5 && !(H_KDS5));
        // static bool H_KB5 = (H_KPB5 && !(H_KTS5));  //             || (H_KPP5  &&  K5>REF(K5,1))
        // static bool H_KS5 = (H_KPS5 && !(H_KTB5));  //             || (H_KPP5  &&  K5<REF(K5,1))

        bool BBP = (YB2 || YB3 || YB4 || YB5); // BC &&
        bool SSP = (YS2 || YS3 || YS4 || YS5); // SC &&

        bool B_2345 = YB2 && YB3 && YB4 && YB5; // 2345全部
        bool S_2345 = YS2 && YS3 && YS4 && YS5; // 2345全部

        bool B_234X = YB2 && YB3 && YB4 && !(YB5); // 234买
        bool S_234X = YS2 && YS3 && YS4 && !(YS5); // 234卖

        bool B_23XX = YB2 && YB3 && !(YB4) && !(YB5); // 23买
        bool S_23XX = YS2 && YS3 && !(YS4) && !(YS5); // 23卖

        bool B_X345 = !(YB2) && YB3 && YB4 && YB5; // 345买
        bool S_X345 = !(YS2) && YS3 && YS4 && YS5; // 345卖

        bool B_XX45 = !(YB2) && !(YB3) && YB4 && YB5; // 45买
        bool S_XX45 = !(YS2) && !(YS3) && YS4 && YS5; // 45卖

        bool BK_5 = !(H_KPB5) && H_KPB4; //  大粉线空缺处
        bool SK_5 = !(H_KPS5) && H_KPS4; // 大粉线空缺处

        // static bool TB01 = H_KB4 && H_KB3;
        // static bool TS01 = H_KS4 && H_KS3;

        bool TB02 = H_KPB5 || H_KPB4 || H_KPB3;
        bool TS02 = H_KPS5 || H_KPS4 || H_KPS3;

        if (TB02) {
            LOG(ERROR) << K2.unit->ActionDay << "  " << K2.unit->Time << "    " << O_1F.cur() << " " << H_1F.cur() << " " << L_1F.cur() << " " << C_1F.cur();
        }

        bool TBALL5 = K53 > REF(K53, 1) && K52 > REF(K52, 1) && K5 > REF(K5, 1);
        bool TSALL5 = K53 < REF(K53, 1) && K52 < REF(K52, 1) && K5 < REF(K5, 1);

        bool TBALL4 = K43 > REF(K43, 1) && K42 > REF(K42, 1) && K4 > REF(K4, 1);
        bool TSALL4 = K43 < REF(K43, 1) && K42 < REF(K42, 1) && K4 < REF(K4, 1);

        bool TBALL3 = K33 > REF(K33, 1) && K32 > REF(K32, 1) && K3 > REF(K3, 1);
        bool TSALL3 = K33 < REF(K33, 1) && K32 < REF(K32, 1) && K3 < REF(K3, 1);

        // 牛头
        bool BB01 = TB02 && X_B32 && X_B43 && D3 < 30 && D4 < 30 && BC && K2 > REF(K2, 1) && REF(K2, 1) < REF(K2, 2) && REF(K2, 1) < 20 && YB5_4 && K53 < 10; //&& KB3 && KB4
        bool SS01 = TS02 && X_S32 && X_S43 && D3 > 70 && D4 > 70 && SC && K2 < REF(K2, 1) && REF(K2, 1) > REF(K2, 2) && REF(K2, 1) > 80 && YS5_4 && K53 > 90; //&& KS3 && KS4
        //----------------------------------------------------------------------------------------------------------------------------------------------------------------

        bool ICO137 = TB02 && BBP && (K33 < 20);               //  ----【绿桃心】 绿80
        bool ICO138 = TS02 && SSP && (K33 > 80);               //---- 【橙三角】 绿80  红80
        bool ICO112 = TB02 && BBP && (K33 < 20) && (K23 < 20); //
        bool ICO113 = TS02 && SSP && (K33 > 80) && (K23 > 80); //

        /// LOG(INFO) << ICO137 << " ttt";

        /// if (ICO137) {
        ///     LOG(INFO) << K2.unit->ActionDay << " ----【绿桃心】 绿80  " << K2.unit->Time << " " << C_1F.cur() << " " << O_1F.cur();
        /// }

        bool ICO148 = TB02 && BBP && (K33 < 10); // , -50, 'ICO148');  // ---- 【绿心】 绿90
        bool ICO149 = TS02 && SSP && (K33 > 90); // , 140, 'ICO148');  //

        bool ICO92 = TB02 && BBP && (K33 < 10) && (K23 < 10); // ---- 【太阳花】 绿90  红90
        bool ICO93 = TS02 && SSP && (K33 > 90) && (K23 > 90); //

        ///  LOG(INFO) << ICO92 << " ttt-ttt";

        bool ICO158 = TB02 && BBP && (K33 < 10) && (K32 < 10); // ---- 【红水滴】 绿90 绿90
        bool ICO159 = TS02 && SSP && (K33 > 90) && (K32 > 90); //

        // static bool ICO = BBP && ((H_KPB3 && !(H_KS5 && H_KS4)) || (H_KB5 && H_KB4));
        // static bool ICO = SSP && ((H_KPS3 && !(H_KB5 && H_KB4)) || (H_KS5 && H_KS4));

        bool ICO1 = YB2 && YB3 && YB4 && YB5 && H_KPB5; //
        bool ICO2 = YS2 && YS3 && YS4 && YS5 && H_KPS5; //

        /*
        DRAWICON(YB2    AND (   X5>REF(X5,1)   OR X4>REF(X4,1)        )    ,-31,'ICO132');  // 【橙色五角星】
        DRAWICON(YS2    AND (   X5<REF(X5,1)   OR X4<REF(X4,1)        )    ,126,'ICO132');

        DRAWICON(YB2    AND (   X5>REF(X5,1)   OR X4>REF(X4,1)    )  AND  K23<10  ,-31,'ICO128');  // 【粉棱形】
        DRAWICON(YS2    AND (   X5<REF(X5,1)   OR X4<REF(X4,1)    )   AND  K23>90 ,126,'ICO128');

        DRAWICON(YB2  AND  YB3 AND YB4 AND YB5 AND  H_KPB5  ,-25,'ICO138');  // 【橙色五角星】^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        DRAWICON(YS2 AND  YS3 AND YS4 AND YS5 AND  H_KPS5   ,120,'ICO138');
        */

        ICO132_B = (YB2 && (X5 > X5.ref(1) || X4 > X4.ref(1))); // 【基本正确！！ 2023-11-17】
        ICO132_S = (YS2 && (X5 < X5.ref(1) || X4 < X4.ref(1)));

        if (ICO132_B == true) {
            LOG(ERROR) << K2.unit->ActionDay << " ----【绿桃心】 绿80  " << K2.unit->Time << " " << C_1F.cur() << " " << O_1F.cur();
            // LOG(ERROR) << x.unit->index << "  index !! ";
            // for (auto ix : ICO132_B.points_) {
            //     LOG(ERROR) << ix << " O: " << ICO132_B.O[ix] << " H: " << ICO132_B.H[ix] << " L: " << ICO132_B.L[ix] << " C: " << ICO132_B.C[ix];
            // }
            // exit(-1);
        }

        // for (auto tp : x.unit->output) {
        //     std::string name;
        //     double *data;
        //     int color;
        //     auto tp2 = std::make_tuple(std::ref(name), std::ref(data), std::ref(color)) = tp;
        //     double *kk = std::get<1>(tp);
        //     LOG(INFO) << " hahaha :: is ok ? :: " << name << " " << kk[x.unit->index];
        // }

        // if (iii == 10) {
        //     exit(-1);
        // }
    }); // end onBar() ;

    PLOT(K3, 120);
    PLOT(D3, 120);
    PLOT(K32, 120);
    PLOT(D32, 120);
    PLOT(K33, 120);
    PLOT(D33, 120);

    bb.Run();

    std::cout << ICO132_B.points_.size() << "    -------------------------------------    ICO132_B.points_.size() ICO132_B.points_.size()      " << std::endl;
    for (auto ix : ICO132_B.points_) {
        LOG(ERROR) << ix << " O: " << ICO132_B.OO[ix] << " H: " << ICO132_B.HH[ix] << " L: " << ICO132_B.LL[ix] << " C: " << ICO132_B.CC[ix];
    }

    // for (int i = 100; i > 0; i--) {
    //     //   LOG(INFO) << " " << K22.ref(i) << " " << K23.ref(i) << " -- " << K3.ref(i) << " " << K33.ref(i) << " " << D33.ref(i) << " -- " << K4.ref(i) << " " << D4.ref(i) << " " << K43.ref(i) << " " << D43.ref(i) << " -- " << O_1F.ref(i) << " " << C_1F.ref(i);
    // }

    auto end = std::chrono::system_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "花费了" << double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den << "秒" << std::endl;
    return 0;
}

int trading_test1() {
    for (int i = 0; i < 5; i++) {
        main_01();
    }
    return 0;
}
} // namespace uBEE