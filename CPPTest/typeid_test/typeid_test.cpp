// ysoftman
// typeid 사용하기
#include <iostream>

using namespace std;

int main()
{
    cout << "typeid() test" << endl;

    string str = "ysoftman";
    int num = 123;
    bool bin = true;
    float fnum = 0.123;
    double dnum = 0.123;

    // 값의 타입을 파악하기
    cout << num << " typename:" << typeid(num).name() << endl;
    cout << str << " typename:" << typeid(str).name() << endl;
    cout << bin << " typename:" << typeid(bin).name() << endl;
    cout << fnum << " typename:" << typeid(fnum).name() << endl;
    cout << dnum << " typename:" << typeid(dnum).name() << endl;

    return 0;
}
