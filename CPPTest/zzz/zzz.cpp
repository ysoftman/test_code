/* 
author: ysoftman
title: C/CPP zzz
desc: C/CPP 관련 이것저것 테스트하기 위한 코드
*/
#include <stdio.h>
#include <iostream>

struct aa {
	int a;
	long b;
};

struct aa my = {10, 200};

int main()
{
	int a = 10;
	printf ("a=%d\n", a);
	std::cout << "a=" << a << std::endl;
	std::cout << "my.a:" << my.a << std::endl;
	std::cout << "my.b:" << my.b << std::endl;
	return 0;
}



