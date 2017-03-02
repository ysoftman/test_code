// ysoftman
// enum 변수 초기화 필요 테스트
#include <iostream>
#include <string>

using namespace std;

enum MY_FRUIT_TYPE {
    MY_APPLE = 0,
    MY_LEMON,
    MY_BANANA,   
};

struct testEnum
{
    // gcc 최신 버전에서  초기화 0으로 되지 않음
    MY_FRUIT_TYPE type;
    std::string type_str;

    testEnum()
    {
        type = MY_APPLE;
        type_str = "ysoftman";
    }
};

int main()
{
    testEnum myfruit;
    cout << myfruit.type << endl;
    cout << myfruit.type_str << endl;
    return 0;
}

