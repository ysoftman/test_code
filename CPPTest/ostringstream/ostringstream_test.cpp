// ysoftman
// ostringstream test
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;
int main()
{   
    double a = 0.0000000000000123456789;

    ostringstream ss;
    ss << "a:" << a;
    string str = ss.str();    
    cout << str << endl;

    double b = 0.0000000000012345678912345678912346;
    ostringstream ss2;
    ss2 << "b:" << fixed << b;
    string str2 = ss2.str();    
    cout << str2 << endl;
    
    return 0;
}
