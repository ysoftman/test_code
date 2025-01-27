// ysoftman
// c++ 에서 스트링 리터럴은 char* 로 선언은 deprecated 되었다.

#include <iostream>

using namespace std;

// conversion from string literal to 'char *' is deprecated.
// char *getstring()
// 방법1
// string getstring()
// 방법2
const char *getstring() { return "aaa"; }

int main() {
    // conversion from string literal to 'char *' is deprecated.
    // char *str = "ysoftman";
    // 방법1
    char str1[] = "ysoftman";
    cout << str1 << endl;
    // 방법2
    char *str2 = (char *)"ysoftman";
    cout << str2 << endl;
    // 방법3
    const char *str3 = "ysoftman";
    cout << str3 << endl;
    // 방법3
    string str4 = "ysoftman";
    cout << str4 << endl;

    cout << getstring() << endl;
    return 0;
}
