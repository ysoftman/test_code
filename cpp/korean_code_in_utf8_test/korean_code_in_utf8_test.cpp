////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// utf-8 인코딩으로 한글(11172자) 출력 
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

using namespace std;

int main()
{
	// utf-8 한글을 파일로 출력
	FILE *fp = fopen("utf8-hangul.txt", "w");

	// 한글 유니코드(UCS) 0xAC00(가) ~ 0xD7A3(