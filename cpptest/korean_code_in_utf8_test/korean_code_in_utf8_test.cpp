////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// utf-8 ÀÎÄÚµùÀ¸·Î ÇÑ±Û(11172ÀÚ) Ãâ·Â 
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

using namespace std;

int main()
{
	// utf-8 ÇÑ±ÛÀ» ÆÄÀÏ·Î Ãâ·Â
	FILE *fp = fopen("utf8-hangul.txt", "w");

	// ÇÑ±Û À¯´ÏÄÚµå(UCS) 0xAC00(°¡) ~ 0xD7A3(ÆR) 11172ÀÚ -> utf-8 ÀÎÄÚµùÀ¸·Î º¯È¯
	char hangul[3];
	int cnt = 0;
	for (unsigned short i = 0xAC00; i <= 0xD7A3; i++)
	{
		// Âü°í
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
