// ysoftman
// boost format 사용하기
#include <iostream>
#include <string>
#include <vector>
#include <boost/format.hpp>

using namespace std;
using namespace boost;

int main()
{
    cout << "boost format test" << endl;
    cout << format("%d %s %s") % 123 % "abc" % "ysoftman" << endl;
    cout << format("second arg: %2%, first arg: %1%") % 100 % 200 << endl;

    return 0;
}
