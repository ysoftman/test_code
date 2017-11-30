// ysoftman
// hash_value 사용하기
#include <iostream>
#include <string>
#include <boost/functional/hash.hpp>

using namespace std;

int main()
{
    cout << "boost hash_value test..." << endl;
    string str = "ysoftman";
    cout << "str=" << str << endl;
    size_t hashed = boost::hash_value(str);
    cout << "boost hash_value=" << hashed << endl;
    return 0;
}
