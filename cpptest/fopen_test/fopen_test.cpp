////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// fopen�� text���� binary��� ����
// ������ ȯ�濡�� ���๮��(\n)�� CR(CarriageReturn) �� LF(LineFeed) �����̴�.
// LF(Line Feed) : Dec(10) Hex(0x0a)
// CR(Carriage Return) : Dec(13) Hex(0x0d)
// fprintf(fp, "\n"); �ϸ� �����δ� 
// MAC ������ CR �ڵ� 1����Ʈ�� ������.
// UNIX ������ LF �ڵ� 1����Ʈ�� ������.
// Windows/DOS ������ CR �� LF �ڵ� 2����Ʈ�� ������.
// Windows/DOS ������ ���� ���½� text ����϶� CRLF �� LF �� �о�´�.
// Windows/DOS ������ ���� ���½� binary ����϶� �״�� CRLF �� �о�´�.
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	FILE *fp = NULL;
	int num_of_bytes = 0;
	char c = NULL;

	// ���� ����
	fp = fopen("CRLF.txt", "w");
	fprintf(fp, "YOON BYOUNG HOON\n������\n��ܼ��\n");
	fclose(fp);

	// text ���� �б�
	fp = fopen("CRLF.txt", "rt");
	num_of_bytes = 0;
	while ( (c = fgetc(fp)) != EOF )
	{
		num_of_bytes++;
	}
	fprintf(stdout, "[Text mode open] ����ũ��(����Ʈ����):%d\n", num_of_bytes);
	fclose(fp);

	// binary ���� �б�
	fp = fopen("CRLF.txt", "rb");
	num_of_bytes = 0;
	while ( (c = fgetc(fp)) != EOF )
	{
		num_of_bytes++;
	}
	fprintf(stdout, "[Binary mode open] ����ũ��(����Ʈ����):%d\n", num_of_bytes);
	fclose(fp);

}


