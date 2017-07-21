// ysoftman
// boost tokenizer 사용하기
#include <iostream>
#include <vector>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;

int main()
{
    cout << "boost tokenizer test" << endl;

    string str = "Yoon,Byoung_Hoon Boost";
    cout << "str = " << str << endl;

    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    // 공백으로만 구분하여 토큰 생성
    tokenizer tok(str, boost::char_separator<char>(" "));
    for (tokenizer::iterator iter = tok.begin(); iter != tok.end(); ++iter)
        cout << *iter << endl;

    // 공백,_ 3개 문자로 구분하여 토큰 생성
    tokenizer tok2(str, boost::char_separator<char>(" ,_"));
    for (tokenizer::iterator iter = tok2.begin(); iter != tok2.end(); ++iter)
        cout << *iter << endl;

    // 공백,_ 3개 문자로 구분하고 B 와 H 글자를 토큰으로 만든다.
    tokenizer tok3(str, boost::char_separator<char>(" ,_", "BH"));
    for (tokenizer::iterator iter = tok3.begin(); iter != tok3.end(); ++iter)
        cout << *iter << endl;

    return 0;
}
