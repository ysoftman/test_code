// ysoftman
// inheritance 관련 테스트
#include <iostream>
#include <typeinfo>  // for typeid()

using namespace std;

class C1 {
   public:
    void myfunc() { cout << typeid(C1).name() << "::" << __FUNCTION__ << endl; }
};

class C2 {
   public:
    void myfunc() { cout << typeid(C2).name() << "::" << __FUNCTION__ << endl; }
};

// 다중 상속시
class myClass : public C1, public C2 {
   public:
    void callfunc() {
        // 같은 함수이름으로 모호성이 발생 다음과 같은 에러 발생
        // member 'myfunc' found in multiple base classes of different types
        // member found by ambiguous name lookup        void myfunc()
        // myfunc();
        // myfunc();
        // 스코프로 어떤 부모클래스의 함수인지 명확히 명시해야 한다.
        C1::myfunc();
        C2::myfunc();
    }
};

int main() {
    myClass mc;
    mc.callfunc();

    return 0;
}
