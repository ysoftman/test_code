/*
author: ysoftman
title : and or 키워드 테스트

[reference]
https://en.cppreference.com/w/cpp/keyword
https://en.cppreference.com/w/cpp/language/operator_alternative
https://en.wikipedia.org/wiki/C_alternative_tokens
http://cs.smu.ca/~porter/csc/ref/cpp_keywords.html
http://www.trytoprogram.com/cplusplus-programming/history/

히스토리
and or 등의 키워드는 {}, [,] # 등 특수문자를 사용하지 못하는 ISO 646 환경에서
사용하기 위해서 ascii 의 조합으로 대체(alternative)하기 위해 만들어 졌다.
초기에 Bjarne Stroustrup 가 c++ 만들기 전에
<iso646.h> 에 연산자 매크로 11개 작성해 C90 라이브러리에 포함시켰다.
이후 c++98(최초 ISO c++ 표준버전) 에 <ciso646> 으로 제공됐지만
하위 버전과 호환을 위한 내용이 없는 파일만 유지하고 있다.
ms visual c++ 의 경우 <csio646> 헤더를 포함해야 한다.

헤더파일 위치 확인
gcc -xc - -v -E
vi /Library/Developer/CommandLineTools/usr/include/c++/v1/ciso646
*/

#include <stdio.h>

int main()
{
	int a = 7;
	printf("a > 5 && a < 20 is %d\n", a > 5 and a < 20);
	a = 10;
	printf("a == 10 || a == 20 is %d\n", a == 10 or a == 20);
	printf("!(a == 10) is %d\n", not(a == 10));
	printf("1 != 2 is %d\n", 1 not_eq 2);
	// formatting 하면 compl1 로 붙어버린다.
	// printf("~1  = %d\n", compl 1);
	printf("1 & 2 = %d\n", 1 bitand 2);
	printf("1 | 2 = %d\n", 1 bitor 2);
	printf("1 ^ 2 = %d\n", 1 xor 2);
	a = 1;
	a and_eq 2;
	printf("a(1) &= 2, a = %d\n", a);
	a = 1;
	a or_eq 2;
	printf("a(1) |= 2, a = %d\n", a);
	a = 1;
	a xor_eq 2;
	printf("a(1) ^= 2, a = %d\n", a);
}