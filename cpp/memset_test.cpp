// ysoftman
// memset() 를 사용한 초기화시 유념해야 할 것들
// memset 함수는 for 문에 비해 굉장히 빠르고 간편한다.
// 하지만 처리 단위가 byte 이기 때문에 크기가 1byte 보다 큰 int, float 와 같은 타입의 경우는
// 0 또는 -1 인 외에는 원하는 정수형태로 초기화가 되지 않는다.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	// byte(char) 타입의 경우 1 값으로 초기화 된다.
	char *pCh = new char[100];
	memset(pCh, 1, 100 * sizeof(char));
	printf("%c %d\n", pCh[0], pCh[0]);

	// int(4byte) 타입의 경우
	// 0 은 int의 모든 바이트로 0 으로 만들고 이는 곧 int 에서의 정수 0과 같다.
	// pNum[0] = [0000000000000000000000000000000] 이 된다.
	int *pInt1 = new int[100];
	memset(pInt1, 0, 100 * sizeof(int));
	printf("%d\n", pInt1[0]);

	// -1 은 int의 모든 바이트로 1 으로 만들고 이는 곧 int 에서의 정수 -1과 같다.
	// pNum[0] = [1111111111111111111111111111111] 이 된다.
	int *pInt2 = new int[100];
	memset(pInt2, -1, 100 * sizeof(int));
	printf("%d\n", pInt2[0]);

	// 1 값이 아닌 16843009 값으로 초기화 된다.
	// pNum[0] = [00000001000000010000000100000001] 으로 16843009 값이 되버린다.
	int *pNum1 = new int[100];
	memset(pNum1, 1, 100 * sizeof(int));
	printf("%d\n", pNum1[0]);

	delete[] pCh;
	delete[] pInt1;
	delete[] pInt2;
	delete[] pNum1;

	return 0;
}
