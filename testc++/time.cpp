#include <chrono>
#include <iostream>
#include <iomanip>
#include <ctime>

void test_timepoint2()
{
    using namespace std::chrono;
    system_clock::time_point now = system_clock::now();
    time_t last = system_clock::to_time_t(now - hours(24));
    time_t next = system_clock::to_time_t(now + hours(24));
    std::cout << "One day ago, the time was "
        << std::put_time(std::localtime(&last), "%F %T") << '\n'; // 格式命令同strftime(3)
    std::cout << "Next day, the time is "
        << std::put_time(std::localtime(&next), "%F %T") << '\n';
}

int main() {
	test_timepoint2();

}
