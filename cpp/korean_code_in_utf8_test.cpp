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

	// 한글 유니코드(UCS) 0xAC00(가) ~ 0xD7A3(힣) 11172자 -> utf-8 인코딩으로 변환
	char hangul[3];
	int cnt = 0;
	for (unsigned short i = 0xAC00; i <= 0xD7A3; i++)
	{
		// 참고
		// http://www.codeguru.com/cpp/misc/misc/multi-lingualsupport/article.php/c10451/The-Basics-of-UTF8.htm
		hangul[0] = ((char)(0xE0 | i >> 12));
		hangul[1] = ((char)(0x80 | i >> 6 & 0x3F));
		hangul[2] = ((char)(0x80 | i & 0x3F));
		fprintf(fp, "%X = %c%c%c\n", i, hangul[0], hangul[1], hangul[2]);
		++cnt;
	}
	printf("cnt = %d\n", cnt);

	fclose(fp);

	return 0;
}
