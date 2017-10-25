// ysoftman
// boost join 사용하기
#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string/join.hpp>

using namespace std;

int main()
{
    cout << "boost join test" << endl;

    vector<string> strVec;
    strVec.push_back("Yoon");
    strVec.push_back("Byoung");
    strVec.push_back("Hoon");
    string joined_string = boost::algorithm::join(strVec, ",\n");
    cout << joined_string << endl;

    return 0;
}
