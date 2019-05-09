// ysoftman
// string find test
// g++ string_find_test.cpp -std=c++11
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> vecStr;
    vecStr.push_back("lemon");
    vecStr.push_back("apple");
    vecStr.push_back("banana");

    cout << "find(\"na\")" << endl;
    for (auto i : vecStr)
    {
        // "na" 문자열이 포함된 경우만 찾는다.
        if (i.find("na") != string::npos)
        {
            cout << i << endl;
        }
    }

    cout << "find(\"ap\")" << endl;
    for (auto i : vecStr)
    {
        // cout << sizeof("ap") << endl;
        // "ap" 문자열로 시작하는 문자열만 찾는다.
        if (i.find("ap", 0, sizeof("ap") - 1) != string::npos)
        {
            cout << i << endl;
        }
    }

    cout << "find_first_of(\"ml\")" << endl;
    for (auto i : vecStr)
    {
        // m 또는 l 이 포함된 포함된 경우만 찾는다.
        // 스트링에서 m 또는 l 중 처음 매치되는 위치를 리턴한다.
        size_t pos = i.find_first_of("ml");
        if (pos != string::npos)
        {
            cout << i << "   pos:" << pos << endl;
        }
    }
}