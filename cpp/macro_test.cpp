////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Preprocessor(macro) 연산자 테스트
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

// 숫자 정의, define 보단 const 를 사용
#define A 123
const int a = 456;

// 3항 연산자로 max 함수
#define max(x, y) (x > y ? x : y)

// "" 를 붙여 토큰 x 를 스트링 리터럴로 표시한다.(token(parameter) is replace by string)
#define makestr(x) #x

// 토큰 2개를 붙인다.(concatenate)
#define concat(x, y) (x##y)

int main()
{
	printf("%d\n", A);
	printf("%d\n", a);
	printf("%d\n", max(9, 5));
	// "" 가 없어 에러
	// printf("%s\n", ysoftman);
	printf("%s\n", makestr(make string.));
	// print + f 를 만들어 사용
	concat(print, f)("zzz\n");
}
