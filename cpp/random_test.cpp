// ysoftman
// 난수 발생

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <random>
using std::cout;
using std::endl;

/*
C Style 랜덤 생성
srand() 와 rand() 소스
static UINT32 next = 1;

int __cdecl rand(void)
{
   next = next * 1103515245 + 12345;
   // return (unsigned int)(next / 65536) % 32768;
   return (UINT32)(next>>16) & RAND_MAX;
}

void __cdecl srand(unsigned int seed)
{
   // And you *should* get a warning if sizes dont match
   next = seed;
}
주의 사항 1
멀티쓰레드 프로그램에서는 각 쓰레드마다 srand 로 씨드 초기화하거나
랜덤함수를 직접 구현(씨드는 글로벌 변수)하여 모든 쓰레드에서 구현한 랜덤함수를 사용하자.
주의 사항 2
rand() 로 나올 수 있는 값은 0 ~ RAND_MAX
윈도우 RAND_MAX -> 0x7fff -> 32,767 -> 2^15-1
리눅스 RAND_MAX -> 0x7fffffff -> 2147483647 -> 2^31-1

주의 사항 3
랜덤 값이 균등하게 분포하지 않는다.
*/
void randomCStyle()
{
	int num = 0;
	int seed = (unsigned int)time(NULL);
	srand(seed);
	for (int i = 0; i < 10; i++)
	{
		num = rand();
		// printf("random number is %d\n", num);
		num = (num % 100) + 1;
		printf("C-style random number: %d\n", num);
	}
}

/*
CPP Style 랜덤 생성
랜덤 값이 균등하게 분포한다.
*/
void randomCppStyle()
{
	// 랜던 디바이스(/dev/random, /dev/urandom, /dev/arandom OS 의 랜덤 파일등을 이용)
	// https://en.cppreference.com/w/cpp/numeric/random/random_device
	std::random_device rd;
	// 랜덤 디바이스를 씨드로 mt19937 랜덤 엔진 사용
	// https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine
	std::mt19937 gen(rd());

	// 1~100 균등 분포하도록
	// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
	std::uniform_int_distribution<int> distrib(1, 100);

	for (int i = 0; i < 10; i++)
	{
		cout << "CPP-style random number:" << distrib(gen) << endl;
	}
}

int main()
{
	randomCStyle();
	randomCppStyle();
	return 0;
}
