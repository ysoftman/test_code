// ysoftman
// boost_assert 사용하기
#include <iostream>
#include <string>
#include <boost/assert.hpp>

using namespace std;

int main()
{
    cout << "BOOST_ASSERT test..." << endl;
    string str = "ysoftman";
    BOOST_ASSERT(str == "ysoftman");
    cout << "str == \"ysoftman\"" << endl;
    BOOST_ASSERT(str != "ysoftman");
    cout << "str != \"ysoftman\"" << endl;
    return 0;
}
