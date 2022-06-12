// ysoftman
// std thread test
// g++ -std=c++11 std_chrono.cpp && ./a.out
#include <iostream>
#include <chrono>
#include <thread>

using std::cout;
using std::endl;

void elapsed_test()
{
    // steady_clock: monotonic clock that will never be adjusted
    auto begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 10; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    auto end = std::chrono::steady_clock::now();
    // auto elapsed = end - begin;
    std::chrono::duration<double> elapsed_seconds = end - begin;
    cout << "elapsed: " << elapsed_seconds.count() << "s" << endl;
}

int main()
{
    auto minutes = std::chrono::minutes(1);
    // count(): returns the count of ticks
    cout << std::chrono::nanoseconds(minutes).count() << endl;
    cout << std::chrono::microseconds(minutes).count() << endl;
    cout << std::chrono::milliseconds(minutes).count() << endl;
    cout << std::chrono::seconds(minutes).count() << endl;
    cout << std::chrono::minutes(minutes).count() << endl;

    // tick 가장 작인 시간 순간
    // https://en.cppreference.com/w/cpp/chrono/duration
    // duration 은 시점의 간격을, tick, tick기간(2개의 tick 초단위 간격)으로 저장하고 있다.
    // 초로 환산
    cout << std::chrono::duration<double>(minutes).count() << endl;

    elapsed_test();
    return 0;
}
