// ysoftman
// std move test
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    string lemon = "lemon";
    string apple = "apple";

    vector<string> plates;

    // lemon 값을 plates 벡터에 복사한다.
    plates.push_back(lemon);
    // move() 는 변수값(rvalue) reference 를 리턴하기 때문에
    // apple 값이 plates 벡터로 이동(메모리 소유권 이전)되는 효과가 있다.
    // 복사보다는 빠르지만 이동후 apple 변수의 빈값이 된다.
    plates.push_back(std::move(apple));

    for (string &str : plates)
    {
        cout << "plates => " << str << endl;
    }

    cout << "lemon: " << lemon << endl;
    // apple 변수(lvalue)의 값은 위에서 벡터로 이동되어 빈값이다.
    cout << "apple: " << apple << endl;

    int a = 123;
    int b = 0;
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;
    // object 가 아니면 move 를 사용해도 복사된다.
    b = std::move(a);
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;

    string aa = "aa";
    string bb;
    cout << "aa:" << aa << endl;
    cout << "bb:" << bb << endl;
    // string 은 object 라 이동된다.
    bb = std::move(aa);
    cout << "aa:" << aa << endl;
    cout << "bb:" << bb << endl;

    return 0;
}
