////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// bit field 테스트
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int main()
{
	struct bitField {
		unsigned int nNum;
		unsigned char bitNum : 1;	// 8비트가 아닌 1비트만 메모리 할당한다.
	};

	bitField bf;
	bf.nNum = 100;
	sizeof(bf.nNum);
	//sizoef(bf.bitNum);	// 1비트 이기땜문에 사용할 수 없다.
	bf.bitNum = 1;		// 1비트 0,1 만을 사용할 수 있다.
	printf("bf.nNum = %d\n", bf.nNum);
	printf("bf.bitNum = %d\n", bf.bitNum);
	return 0;
}


