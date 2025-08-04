// ysoftman
// this test

#include <iostream>
#include <string>

using namespace std;

class foobar {
   public:
    int     num;
    foobar &set_num(int num) {
        // this 사용이유 1
        // 파리미터와 클래스 멤버변수가 이름이 같을때 구분하기 위해
        this->num = num;
        cout << "this->num: " << this->num << endl;

        // this 사용이유 2
        // 클래스 인스턴스 자체를 리턴하기 위해
        return *this;
    }
    foobar *set_num2(int num) {
        // this 사용이유 1
        // 파리미터와 클래스 멤버변수가 이름이 같을때 구분하기 위해
        this->num = num;
        cout << "this->num: " << this->num << endl;

        // this 사용이유 2
        // 클래스 인스턴스 자체를 리턴하기 위해
        return this;
    }

    int cnt;
    // this 포인터를 리턴
    foobar *this_pointer() { return this; }
    // this 역참조에 대한 주소값을 리턴
    foobar &this_reference() { return *this; }
    foobar  this_dereference() { return *this; }
};

int main() {
    foobar fb;
    fb.set_num(1).set_num(2).set_num(3);
    cout << "fb.num: " << fb.num << endl;
    fb.set_num2(7)->set_num2(8)->set_num2(9);
    cout << "fb.num: " << fb.num << endl;

    printf("fb %p\n", &fb);

    printf("fb.this_pointer() %p\n", fb.this_pointer());
    fb.this_pointer()->cnt++;

    printf("&fb.this_reference() %p\n", &fb.this_reference());
    fb.this_reference().cnt++;

    // this_dereference 는 설정할 수 없다.
    // fb.this_dereference().cnt++;
    // this 역참조는 값복사해서 써야 한다.
    foobar fb2 = fb.this_dereference();
    printf("fb.this_dereference() --> &fb2 %p\n", &fb2);
    fb2.cnt++;

    return 0;
}
