
#include "future_env.h"

namespace uBEE {

int SectionsBase_sub01(int i) {

    bool m_line = true;
    bool b01 = true;
    bool b02 = true;

    StopsegsList<8, 9> MM;

    StopsegsList<8, 12> MT12;
    StopsegsList<8, 12> NT12;

    // ---------------------------------------------------------------------1
    MM = m_line;
    if (MM.value_ != true) {
        return 1;
    }
    if (MM != true) { //  MM.points_.size()  = 1
        return 1001;
    }

    //  LOG(INFO) << MM.points_[i];
    //  ---------------------------------------------------------------------2
    MM = false; //  MM.points_.size()  = 0
    if (MM.value_ != false) {
        return 2;
    }
    if (MM != false) {
        return 2001;
    }

    //  --------------------------------------------------------------------3
    MM = true && false; //  MM.points_.size()  = 0
    if (MM != false) {
        return 3;
    }
    MM = true || false;
    if (MM != true) { //  MM.points_.size()  = 1
        return 3001;
    }

    //  --------------------------------------------------------------------4
    m_line = true;
    MM = false; //  MM.points_.size()  = 0

    MM = MM && m_line; // MM.points_.size()  = 0
    if (MM != false) {
        return 4;
    }
    MM = m_line && MM; // MM.points_.size()  = 0
    if (MM != false) {
        return 4001;
    }

    MM = MM || m_line;
    if (MM != true) { //  MM.points_.size()  = 1
        return 4002;
    }
    MM = m_line || MM;
    if (MM != true) { //  MM.points_.size()  = 1
        return 4003;
    }

    MM = !MM; //  MM.points_.size()  = 0
    if (false != MM) {
        return 4004;
    }

    MM = !MM;
    if (MM != true) { //  MM.points_.size()  = 1
        return 4005;
    }

    //  ----------------------------------------------------------------------5
    MM = true; //  MM.points_.size()  = 1

    static PointsList<8, 9> NN;
    MM = NN; //  MM.points_.size()  = 0

    if (MM != NN) { // MM:false
        return 5;
    }
    if (NN != MM) { // MM:false
        return 5001;
    }
    if (!NN == MM) { // MM:false
        return 5002;
    }
    if (MM == !NN) { // MM:false
        return 5003;
    }
    // 新增测试 2023-11-20
    if (MM) {
        return 5004;
    }

    //  ----------------------------------------------------------------------6
    NN = true;
    if (!NN) {
        return 6;
    }

    if (MM == NN) { // MM:false
        return 6000;
    }

    if (MM != (NN && false)) { // MM:false
        return 6001;
    }
    if (MM != NN.value_ && false) { // MM:false
        return 6002;
    }

    if (MM == NN || false) { // MM:false   // NN:true
        return 6002;
    }

    if (MM == (NN || false)) { // MM:false   // NN:true
        return 6002;
    }

    //  ----------------------------------------------------------------------7
    MM = false;
    NN = true;

    m_line = MM && NN;
    if (m_line) {
        return 7;
    }
    m_line = MM || NN;
    if (!m_line) {
        return 7001;
    }
    m_line = (!MM);
    if (!m_line) {
        return 7002;
    }

    //  ----------------------------------------------------------------------8

    MM = true; // 为下一次循环初始化，保证 MM会point_.push_back(index)  把index push进 point_

    NN = false;
    // 因为NN不是static变量，每次循环都会初始化。
    return 0;
}

int SectionsBase_test1() {

    int rtn = 0;
    Base *bb = new Base;
    rtn = Prepare_env(bb);

    Future<8, period_1F> x(bb); //  Future<8, 9> x(&bb);
    Future<8, period_5F> y(bb); //  Future<8, 12> y(&bb);

    for (int i = 0; i < 1000; i++) {
        x.unit->index = i;
        rtn = SectionsBase_sub01(i);
        if (rtn != 0) {
            // LOG(INFO) << "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii is: " << i << "  rtn: " << rtn;
            break;
        }
    }
    delete bb;
    return rtn;
} // end test01() ;

int SectionsBase_test2() {
    std::cout << " ########################################## section  test 2 #######################################" << std::endl;
    int rtn = 0;
    Base *bb = new Base;
    rtn = Prepare_env(bb);

    Future<8, period_1F> x(bb); //  Future<8, 9> x(&bb);
    Future<8, period_5F> y(bb); //  Future<8, 12> y(&bb);

    int j = 0;
    bool b = false;

    StopsegsList<8, 9> S1;
    StopsegsList<8, 9> S2;
    StopsegsList<8, 9> S3;

    PointsList<8, 9> P1;
    PointsList<8, 9> P2;
    PointsList<8, 9> P3;
    PointsList<8, 9> P4;

    EMA_t<8, 9> E1;
    EMA_t<8, 9> E2;
    EMA_t<8, 9> E3;

    rtn = 0;

    int s_len;
    int s_B;
    int s_E;
    int s_size;
    int s_type;
    int s_flag;

    bb->onBars([&](int e) {
        if (e > -1) {
            S2 = false;
        }
        E1.ema(E1.O, 3);
        E2.ema(E2.O, 13);
        E3.ema(E3.O, 23);

        S2 = S2.OO[S2.x] < 0 ? false : true;

        if (S2.unit->index == 3) {
            S2.set_segflag(105);
        }
        if (S2.unit->index == 12) {
            S2.set_segflag(108);
        }

        if (S2 && !S2.ref(1)) {
            S2.set_segflag(2023);
        }

        //  ------------------------- section 测试 ------------------------------------
        //  ---------------  test1  -------------
        S1.set_section(e);
        if (e == 10) {
            s_len = S1.cur_section_len();
            s_B = S1.cur_section_begin();
            s_size = S1.sections_.size() - 1;
            s_type = S1.cur_section();
        }
        //   std::cout << " begin: " << S1.cur_section_begin() << " Len: " << S1.cur_section_len() << std::endl;
        std::cout << " e: " << e << " " << S1.cur_section() << " size: " << S1.sections_.size();
        if (e <= 1) {
            std::cout << std::endl;
        }
        if (s_size > 1) {
            std::cout << " ref_B: " << S1.sections_[s_size].B << " ref_E: " << S1.sections_[s_size].E << std::endl;
        }
        //  ---------------  test2  -------------
        if (e % 2 == 0) { //  每7次才执行下面的内容， section 的长度是7
            S2.set_section(e);
        }
        // std::cout << " begin: " << S2.cur_section_begin() << " Len: " << S2.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << S2.cur_section() << " size: " << S2.sections_.size();
        // if (e > 1) {
        //     std::cout << " ref_B: " << S2.sections_[S2.sections_.size() - 2].B << " ref_E: " << S2.sections_[S2.sections_.size() - 2].E << std::endl;
        // }

        //  ---------------  test3  -------------
        if (e % 3 == 0) { //  每7次才执行下面的内容， section 的长度是7
            S3.set_section(e);
        }
        // std::cout << " begin: " << S3.cur_section_begin() << " Len: " << S3.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << S3.cur_section() << " size: " << S3.sections_.size();
        // if (S3.sections_.size() > 1) {
        //     std::cout << " ref_B: " << S3.sections_[S3.sections_.size() - 2].B << " ref_E: " << S3.sections_[S3.sections_.size() - 2].E << std::endl;
        // }
        //  -- -- -- -- -- -- -- -test4-- -- -- -- -- -- -
        if (e >= 0 && e < 5) {
            P1.set_section(100);
        }
        if (e >= 5 && e < 10) {
            P1.set_section(200);
        }
        if (e >= 10 && e < 15) {
            P1.set_section(300);
        }
        if (e >= 15 && e < 20) {
            P1.set_section(100);
        }
        // std::cout << " begin: " << P1.cur_section_begin() << " Len: " << P1.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << P1.cur_section() << " size: " << P1.sections_.size() << std::endl;
        // if (P1.sections_.size() > 1) {
        //     std::cout << " ref_B: " << P1.sections_[P1.sections_.size() - 2].B << " ref_E: " << P1.sections_[P1.sections_.size() - 2].E << std::endl;
        // }

        if (e >= 5 && e < 10) {
            P2.set_section(100);
        }
        if (e >= 10 && e < 15) {
            P2.set_section(200);
        }
        if (e >= 15 && e < 20) {
            P2.set_section(300);
        }
        if (e >= 20 && e < 25) {
            P2.set_section(100);
        }
        // std::cout << " begin: " << P2.cur_section_begin() << " Len: " << P2.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << P2.cur_section() << " size: " << P2.sections_.size() << std::endl;
        // if (P2.sections_.size() > 1) {
        //     std::cout << " ref_B: " << P2.sections_[P2.sections_.size() - 2].B << " ref_E: " << P2.sections_[P2.sections_.size() - 2].E << std::endl;
        // }
        //  ---------------  test5  -------------

        if (e >= 0 && e < 5) {
            P3.set_section(100);
        }
        if (e >= 10 && e < 15) {
            P3.set_section(100);
        }
        if (e >= 20 && e < 25) {
            P3.set_section(100);
        }
        // std::cout << " begin: " << P3.cur_section_begin() << " Len: " << P3.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << P3.cur_section() << " size: " << P3.sections_.size() << std::endl;
        // if (P3.sections_.size() > 1) {
        //     std::cout << " ref_B: " << P3.sections_[P3.sections_.size() - 2].B << " ref_E: " << P3.sections_[P3.sections_.size() - 2].E << std::endl;
        // }

        if (e >= 5 && e < 10) {
            P4.set_section(100);
        }
        if (e >= 15 && e < 20) {
            P4.set_section(100);
        }
        if (e >= 25 && e < 30) {
            P4.set_section(100);
        }
        // std::cout << " begin: " << P4.cur_section_begin() << " Len: " << P4.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << P4.cur_section() << " size: " << P4.sections_.size() << std::endl;
        // if (P4.sections_.size() > 1) {
        //     std::cout << " ref_B: " << P4.sections_[P4.sections_.size() - 2].B << " ref_E: " << P4.sections_[P4.sections_.size() - 2].E << std::endl;
        // }
        //  ---------------  test6 异常测试 ----------------------------
        // section 起始处 设置一个其它的值，再设置回去  ----------
        if (e == 0) {
            E1.set_section(INT_MIN);
        }
        if (e >= 0 && e < 5) {
            E1.set_section(100);
        }
        if (e >= 5 && e < 10) {
            E1.set_section(200);
        }
        // section 起始处 设置一个其它的值，再设置回去
        if (e == 10) {
            E1.set_section(INT_MIN);
        }
        if (e >= 10 && e < 15) {
            E1.set_section(300);
        }
        if (e >= 15 && e < 20) {
            E1.set_section(100);
        }
        //   std::cout << " begin: " << E1.cur_section_begin() << " Len: " << E1.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << E1.cur_section() << " size: " << E1.sections_.size() << std::endl;
        // if (E1.sections_.size() > 1) {
        //     std::cout << " ref_B: " << E1.sections_[E1.sections_.size() - 2].B << " ref_E: " << E1.sections_[E1.sections_.size() - 2].E << std::endl;
        // }

        // section 结束处 设置一个其它的值，再设置回去 ---------------
        if (e >= 0 && e < 5) {
            E2.set_section(100);
        }
        if (e == 5) {
            E2.set_section(INT_MIN);
        }
        if (e == 6) {
            E2.set_section(INT_MIN);
        }
        if (e >= 10 && e < 15) {
            E2.set_section(100);
        }
        if (e == 18) {
            E2.set_section(INT_MIN);
        }
        if (e >= 20 && e < 25) {
            E2.set_section(100);
        }
        // std::cout << " begin: " << E2.cur_section_begin() << " Len: " << E2.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << E2.cur_section() << " size: " << E2.sections_.size() << std::endl;
        // if (E2.sections_.size() > 1) {
        //     std::cout << " ref_B: " << E2.sections_[E2.sections_.size() - 2].B << " ref_E: " << E2.sections_[E2.sections_.size() - 2].E << std::endl;
        // }

        // section 中间位置 设置一个其它的值，再设置回去 ---------------
        if (e >= 0 && e < 5) {
            E3.set_section(100);
        }
        if (e == 3 || e == 4) {
            E3.set_section(345);
            int x = E3.cur_section_len();
            //  std::cout << x << std::endl;
            E3.set_section(100);
        }

        if (e >= 10 && e < 15) {
            E3.set_section(100);
        }

        if (e >= 20 && e < 25) {
            E3.set_section(100);
        }
        // std::cout << " begin: " << E3.cur_section_begin() << " Len: " << E3.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << E2.cur_section() << " size: " << E2.sections_.size() << std::endl;
        // if (E2.sections_.size() > 1) {
        //     std::cout << " ref_B: " << E2.sections_[E2.sections_.size() - 2].B << " ref_E: " << E2.sections_[E2.sections_.size() - 2].E << std::endl;
        // }

        //  ---------------  test6  -------------

        // if (e % 7 == 0) { //  每7次才执行下面的内容， section 的长度是7
        //     for_section_test = !for_section_test;
        //     type++;
        //     if (type == 4) { // 4种类型的section
        //         type = 0;
        //     }
        // }

        //  ------------------------- section 测试 ------------------------------------
    });

    //  100 100 100 100 100 ,-100 -100 -100 -100 -100, 100 100 100 100 100 , -100 -100 -100 -100 -100,
    for (int i = 0; i < 100000; i++) {
        if (i % 5 == 0) {
            b = !b;
        }

        x.unit->index = i;
        x.OO[i] = b ? -100.0 : 100.0;

        bb->unit_array_[8][9]->func_signal();     // 这是前置处理。
        bb->onBarsHandler(i);                     // todo 这个参数 i 应该是没有在trader里用到。
        bb->unit_array_[8][9]->func_signal_end(); // 这是后置处理。  S2._update() 会在这里调用。
        // --------------------------------------------------------------------

        if (i > 100) {
            delete bb;
            return 0;
        }
    }
    delete bb;
    return rtn;
} // end test02() ;

int SectionsBase_test3() {
    std::cout << " ########################################## section test 3 #######################################" << std::endl;

    int rtn = 0;
    Base *bb = new Base;
    rtn = Prepare_env(bb);

    Future<8, period_1F> x(bb); //  Future<8, 9> x(&bb);
    Future<8, period_5F> y(bb); //  Future<8, 12> y(&bb);

    int j = 0;
    bool b = false;

    StopsegsList<8, 9> S1;
    StopsegsList<8, 9> S2;
    StopsegsList<8, 9> S3;

    PointsList<8, 9> P1;
    PointsList<8, 9> P2;
    PointsList<8, 9> P3;
    PointsList<8, 9> P4;

    EMA_t<8, 9> E1;
    EMA_t<8, 9> E2;
    EMA_t<8, 9> E3;

    EMA_t<8, 9> E4;
    EMA_t<8, 9> E5;
    EMA_t<8, 9> E6;

    rtn = 0;

    // int s_len = -1;
    // int s_B = -1;
    // int s_E = -1;
    // int s_size = 0;
    // int s_flag = -1024;

    int s_len;
    int s_B;
    int s_E;
    int s_size;
    int s_type;
    int s_flag;

    bb->onBars([&](int e) {
        if (e > -1) {
            S2 = false;
        }
        E1.ema(E1.O, 3);
        E2.ema(E2.O, 13);
        E3.ema(E3.O, 23);

        E4.ema(E1.O, 33);
        E5.ema(E2.O, 113);
        E6.ema(E3.O, 123);

        S2 = S2.OO[S2.x] < 0 ? false : true;

        if (S2.unit->index == 3) {
            S2.set_segflag(105);
        }
        if (S2.unit->index == 12) {
            S2.set_segflag(108);
        }

        if (S2 && !S2.ref(1)) {
            S2.set_segflag(2023);
        }

        //  ------------------------- section 测试 ------------------------------------
        //  ---------------  test1  -------------
        S1.set_section(e);

        if (e == 5) {
            S1.set_section_flag(30);
        }

        if (e == 7) {
            s_len = S1.cur_section_len();
            s_B = S1.cur_section_begin();
            s_size = S1.sections_.size() - 1;
            s_type = S1.cur_section();
            if (S1.sections_[s_size - 1].flag != 30) {
                rtn = 10001;
                return;
            }

            if (s_size != 6 || s_type != 7 || s_B != 7) {
                rtn = 10002;
                return;
            }
        }

        //  ---------------  test2  -------------
        if (e % 2 == 0) { //  每2次才执行下面的内容， section 的长度是7
            S2.set_section(e);
        }

        if (e == 6) {
            S2.set_section_flag(50);
        }

        if (e == 8) {
            s_len = S2.cur_section_len();
            s_B = S2.cur_section_begin();
            s_size = S2.sections_.size() - 1;
            s_type = S2.cur_section();
            // std::cout << "flag: " << S2.sections_[s_size].flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << std::endl;

            if (S2.sections_[s_size].flag != 50) {
                rtn = 20001;
                return;
            }

            if (s_size != 3 || s_type != 8 || s_B != 8) {
                rtn = 20002;
                return;
            }
        }

        // std::cout << " begin: " << S2.cur_section_begin() << " Len: " << S2.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << S2.cur_section() << " size: " << S2.sections_.size();
        // if (e > 1) {
        //     std::cout << " ref_B: " << S2.sections_[S2.sections_.size() - 2].B << " ref_E: " << S2.sections_[S2.sections_.size() - 2].E << std::endl;
        // }

        //  ---------------  test3  -------------
        if (e % 3 == 0) { //  每7次才执行下面的内容， section 的长度是7
            S3.set_section(e);
        }

        // std::cout << " begin: " << S3.cur_section_begin() << " Len: " << S3.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << S3.cur_section() << " size: " << S3.sections_.size();
        // if (S3.sections_.size() > 1) {
        //     std::cout << " ref_B: " << S3.sections_[S3.sections_.size() - 2].B << " ref_E: " << S3.sections_[S3.sections_.size() - 2].E << std::endl;
        // }
        //  -- -- -- -- -- -- -- -test4-- -- -- -- -- -- -
        if (e >= 0 && e < 5) {
            P1.set_section(100);
        }
        if (e >= 5 && e < 10) {
            P1.set_section(200);
        }
        if (e >= 10 && e < 15) {
            P1.set_section(300);
        }
        if (e >= 15 && e < 20) {
            P1.set_section(100);
        }

        if (e == 3) {
            P1.set_section_flag(33);
        }

        if (e == 4) { // 修改type，再改回来，看flag是否还是33.
            P1.set_section(77);
            std::cout << "idx:" << P1.x << "  type:" << P1.cur_section() << std::endl;
            P1.set_section(100);
        }

        if (e == 6) {
            P1.set_section_flag(69);
        }

        if (e == 8) {
            s_len = P1.cur_section_len();
            s_B = P1.cur_section_begin();
            s_size = P1.sections_.size() - 1;
            s_type = P1.cur_section();
            // std::cout << "flag: " << P1.sections_[s_size - 1].flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (P1.sections_[s_size - 1].flag != 33 || P1.cur_section_flag() != 69) {
                rtn = 30001;
                return;
            }

            if (s_size != 1 || s_type != 200 || s_B != 5 || s_len != 4) {
                rtn = 30002;
                return;
            }
        }

        // std::cout << " begin: " << P1.cur_section_begin() << " Len: " << P1.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << P1.cur_section() << " size: " << P1.sections_.size() << std::endl;
        // if (P1.sections_.size() > 1) {
        //     std::cout << " ref_B: " << P1.sections_[P1.sections_.size() - 2].B << " ref_E: " << P1.sections_[P1.sections_.size() - 2].E << std::endl;
        // }

        if (e >= 5 && e < 10) {
            P2.set_section(100);
        }
        if (e >= 10 && e < 15) {
            P2.set_section(200);
        }
        if (e >= 15 && e < 20) {
            P2.set_section(300);
        }
        if (e >= 20 && e < 25) {
            P2.set_section(100);
        }

        if (e == 3) {
            P2.set_section_flag(33);
        }

        if (e == 4) { // 修改type，再改回 INT_MIN .
            P2.set_section(77);
            std::cout << "idx:" << P2.x << "  type:" << P2.cur_section() << std::endl;
            P2.set_section(100);
            P2.set_section(INT_MIN);
        }

        if (e == 6) {
            P2.set_section_flag(69);
        }
        if (e == 11) {
            P2.set_section_flag(169);
        }

        if (e == 14) {
            s_len = P2.cur_section_len();
            s_B = P2.cur_section_begin();
            s_size = P2.sections_.size() - 1;
            s_type = P2.cur_section();
            // std::cout << "flag: " << P2.sections_[s_size - 1].flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (P2.sections_[s_size - 1].flag != 69 || P2.cur_section_flag() != 169) {
                rtn = 40001;
                return;
            }

            if (s_size != 1 || s_type != 200 || s_B != 10 || s_len != 5) {
                rtn = 40002;
                return;
            }
        }

        // std::cout << " begin: " << P2.cur_section_begin() << " Len: " << P2.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << P2.cur_section() << " size: " << P2.sections_.size() << std::endl;
        // if (P2.sections_.size() > 1) {
        //     std::cout << " ref_B: " << P2.sections_[P2.sections_.size() - 2].B << " ref_E: " << P2.sections_[P2.sections_.size() - 2].E << std::endl;
        // }
        //  ---------------  test5  -------------

        if (e >= 0 && e < 5) {
            P3.set_section(100);
        }
        if (e >= 10 && e < 15) {
            P3.set_section(100);
        }
        if (e >= 20 && e < 25) {
            P3.set_section(100);
        }

        // std::cout << " begin: " << P3.cur_section_begin() << " Len: " << P3.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << P3.cur_section() << " size: " << P3.sections_.size() << std::endl;
        // if (P3.sections_.size() > 1) {
        //     std::cout << " ref_B: " << P3.sections_[P3.sections_.size() - 2].B << " ref_E: " << P3.sections_[P3.sections_.size() - 2].E << std::endl;
        // }

        if (e >= 5 && e < 10) {
            P4.set_section(100);
        }
        if (e >= 15 && e < 20) {
            P4.set_section(100);
        }
        if (e >= 25 && e < 30) {
            P4.set_section(100);
        }

        // std::cout << " begin: " << P4.cur_section_begin() << " Len: " << P4.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << P4.cur_section() << " size: " << P4.sections_.size() << std::endl;
        // if (P4.sections_.size() > 1) {
        //     std::cout << " ref_B: " << P4.sections_[P4.sections_.size() - 2].B << " ref_E: " << P4.sections_[P4.sections_.size() - 2].E << std::endl;
        // }
        //  ---------------  test6 异常测试 ----------------------------
        // section 起始处 设置一个其它的值，再设置回去  ----------
        if (e == 0) {
            E4.set_section(INT_MIN);
            E4.set_section_flag(33);
        }
        if (e > 0 && e < 5) {
            E4.set_section(100);
        }
        if (e >= 5 && e < 10) {
            E4.set_section(200);
        }
        // section 起始处 设置一个其它的值，再设置回去
        if (e == 10) {
            E4.set_section(INT_MIN);
        }
        if (e > 10 && e < 15) {
            E4.set_section(300);
        }
        if (e == 10) {
            E4.set_section_flag(1212);
        }
        if (e == 11) {
            E4.set_section_flag(1213);
        }
        if (e >= 15 && e < 20) {
            E4.set_section(100);
        }
        if (e == 20) {
            E4.set_section(INT_MIN);
        }

        // ------------------E4 测试输出 begin -----------------------------------------
        if (e == 0) {
            s_len = E4.cur_section_len();
            s_B = E4.cur_section_begin();
            s_size = E4.sections_.size() - 1;
            s_type = E4.cur_section();
            s_flag = E4.cur_section_flag();
            std::cout << "flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != -1 || s_type != INT_MIN || s_flag != INT_MIN || s_B != INT_MIN || s_len != INT_MIN) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 140001;
                return;
            }
        }
        if (e == 1) {
            s_len = E4.cur_section_len();
            s_B = E4.cur_section_begin();
            s_size = E4.sections_.size() - 1;
            s_type = E4.cur_section();
            s_flag = E4.cur_section_flag();
            std::cout << "flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != -1 || s_type != 100 || s_flag != INT_MIN || s_B != 1 || s_len != 1) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 140002;
                return;
            }
        }

        if (e == 2) {
            s_len = E4.cur_section_len();
            s_B = E4.cur_section_begin();
            s_size = E4.sections_.size() - 1;
            s_type = E4.cur_section();
            s_flag = E4.cur_section_flag();
            std::cout << "flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != 0 || s_type != 100 || s_flag != INT_MIN || s_B != 1 || s_len != 2) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 140003;
                return;
            }
        }

        if (e == 10) {
            s_len = E4.cur_section_len();
            s_B = E4.cur_section_begin();
            s_size = E4.sections_.size() - 1;
            s_type = E4.cur_section();
            s_flag = E4.cur_section_flag();
            std::cout << "### 140004 flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != 1 || s_type != INT_MIN || s_flag != INT_MIN || s_B != INT_MIN || s_len != INT_MIN) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 140004;
                return;
            }
        }

        if (e == 11) {
            s_len = E4.cur_section_len();
            s_B = E4.cur_section_begin();
            s_size = E4.sections_.size() - 1;
            s_type = E4.cur_section();
            s_flag = E4.cur_section_flag();
            std::cout << "### 140005 flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != 1 || s_type != 300 || s_flag != 1213 || s_B != 11 || s_len != 1) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 140005;
                return;
            }
        }

        if (e == 12) {
            s_len = E4.cur_section_len();
            s_B = E4.cur_section_begin();
            s_size = E4.sections_.size() - 1;
            s_type = E4.cur_section();
            s_flag = E4.cur_section_flag();
            std::cout << "### 140006 flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != 2 || s_type != 300 || s_flag != 1213 || s_B != 11 || s_len != 2) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 140006;
                return;
            }
        }

        if (e == 14) {
            s_len = E4.cur_section_len();
            s_B = E4.cur_section_begin();
            s_size = E4.sections_.size() - 1;
            s_type = E4.cur_section();
            s_flag = E4.cur_section_flag();
            std::cout << "### 140007 flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != 2 || s_type != 300 || s_flag != 1213 || s_B != 11 || s_len != 4) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 140007;
                return;
            }
        }

        if (e == 15) {
            s_len = E4.cur_section_len();
            s_B = E4.cur_section_begin();
            s_size = E4.sections_.size() - 1;
            s_type = E4.cur_section();
            s_flag = E4.cur_section_flag();
            std::cout << "### 140008 flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != 2 || s_type != 100 || s_flag != INT_MIN || s_B != 15 || s_len != 1) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 140008;
                return;
            }
        }

        //  ---------------  test6 异常测试 ----------------------------
        // section 起始处 设置一个其它的值，再设置回去  ----------
        if (e == 0) {
            E1.set_section(INT_MIN);
            E1.set_section_flag(33);
        }
        if (e >= 0 && e < 5) {
            E1.set_section(100);
        }
        if (e >= 5 && e < 10) {
            E1.set_section(200);
        }
        // section 起始处 设置一个其它的值，再设置回去
        if (e == 10) {
            E1.set_section(INT_MIN);
        }
        if (e >= 10 && e < 15) {
            E1.set_section(300);
        }
        if (e == 10) {
            E1.set_section_flag(1212);
        }
        if (e >= 15 && e < 20) {
            E1.set_section(100);
        }
        if (e == 20) {
            E1.set_section(INT_MIN);
        }

        // ------------------E1 测试输出 begin -----------------------------------------
        if (e == 0) {
            s_len = E1.cur_section_len();
            s_B = E1.cur_section_begin();
            s_size = E1.sections_.size() - 1;
            s_type = E1.cur_section();
            s_flag = E1.cur_section_flag();
            std::cout << "flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != -1 || s_type != 100 || s_flag != INT_MIN || s_B != 0 || s_len != 1) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 110001;
                return;
            }
        }

        if (e == 10) {
            s_len = E1.cur_section_len();
            s_B = E1.cur_section_begin();
            s_size = E1.sections_.size() - 1;
            s_type = E1.cur_section();
            s_flag = E1.cur_section_flag();
            std::cout << "### 110002 flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != 1 || s_type != 300 || s_flag != 1212 || s_B != 10 || s_len != 1) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 110002;
                return;
            }
        }

        if (e == 11) {
            s_len = E1.cur_section_len();
            s_B = E1.cur_section_begin();
            s_size = E1.sections_.size() - 1;
            s_type = E1.cur_section();
            s_flag = E1.cur_section_flag();
            std::cout << "### 110003 flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != 2 || s_type != 300 || s_flag != 1212 || s_B != 10 || s_len != 2) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 110003;
                return;
            }
        }

        if (e == 20) {
            s_len = E1.cur_section_len();
            s_B = E1.cur_section_begin();
            s_size = E1.sections_.size() - 1;
            s_type = E1.cur_section();
            s_flag = E1.cur_section_flag();
            std::cout << "### 110004 flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != 3 || s_type != INT_MIN || s_flag != INT_MIN || s_B != INT_MIN || s_len != INT_MIN) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 110004;
                return;
            }
        }

        if (e == 21) {
            s_len = E1.cur_section_len();
            s_B = E1.cur_section_begin();
            s_size = E1.sections_.size() - 1;
            s_type = E1.cur_section();
            s_flag = E1.cur_section_flag();
            std::cout << "### 110005 flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != 3 || s_type != INT_MIN || s_flag != INT_MIN || s_B != INT_MIN || s_len != INT_MIN) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 110005;
                return;
            }
        }

        if (e == 71) {
            s_len = E1.cur_section_len();
            s_B = E1.cur_section_begin();
            s_size = E1.sections_.size() - 1;
            s_type = E1.cur_section();
            s_flag = E1.cur_section_flag();
            std::cout << "### 110006 flag: " << s_flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (s_size != 3 || s_type != INT_MIN || s_flag != INT_MIN || s_B != INT_MIN || s_len != INT_MIN) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 110006;
                return;
            }
        }

        // ------------------E1 测试输出 end -------------------------------------------

        //   std::cout << " begin: " << E1.cur_section_begin() << " Len: " << E1.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << E1.cur_section() << " size: " << E1.sections_.size() << std::endl;
        // if (E1.sections_.size() > 1) {
        //     std::cout << " ref_B: " << E1.sections_[E1.sections_.size() - 2].B << " ref_E: " << E1.sections_[E1.sections_.size() - 2].E << std::endl;
        // }

        // section 结束处 设置一个其它的值，再设置回去 ---------------
        // 0 - 4 section type = 100  ------- 第1段 ------------
        if (e >= 0 && e < 5) {
            E2.set_section(100);
        }
        if (e == 5) {
            E2.set_section(INT_MIN);
        }
        if (e == 6) {
            E2.set_section(INT_MIN);
        }
        // 10 - 14 section type = 100 ------- 第2段 ------------
        if (e >= 10 && e < 15) {
            E2.set_section(100);
        }
        if (e == 18) {
            E2.set_section(INT_MIN);
        }

        // 20 - 24 section type = 100  ------- 第3段 ------------
        if (e >= 20 && e < 25) {
            E2.set_section(107);
        }

        if (e == 3) {
            E2.set_section_flag(33);
        }

        if (e == 4) { // 修改type，再改回 INT_MIN .
            if (E2.cur_section_flag() != 33) {
                rtn = 500011;
                return;
            }
            E2.set_section(77);
            std::cout << "idx:" << E2.x << "  type:" << E2.cur_section() << std::endl;
            E2.set_section(100);
            E2.set_section_flag(133);
            if (E2.cur_section_flag() != 133) {
                rtn = 500012;
                return;
            }
        }
        if (e == 5) {
            E2.set_section_flag(233);
        }

        if (e == 6) {
            E2.set_section_flag(69);
        }

        if (e == 11) {
            E2.set_section_flag(169);
        }

        if (e == 21) {
            E2.set_section_flag(234);
        }

        if (e == 25) {
            E2.set_section_flag(1233);
        }

        if (e == 6) {
            E2.set_section_flag(69);
        }

        if (e == 14) {
            s_len = E2.cur_section_len();
            s_B = E2.cur_section_begin();
            s_size = E2.sections_.size() - 1;
            s_type = E2.cur_section();
            std::cout << "flag: " << E2.sections_[s_size - 1].flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (E2.sections_[s_size - 1].flag != 133 || E2.cur_section_flag() != 169) {
                rtn = 50002;
                return;
            }

            if (s_size != 1 || s_type != 100 || s_B != 10 || s_len != 5) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 50003;
                return;
            }
        }

        if (e == 15) {
            s_len = E2.cur_section_len();
            s_B = E2.cur_section_begin();
            s_size = E2.sections_.size() - 1;
            s_type = E2.cur_section();
            std::cout << "flag: " << E2.sections_[s_size - 1].flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (E2.sections_[s_size - 1].flag != 133 || E2.cur_section_flag() != INT_MIN) {
                rtn = 50004;
                return;
            }

            if (s_size != 1 || s_type != INT_MIN || s_B != INT_MIN || s_len != INT_MIN) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 50005;
                return;
            }
        }

        if (e == 20) {
            s_len = E2.cur_section_len();
            s_B = E2.cur_section_begin();
            s_size = E2.sections_.size() - 1; // = 1
            s_type = E2.cur_section();
            std::cout << "flag: " << E2.sections_[s_size - 1].flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (E2.sections_[s_size - 1].flag != 133 || E2.cur_section_flag() != INT_MIN) {
                rtn = 60001;
                return;
            }

            if (s_size != 1 || s_type != 107 || s_B != 20 || s_len != 1) { // 这时有两个段 0段(0-4), 1段(10-14)
                rtn = 60002;
                return;
            }
        }

        if (e == 21) {
            s_len = E2.cur_section_len();
            s_B = E2.cur_section_begin();
            s_size = E2.sections_.size() - 1; // = 2   只有 0, 1, 2三个段。
            s_type = E2.cur_section();
            std::cout << "e= 21 flag: " << E2.sections_[s_size - 1].flag << "  size:" << s_size << " B:" << s_B << "  type:" << s_type << " len:" << s_len << std::endl;

            if (E2.sections_[s_size - 1].flag != 169 || E2.cur_section_flag() != 234) {
                rtn = 60003;
                return;
            }

            if (s_size != 2 || s_type != 107 || s_B != 20 || s_len != 2) { // 这时有三个段 0段(0-4), 1段(10-14) 2段 (20-24)
                rtn = 60004;
                return;
            }
        }

        if (e == 70) {
            s_size = E2.sections_.size() - 1;
            if (E2.sections_[s_size].flag != 234 || s_size != 2 || E2.cur_section_flag() != INT_MIN || E2.cur_section_begin() != INT_MIN || E2.cur_section_len() != INT_MIN) {
                rtn = 70004;
                return;
            }
        }
        // std::cout << " begin: " << E2.cur_section_begin() << " Len: " << E2.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << E2.cur_section() << " size: " << E2.sections_.size() << std::endl;
        // if (E2.sections_.size() > 1) {
        //     std::cout << " ref_B: " << E2.sections_[E2.sections_.size() - 2].B << " ref_E: " << E2.sections_[E2.sections_.size() - 2].E << std::endl;
        // }

        // section 中间位置 设置一个其它的值，再设置回去 ---------------
        if (e >= 0 && e < 5) {
            E3.set_section(100);
        }
        if (e == 3 || e == 4) {
            E3.set_section(345);
            int x = E3.cur_section_len();
            std::cout << x << std::endl;
            E3.set_section(100);
        }

        if (e >= 10 && e < 15) {
            E3.set_section(100);
        }

        if (e >= 20 && e < 25) {
            E3.set_section(100);
        }
        //   std::cout << " begin: " << E3.cur_section_begin() << " Len: " << E3.cur_section_len() << std::endl;
        // std::cout << " e: " << e << " " << E2.cur_section() << " size: " << E2.sections_.size() << std::endl;
        // if (E2.sections_.size() > 1) {
        //     std::cout << " ref_B: " << E2.sections_[E2.sections_.size() - 2].B << " ref_E: " << E2.sections_[E2.sections_.size() - 2].E << std::endl;
        // }

        //  ---------------  test6  -------------

        // if (e % 7 == 0) { //  每7次才执行下面的内容， section 的长度是7
        //     for_section_test = !for_section_test;
        //     type++;
        //     if (type == 4) { // 4种类型的section
        //         type = 0;
        //     }
        // }

        //  ------------------------- section 测试 ------------------------------------
    });

    //  100 100 100 100 100 ,-100 -100 -100 -100 -100, 100 100 100 100 100 , -100 -100 -100 -100 -100,
    for (int i = 0; i < 100000; i++) {
        if (i % 5 == 0) {
            b = !b;
        }

        x.unit->index = i;
        x.OO[i] = b ? -100.0 : 100.0;

        bb->unit_array_[8][9]->func_signal(); // 这是前置处理。
        bb->onBarsHandler(i);                 // todo 这个参数 i 应该是没有在trader里用到。
        if (rtn != 0) {
            return rtn;
        }
        bb->unit_array_[8][9]->func_signal_end(); // 这是后置处理。  S2._update() 会在这里调用。
        // --------------------------------------------------------------------

        if (i > 100) {
            delete bb;
            return 0;
        }
    }
    delete bb;
    return rtn;

} // end test03() ;

} // namespace uBEE