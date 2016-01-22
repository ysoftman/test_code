////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 메인 함수에서 인자 받기
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// argc 인자의 수
// argv 인자의 값
void main(int argc, char **argv) //char *argv[] 와 같은말
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


