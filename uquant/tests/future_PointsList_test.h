
#include "future_env.h"

namespace uBEE {

int PointsList_sub01(int i) {

    bool m_line = true;
    bool b01 = true;
    bool b02 = true;

    static PointsList<8, 9> MM;

    static PointsList<8, 12> MT12;
    static PointsList<8, 12> NT12;

    // ---------------------------------------------------------------------1
    MM = m_line;
    if (MM.value_ != true) {
        return 1;
    }
    if (MM != true) { //  MM.points_.size()  = 1
        return 1001;
    }
    if (MM.points_.size() != i + 1) {
        return MM.points_.size() + 10000000;
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
    if (MM.points_.size() != i) { //  MM.points_.size()  = 0
        return MM.points_.size() + 20000000;
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
    if (MM.points_.size() != i + 1) { //  MM.points_.size()  = 1
        return MM.points_.size() + 30000000;
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
    if (MM.points_.size() != i + 1) { // MM.points_.size()  = 0
        return MM.points_.size() + 40000000;
    }

    MM = !MM; //  MM.points_.size()  = 0
    if (false != MM) {
        return 4004;
    }
    if (MM.points_.size() != i) { // MM.points_.size()  = 0
        return MM.points_.size() + 40000000;
    }

    MM = !MM;
    if (MM != true) { //  MM.points_.size()  = 1
        return 4005;
    }
    if (MM.points_.size() != i + 1) { //  MM.points_.size()  = 1
        return MM.points_.size() + 40000000;
    }

    //  ----------------------------------------------------------------------5
    MM = true;                        //  MM.points_.size()  = 1
    if (MM.points_.size() != i + 1) { //  MM.points_.size()  = 1
        return MM.points_.size() + 51000000;
    }
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

    if (MM.points_.size() != i) {
        LOG(INFO) << MM.points_.size() << "   MM.value_: " << MM.value_;
        return MM.points_.size() + 52000000;
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
    if (MM.points_.size() != i) {
        return MM.points_.size() + 61000000;
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
    if (MM.points_.size() != i + 1) {
        return MM.points_.size() + 62000000;
    }
    NN = false;
    // 因为NN不是static变量，每次循环都会初始化。
    return 0;
}

int PointsList_test() {

    int rtn = 0;
    Base *bb = new Base;
    rtn = Prepare_env(bb);

    std::cout << "  PointsList_test !!  befor Future<8,9> !!" << std::endl;

    static Future<8, period_1F> x(bb); //  Future<8, 9> x(&bb);
    static Future<8, period_5F> y(bb); //  Future<8, 12> y(&bb);

    std::cout << "  PointsList_test   after Future<8,9> !!" << std::endl;

    for (int i = 0; i < 1000; i++) {
        x.unit->index = i;
        rtn = PointsList_sub01(i);
        if (rtn != 0) {
            // LOG(INFO) << "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii is: " << i << "  rtn: " << rtn;
            break;
        }
    }

    return rtn;
} // end test01() ;
} // namespace uBEE
