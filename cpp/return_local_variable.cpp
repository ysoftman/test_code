#include <iostream>

using namespace std;

char *func1(char *str)
{
    str[0] = 'a';
    str[1] = 'b';
    str[2] = 'c';
    return str;
}

string func2()
{
    string str = "abc";
    return str;
}

// warning: address of stack memory associated with local variable 'str' returned
// value 타압의 로컬 변수는 값 자체가 리턴되어 문제가 없지만
// reference(pointer, array) 타입의 로컬 변수는 실제 값을 가르키는 메모리 주소 값이 리턴되는데
// 함수 리턴시 로컬 변수의 메모리는 이미 해제되어
// caller 에서는 리턴된 메모리 주소에 해당 되는 값은 이미 유실된 상태이다.
// 참고
// assembly 코드 보기
// -c : 컴파일만하여 오브젝트 파일 생성
// -g : 소스레벨의 디버깅 정보 포함(소스 내용을 포함한다.)
// g++ -c -g return_local_variable.cpp
// -d : disassemble
// -S : disassembly 코드에 해당하는 소스코드 표시
// objdump -dS return_local_variable.o
// mac 에서는
// objdump -disassemble -source return_local_variable.o
char *func3()
{
    // static 으로 선언하면 되긴 하지만 비추
    char str[4] = {
        0,
    };
    str[0] = 'a';
    str[1] = 'b';
    str[2] = 'c';
    return str;
}

int main()
{
    char str[4] = {
        0,
    };
    cout << "func1 " << func1(str) << endl;
    cout << "func2 " << func2() << endl;
    cout << "func3 " << func3() << endl;
}
