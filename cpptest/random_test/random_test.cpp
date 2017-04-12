////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ���� �߻�
// srand() �� rand() �ҽ�
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
// ���� ���� 1
// ��Ƽ������ ���α׷������� �� �����帶�� srand �� ���� �ʱ�ȭ�ϰų�
// �����Լ��� ���� ����(����� �۷ι� ����)�Ͽ� ��� �����忡�� ������ �����Լ��� �������.
// ���� ���� 2
// rand() �� ���� �� �ִ� ���� 0 ~ RAND_MAX
// ������ RAND_MAX -> 0x7fff -> 32,767 -> 2^15-1
// ������ RAND_MAX -> 0x7fffffff -> 2147483647 -> 2^31-1
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
int main()
{
	int num = 0;
	int seed = 0;

	// �׽�Ʈ
	// ���� ���带 ���� unix epoch time(��) ���� �ѹ��� ����
	seed = (unsigned int)time(NULL);
	srand(seed);
	for (int i=0; i<10; i++)
	{
		num = rand();
		printf("random number is %d\n", num);
		num = num%100;
		printf("random number is %d\n", num);
	}

	return 0;
}

