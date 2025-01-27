// ysoftman
// c++ 11 lambda 함수
// 람다 함수(람다식, 익명함수), 임시적으로 closure 객체가 만들어 진다.
// 람다식은 코드를 간결하게 작성할 수 있고 캡쳐를 통한 필요한 데이터(변수등..)만 사용할 수 있다.
// 하지만 때로는 남발하면 코드 읽기가 더 어려울 수 있고 기초적인 반복문(for)보다 단계를 더 거치기
// 때문에 느리다. g++ -std=c++11 lambda_function.cpp && ./a.out

#include <iostream>

using namespace std;
int main() {
    cout << "lambda function test" << endl;
    int a = 1;
    int b = 2;
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;

    // 람다함수명 =
    // [캡쳐할변수](함수파라미터)->함수리턴타입{함수내용}(외부에서 받을
    // 인자) [a, b] 현재(main) 스코프 내의 a, b 변수 캡쳐 a, b를 수정할 수 없다
    int my_lambda_func1 = [a, b]() -> int {
        // error: cannot assign to a variable captured by copy in a non-mutable lambda
        // a = 10;
        return a + b;
    }();
    cout << my_lambda_func1 << endl;

    // 주소값으로 캡쳐하면 수정할 수 있다.
    int my_lambda_func2 = [&a, &b]() -> int {
        a = 10;
        b = 20;
        return a + b;
    }();
    cout << my_lambda_func2 << endl;
    cout << "a:" << a << endl;
    cout << "b:" << b << endl;

    // [=] 현재(main) 스코프 내의 모든 변수를 캡쳐
    // a, b를 수정할 수 없다
    int my_lambda_func3 = [=]() -> int {
        // error: cannot assign to a variable captured by copy in a non-mutable lambda
        // a = 10;
        return a + b;
    }();
    cout << my_lambda_func3 << endl;

    // [] 아무것도 캡쳐하지 않는다는 의미
    // -std=c++14 부터 파라미터 명시에 auto 를 사용할 수 있다.
    // int my_lambda_func2 = [](auto mya, auto myb) -> int { return mya + myb; }(a, b);
    int my_lambda_func4 = [](int mya, int myb) -> int { return mya * myb; }(a, b);
    cout << my_lambda_func4 << endl;
    return 0;
}
