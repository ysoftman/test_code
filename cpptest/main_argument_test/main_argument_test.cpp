////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ���� �Լ����� ���� �ޱ�
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// argc ������ ��
// argv ������ ��
void main(int argc, char **argv) //char *argv[] �� ������
{
	fprintf(stderr, "argc = %d\n", argc);
	if (argc <= 1)
	{
		exit(1);
	}
	for (int i=0; i<argc; i++)
	{
		fprintf(stderr, "argv[%d] = %s\n", i, argv[i]);
	}
}


