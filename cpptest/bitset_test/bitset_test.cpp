// ysoftman
// C++ std library bitset 사용예
#include <iostream>
#include <bitset>

using namespace std;
int main()
{
    cout << "bitset test1" << endl;
    // 5bit 공간에 정수 7을 설정
    std::bitset<5> bitnum(7);
    // 00111(7) 의 1 카운트
    cout << bitnum.to_ulong() << " -> " << bitnum.to_string() << " -> " << bitnum.count() << endl;

    cout << "bitset test2" << endl;
    const int bitspace = 5;
    // bitspace 가 작으면 상위 비트를 설정할 수 없어 정확한 비트 카운트가 될 수 없다.
    for (int i = 0; i <= 10; i++)
    {
        cout << bitset<bitspace>(i).to_ulong() << " -> "
             << bitset<bitspace>(i).to_string() << " -> "
             << bitset<bitspace>(i).count() << endl;
    }
    return 0;
}
