#pragma once

namespace uBEE {

template <int... N> class IND_KD_MACD : public OhlcvSerial<N...> {
  public:
    // ########################################################### KD ######
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

    // ############################################################# MACD ######

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
    // ---------------------------------------------------
    FutureSerial<N...> O{'o'};
    // FutureSerial<N...> H{'h'};
    // FutureSerial<N...> L{'l'};
    FutureSerial<N...> C{'c'};
    // FutureSerial<N...> V{'v'};

    RSV_t<N...> RSV1;
    EMA_t<N...> R1;
    SMA_t<N...> K1;

    RSV_t<N...> RSV2;
    EMA_t<N...> R2;
    SMA_t<N...> K2;
    EMA_t<N...> D2;
    SMA_t<N...> K22;
    EMA_t<N...> D22;
    SMA_t<N...> K23;
    EMA_t<N...> D23;

    RSV_t<N...> RSV3;
    EMA_t<N...> R3;
    SMA_t<N...> K3;
    EMA_t<N...> D3;
    SMA_t<N...> K32;
    EMA_t<N...> D32;
    SMA_t<N...> K33;
    EMA_t<N...> D33;

    RSV_t<N...> RSV4;
    EMA_t<N...> R4;
    SMA_t<N...> K4;
    EMA_t<N...> D4;
    SMA_t<N...> K42;
    EMA_t<N...> D42;
    SMA_t<N...> K43;
    EMA_t<N...> D43;

    RSV_t<N...> RSV5;
    EMA_t<N...> R5;
    SMA_t<N...> K5;
    EMA_t<N...> D5;
    SMA_t<N...> K52;
    EMA_t<N...> D52;
    SMA_t<N...> K53;
    EMA_t<N...> D53;

    // MACD 2
    FutureSerial<N...> DIF2;
    EMA_t<N...> X2;
    EMA_t<N...> DEA2;
    EMA_t<N...> EMA_S2{OHLCV::C1, S2}; // 这种写法很牛嘛！
    EMA_t<N...> EMA_L2{OHLCV::C1, L2};

    // MACD 3
    FutureSerial<N...> DIF3;
    EMA_t<N...> X3;
    EMA_t<N...> DEA3;
    EMA_t<N...> EMA_S3{'c', S3};
    EMA_t<N...> EMA_L3{'C', L3};

    // MACD 4
    FutureSerial<N...> DIF4;
    EMA_t<N...> X4;
    EMA_t<N...> DEA4;
    EMA_t<N...> EMA_S4;
    EMA_t<N...> EMA_L4;

    // MACD 5
    FutureSerial<N...> DIF5;
    EMA_t<N...> X5;
    EMA_t<N...> DEA5;
    EMA_t<N...> EMA_S5;
    EMA_t<N...> EMA_L5;

    // MACD 6
    FutureSerial<N...> DIF6;
    EMA_t<N...> X6;
    EMA_t<N...> DEA6;
    EMA_t<N...> EMA_S6;
    EMA_t<N...> EMA_L6;

    // ======== 记录诸如 cross(ma5,ma10) 之类的点 ==买卖点================
    PointsList<N...> YB_32;
    PointsList<N...> YS_32;

    PointsList<N...> ICO132_B; //  【橙色五角星】
    PointsList<N...> ICO132_S; //  【橙色五角星】

    PointsList<N...> ICO137_B; // ----【绿桃心】 绿80
    PointsList<N...> ICO137_S; // ----【绿桃心】 绿80

    PointsList<N...> ICO112_B; // ---- 【橙三角】 绿80  红80
    PointsList<N...> ICO112_S; // ---- 【橙三角】 绿80  红80

    PointsList<N...> ICO148_B; // ---- 【绿心】 绿90
    PointsList<N...> ICO148_S; // ---- 【绿心】 绿90

    PointsList<N...> ICO92_B; // ---- 【太阳花】 绿90  红90
    PointsList<N...> ICO92_S; // ---- 【太阳花】 绿90  红90

    BoolsegsList<N...> H_KPP5;
    BoolsegsList<N...> H_KPB5;
    BoolsegsList<N...> H_KPS5;
    BoolsegsList<N...> H_KB5;
    BoolsegsList<N...> H_KS5;

    StopsegsList<N...> H_KPP3;
    StopsegsList<N...> H_KPB3;
    StopsegsList<N...> H_KPS3;
    StopsegsList<N...> H_KB3;
    StopsegsList<N...> H_KS3;

    BoolsegsList<N...> H_KPP4;
    BoolsegsList<N...> H_KPB4;
    BoolsegsList<N...> H_KPS4;
    BoolsegsList<N...> H_KB4;
    BoolsegsList<N...> H_KS4;

    BoolSerial<N...> TB02;
    BoolSerial<N...> TS02;

  public:
    IND_KD_MACD() {
        //   EMA_S2.ema(OHLCV::C1, S2);
        //   EMA_L2.ema(OHLCV::C1, L2);  // 改成了上面的写法
        //   EMA_S3.ema(OHLCV::C1, S3); // 这种写法也行，但看起来不太好。最好是在构造函数里搞定。
        //   EMA_L3.ema('C', L3);
        EMA_S4.ema('c', S4);
        EMA_L4.ema('C', L4);
        EMA_S5.ema(OHLCV::C1, S5);
        EMA_L5.ema(OHLCV::C1, L5);
        EMA_S6.ema(OHLCV::C1, S6);
        EMA_L6.ema(OHLCV::C1, L6);

        PLOT(K2, 0);
        PLOT(D2, 0);
        PLOT(K22, 0);
        PLOT(K23, 0);
        PLOT(K3, 0);
        PLOT(D3, 0);
        PLOT(K33, 0);
        PLOT(D33, 0);
        PLOT(K4, 0);
        PLOT(D4, 0);
        PLOT(K43, 0);
        PLOT(D43, 0);
        PLOT(K5, 0);
        PLOT(D5, 0);
        PLOT(K53, 0);
        PLOT(D53, 0);

        PLOT(K3, 120);
        PLOT(D3, 120);
        PLOT(K32, 120);
        PLOT(D32, 120);
        PLOT(K33, 120);
        PLOT(D33, 120);

        // ===收集上传到web ======================
        PLOT(X2, 0);
        PLOT(DEA2, 0);
        PLOT(X3, 0);
        PLOT(DEA3, 0);
        PLOT(X4, 0);
        PLOT(DEA4, 0);
        PLOT(X5, 0);
        PLOT(DEA5, 0);
        PLOT(X6, 0);
        PLOT(DEA6, 0);

        PLOT(ICO132_B, 0); //  【橙色五角星】
        PLOT(ICO132_S, 0); //  【橙色五角星】
        PLOT(ICO137_B, 0); // ----【绿桃心】 绿80
        PLOT(ICO137_S, 0); // ----【绿桃心】 绿80
        PLOT(ICO112_B, 0); // ---- 【橙三角】 绿80  红80
        PLOT(ICO112_S, 0); // ---- 【橙三角】 绿80  红80
        PLOT(ICO148_B, 0); // ---- 【绿心】 绿90
        PLOT(ICO148_S, 0); // ---- 【绿心】 绿90
        PLOT(ICO92_B, 0);  // ---- 【太阳花】 绿90  红90
        PLOT(ICO92_S, 0);  // ---- 【太阳花】 绿90  红90

        PLOT(H_KB5, 0);
        PLOT(H_KPB5, 0);
        PLOT(H_KS5, 0);
        PLOT(H_KPS5, 0);
        PLOT(H_KB3, 0);
        PLOT(H_KS3, 0);
        PLOT(H_KPB3, 0);
        PLOT(H_KPS3, 0);
        PLOT(H_KPB4, 0);
        PLOT(H_KPS4, 0);
    };

    // ======== 记录诸如 cross(ma5,ma10) 之类的点 ===================

    void run() {

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
            D33.EMA(K33, B2);
        }

        // KD 4
        {
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
            RSV_T<N...> RSV6(A6);
            EMA_T<N...> R6(RSV6, 55);
            SMA_T<N...> K6(R6, B6, 1);
            EMA_T<N...> D6(K6, B6 / 2);
            SMA_T<N...> K62(R6, B4 * 2, 1);
            EMA_T<N...> D62(K62, B4);
            SMA_T<N...> K63(R6, B4, 1);
            EMA_T<N...> D63(K63, B4 / 2);
            */
        }

        // MACD 2
        {
            //  EMA_S2.ema();
            //  EMA_L2.ema();
            //  EMA_S2.ema(C_1F, S2);
            //  EMA_L2.ema(C_1F, L2);
            DIF2 = EMA_S2 - EMA_L2;
            X2.EMA(DIF2, 1);
            DEA2.EMA(X2, 3);
        }

        // MACD 3
        {
            //  EMA_S3.ema();
            //  EMA_L3.ema();
            // DIF3 = (EMA_S3.ema() - EMA_L3.ema()) / 1.5; // todo 这种方式，ema()是否执再执行了一次？
            // X3.ema(DIF3, 55);
            X3.ema((EMA_S3.ema() - EMA_L3.ema()) / 1.5, 55);
            DEA3.ema(X3, 13);

            if (X3 > X3.ref(1)) {
                X3.set_section(100);
            } else {
                X3.set_section(200);
            }
        }

        // MACD 4
        {
            EMA_S4.ema();
            EMA_L4.EMA();
            DIF4 = (EMA_S4 - EMA_L4) / 1.5 / 1.5;
            X4.EMA(DIF4, 89);
            DEA4.EMA(X4, 21);
        }

        // MACD 5
        {
            //  EMA_S5.ema();
            //  EMA_L5.ema();
            DIF5 = (EMA_S5 - EMA_L5) / 1.5 / 1.5 / 1.5;
            X5.EMA(DIF5, 144);
            DEA5.EMA(X5, 89);
        }

        // MACD 6
        {
            //   EMA_S6.ema();
            //   EMA_L6.ema();
            DIF6 = (EMA_S6 - EMA_L6) / 1.5 / 1.5 / 1.5 / 1.5;
            X6.EMA(DIF6, 144);
            DEA6.EMA(X6, 144);
        }

        bool X_B32 = (X2 < 0 && X3 < 0 && X2 > X3);
        bool X_S32 = (X2 > 0 && X3 > 0 && X2 < X3);
        bool X_B43 = (X3 < 0 && X4 < 0 && X3 > X4);
        bool X_S43 = (X3 > 0 && X4 > 0 && X3 < X4);
        bool X_B54 = (X4 < 0 && X5 < 0 && X4 > X5);
        bool X_S54 = (X4 > 0 && X5 > 0 && X4 < X5);

        // static BoolSerial<8, 9> X_B32 = (X2 < 0 && X3 < 0 && X2 > X3);
        // static BoolSerial<8, 9> X_S32 = (X2 > 0 && X3 > 0 && X2 < X3);
        // static BoolSerial<8, 9> X_B43 = (X3 < 0 && X4 < 0 && X3 > X4);
        // static BoolSerial<8, 9> X_S43 = (X3 > 0 && X4 > 0 && X3 < X4);
        // static BoolSerial<8, 9> X_B54 = (X4 < 0 && X5 < 0 && X4 > X5);
        // static BoolSerial<8, 9> X_S54 = (X4 > 0 && X5 > 0 && X4 < X5);

        // bool m_line = x.c >= x.o;                             // 阳线 收盘价大于开盘价
        // bool f_line = x.c <= x.o;                             // 阴线 收盘价小于开盘价
        // bool m_pin = x.C >= x.O && (x.C - x.L) < (x.H - x.C); // 阳线 长影线
        // bool f_pin = x.c <= x.o && (x.c - x.l) > (x.h - x.c); // 阴线 长影线

        // bool BC = K1 > K1.ref(1) || x.c > x.c.ref(1) || m_line || f_pin;
        // bool SC = K1 < K1.ref(1) || x.c < x.c.ref(1) || f_line || m_pin;

        bool m_line = C >= this->O;                                                   // 阳线 收盘价大于开盘价
        bool f_line = this->C <= this->O;                                             // 阴线 收盘价小于开盘价
        bool m_pin = this->C >= this->O && (this->C - this->L) < (this->H - this->C); // 阳线 长影线
        bool f_pin = this->C <= this->O && (this->C - this->L) > (this->H - this->C); // 阴线 长影线

        bool BC = K1 > K1.ref(1) || this->C > this->C.ref(1) || m_line || f_pin;
        bool SC = K1 < K1.ref(1) || this->C < this->C.ref(1) || f_line || m_pin;

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
        //***********************************************************************************
        // static PointsList<N...> YB_32;
        // static PointsList<N...> YS_32;

        YB_32 = RSV2 >= RSV3 && RSV2.ref(1) >= RSV3.ref(1);      //*****
        YS_32 = RSV2 <= RSV3 && RSV2.ref(1) <= RSV3.ref(1);      //*****
        bool YB_43 = RSV3 >= RSV4 && RSV3.ref(1) >= RSV4.ref(1); //*****
        bool YB_54 = RSV4 >= RSV5 && RSV4.ref(1) >= RSV5.ref(1); //*****

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

        // -----------------------********--------------------------------------------********------------------------------------
        // bool H_KPB3 = (K33 > K3 || K32 > K3 || X3 > REF(X3, 1));
        // bool H_KPS3 = (K33 < K3 || K32 < K3 || X3 < REF(X3, 1));
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

        // H_KPB3 = (K33 > K3 || K32 > K3 || X3 > REF(X3, 1));
        // H_KPS3 = (K33 < K3 || K32 < K3 || X3 < REF(X3, 1));
        // H_KPP3 = H_KPB3 && H_KPS3;

        if (K33 > K3 || K32 > K3 || X3 > REF(X3, 1)) {
            H_KPB3 = true;
        }
        if (K33 < K3 || K32 < K3 || X3 < REF(X3, 1)) {
            H_KPS3 = true;
        }
        if (H_KPB3 && H_KPS3) {
            H_KPP3 = true;
        };

        if (H_KPP3 && H_KPB3 and !(H_KPB3.ref(1))) {
            // if (H_KPP3 && H_KPB3.is_begin()) {
            // H_KPP3.set_segmark(1,true);   //  这个标志，对整个段起作用。
            H_KPP3.set_segflag(100); //  这个标志，对整个段起作用。
        }

        // H_KB3 = (H_KPB3 && (!H_KPP3)) || (H_KPP3 && H_KPP3.get_segmark(1));
        H_KB3 = (H_KPB3 && (!H_KPP3)) || (H_KPP3 && (H_KPP3.cur_segflag() == 100));
        if (H_KB3) {
            H_KPB3.set_section(1);
        }
        if (H_KPB3 && !H_KB3) {
            H_KPB3.set_section(0);
        }

        if (H_KPP3 && H_KPS3 and !(H_KPS3.ref(1))) {
            // if (H_KPP3 && H_KPS3.is_begin()) {
            // H_KPP3.set_segmark(2,true);
            H_KPP3.set_segflag(200);
        }
        // H_KS3 = (H_KPS3 && (!H_KPP3)) || (H_KPP3 && H_KPP3.get_segmark(2));
        H_KS3 = (H_KPS3 && (!H_KPP3)) || (H_KPP3 && (H_KPP3.cur_segflag() == 200));
        if (H_KS3) {
            H_KPS3.set_section(1);
        }
        if (H_KPS3 && !H_KS3) {
            H_KPS3.set_section(0);
        }

        // -----------------------********--------------------------------------------********------------------------------------

        H_KPB4 = (K43 > K4 || K42 > K4 || X4 > REF(X4, 1));
        H_KPS4 = (K43 < K4 || K42 < K4 || X4 < REF(X4, 1));
        H_KPP4 = H_KPB4 && H_KPS4;

        if (H_KPP4 && H_KPB4 and !(H_KPB4.ref(1))) {
            // if (H_KPP4 && H_KPB4.is_begin()) {
            // H_KPP4.set_segmark(1,true);   //  这个标志，对整个段起作用。
            H_KPP4.set_segflag(100); //  这个标志，对整个段起作用。在某个段中，只要设置一次，从这个设置点到最终都起作用。
        }
        // H_KB4 = (H_KPB4 && (!H_KPP4)) || (H_KPP4 && H_KPP4.get_segmark(1));
        H_KB4 = (H_KPB4 && (!H_KPP4)) || (H_KPP4 && (H_KPP4.cur_segflag() == 100));
        if (H_KB4) {
            H_KPB4.set_section(1); // 设置section ID, set_section，必须每个切版都需要设置，如果某个切片没有设置，则自动换成另一个section，且默认section_id = -1;
        }
        if (H_KPB4 && !H_KB4) {
            H_KPB4.set_section(0);
        }

        if (H_KPP4 && H_KPS4 and !(H_KPS4.ref(1))) {
            // if (H_KPP4 && H_KPS4.is_begin()) {
            // H_KPP4.set_segmark(2,true);
            H_KPP4.set_segflag(200);
        }
        // H_KS4 = (H_KPS4 && (!H_KPP4)) || (H_KPP4 && H_KPP4.get_segmark(2));
        H_KS4 = (H_KPS4 && (!H_KPP4)) || (H_KPP4 && (H_KPP4.cur_segflag() == 200));
        if (H_KS4) {
            H_KPS4.set_section(1);
        }
        if (H_KPS4 && !H_KS4) {
            H_KPS4.set_section(0);
        }

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

        // -----------------------********--------------------------------------------********------------------------------------
        H_KPB5 = (K53 > K5 || K52 > K5 || X5 > REF(X5, 1));
        H_KPS5 = (K53 < K5 || K52 < K5 || X5 < REF(X5, 1));
        H_KPP5 = H_KPB5 && H_KPS5;

        if (H_KPP5 && H_KPB5 and !(H_KPB5.ref(1))) {
            // H_KPP5.set_segmark(1,true);   //  这个标志，对整个段起作用。
            H_KPP5.set_segflag(100); //  这个标志，对整个段起作用。
        }
        // H_KB5 = (H_KPB5 && (!H_KPP5)) || (H_KPP5 && H_KPP5.get_segmark(1));
        H_KB5 = (H_KPB5 && (!H_KPP5)) || (H_KPP5 && (H_KPP5.cur_segflag() == 100));
        if (H_KB5) {
            H_KPB5.set_section(1);
        }
        if (H_KPB5 && !H_KB5) {
            H_KPB5.set_section(0);
        }

        if (H_KPP5 && H_KPS5 and !(H_KPS5.ref(1))) {
            // H_KPP5.set_segmark(2,true);
            H_KPP5.set_segflag(200);
        }
        // H_KS5 = (H_KPS5 && (!H_KPP5)) || (H_KPP5 && H_KPP5.get_segmark(2));
        H_KS5 = (H_KPS5 && (!H_KPP5)) || (H_KPP5 && (H_KPP5.cur_segflag() == 200));
        if (H_KS5) {
            H_KPS5.set_section(1);
        }
        if (H_KPS5 && !H_KS5) {
            H_KPS5.set_section(0);
        }

        // bool H_KPB5 = (K53 > K5 || K52 > K5 || X5 > REF(X5, 1));
        // bool H_KPS5 = (K53 < K5 || K52 < K5 || X5 < REF(X5, 1));
        // static bool H_KPP5 = H_KPB5 && H_KPS5;          // 【重叠部分】P
        // static bool H_KCB5 = BARSLAST(!(H_KPB5));     //  粉线上涨周期
        // static bool H_KCS5 = BARSLAST(!(H_KPS5));     // 粉线下跌周期
        // static bool H_KDB5 = COUNT(H_KPS5 && !(REF(H_KPS5, 1)), H_KCB5 + 1);  // 粉线上涨周期内，有多少次  MACD 和 KD同时上涨
        // static bool H_KDS5 = COUNT(H_KPB5 && !(REF(H_KPB5, 1)), H_KCS5 + 1);
        // static bool H_KTB5 = (H_KPP5 && !(H_KDB5));  //  上涨的 头部
        // static bool H_KTS5 = (H_KPP5 && !(H_KDS5));
        // static bool H_KB5 = (H_KPB5 && !(H_KTS5));  //             || (H_KPP5  &&  K5>REF(K5,1))
        // static bool H_KS5 = (H_KPS5 && !(H_KTB5));  //             || (H_KPP5  &&  K5<REF(K5,1))

        // -----------------------********--------------------------------------------********------------------------------------

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

        // bool TB02 = H_KPB5 || H_KPB4 || H_KPB3;
        // bool TS02 = H_KPS5 || H_KPS4 || H_KPS3;

        // static BoolSerial<8, 9> TB02;
        // static BoolSerial<8, 9> TS02;
        TB02 = H_KPB5 || H_KPB4 || H_KPB3;
        TS02 = H_KPS5 || H_KPS4 || H_KPS3;

        if (TB02) {
            LOG(ERROR) << K2.unit->ActionDay << "  " << K2.unit->Time << "    " << this->O.cur() << " " << this->H.cur() << " " << this->L.cur() << " " << this->C.cur();
        }

        bool TBALL5 = K53 > REF(K53, 1) && K52 > REF(K52, 1) && K5 > REF(K5, 1);
        bool TSALL5 = K53 < REF(K53, 1) && K52 < REF(K52, 1) && K5 < REF(K5, 1);

        bool TBALL4 = K43 > REF(K43, 1) && K42 > REF(K42, 1) && K4 > REF(K4, 1);
        bool TSALL4 = K43 < REF(K43, 1) && K42 < REF(K42, 1) && K4 < REF(K4, 1);

        bool TBALL3 = K33 > REF(K33, 1) && K32 > REF(K32, 1) && K3 > REF(K3, 1);
        bool TSALL3 = K33 < REF(K33, 1) && K32 < REF(K32, 1) && K3 < REF(K3, 1);

        // ==========  牛头  ====================
        bool BB01 = TB02 && X_B32 && X_B43 && D3 < 30 && D4 < 30 && BC && K2 > REF(K2, 1) && REF(K2, 1) < REF(K2, 2) && REF(K2, 1) < 20 && YB5_4 && K53 < 10; //&& KB3 && KB4
        bool SS01 = TS02 && X_S32 && X_S43 && D3 > 70 && D4 > 70 && SC && K2 < REF(K2, 1) && REF(K2, 1) > REF(K2, 2) && REF(K2, 1) > 80 && YS5_4 && K53 > 90; //&& KS3 && KS4
        //----------------------------------------------------------------------------------------------------------------------------------------------------------------

        ICO137_B = TB02 && BBP && (K33 < 20); //  【***正确***】 ----【绿桃心】 绿80
        ICO137_S = TS02 && SSP && (K33 > 80); //  【***正确***】 ----【绿桃心】 绿80

        ICO112_B = TB02 && BBP && (K33 < 20) && (K23 < 20); // ---- 【橙三角】 绿80  红80
        ICO112_S = TS02 && SSP && (K33 > 80) && (K23 > 80); // ---- 【橙三角】 绿80  红80

        ICO148_B = TB02 && BBP && (K33 < 10); // ---- 【绿心】 绿90
        ICO148_S = TS02 && SSP && (K33 > 90); // ---- 【绿心】 绿90

        ICO92_B = TB02 && BBP && (K33 < 10) && (K23 < 10); // ---- 【太阳花】 绿90  红90
        ICO92_S = TS02 && SSP && (K33 > 90) && (K23 > 90); // ---- 【太阳花】 绿90  红90

        ///  LOG(INFO) << ICO92 << " ttt-ttt";

        bool ICO158 = TB02 && BBP && (K33 < 10) && (K32 < 10); // ---- 【红水滴】 绿90 绿90
        bool ICO159 = TS02 && SSP && (K33 > 90) && (K32 > 90); //

        // static bool ICO = BBP && ((H_KPB3 && !(H_KS5 && H_KS4)) || (H_KB5 && H_KB4));
        // static bool ICO = SSP && ((H_KPS3 && !(H_KB5 && H_KB4)) || (H_KS5 && H_KS4));

        bool ICO1 = YB2 && YB3 && YB4 && YB5 && H_KPB5; //
        bool ICO2 = YS2 && YS3 && YS4 && YS5 && H_KPS5; //

        ICO132_B = (YB2 && (X5 > X5.ref(1) || X4 > X4.ref(1))); //   【***正确***】 【橙色五角星】
        ICO132_S = (YS2 && (X5 < X5.ref(1) || X4 < X4.ref(1))); //   【***正确***】 【橙色五角星】

        // 开平仓测试！ ==============
        // if (ICO132_B) {
        //     if (trader.sellposition() > 4) {
        //         trader.sellclose(1);
        //     } else {
        //         trader.buyopen(1);
        //     }
        //     if (trader.sellposition() > 8) {
        //         trader.sellclose(1009);
        //     }
        // }
        // if (ICO132_S) {
        //     if (trader.buyposition() > 4) {
        //         trader.buyclose(1);
        //     } else {
        //         trader.sellopen(1);
        //     }

        //     if (trader.buyposition() > 8) {
        //         trader.buyclose(1009);
        //     }
        // }
        // 开平仓测试！ ==============

        if (ICO137_B == true) {
            LOG(ERROR) << K2.unit->ActionDay << " ----【绿桃心】 绿80  " << K2.unit->Time << " " << this->C.cur() << " " << this->O.cur();
        }

        // if (iii == 10) {
        //     exit(-1);
        // }
    }; // end onBar() ;
};
} // namespace uBEE
