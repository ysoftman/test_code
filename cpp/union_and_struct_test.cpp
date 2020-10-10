// ysoftman
// union 과 struct 의 차이
#include <stdio.h>
#include <string.h>

struct ST
{
	unsigned char ucChar;
	unsigned int unInt;
};

union UI {
	unsigned char ucChar;
	unsigned int unInt;
};

int main()
{
	ST stInstance;
	memset(&stInstance, 0, sizeof(stInstance));
	// 8 byte 출력
	// 1바이트 char 형이 4바이트 int 형과 같은 4바이트 메모리를 차지하게 된다.
	// 멤버 변수를 추가하면 현재 구조체에 할당된 메모리 크기를 넘어가게 될 경우
	// 가장 큰 멤버 변수의 타입의 크기 단위로 메모리를 할당하게 된다.
	// 4byte 를 넘어가면 -> 8byte 를 넘어가면 -> 12byte ...
	printf("stInstance size : %lu bytes\n", sizeof(stInstance));

	UI uiInstance;
	memset(&uiInstance, 0, sizeof(uiInstance));
	// 4 byte 출력
	// 1바이트 char 형이 4바이트 int 형과 같은 4바이트 메모리를 차지하지만 하나의 하나의 4바이트 메모리공간을 공유한다.
	printf("uiInstance size : %lu bytes\n", sizeof(uiInstance));

	printf("\n\n");

	// struct 의 멤버는 각각의 독립적인 메모리 공간이 있어 각각 값을 유지한다.
	stInstance.ucChar = 255;
	stInstance.unInt = 65535;
	printf("stInstance.ucChar = %d   stInstance.unInt = %d\n", stInstance.ucChar, stInstance.unInt);
	printf("stInstance.ucChar[0] = %x\n", stInstance.ucChar);
	// little/big endian 에 따라 byte order 가 다르게 나올 수 있다.
	printf("stInstance.unInt[0] = %x\n", (stInstance.unInt & 0x000000ff));
	printf("stInstance.unInt[1] = %x\n", (stInstance.unInt & 0x0000ff00) >> 8);
	printf("stInstance.unInt[2] = %x\n", (stInstance.unInt & 0x00ff0000) >> 16);
	printf("stInstance.unInt[3] = %x\n", (stInstance.unInt & 0xff000000) >> 24);
	printf("\n");

	// 가장 큰 메모리 공간을 공유함으로 각 바이트는 최근에 할당한 값이 유지된다.
	uiInstance.unInt = 65535;
	uiInstance.ucChar = 1;
	printf("uiInstance.ucChar = %d   uiInstance.b = %d\n", uiInstance.ucChar, uiInstance.unInt);
	printf("uiInstance.ucChar[0] = %x\n", uiInstance.ucChar);
	// little/big endian 에 따라 byte order 가 다르게 나올 수 있다.
	printf("uiInstance.unInt[0] = %x\n", (uiInstance.unInt & 0x000000ff));
	printf("uiInstance.unInt[1] = %x\n", (uiInstance.unInt & 0x0000ff00) >> 8);
	printf("uiInstance.unInt[2] = %x\n", (uiInstance.unInt & 0x00ff0000) >> 16);
	printf("uiInstance.unInt[3] = %x\n", (uiInstance.unInt & 0xff000000) >> 24);
	printf("\n");

	return 0;
}
