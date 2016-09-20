// ysoftman
// number test

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double n = 0.56789;
    cout << n << endl;
 
    // 반올림
    cout << round(n) << endl;
    // 버림
    cout << floor(n) << endl;
    // 올림
    cout << ceil(n) << endl;


    double d = 0.123456789123456789;
    cout << d << endl;
    // 소수점 3자리까만 살리기
    d = (double)((int)(d * 1000)) / 1000;
    cout << d << endl;

    return 0;
}