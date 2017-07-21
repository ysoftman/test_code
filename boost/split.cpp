// ysoftman
// boost split 사용하기
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
    
    cout << "separator = ," << endl;
    cout << "count = " << vecResult.size() << endl;
    vector<string>::iterator iter;
    for (iter = vecResult.begin(); iter != vecResult.end(); iter++)
    {
        cout << (*iter).c_str() << endl;
    }

    return 0;
}
