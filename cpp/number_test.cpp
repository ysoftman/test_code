// ysoftman
// number test

#include <cmath>
#include <iostream>
using namespace std;

void test_number(double n) {
    // 반올림
    cout << "round(n): " << round(n) << endl;
    // 내림
    cout << "floor(n): " << floor(n) << endl;
    // 버림
    cout << "trunc(n): " << trunc(n) << endl;
    // 올림
    cout << "ceil(n): " << ceil(n) << endl;
}

int main() {
    double n = 0.56789;
    cout << "n: " << n << endl;
    test_number(n);
    n = -0.56789;
    cout << "n: " << n << endl;
    test_number(n);

    double d = 0.123456789123456789;
    cout << "d: " << d << endl;
    // 소수점 3자리까만 살리기
    d = (double)((int)(d * 1000)) / 1000;
    cout << "(double)((int)(d * 1000)) / 1000: " << d << endl;

    return 0;
}