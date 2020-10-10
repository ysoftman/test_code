// ysoftman
// define 상수 관련 테스트
#include <stdio.h>

#define MY_NUM 100

int main()
{

	int num = 0;
	printf("MY_NUM : %d\n", MY_NUM);
	// define 상수에 값 할당 -> 컴파일시 에러
	//MY_NUM = 1;
	// define 상수에 ++ 연산 ->  컴파일시 에러
	//num = ++MY_NUM;
	printf("num : %d\n", num);

	return 0;
}
