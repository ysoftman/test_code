#include <iostream>

using std::cout;
using std::endl;

// c, c++ 등 많은 언어에서 이렇게 정의 되어 있다.
#define modulo(a, b) (a - b * (a / b))

int main()
{
    cout << "modulo implementation test" << endl;
    cout << 2 % 3 << " == " << modulo(2, 3) << endl;
    cout << 7 % 3 << " == " << modulo(7, 3) << endl;
    cout << 10 % 7 << " == " << modulo(10, 7) << endl;
    cout << 9 % 7 << " == " << modulo(9, 7) << endl;
    cout << 342 % 3 << " == " << modulo(342, 9) << endl;
    return 0;
}
