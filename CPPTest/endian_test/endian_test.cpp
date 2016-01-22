////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Big Endian(UNIX with RISC(Motoloa 6800, MIPS, SPARC, etc...))
// Little Endian(Windows with Intel x86, DEC Alpah, etc...)
// �� ��� ���� ���̷��� �޸𸮻� Mapping ����� Ʋ���� byte swapping�� �ʿ�
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>

#include <winsock2.h>	// for htonl()


#pragma comment (lib, "ws2_32.lib")	// for use library(ws2_32.lib)


struct STUDENT {
	char name[5];
	long Name[4];	// for Number Expression of Charater Name
	int age;
};


void main()
{
	STUDENT std;
	// B = 66(ASCII)
	// I = 73(ASCII)
	// L = 76(ASCII)
	strcpy(std.name, "BILL");

	std.age = 26;
	
	printf("\n�� Little Endian(Windows) ��\n");
	printf("[Name]\n%p/%p/%p/%p\n%d/%d/%d/%d\n%c/%c/%c/%c\n[Age]\n%p\n%d\n",
		std.name[0], std.name[1], std.name[2], std.name[3],
		std.name[0], std.name[1], std.name[2], std.name[3],
		std.name[0], std.name[1], std.name[2], std.name[3],
		std.age,
		std.age);

	printf("\nTransferring... Windows -> UNIX\n");

	std.age = htonl(std.age);

	std.Name[0] = htonl(66);
	std.Name[1] = htonl(73);
	std.Name[2] = htonl(76);
	std.Name[3] = htonl(76);
	
	printf("\n�� Big Endian(UNIX) ��\n");
	printf("[Name]\n%p/%p/%p/%p\t%d\n%d/%d/%d/%d\n%c/%c/%c/%c\n[Age]\n%p\n%d\n",
		std.Name[0], std.Name[1], std.Name[2], std.Name[3], &std.Name[0],
		std.Name[0], std.Name[1], std.Name[2], std.Name[3],
		std.Name[0], std.Name[1], std.Name[2], std.Name[3],
		std.age, 
		std.age);

	printf("\nTransferring...UNIX -> Windows\n");

	std.age = htonl(std.age);

	std.Name[0] = htonl(std.Name[0]);
	std.Name[1] = htonl(std.Name[1]);
	std.Name[2] = htonl(std.Name[2]);
	std.Name[3] = htonl(std.Name[3]);

	printf("\n�� Little Endian(Windows) ��\n");
	printf("[Name]\n%p/%p/%p/%p\n%d/%d/%d/%d\n%c/%c/%c/%c\n[Age]\n%p\n%d\n",
		std.Name[0], std.Name[1], std.Name[2], std.Name[3],
		std.Name[0], std.Name[1], std.Name[2], std.Name[3],
		std.Name[0], std.Name[1], std.Name[2], std.Name[3],
		std.age, 
		std.age);

}


