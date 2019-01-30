// ysoftman
// boost split 사용하기
// 빌드 및 실행
// g++ -std=c++11 split.cpp && ./a.out
#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace std;

int main()
{
    cout << "boost split test" << endl;

    string str = "Yoon,Byoung,Hoon";
    cout << "str = " << str << endl;

    vector<string> vecResult;
    boost::split(vecResult, str, boost::is_any_of(","));

    string str2 = "ysoftman/bill";
    vector<string> vecTemp;
    boost::split(vecTemp, str2, boost::is_any_of("/"));
    // auto 는 c++11 버전이상
    for (auto v : vecTemp)
    {
        // vecResult.insert(vecResult.begin(), v);
        // vecResult.insert(vecResult.end(), v);
        vecResult.push_back(v);
    }

    cout << "separator = ," << endl;
    cout << "count = " << vecResult.size() << endl;
    vector<string>::iterator iter;
    for (iter = vecResult.begin(); iter != vecResult.end(); iter++)
    {
        cout << (*iter).c_str() << endl;
    }

    return 0;
}
