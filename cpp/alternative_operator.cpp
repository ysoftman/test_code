#include <iostream>

using namespace std;

// https://en.cppreference.com/w/c/language/operator_alternative
// ^, | ~ 등을 사용할 수 없는 곳에서 대체 토큰을 사용할 수 있다.
int main() {
    int a = 1, b = 2;
    cout << a << endl;
    cout << b << endl;
    cout << ~a << endl;
    cout << compl a << endl;
    cout << not a << endl;
    cout << (a xor b) << endl;
    cout << (a and b) << endl;
    cout << (a or b) << endl;
    cout << (a bitand b) << endl;
    cout << (a bitor b) << endl;
    cout << (a not_eq b) << endl;
    return 0;
}
