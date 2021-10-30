// ysoftman
// c++11 Rvalue reference(&&) test
// g++ -std=c++11 ./rvalue_reference.cpp && ./a.out
#include <iostream>
using namespace std;

int main()
{
    // a 는 Lvalue: 값을 가지고 담고 있는 메모리로 주소가 정해져 있고 이 주소를 항상 파악할 수 있다.(변수이름)
    // 100 + 100 + 100 은 Rvalue: Lvalue 가 아닌, 값 자체를 나타내느 표현
    // 100+100 => temp 임시 공간에 저장하고 temp + 100 을 a 에 저장한다.
    // 이때 temp 라는 임시공간이 생성되었다 사라지는데, 이를 활용할 수 있으면 불필요한 복사 과정을 줄여 성능을 높일 수 있다.
    int a = 100 + 100 + 100;

    // 이전부터 있었단 a(Lvalue)의 주소를 참조해 val1,a는 이름만 다를 뿐 같은 주소를 가진다.
    int &val1 = a;
    printf("a(%p):%d\nval1(%p):%d\n", &a, a, &val1, val1);

    // c++11 부터 && 로 Rvalue 값(이 저장된 임시 공간)을 참조(메모리 주소)할 수 있다.
    int &&val2 = 100 + 100;
    printf("val2(%p):%d\n", &val2, val2);
    return 0;
}
