// ysoftman
// std move test
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int num1 = 123;
    // object 가 아니면 move 를 사용해도 복사된다.
    int num2 = std::move(num1);
    cout << "num1:" << num1 << endl;
    cout << "num2:" << num2 << endl;

    int *pt1 = &num1;
    // object 가 아니면 move 를 사용해도 복사된다.
    int *pt2 = std::move(pt1);
    cout << "pt1:" << pt1 << "->" << *pt1 << endl;
    cout << "pt2:" << pt2 << "->" << *pt2 << endl;

    string str1 = "aaa";
    // string 은 object 라 이동된다.(소유권이 이전된다.)
    // str1 -> "aaa" 인데 str2=move(str1) 되면
    // str1 -> X
    // str2 -> "aaa" 가 되어 str1 로는 "aaa"를 참조할 수 없다.
    string str2 = std::move(str1);
    cout << "str1:" << str1 << endl;
    cout << "str2:" << str2 << endl;

    string lemon = "lemon";
    string apple = "apple";
    vector<string> plates;
    // lemon 값을 plates 벡터에 복사한다.
    plates.push_back(lemon);
    // move() 는 변수값(rvalue) reference 를 리턴하기 때문에
    // apple 값이 plates 벡터로 이동(메모리 소유권 이전)되는 효과가 있다.
    // 복사보다는 빠르지만 이동후 apple 변수는 빈값이 된다.
    plates.push_back(std::move(apple));
    for (string &str : plates) {
        cout << "plates => " << str << endl;
    }
    cout << "lemon: " << lemon << endl;
    // apple 변수(Lvalue)의 값은 위에서 벡터로 이동되어 빈값이다.
    cout << "apple: " << apple << endl;

    return 0;
}
