// ysoftman
// c++ 11 auto 사용하기
// g++ -std=c++11 auto_test.cpp

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cout << "auto test" << endl;

    std::vector<int> vecNum;
    vecNum.push_back(1);
    vecNum.push_back(2);
    vecNum.push_back(3);
    vecNum.push_back(4);
    vecNum.push_back(5);
    // 컨테이너 타입 맞는 iterator 를 사용하는 일반적인 방법
    cout << "using   std::vector<int>::iterator" << endl;
    std::vector<int>::iterator iter;
    for (iter = vecNum.begin(); iter != vecNum.end(); ++iter)
    {
        cout << *iter << endl;
    }

    // auto 를 사용하면 데이터에 맞게 자동으로 iterate 할 수 있다.
    cout << "using   auto v = vecNum.begin(); v != vecNum.end(); ++v" << endl;
    for (auto v = vecNum.begin(); v != vecNum.end(); ++v)
    {
        cout << *v << endl;
    }

    // auto 를 다음과 같이 더 간단하게 사용할 수 있다.
    cout << "using   auto const v : vecNum" << endl;
    // auto 선언시 레퍼런스를 사용하면 레퍼린스로 vector 값을 변경할 수 있다.
    for (auto &v : vecNum)
    {
        v += 10;
    }
    for (auto v : vecNum)
    {
        cout << v << endl;
    }

    return 0;
}