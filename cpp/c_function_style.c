#include <stdio.h>

// 함수 이름 과 { 시작 전에 파라미터를 선언하는 것으로
// K&R(Kernighan and Ritchie) old(obsolete) 방식이다.
int   func1(int_param, char_param)
int   int_param;
char *char_param;
{
    printf("%s int_param=%d char_param=%s\n", __FUNCTION__, int_param, char_param);
    return 0;
}

int func2(int int_param, char *char_param) {
    printf("%s int_param=%d char_param=%s\n", __FUNCTION__, int_param, char_param);
    return 0;
}

int main() {
    printf("%s\n", __FUNCTION__);

    func1(1, "ysoftman");
    func1(1, "ysoftman");
    return 0;
}