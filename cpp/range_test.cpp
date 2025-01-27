// g++ -std=c++11 ./range_test.cpp && ./a.out
#include <iostream>
#include <map>

// using namespace std;
using std::cout;
using std::endl;
using std::string;

int main() {
    std::map<string, int> m{{"lemon", 100}, {"apple", 200}};
    m.insert({"orange", 300});

    // i : 복사된 값, 원본 m 의 값은 변경되지 않음
    for (auto i : m) {
        i.second = -1;
        cout << i.first << ":" << i.second << endl;
    }
    for (auto i : m) {
        cout << i.first << ":" << i.second << endl;
    }

    // i : 참조, 원본m의 값이 변경됨
    for (auto &i : m) {
        i.second = -2;
        cout << i.first << ":" << i.second << endl;
    }
    for (auto i : m) {
        cout << i.first << ":" << i.second << endl;
    }

    // i : 참조, i도 변경 안되도록 하기
    for (auto const &i : m) {
        // i.second = -3; // compile error
        cout << i.first << ":" << i.second << endl;
    }
    return 0;
}
