#include <iostream>
using namespace std;

extern int aaa();
extern int bbb();

int        main() {
    cout << __FUNCTION__ << endl;
    aaa();
    bbb();
    return 0;
}