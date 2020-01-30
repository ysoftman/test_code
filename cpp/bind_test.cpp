// ysoftman
// boost bind() 기능이 -> c++11 bind() 로 포함되었다.
// g++ -std=c++11 bind_test.cpp
#include <iostream>

using namespace std;

struct Fruit
{
    int cost;
    string name;
    void printColor(string color)
    {
        cout << color << endl;
    }
};

int add(int a, int b)
{
    return a + b;
}
int main()
{
    cout << "add(1,2) = " << add(1, 2) << endl;

    // bind 로 함수 wrapping
    // f1 에는 인자값이 2,5 로 고정되어 있어 인자를 전달 할 수 없다.
    auto f1 = std::bind(add, 2, 5);
    cout << "f1() = " << f1() << endl;
    // f1(어떤 값을 써도 인자로 전달되지 않는다.) 는 인자값이 2,5로 고정
    cout << "f1(9, 9, \"aaaa\") = " << f1(9, 9, "aaaa") << endl;

    // placeholders 로 _1, _2 등을 주면 인자를 전달 할 수 있다.
    auto f2 = std::bind(add, std::placeholders::_1, std::placeholders::_2);
    cout << "f2(1,1) = " << f2(1, 1) << endl;
    cout << "f2(2,3) = " << f2(2, 3) << endl;

    // member 함수를 바인드 할 수도 있다.
    Fruit ft;
    auto f3 = std::bind(&Fruit::printColor, &ft, std::placeholders::_1);
    cout << "f3(\"yellow\") = ";
    f3("yellow");
    cout << "f3(\"red\") = ";
    f3("red");

    // member 변수를 바인드 할 수도 있다.
    auto f4 = std::bind(&Fruit::cost, std::placeholders::_1);
    cout << "f4(ft) = " << f4(ft) << endl;
    ft.cost = 5;
    cout << "f4(ft) = " << f4(ft) << endl;
    auto f5 = std::bind(&Fruit::name, std::placeholders::_1);
    cout << "f5(ft) = " << f5(ft) << endl;
    ft.name = "lemon";
    cout << "f5(ft) = " << f5(ft) << endl;

    return 0;
}
