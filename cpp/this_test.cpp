// ysoftman
// this test

#include <iostream>
#include <string>

using namespace std;

class foobar
{
public:
    int cnt;
    string str;

    void print_variables()
    {
        cout << cnt << "   " << str << endl;
    }
    // this 포인터를 리턴
    foobar *this_pointer()
    {
        return this;
    }
    // this 역참조에 대한 주소값을 리턴
    foobar &this_reference()
    {
        return *this;
    }
    foobar this_dereference()
    {
        return *this;
    }
};

int main()
{
    foobar fb;
    printf("%p  fb\n", &fb);
    fb.cnt = 0;

    printf("%p  ", fb.this_pointer());
    fb.this_pointer()->cnt++;
    fb.this_pointer()->str = "a";
    fb.print_variables();

    printf("%p  ", &fb.this_reference());
    fb.this_reference().cnt++;
    fb.this_reference().str = "b";
    fb.print_variables();

    // this_dereference 는 설정할 수 없다.
    // fb.this_dereference().cnt++;
    // this 역참조는 값복사해서 써야 한다.
    foobar fb2 = fb.this_dereference();
    printf("%p  ", &fb2);
    fb2.cnt++;
    fb2.str = "c";
    fb2.print_variables();

    // fb 는 변하지 않는다.
    printf("%p  ", &fb.this_reference());
    fb.print_variables();
}
