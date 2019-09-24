// ysoftman
// 난수 발생
// srand() 와 rand() 소스
//static UINT32 next = 1;
//
//int __cdecl rand(void)
//{
//    next = next * 1103515245 + 12345;
//    // return (unsigned int)(next / 65536) % 32768;
//    return (UINT32)(next>>16) & RAND_MAX;
//}
//
//void __cdecl srand(unsigned int seed)
//{
//    // And you *should* get a warning if sizes dont match
//    next = seed;
//}
// 주의 사항 1
// 멀티쓰레드 프로그램에서는 각 쓰레드마다 srand 로 씨드 초기화하거나
// 랜덤함수를 직접 구현(씨드는 글로벌 변수)하여 모든 쓰레드에서 구현한 랜덤함수를 사용하자.
// 주의 사항 2
// rand() 로 나올 수 있는 값은 0 ~ RAND_MAX
// 윈도우 RAND_MAX -> 0x7fff -> 32,767 -> 2^15-1
// 리눅스 RAND_MAX -> 0x7fffffff -> 2147483647 -> 2^31-1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	int num = 0;
	int seed = 0;

	// 테스트
	// 랜덤 씨드를 현재 unix epoch time(초) 으로 한번만 설정
	seed = (unsigned int)time(NULL);
	srand(seed);
	for (int i = 0; i < 10; i++)
	{
		num = rand();
		printf("random number is %d\n", num);
		num = num % 100;
		printf("random number is %d\n", num);
	}

	return 0;
}
