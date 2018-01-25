// ysoftman
// boost string replace 사용하기
#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string/replace.hpp>

using namespace std;

int main()
{
    cout << "boost string-replace test" << endl;

    string str = "yoon byoung hoon";
    cout << "str = " << str << endl;

    // 원본 자체를 replace
    boost::replace_all(str, " ", "%20");
    cout << "str = " << str << endl;

    str = "yoon byoung hoon";
    cout << "str = " << str << endl;

    // 원본은 변경하지 않고 replace
    string replaced_string = boost::replace_all_copy(str, " ", "%20");
    cout << "replaced_string = " << replaced_string << endl;
    return 0;
}
