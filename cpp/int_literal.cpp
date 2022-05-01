// ysoftman
// digit literal test
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    cout << 10000 << endl;
    // https://en.cppreference.com/w/cpp/language/integer_literal
    cout << 10'000 << endl; // c++14 부터 지원
}
