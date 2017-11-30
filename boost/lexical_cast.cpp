// ysoftman
// boost lexical_cast 사용하기
#include <iostream>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std;

int main()
{
    cout << "boost lexical_cat test" << endl;
    int a = 10;
    string str = "num=";
    // int -> string 으로 변환
    str += boost::lexical_cast<string>(a);
    cout << str << endl;


    string num = "12345";
    // string -> int 으로 변환
    int b = boost::lexical_cast<int>(num);
    cout << b << endl;

    return 0;
}
