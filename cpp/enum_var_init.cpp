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

struct testEnum {
    std::string type_str;
    MY_FRUIT_TYPE type;

    // gcc 최신 버전에서 enum 타입의 변수가 0으로 초기화 되지 않는다.
    // 따라서 다음과 같이 초기화해야 한다.
    testEnum() {
        type = MY_APPLE;
        // string 은 따로 초기화하지 않으면 empty
        type_str = "ysoftman";
    }
};

int main() {
    testEnum myfruit;
    cout << myfruit.type << endl;
    cout << myfruit.type_str << endl;
    return 0;
}
