////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// bit field �׽�Ʈ
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int main()
{
	struct bitField {
		unsigned int nNum;
		unsigned char bitNum : 1;	// 8��Ʈ�� �ƴ� 1��Ʈ�� �޸� �Ҵ��Ѵ�.
	};

	bitField bf;
	bf.nNum = 100;
	sizeof(bf.nNum);
	//sizoef(bf.bitNum);	// 1��Ʈ �̱ⶫ���� ����� �� ����.
	bf.bitNum = 1;		// 1��Ʈ 0,1 ���� ����� �� �ִ�.
	printf("bf.nNum = %d\n", bf.nNum);
	printf("bf.bitNum = %d\n", bf.bitNum);
	return 0;
}


