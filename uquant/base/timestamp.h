#ifndef _SEE_TIMESTAMP_H_
#define _SEE_TIMESTAMP_H_
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

inline uint64_t getns() { return std::chrono::high_resolution_clock::now().time_since_epoch().count(); }
inline uint64_t overhead_getns() {
    std::size_t iterations(10);
    uint64_t sum = 0;
    for (std::size_t i = 0; i < iterations; ++i) {
        uint64_t a = getns();
        uint64_t b = getns();
        sum += b - a;
    }
    return sum / iterations;
}

inline uint64_t rdtsc() { return __builtin_ia32_rdtsc(); }

// #define time_test_before before = rdtsc()
// #define time_test_finish        \
//     latency = rdtsc() - before; \
//     std::cout << "latency: " << latency << std::endl

#define time_test_before(x) x = rdtsc()
#define time_test_finish(x, y)                                                                                                                                                                                                                                                         \
    x = rdtsc() - y;                                                                                                                                                                                                                                                                   \
    std::cout << "latency: " << x << std::endl

inline uint64_t overhead_rdtsc() {
    std::size_t iterations(10);
    uint64_t sum = 0;
    for (std::size_t i = 0; i < iterations; ++i) {
        uint64_t a = rdtsc();
        uint64_t b = rdtsc();
        sum += b - a;
    }
    return sum / iterations;
}

inline uint64_t rdtscp() {
    unsigned int dummy;
    return __builtin_ia32_rdtscp(&dummy);
}

// 这里一定要inline才行，否则：multiple definition of `kk[abi:cxx11]()';
// inline std::string kk() { return "akdfl"; }
std::string getCurrentSystemTime();

inline int days_from_civil(int y, unsigned m, unsigned d) noexcept {
    static_assert(std::numeric_limits<unsigned>::digits >= 18, "This algorithm has not been ported to a 16 bit unsigned integer");
    static_assert(std::numeric_limits<int>::digits >= 20, "This algorithm has not been ported to a 16 bit signed integer");
    y -= m <= 2;
    const int era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = static_cast<unsigned>(y - era * 400);           // [0, 399]
    const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; // [0, 365]
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;          // [0, 146096]
    return era * 146097 + static_cast<int>(doe) - 719468;
}

inline int read2(std::string const &str, int pos) { return (str[pos] - '0') * 10 + (str[pos + 1] - '0'); }
inline int read4(std::string const &str, int pos) { return (str[pos] - '0') * 1000 + (str[pos + 1] - '0') * 100 + (str[pos + 2] - '0') * 10 + (str[pos + 3] - '0'); }

// yyyy-mm-dd hh:MM:ss -> count of non-leap seconds since 1970-01-01 00:00:00 UTC
// 0123456789012345678
inline long long EpochConverter(std::string const &str) {
    auto y = read4(str, 0);
    auto m = read2(str, 5);
    auto d = read2(str, 8);
    auto h = read2(str, 11);
    auto M = read2(str, 14);
    auto s = read2(str, 17);
    return days_from_civil(y, m, d) * 86400LL + h * 3600 + M * 60 + s;
}

inline long long EpochConverter2(std::string const &str) {
    auto y = read4(str, 0);
    auto m = read2(str, 4);
    auto d = read2(str, 6);
    auto h = read2(str, 9);
    auto M = read2(str, 11);
    return days_from_civil(y, m, d) * 86400LL + h * 3600 + M * 60;
}

#endif //