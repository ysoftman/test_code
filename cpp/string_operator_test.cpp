// ysoftman
// string operator test
#include <iostream>
#include <string>

using namespace std;

int main() {
    string str1 = "1";
    string str2 = "2";
    string str3 = "3";
    string result;

    // const char * 타입은 + 연산을 할 수 없다.
    // result += "1" + "2" + "3";
    // result += str1.c_str() + str2.c_str() + str3.c_str();

    // string 타입만 + 연산이 가능하다.
    result += str1 + str2 + str3;
    cout << result << endl;
    return 0;
}
