// ysoftman
// string 값을 인덱싱 해보기
#include <iostream>
using namespace std;

int main() {
    string str = "ysoftman";
    for (int i = 0; i < 10; i++) {
        // string::operator[] 는 index 범위를 넘어선 경우 null character(\0) 취급
        if (str[i] == '\0') {
            cout << i << " "
                 << "empty" << endl;
            continue;
        }
        cout << i << " " << str[i] << endl;
    }
    return 0;
}