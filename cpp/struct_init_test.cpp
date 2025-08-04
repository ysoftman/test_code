#include <iostream>
#include <string>
using namespace std;

struct my_struct {
    int         num;
    string      str;
    float       fnum;
    const char *cstr;
};

void print_my_struct(my_struct st) {
    cout << "-----" << endl;
    cout << "st.num:" << st.num << endl;
    cout << "st.fnum:" << st.fnum << endl;
    cout << "st.str:" << st.str << endl;
    cout << "st.cstr:" << st.cstr << endl;
}
int main() {
    cout << "initialize struct instance test" << endl;
    // initialize struct - case1
    my_struct my1;
    my1.fnum = 12.34;
    my1.str  = "ysoftman1";
    my1.cstr = "ysoftman2";
    my1.num  = 100;
    print_my_struct(my1);

    // initialize struct - case2
    my_struct my2 = {111, "lemon", 99.99, "apple"};
    print_my_struct(my2);

    // initialize struct - case3
    my_struct my3 = {.fnum = 77.123, .str = "juice1", .cstr = "juice2", .num = 55};
    print_my_struct(my3);

    return 0;
}
