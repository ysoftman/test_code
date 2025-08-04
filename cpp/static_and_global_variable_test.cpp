// ysoftman
// static 과 전역변수 차이
// 둘다 프로그램이 시작되면 생성되고 프로그램이 종료될 때까지 유지되는 lifetime 은 같다
// 하지만 static 은 자신이 선언된 scope(블럭, 함수, 파일...) 내에서만 접근 가능하다.
// gcc static_and_global_variable_test.cpp static_and_global_variable_support_test.cpp && a.out
#include <stdio.h>

extern int nVar3;
extern int nVar4;

int        nVar1 = 0;

void       func1() {
    static int nVar2 = 0;
    printf("nVar2 = %d\n", ++nVar2);
}

int main() {
    for (int i = 0; i < 5; ++i) {
        printf("nVar1 = %d\n", ++nVar1);
        func1();
    }
    printf("extern int nVar3 = %d\n", nVar3);
    // printf("extern int nVar4 = %d\n", nVar4);	// 런타임 에러 - 외부의 static 은 접근할 수
    // 없다.
    return 0;
}
