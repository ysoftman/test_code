// ysoftman
// bit field 테스트
#include <stdio.h>

int main()
{
	struct bitField
	{
		unsigned int nNum;
		unsigned char bitNum : 1; // 8비트가 아닌 1비트만 메모리 할당한다.
	};

	// c++ 에선 struct 를 생략해도 된다.
	struct bitField bf;

	bf.nNum = 100;
	printf("%lu\n", sizeof(bf));
	printf("%lu\n", sizeof(bf.nNum));
	// printf("%lu\n", sizeof(bf.bitNum)); // 1비트 이기때문에 사용할 수 없다.
	printf("bf.nNum = %d\n", bf.nNum);

	// 1비트 0,1 만을 사용할 수 있다.
	bf.bitNum = 0;
	printf("bf.bitNum = %d\n", bf.bitNum);
	bf.bitNum = 1;
	printf("bf.bitNum = %d\n", bf.bitNum);

	// 오버플로 경고 메시지 발생
	// 오버플로 되어 0 또는 1 값으로 설정됨
	// bf.bitNum = 2;
	// printf("bf.bitNum = %d\n", bf.bitNum);
	// bf.bitNum = 3;
	// printf("bf.bitNum = %d\n", bf.bitNum);
	// bf.bitNum = 4;
	// printf("bf.bitNum = %d\n", bf.bitNum);

	return 0;
}
