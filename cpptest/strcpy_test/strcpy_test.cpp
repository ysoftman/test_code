////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// strcpy() 초기화 착각...
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	char str[5] = "abcd";

	// strcpy() 함수로 문자열을 초기화하기 위해선 아래와 같이 무심코 사용하는 경우가 있다.
	// 아래의 경우는 str[0]=\0, str[4]=\0 이지만 str[1]=b, str[2]=c, str[3]=d 가 남아 있다.
	strcpy(str, "");

	// 따라서 진짜 초기화하기 위해서는 memset 을 사용하자.
	memset(str, 0, sizeof(char)*5);



	// 런타임 에러 발생
	//char *aa = "0123456789";
	//char *bb = "ysoftman";
	
	char aa[100] = "0123456789";
	char bb[100] = "ysoftman";
	strcpy(aa, bb);

	printf("aa=%s\n", aa);
	printf("bb=%s\n", bb);

}


