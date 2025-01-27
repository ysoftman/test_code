// g++ -std=c++11 ./accumulate_test.cpp && ./a.out
#include <iostream>
#include <numeric>
#include <vector>

using std::accumulate;
using std::cout;
using std::endl;

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 초기값 0 설정 후 합산
    cout << accumulate(v.begin(), v.end(), 0) << endl;

    // 초기값 -55 설정 후 합산
    cout << accumulate(v.begin(), v.end(), -55) << endl;
    return 0;
}
