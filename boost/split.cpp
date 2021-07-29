// ysoftman
// boost split 사용하기
// 빌드 및 실행
// g++ -std=c++11 split.cpp && ./a.out
#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/range/adaptor/reversed.hpp>

using namespace std;

int main()
{
    cout << "boost split test" << endl;

    string str = "Yoon,Byoung,Hoon";
    cout << "str = " << str << endl;
    cout << "separator = ," << endl;
    vector<string> vecResult;
    vector<string>::iterator iter;
    boost::split(vecResult, str, boost::is_any_of(","));
    for (iter = vecResult.begin(); iter != vecResult.end(); iter++)
    {
        cout << (*iter).c_str() << endl;
    }

    str = "A/B/C/D/E/F/G";
    cout << "str = " << str << endl;
    cout << "separator = /" << endl;
    vector<string> vecTemp;
    // vecTemp.clear();
    // 기존 vecResult 내용은 삭제된다.
    // boost::split(vecResult, str, boost::is_any_of("/"));
    boost::split(vecTemp, str, boost::is_any_of("/"));
    // auto 는 c++11 버전이상
    for (auto v : boost::adaptors::reverse(vecTemp))
    {
        vecResult.insert(vecResult.begin(), v);
    }

    cout << "---- vecResult --- " << endl;
    for (iter = vecResult.begin(); iter != vecResult.end(); iter++)
    {
        cout << (*iter).c_str() << endl;
    }

    return 0;
}
