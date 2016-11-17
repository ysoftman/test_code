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

    string str = "Yoon,Byoung,Hoon";
    cout << "str = " << str << endl;

    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(",");
    tokenizer tok(str, sep);

    cout << "separator = ," << endl;
    for(tokenizer::iterator iter=tok.begin(); iter!=tok.end(); ++iter)
    {
        cout << *iter << endl;
    }

    return 0;
}
