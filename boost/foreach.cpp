// ysoftman
// boost foreach 사용하기
#include <iostream>
#include <vector>
#include <string>
#include <boost/foreach.hpp>

using namespace std;

int main()
{
    cout << "foreach test" << endl;

    string str = "ysoftman";
    // array, vector, string, ... 등 다양하게 루프를 돌리 수 있다.
    BOOST_FOREACH(char ch, str)
    {
        cout << ch << endl;
    }

    int array[] = {1,2,3,4,5};
    BOOST_FOREACH(int n, array)
    {
        cout << n << endl;
    }

    vector<string> vec;
    vec.push_back("green");
    vec.push_back("red");
    vec.push_back("blue");
    vec.push_back("yellow");
    BOOST_FOREACH(string str, vec)
    {
        cout << str << endl;
    }

    return 0;
}
