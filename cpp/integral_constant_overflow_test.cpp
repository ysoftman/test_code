// ysoftman
// 정수형 상수 오버플로우
#include <stdio.h>

int main() {
    // warning C4307: '*' : integral constant overflow
    // 아래와 같이 큰 값을 계산하면 계산에 할당된 공간(4byte)를 넘어서 오버플로우 발생
    // 참고 http://msdn.microsoft.com/ko-kr/library/4kze989h(v=vs.90).aspx
    unsigned long long size1 = 1024 * 1024 * 1024 * 10;
    printf("size1 : %lld\n", size1);

    unsigned long long size2 = 1024;
    size2 *= 1024 * 1024 * 10;
    printf("size2 : %lld\n", size2);
}
