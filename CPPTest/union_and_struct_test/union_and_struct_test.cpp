////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// union �� struct �� ����
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>

struct ST {
	unsigned char ucChar;
	unsigned int unInt;
	
};

union UI {
	unsigned char ucChar;
	unsigned int unInt;
};

void main()
{
	ST stInstance;
	memset(&stInstance, 0, sizeof(stInstance));
	// 8 byte ���
	// 1����Ʈ char ���� 4����Ʈ int ���� ���� 4����Ʈ �޸𸮸� �����ϰ� �ȴ�.
	// ��� ������ �߰��ϸ� ���� ����ü�� �Ҵ�� �޸� ũ�⸦ �Ѿ�� �� ���
	// ���� ū ��� ������ Ÿ���� ũ�� ������ �޸𸮸� �Ҵ��ϰ� �ȴ�.
	// 4byte �� �Ѿ�� -> 8byte �� �Ѿ�� -> 12byte ...
	printf("stInstance size : %d bytes\n", sizeof(stInstance));

	UI uiInstance;
	memset(&uiInstance, 0, sizeof(uiInstance));
	// 4 byte ���
	// 1����Ʈ char ���� 4����Ʈ int ���� ���� 4����Ʈ �޸𸮸� ���������� �ϳ��� �ϳ��� 4����Ʈ �޸𸮰����� �����Ѵ�.
	printf("uiInstance size : %d bytes\n", sizeof(uiInstance));
	
	printf("\n\n");

	// struct �� ����� ������ �������� �޸� ������ �־� ���� ���� �����Ѵ�.
	stInstance.ucChar = 255;
	stInstance.unInt = 65535;
	printf("stInstance.ucChar = %d   stInstance.unInt = %d\n", stInstance.ucChar, stInstance.unInt);
	printf("stInstance.ucChar[0] = %x\n", stInstance.ucChar);
	// little/big endian �� ���� byte order �� �ٸ��� ���� �� �ִ�.
	printf("stInstance.unInt[0] = %x\n", (stInstance.unInt & 0x000000ff));
	printf("stInstance.unInt[1] = %x\n", (stInstance.unInt & 0x0000ff00) >> 8);
	printf("stInstance.unInt[2] = %x\n", (stInstance.unInt & 0x00ff0000) >> 16);
	printf("stInstance.unInt[3] = %x\n", (stInstance.unInt & 0xff000000) >> 24);
	printf("\n");

	// ���� ū �޸� ������ ���������� �� ����Ʈ�� �ֱٿ� �Ҵ��� ���� �����ȴ�.
	uiInstance.unInt = 65535;
	uiInstance.ucChar = 1;
	printf("uiInstance.ucChar = %d   uiInstance.b = %d\n", uiInstance.ucChar, uiInstance.unInt);
	printf("uiInstance.ucChar[0] = %x\n", uiInstance.ucChar);
	// little/big endian �� ���� byte order �� �ٸ��� ���� �� �ִ�.
	printf("uiInstance.unInt[0] = %x\n", (uiInstance.unInt & 0x000000ff));
	printf("uiInstance.unInt[1] = %x\n", (uiInstance.unInt & 0x0000ff00) >> 8);
	printf("uiInstance.unInt[2] = %x\n", (uiInstance.unInt & 0x00ff0000) >> 16);
	printf("uiInstance.unInt[3] = %x\n", (uiInstance.unInt & 0xff000000) >> 24);
	printf("\n");
}

