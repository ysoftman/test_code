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
	//sizoef(bf.bitNum);	// 1��Ʈ �̱⶧���� ����� �� ����.
	printf("bf.nNum = %d\n", bf.nNum);

	// 1��Ʈ 0,1 ���� ����� �� �ִ�.
	bf.bitNum = 0;
	printf("bf.bitNum = %d\n", bf.bitNum);
	bf.bitNum = 1;
	printf("bf.bitNum = %d\n", bf.bitNum);

	// �������ο�Ǿ� 0 �Ǵ� 1 ������ ������
	bf.bitNum = 2;
	printf("bf.bitNum = %d\n", bf.bitNum);
	bf.bitNum = 3;
	printf("bf.bitNum = %d\n", bf.bitNum);
	bf.bitNum = 4;
	printf("bf.bitNum = %d\n", bf.bitNum);

	return 0;
}


