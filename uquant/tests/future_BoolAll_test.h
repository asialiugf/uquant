
#include "future_env.h"

namespace uBEE {

int BoolAll_sub01(int i) {

    bool m_line = true;
    bool b01 = true;
    bool b02 = true;

    static PointsList<8, 9> MM;
    static StopsegsList<8, 9> NN;
    static BoolSerial<8, 9> TT;

    static PointsList<8, 12> MM3;
    static BoolsegsList<8, 12> NN3;
    static BoolSerial<8, 12> TT3;

    // ---------------------------------------------------------------------1
    MM = true;
    NN = false;
    TT = true;

    MM3 = true;
    NN3 = false;
    TT3 = true;

    MM = !TT;
    if (MM) {
        return 10001;
    }

    MM = NN;
    if (MM) {
        return 10002;
    }

    MM = !TT3;
    if (MM) {
        return 10003;
    }

    MM = NN3;
    if (MM) {
        return 10004;
    }

    TT = !MM3;
    if (TT) {
        return 10005;
    }

    TT = NN3;
    if (TT) {
        return 10006;
    }

    // ---------------------------------------------------------------------1

    return 0;
}

int BoolAll_test() {

    int rtn = 0;
    Base *bb = new Base;
    rtn = Prepare_env(bb);

    static Future<8, period_1F> x(bb); //  Future<8, 9> x(&bb);
    static Future<8, period_5F> y(bb); //  Future<8, 12> y(&bb);

    rtn = BoolAll_sub01(100);

    return rtn;
} // end test01() ;
} // namespace uBEE
