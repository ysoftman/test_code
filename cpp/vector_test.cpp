// ysoftman
// stl vector 의 값(클래스) 삭제 테스트
// g++ -std=c++11 vector_test.cpp && ./a.out
#include <stdio.h>

#include <algorithm>  // std::copy()
#include <iostream>
#include <iterator>  // back_inserter()
#include <string>
#include <vector>
using namespace std;

class Dummy {
   public:
    Dummy() {
        a = 1;
        printf("Dummy()\n");
    };
    ~Dummy() {
        a = 0;
        printf("~Dummy()\n");
    };
    int a;
};

void vector_test1() {
    Dummy dummy1;
    printf("dummy1.a = %d\n", dummy1.a);
    Dummy *dummy2 = new Dummy();
    printf("dummy2.a = %d\n", dummy2->a);
    delete dummy2;

    printf("\n\n");

    std::vector<Dummy> vecDummy1;
    for (int i = 0; i < 5; i++) {
        Dummy dummy3;
        vecDummy1.push_back(dummy3);
    }
    // 소멸자 제대로 호출(하지만 많이 너무 많이 호출된다)
    vecDummy1.clear();

    printf("\n\n");

    std::vector<Dummy *> vecDummy2;
    for (int i = 0; i < 5; i++) {
        Dummy *dummy4 = new Dummy();
        vecDummy2.push_back(dummy4);
    }
    // 소멸자 호출 안됨
    // 클래스 원소 포인터를 삭제하지만 실제 클래스의 메모리는 삭제하지 않는다.
    // vecDummy2.clear();

    // 따라서 일일히 클래스를 삭제해야 한다.
    // 방법1
    while (!vecDummy2.empty()) {
        delete vecDummy2.back();
        vecDummy2.pop_back();
    }
    // 방법2
    std::vector<Dummy *>::iterator iter;
    std::vector<Dummy *>::iterator iterTemp;
    for (iter = vecDummy2.begin(); iter != vecDummy2.end();) {
        iterTemp = iter;
        // 일일히 delete 한다.
        delete (*iterTemp);
        // 원소 삭제
        iter = vecDummy2.erase(iter++);
    }

    printf("\n\n");
}

void vector_test2() {
    std::vector<std::string> vec_my_data;
    vec_my_data.insert(vec_my_data.begin(), "ccc");
    vec_my_data.insert(vec_my_data.begin(), "bbb");
    vec_my_data.insert(vec_my_data.begin(), "aaa");
    vec_my_data.push_back("ddd");
    vec_my_data.push_back("eee");
    vec_my_data.insert(vec_my_data.end(), "fff");

    for (auto i : vec_my_data) {
        printf("%s\n", i.c_str());
    }
    cout << "---" << endl;

    // 특정 위치 찾아서 추가
    std::vector<std::string>::iterator myiter;
    for (myiter = vec_my_data.begin(); myiter < vec_my_data.end(); ++myiter) {
        if (*myiter == "ccc") {
            printf("find --> %s\n", (*myiter).c_str());
            std::vector<std::string> vec_temp = {"_lemon_", "_apple_", "_orange_"};
            vec_my_data.insert(myiter, vec_temp.begin(), vec_temp.end());
            vec_my_data.insert(vec_my_data.begin(), vec_temp.begin(), vec_temp.begin() + 2);
            vec_my_data.insert(vec_my_data.begin(), vec_temp.begin(), std::next(vec_temp.begin()));
            break;
        }
    }

    // 찾지 못해 myiter 가 끝까지 간경우
    if (myiter == vec_my_data.end()) {
        vec_my_data.push_back("_not_found_");
    }
    // 마지막 원소로 찾은 경우
    else if (std::next(myiter) == vec_my_data.end()) {
        vec_my_data.push_back("_last_found_");
    }

    for (auto i : vec_my_data) {
        printf("%s\n", (i).c_str());
    }
}

void vector_test3() {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int len   = sizeof(arr) / sizeof(int);
    cout << "len: " << len << endl;

    // array to vector
    vector<int> vec(arr, arr + len);
    for (auto i : vec) {
        cout << i << ",";
    }
    cout << endl;

    // copy array

    // method1 - 생성시 다음과 같은 방식들 사용
    // vector<int> vec2(vec);
    // vector<int> vec2(vec.begin(), vec.end());

    // method2 - assign
    // vector<int> vec2;
    // vec2.assign(vec.begin(), vec.end());

    // method2 - std::copy
    // copy() 는 #include <algorithm> 필요
    // back_inserter() 는 #include <iterator> 필요
    vector<int> vec2;
    std::copy(vec.begin(), vec.end(), back_inserter(vec2));

    vec.clear();
    for (auto i : vec2) {
        cout << i << ",";
    }
    cout << endl;
}
int main() {
    cout << "-----test1-----" << endl;
    vector_test1();
    cout << "-----test2-----" << endl;
    vector_test2();
    cout << "-----test3-----" << endl;
    vector_test3();
    return 0;
}
