// g++ -std=c++11 ./constexpr_test.cpp && ./a.out
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

// const 는 변수의 초기화가 런타임에 진행될 수 있지만
// constexpr 를 사용하면 반드시 컴파일시 값이 정해진다.
constexpr double PI = 3.141592;

// 함수에서 constexpr 사용시 inline 함수들과 같이 컴파일 된다.
constexpr double cal_const_value(double a, double b) { return a > b ? 0 : std::pow(a, b); }

int main() {
    cout << "PI = " << PI << endl;
    cout << "2^8 = " << cal_const_value(2, 8) << endl;
    cout << "8^2 = " << cal_const_value(8, 2) << endl;
    return 0;
}
