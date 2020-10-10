// ysoftman
// c++ 11 lambda 함수
// 람다 함수(람다식, 익명함수), 임시적으로 closure 객체가 만들어 진다.
// 람다식은 코드를 간결하게 작성할 수 있고 캡쳐를 통한 필요한 데이터(변수등..)만 사용할 수 있다.
// 하지만 때로는 남발하면 코드 읽기가 더 어려울 수 있고 기초적인 반복문(for)보다 단계를 더 거치기 때문에 느리다.
// g++ -std=c++11 lambda_function.cpp && ./a.out

#include <iostream>

using namespace std;
int main()
{
    cout << "lambda function test" << endl;
    int a = 1;
    int b = 2;

    // 람다함수명 = [캡쳐할변수](함수파라미터)->함수리턴타입{함수내용}(외부에서 받을 인자)
    // [=] 현재함수의 모든 변수를 캡쳐한다는 의미
    int my_lambda_func1 = [=]() -> int { return a + b; }();
    cout << my_lambda_func1 << endl;

    // [] 아무것도 캡쳐하지 않는다는 의미
    // -std=c++14 부터 파라미터 명시에 auto 를 사용할 수 있다.
    // int my_lambda_func2 = [](auto mya, auto myb) -> int { return mya + myb; }(a, b);
    int my_lambda_func2 = [](int mya, int myb) -> int { return mya * myb; }(a, b);
    cout << my_lambda_func2 << endl;
    return 0;
}
