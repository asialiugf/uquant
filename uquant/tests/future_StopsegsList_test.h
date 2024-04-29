
#include "future_env.h"

namespace uBEE {

int StopsegsList_sub01(int i) {

    bool m_line = true;
    bool b01 = true;
    bool b02 = true;

    static StopsegsList<8, 9> MM;

    static StopsegsList<8, 12> MT12;
    static StopsegsList<8, 12> NT12;

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

int StopsegsList_test1() {

    int rtn = 0;
    Base *bb = new Base;
    rtn = Prepare_env(bb);

    Future<8, period_1F> x(bb);
    Future<8, period_5F> y(bb);

    for (int i = 0; i < 1000; i++) {
        x.unit->index = i;
        rtn = StopsegsList_sub01(i);
        if (rtn != 0) {
            // LOG(INFO) << " rtn is: " << i << "  rtn: " << rtn;
            break;
        }
    }

    return rtn;
} // end test01() ;

int StopsegsList_test2() {
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

    StopsegsList<8, 9> S1;
    StopsegsList<8, 9> S2;
    StopsegsList<8, 9> S3;
    StopsegsList<8, 9> S4;

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

        if (S1.x == 6) {
            S1 = true; // -------------------true -----------------
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

        if (S1.x == 7) {
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
            if (segs_size != 1) {
                rtn = 30004;
                return;
            }
        }

        if (S1.x == 8) { //  ----------------自动变为 true --------------------
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

            if (segB != 8 || segE != 8 || seglen != 1) {
                rtn = 40001;
                return;
            }
            if (segvalue != true || refvalue != false || curvalue != true) {
                rtn = 40002;
                return;
            }
            if (segflag != INT_MIN) {
                rtn = 40003;
                return;
            }
            if (segs_size != 2) { // 下一个onbar中更新为3，结束了false的segment， 新的true的segment开始！
                rtn = 40004;
                return;
            }
        }
        if (S1.x == 9) { // ----------------延续 true ---------------------------------
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

            if (segB != 8 || segE != 9 || seglen != 2) {
                rtn = 50001;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 50002;
                return;
            }
            if (segflag != INT_MIN) {
                rtn = 50003;
                return;
            }
            if (segs_size != 3) { // vector 中 push了一个新的 segment.
                rtn = 50004;
                return;
            }
            if (S1.segments_[segs_size - 2].B != 7 || S1.segments_[segs_size - 2].E != 7 || S1.segments_[segs_size - 2].len != 1 || S1.segments_[segs_size - 2].value != false) { //  已经更新为4
                rtn = 50005;
                return;
            }
        }

        if (S1.x == 10) { // ------------主动设置为true后，可以设置flag了---- 并且  延续 true ---------------------------------
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

            if (segB != 8 || segE != 10 || seglen != 3) {
                rtn = 60001;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 60002;
                return;
            }
            if (segflag != 120) {
                rtn = 60003;
                return;
            }
            if (segs_size != 3) {
                rtn = 60004;
                return;
            }
        }

        if (S1.x == 11) { // ------------    主动 true 继续---------------------------------
            S1 = true;

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

            if (segB != 8 || segE != 11 || seglen != 4) {
                rtn = 610001;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 610002;
                return;
            }
            if (segflag != 120) {
                rtn = 610003;
                return;
            }
            if (segs_size != 3) {
                rtn = 610004;
                return;
            }
        }

        if (S1.x == 12) { // ------------ 不再设置 S1 后， 自动切换为 false ---------------------
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

            if (segB != 12 || segE != 12 || seglen != 1) {
                rtn = 70001;
                return;
            }
            if (segvalue != false || refvalue != true || curvalue != false) {
                rtn = 70002;
                return;
            }
            if (segflag != INT_MIN) {
                rtn = 70003;
                return;
            }
            if (segs_size != 3) { // 会在 update中更新为4
                rtn = 70004;
                return;
            }
        }

        if (S1.x == 13) { // ------------   false 延续 ---------------------
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

            if (segB != 12 || segE != 13 || seglen != 2) {
                rtn = 80001;
                return;
            }
            if (segvalue != false || refvalue != false || curvalue != false) {
                rtn = 80002;
                return;
            }
            if (segflag != INT_MIN) {
                rtn = 80003;
                return;
            }
            if (segs_size != 4) { //  已经更新为4
                rtn = 80004;
                return;
            }
            if (S1.segments_[segs_size - 2].B != 8 || S1.segments_[segs_size - 2].E != 11 || S1.segments_[segs_size - 2].len != 4) { //  已经更新为4
                rtn = 80005;
                return;
            }

            if (S1.segments_[segs_size - 2].flag != 120 || S1.segments_[segs_size - 2].value != true) { //  已经更新为4
                rtn = 80006;
                return;
            }

            if (S1.ref(5) != true) {
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
            S3 = true;
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
        if (S3.x == 4) {
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

        if (S3.x == 5) {
            if (segB != 5 || segE != 5 || seglen != 1) {
                rtn = 320001;
                return;
            }
            if (segvalue != false || refvalue != true || curvalue != false) {
                rtn = 320002;
                return;
            }
            if (segflag != INT_MIN) {
                rtn = 320003;
                return;
            }
            if (segs_size != 1) {
                rtn = 320004;
                return;
            }

            // index = 5时，正好是结束点，在onbar中， 还没有更新segment_[]的E 和 len.
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

        if (S3.x == 6) {
            if (segB != 5 || segE != 6 || seglen != 2) {
                rtn = 330001;
                return;
            }
            if (segvalue != false || refvalue != false || curvalue != false) {
                rtn = 330002;
                return;
            }
            if (segflag != INT_MIN) {
                rtn = 330003;
                return;
            }
            if (segs_size != 2) {
                rtn = 330004;
                return;
            }

            // index = 5时，正好是结束点，在onbar中， 还没有更新segment_[]的E 和 len.
            if (S3.segments_[segs_size - 2].B != 0 || S3.segments_[segs_size - 2].E != 4 || S3.segments_[segs_size - 2].len != 5) {
                rtn = 330005;
                return;
            }

            if (S3.segments_[segs_size - 2].flag != 190 || S3.segments_[segs_size - 2].value != true) {
                rtn = 330006;
                return;
            }

            if (S3.ref(2) != true) {
                rtn = 330007;
                return;
            }
        }

        if (S3.x == 10) {
            if (segB != 10 || segE != 10 || seglen != 1) {
                rtn = 340001;
                return;
            }
            if (segvalue != true || refvalue != false || curvalue != true) {
                rtn = 340002;
                return;
            }
            if (segflag != 332) {
                rtn = 340003;
                return;
            }
            if (segs_size != 2) {
                rtn = 340004;
                return;
            }

            // index = 5时，正好是结束点，在onbar中， 还没有更新segment_[]的E 和 len.
            if (S3.segments_[segs_size - 2].B != 0 || S3.segments_[segs_size - 2].E != 4 || S3.segments_[segs_size - 2].len != 5) {
                rtn = 340005;
                return;
            }

            if (S3.segments_[segs_size - 2].flag != 190 || S3.segments_[segs_size - 2].value != true) {
                rtn = 340006;
                return;
            }

            if (S3.ref(2) != false || S3.ref(6) != true || S3.ref(5) != false) {
                rtn = 340007;
                return;
            }
        }

        if (S3.x == 11) {
            if (segB != 10 || segE != 11 || seglen != 2) {
                rtn = 350001;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 350002;
                return;
            }
            if (segflag != 332) {
                rtn = 350003;
                return;
            }
            if (segs_size != 3) { // 更新
                rtn = 350004;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 5 || S3.segments_[segs_size - 2].E != 9 || S3.segments_[segs_size - 2].len != 5) {
                rtn = 350005;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != INT_MIN || S3.segments_[segs_size - 2].value != false) {
                rtn = 350006;
                return;
            }

            // 当前的 segment 没有更新 E 和 len , flag 和 value 是ok的
            if (S3.segments_[segs_size - 1].B != 10 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 350007;
                return;
            }
            if (S3.segments_[segs_size - 1].flag != 332 || S3.segments_[segs_size - 1].value != true) {
                rtn = 350008;
                return;
            }

            if (S3.ref(2) != false || S3.ref(7) != true || S3.ref(6) != false) {
                rtn = 350009;
                return;
            }
        }

        if (S3.x == 14) {
            if (segB != 10 || segE != 14 || seglen != 5) {
                rtn = 360001;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 360002;
                return;
            }
            if (segflag != 443) {
                rtn = 360003;
                return;
            }
            if (segs_size != 3) {
                rtn = 360004;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 5 || S3.segments_[segs_size - 2].E != 9 || S3.segments_[segs_size - 2].len != 5) {
                rtn = 360005;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != INT_MIN || S3.segments_[segs_size - 2].value != false) {
                rtn = 360006;
                return;
            }

            // 当前的 segment 没有更新 E 和 len , flag 和 value 是ok的
            if (S3.segments_[segs_size - 1].B != 10 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 360007;
                return;
            }
            // flag要等到update时才更新。
            if (S3.segments_[segs_size - 1].flag != 332 || S3.segments_[segs_size - 1].value != true) {
                rtn = 360008;
                return;
            }

            if (S3.ref(2) != true || S3.ref(4) != true || S3.ref(5) != false) {
                rtn = 360009;
                return;
            }
        }

        // 16  false自动切为false,结束时再 push新的 segment
        if (S3.x == 15) {
            if (segB != 15 || segE != 15 || seglen != 1) {
                rtn = 370001;
                return;
            }
            if (segvalue != false || refvalue != true || curvalue != false) {
                rtn = 370002;
                return;
            }
            if (segflag != INT_MIN) {
                rtn = 370003;
                return;
            }
            if (segs_size != 3) { // 发现要 push ，等结束时，  在index=15的 update中
                rtn = 370004;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 5 || S3.segments_[segs_size - 2].E != 9 || S3.segments_[segs_size - 2].len != 5) {
                rtn = 370005;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != INT_MIN || S3.segments_[segs_size - 2].value != false) {
                rtn = 370006;
                return;
            }

            // 当前的 segment 没有更新 E 和 len , flag 和 value 是ok的
            if (S3.segments_[segs_size - 1].B != 10 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 370007;
                return;
            }
            // flag 在 index =14 的 update中更新成了 443
            if (S3.segments_[segs_size - 1].flag != 443 || S3.segments_[segs_size - 1].value != true) {
                rtn = 370008;
                return;
            }

            if (S3.ref(2) != true || S3.ref(5) != true || S3.ref(6) != false) {
                rtn = 370009;
                return;
            }
        }

        // 16 17 false自动延续 ------
        if (S3.x == 16) {
            if (segB != 15 || segE != 16 || seglen != 2) {
                rtn = 380001;
                return;
            }
            if (segvalue != false || refvalue != false || curvalue != false) {
                rtn = 380002;
                return;
            }
            if (segflag != INT_MIN) {
                rtn = 380003;
                return;
            }
            if (segs_size != 4) {
                rtn = 380004;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 10 || S3.segments_[segs_size - 2].E != 14 || S3.segments_[segs_size - 2].len != 5) {
                rtn = 380005;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != 443 || S3.segments_[segs_size - 2].value != true) {
                rtn = 380006;
                return;
            }

            // 当前的 segment 没有更新 E 和 len , flag 和 value 是ok的
            if (S3.segments_[segs_size - 1].B != 15 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 380007;
                return;
            }
            // flag要等到update时才更新。
            if (S3.segments_[segs_size - 1].flag != INT_MIN || S3.segments_[segs_size - 1].value != false) {
                rtn = 380008;
                return;
            }

            if (S3.ref(2) != true || S3.ref(6) != true || S3.ref(7) != false) {
                rtn = 380009;
                return;
            }
        }

        // 18 --------------------在默认的flase段中，人为设置   S3 = false;  ----------------------------------
        if (S3.x == 18) {
            if (segB != 15 || segE != 18 || seglen != 4) {
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
            if (segs_size != 4) {
                rtn = 3180004;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 10 || S3.segments_[segs_size - 2].E != 14 || S3.segments_[segs_size - 2].len != 5) {
                rtn = 3180005;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != 443 || S3.segments_[segs_size - 2].value != true) {
                rtn = 3180006;
                return;
            }

            // 当前的 segment 没有更新 E 和 len ,    value 是ok的
            if (S3.segments_[segs_size - 1].B != 15 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 3180007;
                return;
            }
            // flag要等到update时才更新。
            if (S3.segments_[segs_size - 1].flag != INT_MIN || S3.segments_[segs_size - 1].value != false) {
                rtn = 3180008;
                return;
            }

            if (S3.ref(2) != false || S3.ref(4) != true || S3.ref(3) != false) {
                rtn = 3180009;
                return;
            }
        }

        // 19 --------------- 自动切为 true --------- 不能设置 flag -------------------------
        if (S3.x == 19) {
            if (segB != 19 || segE != 19 || seglen != 1) {
                rtn = 3190001;
                return;
            }
            if (segvalue != true || refvalue != false || curvalue != true) {
                rtn = 3190002;
                return;
            }
            if (segflag != INT_MIN) { // set_segflag(1919) 无效！
                rtn = 3190003;
                return;
            }
            if (segs_size != 4) { // 结束时再更新
                rtn = 3190004;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 10 || S3.segments_[segs_size - 2].E != 14 || S3.segments_[segs_size - 2].len != 5) {
                rtn = 3190005;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != 443 || S3.segments_[segs_size - 2].value != true) {
                rtn = 3190006;
                return;
            }

            // 当前的 segment 没有更新 E 和 len , flag 和 value 是ok的
            if (S3.segments_[segs_size - 1].B != 15 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 3190007;
                return;
            }
            // flag要等到update时才更新。
            if (S3.segments_[segs_size - 1].flag != 999 || S3.segments_[segs_size - 1].value != false) {
                rtn = 3190008;
                return;
            }

            if (S3.ref(2) != false || S3.ref(5) != true || S3.ref(4) != false) {
                rtn = 3190009;
                return;
            }
        }

        //  20 ----------- S3 = true;  true段 延续 --------- 可以设置flag -------------------------
        if (S3.x == 20) {
            if (segB != 19 || segE != 20 || seglen != 2) {
                rtn = 3000201;
                return;
            }
            if (segvalue != true || refvalue != true || curvalue != true) {
                rtn = 3000202;
                return;
            }
            if (segflag != 590) {
                rtn = 3000203;
                return;
            }
            if (segs_size != 5) {
                rtn = 3000204;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 15 || S3.segments_[segs_size - 2].E != 18 || S3.segments_[segs_size - 2].len != 4) {
                rtn = 3000205;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != 999 || S3.segments_[segs_size - 2].value != false) {
                rtn = 3000206;
                return;
            }

            // 当前的 segment 没有更新 E 和 len , flag 和 value 是ok的
            if (S3.segments_[segs_size - 1].B != 19 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 3000207;
                return;
            }
            // flag要等到update时才更新成 590。
            if (S3.segments_[segs_size - 1].flag != INT_MIN || S3.segments_[segs_size - 1].value != true) {
                rtn = 3000208;
                return;
            }

            if (S3.ref(0) != true || S3.ref(1) != true || S3.ref(2) != false) {
                rtn = 3000209;
                return;
            }
        }

        // 21 S3 = true; true 延续 ----------------------------------------------
        if (S3.x == 21) {
            if (segB != 19 || segE != 21 || seglen != 3) {
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
            if (segs_size != 5) {
                rtn = 3000214;
                return;
            }

            if (S3.segments_[segs_size - 2].B != 15 || S3.segments_[segs_size - 2].E != 18 || S3.segments_[segs_size - 2].len != 4) {
                rtn = 3000215;
                return;
            }
            if (S3.segments_[segs_size - 2].flag != 999 || S3.segments_[segs_size - 2].value != false) {
                rtn = 3000216;
                return;
            }

            // 当前的 segment 没有更新 E 和 len , flag 和 value 是ok的
            if (S3.segments_[segs_size - 1].B != 19 || S3.segments_[segs_size - 1].E != INT_MIN || S3.segments_[segs_size - 1].len != 1) {
                rtn = 3000217;
                return;
            }
            // flag 更新成了 590。
            if (S3.segments_[segs_size - 1].flag != 590 || S3.segments_[segs_size - 1].value != true) {
                rtn = 3000218;
                return;
            }

            if (S3.ref(7) != true || S3.ref(2) != true || S3.ref(3) != false) {
                rtn = 3000219;
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

int StopsegsList_test3() {
    std::cout << " ########################################## test 3 #######################################" << std::endl;
    int rtn = 0;
    Base *bb = new Base;
    rtn = Prepare_env(bb);

    Future<8, period_1F> x(bb);
    Future<8, period_5F> y(bb);
    int j = 0;
    bool b = false;
    bool for_section_test = false;
    int type = 0;

    StopsegsList<8, 9> S1;
    StopsegsList<8, 9> S2;
    StopsegsList<8, 9> S3;

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

    bb->onBars([&](int e) {
        rtn = 0;
        // S3--------------------------------------------------------------------------------------------------

        // S3--------------------------------------------------------------------------------------------------
        if (S1.x == 5) {
            S1.set_segflag(1000); // 在 对S1赋值前，设置flag无效，其值永远为 INT_MIN.
            if (S1.cur_segflag() != INT_MIN || S1.segments_.size() != 0) {
                rtn = 10001;
                return;
            }
        }

        if (S1.x == 6) {
            S1 = true; // -----------------------------------------------0------ change !!       S1第一次赋值
            if (S1.cur_segflag() != INT_MIN || S1.segments_.size() != 0) {
                rtn = 10002; // size此时为0，要在后置处理中，更新后才能为1。
                return;
            }
            S1.set_segflag(23); // 当对S1赋值之后， set_segflag() 立刻生效。
            if (S1.cur_segflag() != 23) {
                rtn = 10003;
                return;
            }
        }

        if (S1.x == 11) {
            if (S1.cur_segflag() != 23 || S1.cur_seglen() != 6 || S1.cur_segbegin() != 6) {
                rtn = 100041;
                return;
            }
            S1.set_segflag(723);
            if (S1.cur_segflag() != 723 || S1.segments_.size() != 1) {
                rtn = 10004;
                return;
            }
        }

        if (S1.x == 14) {
            if (S1.cur_segflag() != 723 || S1.segments_.size() != 1) {
                rtn = 10005;
                return;
            }
        }

        if (S1.x == 15) { // S1 改为false后又改回来.
            S1 = false;
            if (S1.cur_segflag() != INT_MIN || S1.segments_.size() != 1) {
                rtn = 100060;
                return;
            }
            S1 = true;
            if (S1.cur_segflag() != 723 || S1.segments_.size() != 1) {
                rtn = 100061;
                return;
            }
        }

        if (S1.x == 18) {
            if (S1.cur_segflag() != 723 || S1.segments_.size() != 1 || S1.cur_seglen() != 13 || S1.cur_segbegin() != 6) {
                rtn = 100062;
                return;
            }
            S1 = false; // ---------------------------------------------1-------- change !!
            if (S1.cur_segflag() != INT_MIN || S1.segments_.size() != 1) {
                rtn = 100063;
                return;
            }
        }

        if (S1.x == 19) {
            if (S1.cur_segflag() != INT_MIN || S1.segments_.size() != 2) {
                rtn = 100070;
                return;
            }
            if (S1.segments_[0].B != 6 || S1.segments_[0].E != 17 || S1.segments_[0].len != 12) {
                rtn = 100071;
                return;
            }
        }

        if (S1.x == 21) {
            S1 = true; // ---------------------------------------------2-------- change !!  ----------------
            if (S1.cur_segflag() != INT_MIN || S1.segments_.size() != 2) {
                rtn = 10008;
                return;
            }
        }

        if (S1.x == 22) {
            if (S1.cur_segflag() != INT_MIN || S1.segments_.size() != 3) { // 0,1,2 2是当前segments_[] 的 idx.
                rtn = 100090;
                return;
            }
            if (S1.segments_[1].B != 18 || S1.segments_[1].E != 20 || S1.segments_[1].len != 3) {
                rtn = 100091;
                return;
            }
            S1.set_segflag(888);
        }

        if (S1.x == 88) {
            if (S1 != true || S1.cur_segflag() != 888 || S1.segments_.size() != 3) { // 0,1,2 2是当前segments_[] 的 idx.
                rtn = 100100;
                return;
            }
            if (S1.segments_[1].B != 18 || S1.segments_[1].E != 20 || S1.segments_[1].len != 3) {
                rtn = 100101;
                return;
            }
        }

        // **************************** S1 test end !! ----------------------------------

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

        // 0 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:7 -- size: 1 B:0 E:-1 len:1 -- ref_B: -100 ref_E: -100  ref_len: -100  tofalse:0  ---  totrue: 0
        // 1 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:7 -- size: 1 B:0 E:-1 len:1 -- ref_B: -100 ref_E: -100  ref_len: -100  tofalse:0  ---  totrue: 0
        // 2 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:7 -- size: 1 B:0 E:-1 len:1 -- ref_B: -100 ref_E: -100  ref_len: -100  tofalse:0  ---  totrue: 0
        // 3 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:105 -- size: 1 B:0 E:-1 len:1 -- ref_B: -100 ref_E: -100  ref_len: -100  tofalse:0  ---  totrue: 0
        // 4 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:105 -- size: 1 B:0 E:-1 len:1 -- ref_B: -100 ref_E: -100  ref_len: -100  tofalse:0  ---  totrue: 0
        // 5 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 2 B:5 E:-1 len:1 -- ref_B: 0 ref_E: 4  ref_len: 5  tofalse:0  ---  totrue: 0
        // 6 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 2 B:5 E:-1 len:1 -- ref_B: 0 ref_E: 4  ref_len: 5  tofalse:0  ---  totrue: 0
        // 7 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 2 B:5 E:-1 len:1 -- ref_B: 0 ref_E: 4  ref_len: 5  tofalse:0  ---  totrue: 0
        // 8 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 2 B:5 E:-1 len:1 -- ref_B: 0 ref_E: 4  ref_len: 5  tofalse:0  ---  totrue: 0
        // 9 O: 100 S2.value_: 1 value:1 cur():1  ref():1  flag:7 -- size: 2 B:5 E:-1 len:1 -- ref_B: 0 ref_E: 4  ref_len: 5  tofalse:0  ---  totrue: 0
        // 10 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 3 B:10 E:-1 len:1 -- ref_B: 5 ref_E: 9  ref_len: 5  tofalse:0  ---  totrue: 0
        // 11 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 3 B:10 E:-1 len:1 -- ref_B: 5 ref_E: 9  ref_len: 5  tofalse:0  ---  totrue: 0
        // 12 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 3 B:10 E:-1 len:1 -- ref_B: 5 ref_E: 9  ref_len: 5  tofalse:0  ---  totrue: 0
        // 13 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 3 B:10 E:-1 len:1 -- ref_B: 5 ref_E: 9  ref_len: 5  tofalse:0  ---  totrue: 0
        // 14 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:7 -- size: 3 B:10 E:-1 len:1 -- ref_B: 5 ref_E: 9  ref_len: 5  tofalse:0  ---  totrue: 0
        // 15 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 4 B:15 E:-1 len:1 -- ref_B: 10 ref_E: 14  ref_len: 5  tofalse:0  ---  totrue: 0
        // 16 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 4 B:15 E:-1 len:1 -- ref_B: 10 ref_E: 14  ref_len: 5  tofalse:0  ---  totrue: 0
        // 17 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 4 B:15 E:-1 len:1 -- ref_B: 10 ref_E: 14  ref_len: 5  tofalse:0  ---  totrue: 0
        // 18 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:108 -- size: 4 B:15 E:-1 len:1 -- ref_B: 10 ref_E: 14  ref_len: 5  tofalse:0  ---  totrue: 0
        // 19 O: 100 S2.value_: 1 value:1 cur():1  ref():1  flag:108 -- size: 4 B:15 E:-1 len:1 -- ref_B: 10 ref_E: 14  ref_len: 5  tofalse:0  ---  totrue: 0
        // 20 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 5 B:20 E:-1 len:1 -- ref_B: 15 ref_E: 19  ref_len: 5  tofalse:0  ---  totrue: 0
        // 21 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 5 B:20 E:-1 len:1 -- ref_B: 15 ref_E: 19  ref_len: 5  tofalse:0  ---  totrue: 0
        // 22 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 5 B:20 E:-1 len:1 -- ref_B: 15 ref_E: 19  ref_len: 5  tofalse:0  ---  totrue: 0
        // 23 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 5 B:20 E:-1 len:1 -- ref_B: 15 ref_E: 19  ref_len: 5  tofalse:0  ---  totrue: 0
        // 24 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:7 -- size: 5 B:20 E:-1 len:1 -- ref_B: 15 ref_E: 19  ref_len: 5  tofalse:0  ---  totrue: 0
        // 25 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 6 B:25 E:-1 len:1 -- ref_B: 20 ref_E: 24  ref_len: 5  tofalse:0  ---  totrue: 0
        // 26 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 6 B:25 E:-1 len:1 -- ref_B: 20 ref_E: 24  ref_len: 5  tofalse:0  ---  totrue: 0
        // 27 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 6 B:25 E:-1 len:1 -- ref_B: 20 ref_E: 24  ref_len: 5  tofalse:0  ---  totrue: 0
        // 28 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 6 B:25 E:-1 len:1 -- ref_B: 20 ref_E: 24  ref_len: 5  tofalse:0  ---  totrue: 0
        // 29 O: 100 S2.value_: 1 value:1 cur():1  ref():1  flag:7 -- size: 6 B:25 E:-1 len:1 -- ref_B: 20 ref_E: 24  ref_len: 5  tofalse:0  ---  totrue: 0
        // 30 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 7 B:30 E:-1 len:1 -- ref_B: 25 ref_E: 29  ref_len: 5  tofalse:0  ---  totrue: 0
        // 31 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 7 B:30 E:-1 len:1 -- ref_B: 25 ref_E: 29  ref_len: 5  tofalse:0  ---  totrue: 0
        // 32 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 7 B:30 E:-1 len:1 -- ref_B: 25 ref_E: 29  ref_len: 5  tofalse:0  ---  totrue: 0
        // 33 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 7 B:30 E:-1 len:1 -- ref_B: 25 ref_E: 29  ref_len: 5  tofalse:0  ---  totrue: 0
        // 34 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:-2147483648 -- size: 7 B:30 E:-1 len:1 -- ref_B: 25 ref_E: 29  ref_len: 5  tofalse:0  ---  totrue: 0
        // 35 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 8 B:35 E:-1 len:1 -- ref_B: 30 ref_E: 34  ref_len: 5  tofalse:0  ---  totrue: 0
        // 36 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 8 B:35 E:-1 len:1 -- ref_B: 30 ref_E: 34  ref_len: 5  tofalse:0  ---  totrue: 0
        // 37 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 8 B:35 E:-1 len:1 -- ref_B: 30 ref_E: 34  ref_len: 5  tofalse:0  ---  totrue: 0
        // 38 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 8 B:35 E:-1 len:1 -- ref_B: 30 ref_E: 34  ref_len: 5  tofalse:0  ---  totrue: 0
        // 39 O: 100 S2.value_: 1 value:1 cur():1  ref():1  flag:7 -- size: 8 B:35 E:-1 len:1 -- ref_B: 30 ref_E: 34  ref_len: 5  tofalse:0  ---  totrue: 0
        // 40 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 9 B:40 E:-1 len:1 -- ref_B: 35 ref_E: 39  ref_len: 5  tofalse:0  ---  totrue: 0
        // 41 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 9 B:40 E:-1 len:1 -- ref_B: 35 ref_E: 39  ref_len: 5  tofalse:0  ---  totrue: 0
        // 42 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 9 B:40 E:-1 len:1 -- ref_B: 35 ref_E: 39  ref_len: 5  tofalse:0  ---  totrue: 0
        // 43 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 9 B:40 E:-1 len:1 -- ref_B: 35 ref_E: 39  ref_len: 5  tofalse:0  ---  totrue: 0
        // 44 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:7 -- size: 9 B:40 E:-1 len:1 -- ref_B: 35 ref_E: 39  ref_len: 5  tofalse:0  ---  totrue: 0
        // 45 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 10 B:45 E:-1 len:1 -- ref_B: 40 ref_E: 44  ref_len: 5  tofalse:0  ---  totrue: 0
        // 46 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 10 B:45 E:-1 len:1 -- ref_B: 40 ref_E: 44  ref_len: 5  tofalse:0  ---  totrue: 0
        // 47 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 10 B:45 E:-1 len:1 -- ref_B: 40 ref_E: 44  ref_len: 5  tofalse:0  ---  totrue: 0
        // 48 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 10 B:45 E:-1 len:1 -- ref_B: 40 ref_E: 44  ref_len: 5  tofalse:0  ---  totrue: 0
        // 49 O: 100 S2.value_: 1 value:1 cur():1  ref():1  flag:7 -- size: 10 B:45 E:-1 len:1 -- ref_B: 40 ref_E: 44  ref_len: 5  tofalse:0  ---  totrue: 0
        // 50 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 11 B:50 E:-1 len:1 -- ref_B: 45 ref_E: 49  ref_len: 5  tofalse:0  ---  totrue: 0
        // 51 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 11 B:50 E:-1 len:1 -- ref_B: 45 ref_E: 49  ref_len: 5  tofalse:0  ---  totrue: 0
        // 52 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 11 B:50 E:-1 len:1 -- ref_B: 45 ref_E: 49  ref_len: 5  tofalse:0  ---  totrue: 0
        // 53 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 11 B:50 E:-1 len:1 -- ref_B: 45 ref_E: 49  ref_len: 5  tofalse:0  ---  totrue: 0
        // 54 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:-2147483648 -- size: 11 B:50 E:-1 len:1 -- ref_B: 45 ref_E: 49  ref_len: 5  tofalse:0  ---  totrue: 0
        // 55 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 12 B:55 E:-1 len:1 -- ref_B: 50 ref_E: 54  ref_len: 5  tofalse:0  ---  totrue: 0
        // 56 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 12 B:55 E:-1 len:1 -- ref_B: 50 ref_E: 54  ref_len: 5  tofalse:0  ---  totrue: 0
        // 57 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 12 B:55 E:-1 len:1 -- ref_B: 50 ref_E: 54  ref_len: 5  tofalse:0  ---  totrue: 0
        // 58 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 12 B:55 E:-1 len:1 -- ref_B: 50 ref_E: 54  ref_len: 5  tofalse:0  ---  totrue: 0
        // 59 O: 100 S2.value_: 1 value:1 cur():1  ref():1  flag:7 -- size: 12 B:55 E:-1 len:1 -- ref_B: 50 ref_E: 54  ref_len: 5  tofalse:0  ---  totrue: 0
        // 60 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 13 B:60 E:-1 len:1 -- ref_B: 55 ref_E: 59  ref_len: 5  tofalse:0  ---  totrue: 0
        // 61 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 13 B:60 E:-1 len:1 -- ref_B: 55 ref_E: 59  ref_len: 5  tofalse:0  ---  totrue: 0
        // 62 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 13 B:60 E:-1 len:1 -- ref_B: 55 ref_E: 59  ref_len: 5  tofalse:0  ---  totrue: 0
        // 63 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 13 B:60 E:-1 len:1 -- ref_B: 55 ref_E: 59  ref_len: 5  tofalse:0  ---  totrue: 0
        // 64 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:7 -- size: 13 B:60 E:-1 len:1 -- ref_B: 55 ref_E: 59  ref_len: 5  tofalse:0  ---  totrue: 0
        // 65 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 14 B:65 E:-1 len:1 -- ref_B: 60 ref_E: 64  ref_len: 5  tofalse:0  ---  totrue: 0
        // 66 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 14 B:65 E:-1 len:1 -- ref_B: 60 ref_E: 64  ref_len: 5  tofalse:0  ---  totrue: 0
        // 67 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 14 B:65 E:-1 len:1 -- ref_B: 60 ref_E: 64  ref_len: 5  tofalse:0  ---  totrue: 0
        // 68 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 14 B:65 E:-1 len:1 -- ref_B: 60 ref_E: 64  ref_len: 5  tofalse:0  ---  totrue: 0
        // 69 O: 100 S2.value_: 1 value:1 cur():1  ref():1  flag:2023 -- size: 14 B:65 E:-1 len:1 -- ref_B: 60 ref_E: 64  ref_len: 5  tofalse:0  ---  totrue: 0
        // 70 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 15 B:70 E:-1 len:1 -- ref_B: 65 ref_E: 69  ref_len: 5  tofalse:0  ---  totrue: 0
        // 71 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 15 B:70 E:-1 len:1 -- ref_B: 65 ref_E: 69  ref_len: 5  tofalse:0  ---  totrue: 0
        // 72 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 15 B:70 E:-1 len:1 -- ref_B: 65 ref_E: 69  ref_len: 5  tofalse:0  ---  totrue: 0
        // 73 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 15 B:70 E:-1 len:1 -- ref_B: 65 ref_E: 69  ref_len: 5  tofalse:0  ---  totrue: 0
        // 74 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:7 -- size: 15 B:70 E:-1 len:1 -- ref_B: 65 ref_E: 69  ref_len: 5  tofalse:0  ---  totrue: 0
        // 75 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 16 B:75 E:-1 len:1 -- ref_B: 70 ref_E: 74  ref_len: 5  tofalse:0  ---  totrue: 0
        // 76 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 16 B:75 E:-1 len:1 -- ref_B: 70 ref_E: 74  ref_len: 5  tofalse:0  ---  totrue: 0
        // 77 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 16 B:75 E:-1 len:1 -- ref_B: 70 ref_E: 74  ref_len: 5  tofalse:0  ---  totrue: 0
        // 78 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 16 B:75 E:-1 len:1 -- ref_B: 70 ref_E: 74  ref_len: 5  tofalse:0  ---  totrue: 0
        // 79 O: 100 S2.value_: 1 value:1 cur():1  ref():1  flag:7 -- size: 16 B:75 E:-1 len:1 -- ref_B: 70 ref_E: 74  ref_len: 5  tofalse:0  ---  totrue: 0
        // 80 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 17 B:80 E:-1 len:1 -- ref_B: 75 ref_E: 79  ref_len: 5  tofalse:0  ---  totrue: 0
        // 81 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 17 B:80 E:-1 len:1 -- ref_B: 75 ref_E: 79  ref_len: 5  tofalse:0  ---  totrue: 0
        // 82 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 17 B:80 E:-1 len:1 -- ref_B: 75 ref_E: 79  ref_len: 5  tofalse:0  ---  totrue: 0
        // 83 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 17 B:80 E:-1 len:1 -- ref_B: 75 ref_E: 79  ref_len: 5  tofalse:0  ---  totrue: 0
        // 84 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:7 -- size: 17 B:80 E:-1 len:1 -- ref_B: 75 ref_E: 79  ref_len: 5  tofalse:0  ---  totrue: 0
        // 85 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 18 B:85 E:-1 len:1 -- ref_B: 80 ref_E: 84  ref_len: 5  tofalse:0  ---  totrue: 0
        // 86 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 18 B:85 E:-1 len:1 -- ref_B: 80 ref_E: 84  ref_len: 5  tofalse:0  ---  totrue: 0
        // 87 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 18 B:85 E:-1 len:1 -- ref_B: 80 ref_E: 84  ref_len: 5  tofalse:0  ---  totrue: 0
        // 88 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 18 B:85 E:-1 len:1 -- ref_B: 80 ref_E: 84  ref_len: 5  tofalse:0  ---  totrue: 0
        // 89 O: 100 S2.value_: 1 value:1 cur():1  ref():1  flag:2023 -- size: 18 B:85 E:-1 len:1 -- ref_B: 80 ref_E: 84  ref_len: 5  tofalse:0  ---  totrue: 0
        // 90 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 19 B:90 E:-1 len:1 -- ref_B: 85 ref_E: 89  ref_len: 5  tofalse:0  ---  totrue: 0
        // 91 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 19 B:90 E:-1 len:1 -- ref_B: 85 ref_E: 89  ref_len: 5  tofalse:0  ---  totrue: 0
        // 92 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 19 B:90 E:-1 len:1 -- ref_B: 85 ref_E: 89  ref_len: 5  tofalse:0  ---  totrue: 0
        // 93 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:7 -- size: 19 B:90 E:-1 len:1 -- ref_B: 85 ref_E: 89  ref_len: 5  tofalse:0  ---  totrue: 0
        // 94 O: -100 S2.value_: 0 value:0 cur():0  ref():0  flag:7 -- size: 19 B:90 E:-1 len:1 -- ref_B: 85 ref_E: 89  ref_len: 5  tofalse:0  ---  totrue: 0
        // 95 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 20 B:95 E:-1 len:1 -- ref_B: 90 ref_E: 94  ref_len: 5  tofalse:0  ---  totrue: 0
        // 96 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 20 B:95 E:-1 len:1 -- ref_B: 90 ref_E: 94  ref_len: 5  tofalse:0  ---  totrue: 0
        // 97 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:2023 -- size: 20 B:95 E:-1 len:1 -- ref_B: 90 ref_E: 94  ref_len: 5  tofalse:0  ---  totrue: 0
        // 98 O: 100 S2.value_: 1 value:1 cur():1  ref():0  flag:7 -- size: 20 B:95 E:-1 len:1 -- ref_B: 90 ref_E: 94  ref_len: 5  tofalse:0  ---  totrue: 0
        // 99 O: 100 S2.value_: 1 value:1 cur():1  ref():1  flag:7 -- size: 20 B:95 E:-1 len:1 -- ref_B: 90 ref_E: 94  ref_len: 5  tofalse:0  ---  totrue: 0
        // 100 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 21 B:100 E:-1 len:1 -- ref_B: 95 ref_E: 99  ref_len: 5  tofalse:0  ---  totrue: 0
        // 101 O: -100 S2.value_: 0 value:0 cur():0  ref():1  flag:-2147483648 -- size: 21 B:100 E:-1 len:1 -- ref_B: 95 ref_E: 99  ref_len: 5  tofalse:0  ---  totrue: 0

        // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        // 3 O: -100 S2.value_: 0  num:1 ---- B:0 E:3  value:0 len:4 mark1:1 mark5: 0  tofalse:-1    ---  totrue: -1 cur():0  ref():0
        if (i == 3) {
            // if (S2.value_ != false || cur != false) {
            //     return 10001;
            // }
            // if (size != 1 || B != 0 || E != 3 || value != false || len != 4) {
            //     return 10002;
            // }
            // if (tofalse != -1 || totrue != -1) {
            //     return 10003;
            // }
        }

        // 4 O: -100 S2.value_: 0  num:1 ---- B:0 E:4  value:0 len:5 mark1:1 mark5: 0  tofalse:-1    ---  totrue: -1 cur():0  ref():0
        if (i == 4) {
            // if (S2.value_ != false || cur != false) {
            //     return 20001;
            // }
            // if (size != 1 || B != 0 || E != 4 || value != false || len != 5) {
            //     return 20002;
            // }
            // if (tofalse != -1 || totrue != -1) {
            //     return 20003;
            // }
        }

        // 5 O: 100 S2.value_: 1  num:2 ---- B:5 E:5  value:1 len:1 mark1:0 mark5: 0  tofalse:-1    ---  totrue: 0 cur():1  ref():0
        if (i == 5) {
            // if (tofalse != -1 || totrue != 0) {
            //     return 30003;
            // }
        }

        // ---------------------------------------------------
        // 18 O: 100 S2.value_: 1  num:4 ---- B:15 E:18  value:1 len:4 mark1:0 mark5: 1  tofalse:8    ---  totrue: 3 cur():1  ref():0
        if (i == 18) {
            // if (S2.value_ != true || cur != true) {
            //     return 40001;
            // }
            // if (size != 4 || B != 15 || E != 18 || value != true || len != 4) {
            //     return 40002;
            // }
            // // if (tofalse != 8 || totrue != 3) {
            // //     return 40003;
            // // }
        }

        // 19 O: 100 S2.value_: 1  num:4 ---- B:15 E:19  value:1 len:5 mark1:0 mark5: 1  tofalse:9    ---  totrue: 4 cur():1  ref():1
        if (i == 19) {
            // if (S2.value_ != true || cur != true) {
            //     return 50001;
            // }
            // if (size != 4 || B != 15 || E != 19 || value != true || len != 5) {
            //     return 50002;
            // }
            // // if (tofalse != 9 || totrue != 4) {
            // //     return 50003;
            // // }
        }

        // 20 O: -100 S2.value_: 0  num:5 ---- B:20 E:20  value:0 len:1 mark1:0 mark5: 0  tofalse:0    ---  totrue: 5 cur():0  ref():1
        if (i == 20) {
            // if (tofalse != 0 || totrue != 5) {
            //     return 60003;
            // }
        }
        //----------------------------------------------------

        if (i > 100) {
            break;
        }
    }
    delete bb;
    return rtn;
} // end test02() ;

} // namespace uBEE