////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// strcpy() �ʱ�ȭ ����...
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	char str[5] = "abcd";

	// strcpy() �Լ��� ���ڿ��� �ʱ�ȭ�ϱ� ���ؼ� �Ʒ��� ���� ������ ����ϴ� ��찡 �ִ�.
	// �Ʒ��� ���� str[0]=\0, str[4]=\0 ������ str[1]=b, str[2]=c, str[3]=d �� ���� �ִ�.
	strcpy(str, "");

	// ���� ��¥ �ʱ�ȭ�ϱ� ���ؼ��� memset �� �������.
	memset(str, 0, sizeof(char)*5);



	// ��Ÿ�� ���� �߻�
	//char *aa = "0123456789";
	//char *bb = "ysoftman";
	
	char aa[100] = "0123456789";
	char bb[100] = "ysoftman";
	strcpy(aa, bb);

	printf("aa=%s\n", aa);
	printf("bb=%s\n", bb);

}


