// ysoftman
// string find test
// g++ string_find_test.cpp -std=c++11
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> vecStr;
    vecStr.push_back("lemon");
    vecStr.push_back("apple");
    vecStr.push_back("banana");

    cout << "find(\"na\")" << endl;
    for (auto i : vecStr) {
        // "na" 문자열이 포함된 경우만 찾는다.
        size_t pos = i.find("na");
        if (pos != string::npos) {
            cout << i << "   pos:" << pos << endl;
        }
    }

    cout << "find(\"ap\", 0, sizeof(\"ap\") - 1)" << endl;
    for (auto i : vecStr) {
        // cout << sizeof("ap") << endl;
        // 0위치부터 "ap" 문자열로 시작하는 문자열만 찾는다.
        size_t pos = i.find("ap", 0, sizeof("ap") - 1);
        if (pos != string::npos) {
            cout << i << "   pos:" << pos << endl;
        }
    }

    cout << "find_first_of(\"al\")" << endl;
    for (auto i : vecStr) {
        // a 또는 l 이 포함된 포함된 경우만 찾는다.
        // 스트링에서 a 또는 l 중 처음 매치되는 위치를 리턴한다.
        size_t pos = i.find_first_of("al");
        if (pos != string::npos) {
            cout << i << "   pos:" << pos << endl;
        }
    }
}