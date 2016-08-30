/* 
author: ysoftman
title : and or 키워드 테스트
*/
#include <stdio.h>

int main()
{
    int a = 7;
	// visual c++ 에서는 and or not xor 키워드 사용 못함
	if (a > 5 and a < 20)
	{
		printf("ok1\n");
	}
    a = 10;
	if (a == 10 or a == 20)
	{
		printf("ok2\n");
    }
}