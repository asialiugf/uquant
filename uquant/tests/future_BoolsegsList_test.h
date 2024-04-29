
#include "future_env.h"

namespace uBEE {

int BoolsegsList_sub01(int i) {

    bool m_line = true;
    bool b01 = true;
    bool b02 = true;

    static BoolsegsList<8, 9> MM;

    static BoolsegsList<8, 12> MT12;
    static BoolsegsList<8, 12> NT12;

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

int BoolsegsList_test1() {

    int rtn = 0;
    Base *bb = new Base;
    rtn = Prepare_env(bb);

    Future<8, period_1F> x(bb);
    Future<8, period_5F> y(bb);

    for (int i = 0; i < 1000; i++) {
        x.unit->index = i;
        rtn = BoolsegsList_sub01(i);
        if (rtn != 0) {
            // LOG(INFO) << " rtn is: " << i << "  rtn: " << rtn;
            break;
        }
    }

    return rtn;
} // end test01() ;

int BoolsegsList_test2() {
    std::cout << " ########################################## test 2 #######################################" << std::endl;
    int rtn = 0;
    Base *bb = new Base;
    rtn = Prepare_env(bb);

    Future<8, period_1F> x(bb);
    Future<8, period_5F> y(bb);
    int j = 0;
    bool b = false;
    bool for_section_test = false;
    int type = 0;

    BoolsegsList<8, 9> S1;
    BoolsegsList<8, 9> S2;
    BoolsegsList<8, 9> S3;
    BoolsegsList<8, 9> S4;

    int tofalse;
    int totrue;

    int flag;

    bool ref4;
    bool cur;

    int size;
    int B;
    int E;
    bool value;
    int len;

    int ref_B = -100;
    int ref_E = -100;
    int ref_len = -100;

    int segflag;
    int segB;
    int segE;
    int seglen;
    bool segvalue;
    bool refvalue;
    bool curvalue;
    int segs_size;

    bb->onBars([&](int e) {
        rtn = 0;
        // **************************** S1 test end !! ----------------------------------
        // -- 测试 最开始不赋值的情况 ---
        if (S1.x == 5) { // S1没有赋值的情况下 设置flag 无效
            S1.set_segflag(120);

            segflag = S1.cur_segflag();
            seglen = S1.cur_seglen();
            segB = S1.cur_segbegin();
            segE = S1.cur_segend();
            segvalue = S1;
            refvalue = S1.ref(1);
            curvalue = S1.cur();
            segs_size = S1.segments_.size();
            // std::cout << " idx: " << S1.x;
            // std::cout << "  B:" << segB << " E:" << segE;
            // std::cout << " len:" << seglen << "  flag:" << segflag << " size:" << segs_size;
            // std::cout << "  cur: " << curvalue << " segvalue:" << segvalue << " this->value_:" << S1.value_ << " refvalue:" << refvalue << std::endl;

            if (segB != INT_MIN || segE != INT_MIN || seglen != INT_MIN) {
                rtn = 10001;
                return;
            }
            if (segvalue != false || refvalue != false || curvalue != false) {
                rtn = 10002;
                return;
            }
            if (segflag != INT_MIN) {
                rtn = 10003;
                return;
            }
            if (segs_size != 0) {
                rtn = 10004;
                return;
            }
        }

        if (S1.x == 6) { // S1 = true;   0
            S1 = true;
            S1.set_segflag(120);

            segflag = S1.cur_segflag();
            seglen = S1.cur_seglen();
            segB = S1.cur_segbegin();
            segE = S1.cur_segend();
            segvalue = S1;
            refvalue = S1.ref(1);
            curvalue = S1.cur();
            segs_size = S1.segments_.size();
            // std::cout << " idx: " << S1.x;
            // std::cout << "  B:" << segB << " E:" << segE;
            // std::cout << " len:" << seglen << "  flag:" << segflag << " size:" << segs_size;
            // std::cout << "  cur: " << curvalue << " segvalue:" << segvalue << " this->value_:" << S1.value_ << " refvalue:" << refvalue << std::endl;

            if (segB != 6 || segE != 6 || seglen != 1) {
                rtn = 20001;
                return;
            }
            if (segvalue != true || refvalue != false || curvalue != true) {
                rtn = 20002;
                return;
            }
            if (segflag != 120) {
                rtn = 20003;
                return;
            }
            if (segs_size != 0) {
                rtn = 20004;
                return;
            }
        }

        if (S1.x == 7) { // S1 = true; than false------- 1
            S1 = true;
            S1.set_segflag(120);
            S1 = false; // ---------------------- false --------------------

            segflag = S1.cur_segflag();
            seglen = S1.cur_seglen();
            segB = S1.cur_segbegin();
            segE = S1.cur_segend();
            segvalue = S1;
            refvalue = S1.ref(1);
            curvalue = S1.cur();
            segs_size = S1.segments_.size();
            // std::cout << " idx: " << S1.x;
            // std::cout << "  B:" << segB << " E:" << segE;
            // std::cout << " len:" << seglen << "  flag:" << segflag << " size:" << segs_size;
            // std::cout << "  cur: " << curvalue << " segvalue:" << segvalue << " this->value_:" << S1.value_ << " refvalue:" << refvalue << std::endl;

            if (segB != 7 || segE != 7 || seglen != 1) {
                rtn = 30001;
                return;
            }
            if (segvalue != false || refvalue != true || curvalue != false) {
                rtn = 30002;
                return;
            }
            if (segflag != INT_MIN) {
                rtn = 30003;
                return;
            }
            if (segs_size != 1) { // 结束onbar后在 update中更新为2
                rtn = 30004;
                return;
            }
        }

        if (S1.x == 8) { //  ----------------自动延续  false --------------------
            S1.set_segflag(120);

            segflag = S1.cur_segflag();
            seglen = S1.cur_seglen();
            segB = S1.cur_segbegin();
            segE = S1.cur_segend();
            segvalue = S1;
            refvalue = S1.ref(1);
            curvalue = S1.cur();
            segs_size = S1.segments_.size();
            std::cout << " idx: " << S1.x;
            std::cout << "  B:" << segB << " E:" << segE;
            std::cout << " len:" << seglen << "  flag:" << segflag << " size:" << segs_size;
            std::cout << "  cur: " << curvalue << " segvalue:" << segvalue << " this->value_:" << S1.value_ << " refvalue:" << refvalue << std::endl;

            if (segB != 7 || segE != 8 || seglen != 2) {
                rtn = 40001;
                return;
            }
            if (segvalue != false || refvalue != false || curvalue != false) {
                rtn = 40002;
                return;
            }
            if (segflag != 120) {
                rtn = 40003;
                return;
            }
            if (segs_size != 2) { // 已更新为2
                rtn = 40004;
                return;
            }
        }
        if (S1.x == 9) { // ----------------延续 false--------------------------------
            S1.set_segflag(140);

            segflag = S1.cur_segflag();
            seglen = S1.cur_seglen();
            segB = S1.cur_segbegin();
            segE = S1.cur_segend();
            segvalue = S1;
            refvalue = S1.ref(1);
            curvalue = S1.cur();
            segs_size = S1.segments_.size();
            // std::cout << " idx: " << S1.x;
            // std::cout << "  B:" << segB << " E:" << segE;
            // std::cout << " len:" << seglen << "  flag:" << segflag << " size:" << segs_size;
            // std::cout << "  cur: " << curvalue << " segvalue:" << segvalue << " this->value_:" << S1.value_ << " refvalue:" << refvalue << std::endl;

            if (segB != 7 || segE != 9 || seglen != 3) {
                rtn = 50001;
                return;
            }
            if (segvalue != false || refvalue != false || curvalue != false) {
                rtn = 50002;
                return;
            }
            if (segflag != 140) {
                rtn = 50003;
                return;
            }
            if (segs_size != 2) {
                rtn = 50004;
                return;
            }
            if (S1.segments_[segs_size - 2].B != 6 || S1.segments_[segs_size - 2].E != 6 || S1.segments_[segs_size - 2].len != 1 || S1.segments_[segs_size - 2].value != true) { //
                rtn = 50005;
                return;
            }
        }

        if (S1.x == 10) { // ------------ 设置 true   ---------------------------------  2
            S1 = true;
            S1.set_segflag(150);

            segflag = S1.cur_segflag();
            seglen = S1.cur_seglen();
            segB = S1.cur_segbegin();
            segE = S1.cur_segend();
            segvalue = S1;
            refvalue = S1.ref(1);
            curvalue = S1.cur();
            segs_size = S1.segments_.size();
            // std::cout << " idx: " << S1.x;
            // std::cout << "  B:" << segB << " E:" << segE;
            // std::cout << " len:" << seglen << "  flag:" << segflag << " size:" << segs_size;
            // std::cout << "  cur: " << curvalue << " segvalue:" << segvalue << " this->value_:" << S1.value_ << " refvalue:" << refvalue << std::endl;

            if (segB != 10 || segE != 10 || seglen != 1) {
                rtn = 60001;
                return;
            }
            if (segvalue != true || refvalue != false || curvalue != true) {
                rtn = 60002;
                return;
            }
            if (segflag != 150) {
                rtn = 60003;
                return;
            }
            if (segs_size != 2) {
                rtn = 60004;
                return;
            }
        }

        if (S1.x == 11) { // ------------  true 继续---------------------------------

            segflag = S1.cur_segflag();
            seglen = S1.cur_seglen();
            segB = S1.cur_segbegin();
            segE = S1.cur_segend();
            segvalue = S1;
            refvalue = S1.ref(1);
            curvalue = S1.cur();
            segs_size = S1.segments_.size();
            // std::cout << " idx: " << S1.x;
            // std::cout << "  B:" << segB << " E:" << segE;
            // std::cout << " len:" << seglen << "  flag:" << segflag << " size:" << segs_size;
            // std::cout << "  cur: " << curvalue << " segvalue:" << segvalue << " this->value_:" << S1.value_ << " refvalue:" << refvalue << std::endl;

            if (segB != 10 || segE != 11 || seglen != 2) {
                rtn = 610001;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 610002;
                return;
            }
            if (segflag != 150) {
                rtn = 610003;
                return;
            }
            if (segs_size != 3) {
                rtn = 610004;
                return;
            }
        }

        if (S1.x == 12) { // ------------ 不再设置 S1 后，  true 继续  ---------------------
            S1.set_segflag(120);

            segflag = S1.cur_segflag();
            seglen = S1.cur_seglen();
            segB = S1.cur_segbegin();
            segE = S1.cur_segend();
            segvalue = S1;
            refvalue = S1.ref(1);
            curvalue = S1.cur();
            segs_size = S1.segments_.size();
            // std::cout << " idx: " << S1.x;
            // std::cout << "  B:" << segB << " E:" << segE;
            // std::cout << " len:" << seglen << "  flag:" << segflag << " size:" << segs_size;
            // std::cout << "  cur: " << curvalue << " segvalue:" << segvalue << " this->value_:" << S1.value_ << " refvalue:" << refvalue << std::endl;

            if (segB != 10 || segE != 12 || seglen != 3) {
                rtn = 70001;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 70002;
                return;
            }
            if (segflag != 120) {
                rtn = 70003;
                return;
            }
            if (segs_size != 3) { //
                rtn = 70004;
                return;
            }
        }

        if (S1.x == 13) { // ------------    true 延续 ---------------------
            S1.set_segflag(150);

            segflag = S1.cur_segflag();
            seglen = S1.cur_seglen();
            segB = S1.cur_segbegin();
            segE = S1.cur_segend();
            segvalue = S1;
            refvalue = S1.ref(1);
            curvalue = S1.cur();
            segs_size = S1.segments_.size();
            // std::cout << " idx: " << S1.x;
            // std::cout << "  B:" << segB << " E:" << segE;
            // std::cout << " len:" << seglen << "  flag:" << segflag << " size:" << segs_size;
            // std::cout << "  cur: " << curvalue << " segvalue:" << segvalue << " this->value_:" << S1.value_ << " refvalue:" << refvalue << std::endl;

            if (segB != 10 || segE != 13 || seglen != 4) {
                rtn = 80001;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 80002;
                return;
            }
            if (segflag != 150) {
                rtn = 80003;
                return;
            }
            if (segs_size != 3) { //
                rtn = 80004;
                return;
            }

            if (S1.segments_[segs_size - 2].B != 7 || S1.segments_[segs_size - 2].E != 9 || S1.segments_[segs_size - 2].len != 3) { //  已经更新为4
                rtn = 80005;
                return;
            }

            if (S1.segments_[segs_size - 2].flag != 140 || S1.segments_[segs_size - 2].value != false) {
                rtn = 80006;
                return;
            }

            if (S1.ref(5) != false) {
                rtn = 80007;
                return;
            }
        }
        // **************************** S1 test end !! ----------------------------------
        // **************************** S1 test end !! ----------------------------------
        // **************************** S1 test end !! ----------------------------------

        // xxxxxxx 0 ---- 4 true
        if (e >= 0 && e < 5) {
            S3 = true;
        }
        if (e == 3) { // ----------------中间设置flag --------
            S3.set_segflag(190);
        }
        // xxxxxxx 0 ---- 4 true

        if (e == 5) {
            S3.set_segflag(290);
        }
        if (e == 6) {
            S3.set_segflag(390);
        }

        // xxxxxxx 10 ---- 14 true
        if (e >= 10 && e < 15) {
            S3 = false;
        }
        if (e == 10) { // ----------------开头 设置flag --------
            S3.set_segflag(332);
        }
        if (e == 14) { // ----------------结尾再更改 flag --------
            S3.set_segflag(443);
        }
        // xxxxxxx 10 ---- 14 true

        // xxxxxxx
        if (e == 18) {
            S3 = true;
            std::cout << "S3 idx:" << S3.x << "  value: " << S3 << std::endl;
            S3 = false; // 这里虽然设置加了false，但是因为人为地对S3进行了赋值，所以后面 当index=19时，因为不再对S3进行赋值，默认改成true。
            S3.set_segflag(999);
        }
        if (e == 19) { // 设置不上
            S3.set_segflag(1919);
        }

        // xxxxxxx 20 ---- 24 true
        // 因为上面18对S3设置为了false，所以从19 - 24 均为true.直到 第25时，不再对S3赋值，所以 S3自动切换成了 false。
        if (e >= 20 && e < 25) {
            S3 = true;
        }

        if (e == 20) {
            S3.set_segflag(590);
        }

        if (e == 24) {
            S3.set_segflag(590);
        }
        // xxxxxxx 20 ---- 24 true

        if (e == 28) {
            S3.set_segflag(590);
        }

        segflag = S3.cur_segflag();
        seglen = S3.cur_seglen();
        segB = S3.cur_segbegin();
        segE = S3.cur_segend();
        segvalue = S3;
        refvalue = S3.ref(1);
        curvalue = S3.cur();
        segs_size = S3.segments_.size();
        // std::cout << " S3 idx: " << S3.x;
        // std::cout << "  B:" << segB << " E:" << segE;
        // std::cout << " len:" << seglen << "  flag:" << segflag << " size:" << segs_size;
        // std::cout << "  cur: " << curvalue << " segvalue:" << segvalue << " this->value_:" << S3.value_ << " refvalue:" << refvalue << std::endl;
        // if (S3.x > 0) {
        //     std::cout << "index: " << S3.x << " b " << S3.segments_[segs_size - 1].B << " e " << S3.segments_[segs_size - 1].E << " l " << S3.segments_[segs_size - 1].len << " f " << S3.segments_[segs_size - 1].flag << " v " << S3.segments_[segs_size - 1].value << std::endl;
        // }
        if (S3.x == 4) { // true -- 0
            if (segB != 0 || segE != 4 || seglen != 5) {
                rtn = 310001;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 310002;
                return;
            }
            if (segflag != 190) {
                rtn = 310003;
                return;
            }
            if (segs_size != 1) {
                rtn = 310004;
                return;
            }
        }

        if (S3.x == 5) { // -- true --
            if (segB != 0 || segE != 5 || seglen != 6) {
                rtn = 320001;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 320002;
                return;
            }
            if (segflag != 290) {
                rtn = 320003;
                return;
            }
            if (segs_size != 1) {
                rtn = 320004;
                return;
            }

            // index = 5时， 延续 true 还没有更新segment_[]的E 和 len.
            if (S3.segments_[segs_size - 1].B != 0 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 320005;
                return;
            }

            if (S3.segments_[segs_size - 1].flag != 190 || S3.segments_[segs_size - 1].value != true) {
                rtn = 320006;
                return;
            }

            if (S3.ref(2) != true) {
                rtn = 320007;
                return;
            }
        }

        if (S3.x == 6) { // -- true --
            if (segB != 0 || segE != 6 || seglen != 7) {
                rtn = 330001;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 330002;
                return;
            }
            if (segflag != 390) {
                rtn = 330003;
                return;
            }
            if (segs_size != 1) {
                rtn = 330004;
                return;
            }

            // index = 6时， 延续 true 还没有更新segment_[]的E 和 len.
            if (S3.segments_[segs_size - 1].B != 0 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 330005;
                return;
            }

            if (S3.segments_[segs_size - 1].flag != 290 || S3.segments_[segs_size - 1].value != true) {
                rtn = 330006;
                return;
            }

            if (S3.ref(2) != true) {
                rtn = 330007;
                return;
            }
        }

        if (S3.x == 10) { // --false --- 1
            if (segB != 10 || segE != 10 || seglen != 1) {
                rtn = 340001;
                return;
            }
            if (segvalue != false || refvalue != true || curvalue != false) {
                rtn = 340002;
                return;
            }
            if (segflag != 332) {
                rtn = 340003;
                return;
            }
            if (segs_size != 1) {
                rtn = 340004;
                return;
            }

            if (S3.segments_[segs_size - 1].B != 0 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 340005;
                return;
            }

            if (S3.segments_[segs_size - 1].flag != 390 || S3.segments_[segs_size - 1].value != true) {
                rtn = 340006;
                return;
            }

            if (S3.ref(2) != true || S3.ref(6) != true || S3.ref(5) != true) {
                rtn = 340007;
                return;
            }
        }

        if (S3.x == 11) { // false 继续
            if (segB != 10 || segE != 11 || seglen != 2) {
                rtn = 350001;
                return;
            }
            if (segvalue != false || refvalue != false || curvalue != false) {
                rtn = 350002;
                return;
            }
            if (segflag != 332) {
                rtn = 350003;
                return;
            }
            if (segs_size != 2) { // 更新
                rtn = 350004;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 0 || S3.segments_[segs_size - 2].E != 9 || S3.segments_[segs_size - 2].len != 10) {
                rtn = 350005;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != 390 || S3.segments_[segs_size - 2].value != true) {
                rtn = 350006;
                return;
            }

            // 当前的 segment 没有更新 E 和 len , flag 和 value 是ok的
            if (S3.segments_[segs_size - 1].B != 10 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 350007;
                return;
            }
            if (S3.segments_[segs_size - 1].flag != 332 || S3.segments_[segs_size - 1].value != false) {
                rtn = 350008;
                return;
            }

            if (S3.ref(1) != false || S3.ref(2) != true || S3.ref(7) != true || S3.ref(6) != true) {
                rtn = 350009;
                return;
            }
        }

        if (S3.x == 14) { // false
            if (segB != 10 || segE != 14 || seglen != 5) {
                rtn = 360001;
                return;
            }
            if (segvalue != false || refvalue != false || curvalue != false) {
                rtn = 360002;
                return;
            }
            if (segflag != 443) {
                rtn = 360003;
                return;
            }
            if (segs_size != 2) {
                rtn = 360004;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 0 || S3.segments_[segs_size - 2].E != 9 || S3.segments_[segs_size - 2].len != 10) {
                rtn = 360005;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != 390 || S3.segments_[segs_size - 2].value != true) {
                rtn = 360006;
                return;
            }

            if (S3.segments_[segs_size - 1].B != 10 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 360007;
                return;
            }
            if (S3.segments_[segs_size - 1].flag != 332 || S3.segments_[segs_size - 1].value != false) {
                rtn = 360008;
                return;
            }

            if (S3.ref(2) != false || S3.ref(4) != false || S3.ref(5) != true) {
                rtn = 360009;
                return;
            }
        }

        if (S3.x == 15) { // false 延续
            if (segB != 10 || segE != 15 || seglen != 6) {
                rtn = 370001;
                return;
            }
            if (segvalue != false || refvalue != false || curvalue != false) {
                rtn = 370002;
                return;
            }
            if (segflag != 443) {
                rtn = 370003;
                return;
            }
            if (segs_size != 2) {
                rtn = 370004;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 0 || S3.segments_[segs_size - 2].E != 9 || S3.segments_[segs_size - 2].len != 10) {
                rtn = 370005;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != 390 || S3.segments_[segs_size - 2].value != true) {
                rtn = 370006;
                return;
            }

            if (S3.segments_[segs_size - 1].B != 10 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 370007;
                return;
            }
            // flag在 上一个onbar的 update中更新为 443
            if (S3.segments_[segs_size - 1].flag != 443 || S3.segments_[segs_size - 1].value != false) {
                rtn = 370008;
                return;
            }

            if (S3.ref(2) != false || S3.ref(5) != false || S3.ref(6) != true) {
                rtn = 370009;
                return;
            }
        }

        if (S3.x == 18) { // false 延续
            if (segB != 10 || segE != 18 || seglen != 9) {
                rtn = 3180001;
                return;
            }
            if (segvalue != false || refvalue != false || curvalue != false) {
                rtn = 3180002;
                return;
            }
            if (segflag != 999) { // 可以设置
                rtn = 3180003;
                return;
            }
            if (segs_size != 2) {
                rtn = 3180004;
                return;
            }

            if (S3.segments_[segs_size - 1].B != 10 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 3180007;
                return;
            }
            // flag要等到update时才更新。
            if (S3.segments_[segs_size - 1].flag != 443 || S3.segments_[segs_size - 1].value != false) {
                rtn = 3180008;
                return;
            }

            if (S3.ref(2) != false || S3.ref(4) != false || S3.ref(3) != false) {
                rtn = 3180009;
                return;
            }
        }

        if (S3.x == 19) { // false  延续
            if (segB != 10 || segE != 19 || seglen != 10) {
                rtn = 3190001;
                return;
            }
            if (segvalue != false || refvalue != false || curvalue != false) {
                rtn = 3190002;
                return;
            }
            if (segflag != 1919) { //
                rtn = 3190003;
                return;
            }
            if (segs_size != 2) { // 结束时再更新
                rtn = 3190004;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 0 || S3.segments_[segs_size - 2].E != 9 || S3.segments_[segs_size - 2].len != 10) {
                rtn = 3190005;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != 390 || S3.segments_[segs_size - 2].value != true) {
                rtn = 3190006;
                return;
            }

            if (S3.segments_[segs_size - 1].B != 10 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 3190007;
                return;
            }
            // flag要等到update时才更新。
            if (S3.segments_[segs_size - 1].flag != 999 || S3.segments_[segs_size - 1].value != false) {
                rtn = 3190008;
                return;
            }

            if (S3.ref(2) != false || S3.ref(5) != false || S3.ref(4) != false) {
                rtn = 3190009;
                return;
            }
        }

        if (S3.x == 20) { //  20 ----------- S3 = true;  true段
            if (segB != 20 || segE != 20 || seglen != 1) {
                rtn = 3000201;
                return;
            }
            if (segvalue != true || refvalue != false || curvalue != true) {
                rtn = 3000202;
                return;
            }
            if (segflag != 590) {
                rtn = 3000203;
                return;
            }
            if (segs_size != 2) { // 在onbar结束后 再update
                rtn = 3000204;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 0 || S3.segments_[segs_size - 2].E != 9 || S3.segments_[segs_size - 2].len != 10) {
                rtn = 3000205;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != 390 || S3.segments_[segs_size - 2].value != true) {
                rtn = 3000206;
                return;
            }

            // 仍然是前一个segment, 要到 本onbar结束后，在update中push新的segment。
            if (S3.segments_[segs_size - 1].B != 10 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 3000207;
                return;
            }
            if (S3.segments_[segs_size - 1].flag != 1919 || S3.segments_[segs_size - 1].value != false) {
                rtn = 3000208;
                return;
            }

            if (S3.ref(0) != true || S3.ref(1) != false || S3.ref(2) != false) {
                rtn = 3000209;
                return;
            }
        }

        if (S3.x == 21) { // 21 S3 = true; true 延续 ----------------------------------------------
            if (segB != 20 || segE != 21 || seglen != 2) {
                rtn = 3000211;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 3000212;
                return;
            }
            if (segflag != 590) {
                rtn = 3000213;
                return;
            }
            if (segs_size != 3) {
                rtn = 3000214;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 10 || S3.segments_[segs_size - 2].E != 19 || S3.segments_[segs_size - 2].len != 10) {
                rtn = 3000215;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != 1919 || S3.segments_[segs_size - 2].value != false) {
                rtn = 3000216;
                return;
            }

            // 在前一onbar后的update中push的最新的 segment. 当前的 segment 没有更新 E 和 len ,   value 是ok的
            if (S3.segments_[segs_size - 1].B != 20 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 3000217;
                return;
            }

            if (S3.segments_[segs_size - 1].flag != 590 || S3.segments_[segs_size - 1].value != true) {
                rtn = 3000218;
                return;
            }

            if (S3.ref(2) != false || S3.ref(12) != true || S3.ref(11) != false) {
                rtn = 3000219;
                return;
            }
        }

        if (S3.x == 51) { // 51   true 延续 ----------------------------------------------
            if (segB != 20 || segE != 51 || seglen != 32) {
                rtn = 3000511;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 3000512;
                return;
            }
            if (segflag != 590) {
                rtn = 3000513;
                return;
            }
            if (segs_size != 3) {
                rtn = 3000514;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 10 || S3.segments_[segs_size - 2].E != 19 || S3.segments_[segs_size - 2].len != 10) {
                rtn = 3000515;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != 1919 || S3.segments_[segs_size - 2].value != false) {
                rtn = 3000516;
                return;
            }

            // 在前一onbar后的update中push的最新的 segment. 当前的 segment 没有更新 E 和 len ,   value 是ok的
            if (S3.segments_[segs_size - 1].B != 20 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 3000517;
                return;
            }

            if (S3.segments_[segs_size - 1].flag != 590 || S3.segments_[segs_size - 1].value != true) {
                rtn = 3000518;
                return;
            }

            if (S3.ref(12) != true || S3.ref(42) != true || S3.ref(41) != false) {
                rtn = 3000519;
                return;
            }
        }

        // **************************** S3 test end !! ----------------------------------
        // **************************** S3 test end !! ----------------------------------
        S4 = S4.OO[S4.x] < 0 ? false : true;

        segflag = S4.cur_segflag();
        seglen = S4.cur_seglen();
        segB = S4.cur_segbegin();
        segE = S4.cur_segend();
        segvalue = S4;
        refvalue = S4.ref(1);
        curvalue = S4.cur();
        segs_size = S4.segments_.size();
        // std::cout << " S4 idx: " << S4.x;
        // std::cout << "  B:" << segB << " E:" << segE;
        // std::cout << " len:" << seglen << "  flag:" << segflag << " size:" << segs_size;
        // std::cout << "  cur: " << curvalue << " segvalue:" << segvalue << " this->value_:" << S4.value_ << " refvalue:" << refvalue << std::endl;
        // if (S4.x > 0) {
        //     std::cout << " S4 index: " << S4.x << " b " << S4.segments_[segs_size - 1].B << " e " << S4.segments_[segs_size - 1].E << " l " << S4.segments_[segs_size - 1].len << " f " << S4.segments_[segs_size - 1].flag << " v " << S4.segments_[segs_size - 1].value <<
        //     std::endl;
        // }

        if (S4.x == 0) {
            S4.set_segflag(100);
        }

        if (S4.x == 4) {
            if (S4.cur_segflag() != 100) {
                rtn = 400001;
                return;
            }
        }
        if (S4.x == 5) {
            if (S4.cur_segflag() != INT_MIN) {
                rtn = 400002;
                return;
            }
        }

        if (S4.x == 15) {
            S4.set_segflag(100);
        }
        if (S4.x == 19) {
            if (S4.cur_segflag() != 100) {
                rtn = 400003;
                return;
            }
        }

        if (S4.x == 25) {
            S4.set_segflag(101);
            if (S4.cur_segflag() != 101) {
                rtn = 400004;
                return;
            }
            S4.set_segflag(102);
            if (S4.cur_segflag() != 102) {
                rtn = 400005;
                return;
            }
        }
        if (S4.x == 29 || S4.x == 28 || S4.x == 27 || S4.x == 26) {
            if (S4.cur_segflag() != 102) {
                rtn = 400006;
                return;
            }
        }

        // **************************** S4 test end !! ----------------------------------
        // **************************** S4 test end !! ----------------------------------

        if (S2.x == 0) {
            S2 = true;
            S2.set_segflag(40);
            if (S2.value_ != true || S2 != true || S2.cur() != true || S2.ref(4) != true || S2.cur_segflag() != 40) {
                rtn = 20000;
                return;
            }
            S2.set_segflag(140);
            if (S2.value_ != true || S2 != true || S2.cur() != true || S2.ref(4) != true || S2.cur_segflag() != 140) {
                rtn = 20001;
                return;
            }
            S2 = false;
            if (S2.value_ != false || S2 != false || S2.cur() != false || S2.ref(4) != false || S2.cur_segflag() != INT_MIN) {
                rtn = 20002;
                return;
            }
            S2.set_segflag(777);
            if (S2.value_ != false || S2 != false || S2.cur() != false || S2.ref(4) != false || S2.cur_segflag() != 777) {
                rtn = 20003;
                return;
            }
            S2 = true;
            if (S2.value_ != true || S2 != true || S2.cur() != true || S2.ref(4) != true || S2.cur_segflag() != INT_MIN) {
                rtn = 20004;
                return;
            }
        }

        S2 = S2.OO[S2.x] < 0 ? false : true;

        ref4 = S2.ref(4);
        cur = S2.cur();

        if (S2 && !S2.ref(1)) {
            S2.set_segflag(2023);
        }

        if (S2.x % 7 == 0) {
            S2.set_segflag(7);
        }

        if (S2.x == 3) {
            S2.set_segflag(105);
        }
        if (S2.x == 18) {
            S2.set_segflag(108);
        }

        tofalse = S2.tofalse_last();
        totrue = S2.totrue_last();
        flag = S2.cur_segflag();
    });

    // -100 -100 -100 -100 -100, 100 100 100 100 100 ,-100 -100 -100 -100 -100, 100 100 100 100 100
    for (int i = 0; i < 100000; i++) {
        x.unit->index = i;
        if (i % 5 == 0) {
            b = !b;
        }
        x.unit->OO[i] = b ? -100 : 100;

        bb->unit_array_[8][9]->func_signal(); // 这是前置处理。 ===================================
        bb->onBarsHandler(i);                 // todo 这个参数 i 应该是没有在trader里用到。
        if (rtn != 0) {
            return rtn;
        }
        bb->unit_array_[8][9]->func_signal_end(); //   这是后置处理。 =================================

        size = S2.segments_.size();
        B = S2.segments_.back().B;
        E = S2.segments_.back().E;
        value = S2.segments_.back().value;
        len = S2.segments_.back().len;

        if (size > 1) {
            ref_B = S2.segments_[size - 2].B;
            ref_E = S2.segments_[size - 2].E;
            ref_len = S2.segments_[size - 2].len;
        }

        // std::cout << S2.x << " O: " << S2.OO[i];
        // std::cout << " S2.value_: " << S2.value_ << " value:" << value << " cur():" << cur << "  ref():" << ref4 << "  flag:" << flag;
        // std::cout << " -- size: " << size << " B:" << B << " E:" << E << " len:" << len;
        // std::cout << " -- ref_B: " << ref_B << " ref_E: " << ref_E << "  ref_len: " << ref_len;
        // std::cout << "  tofalse:" << tofalse << "  ---  totrue: " << totrue << std::endl;

        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        if (i > 100) {
            break;
        }
    }
    delete bb;
    return rtn;

} // end test02() ;
} // namespace uBEE
