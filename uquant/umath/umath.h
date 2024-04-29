#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

namespace uBEE {
int t = std::max(3, 4);

template <int... N> class FutureSerial;

template <typename _Tp> constexpr inline const _Tp &MIN(const _Tp &__a, const _Tp &__b) { return min(__a, __b); }

/*
template <int... N>
constexpr inline const double& MIN(const FutureSerial<N...>& __a, const double& __b) {
    return min(__a.data[this->unit->index], __b);
}
template <typename T, int... N>
constexpr inline const T& MIN(const FutureSerial<N...>& serial, const T& b);
*/

template <typename T, int... N> constexpr inline const T &MIN(const FutureSerial<N...> &serial, const T &b) { return std::min(serial.data[serial.unit->index], b); }

template <typename T, int... N> constexpr inline const T &MAX(const FutureSerial<N...> &serial, const T &b) { return std::max(serial.data[serial.unit->index], b); }

template <typename T, int... N> constexpr inline const T &MIN(const T &b, const FutureSerial<N...> &serial) { return std::min(serial.data[serial.unit->index], b); }

template <typename T, int... N> constexpr inline const T &MAX(const T &b, const FutureSerial<N...> &serial) { return std::max(serial.data[serial.unit->index], b); }

template <int... N> constexpr inline const double &REF(const FutureSerial<N...> &serial, int x) {
    int m = serial.unit->index - x;
    if (x < 0 && m < 0) {
        m = 0;
    };
    return serial.data[m];
}

// 计算当条件x一直为真时的计数。
// 比如计算 MA5>MA10
class BARSLAST_t {
  public:
    int count{0};
    BARSLAST_t(){};
    inline int BARSLAST(bool x) {
        if (x) {
            count++;
        } else {
            count = 0;
        }
        return count;
    }
};
#define BARSLAST_T static BARSLAST_t

/*
double* oo;
oo = new double[1000];
std::fill_n(oo, 1000, -3);
for (int i = 0; i < 1000; i++) {
    std::cout << oo[i] << std::endl;
    oo[i] = i * 2;
}
for (int i = 0; i < 1000; i++) {
    std::cout << oo[i] << std::endl;
}
*/

} // namespace uBEE