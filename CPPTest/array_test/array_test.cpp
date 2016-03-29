////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 배열 테스트
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

// 배열은 포인터의 일종으로 [] 는 참조 파라미터가됨
int modifyarry(int arValue[])
{
	arValue[0] = -1;
	arValue[1] = 10;
	return 0;
}

void main()
{
	int arr[3];

	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 2;

	//arr[3] = 3; // <- 런타임 에러 발생

	for (int i=0;i<3;i++) {
		printf("arr[%d]: %d\n", i, arr[i]);
	}

	modifyarry(arr);

	printf("after modifyarry(arr)\n");

	for (int i=0;i<3;i++) {
		printf("arr[%d]: %d\n", i, arr[i]);
	}
}

