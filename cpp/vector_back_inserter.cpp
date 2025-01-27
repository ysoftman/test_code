// ysoftman
// stl back_inserter test
// g++ -std=c++11 ./stl_vector_back_inserter.cpp && ./a.out
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<string> vec = {"lemon", "apple", "orange"};
    vector<string> add_fruits = {"mango", "banana"};

    // 기존 벡터 뒤에 새로운 벡터를 추가할 수 있다.
    // std::copy(begin(add_fruits), end(add_fruits), std::back_inserter(vec));
    // 또는
    std::copy(add_fruits.begin(), add_fruits.end(), std::back_inserter(vec));

    for (auto i : vec) {
        cout << i << endl;
    }
    return 0;
}
