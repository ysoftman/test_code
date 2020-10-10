// ysoftman
// fopen의 text모드와 binary모드 차이
// 윈도우 환경에서 개행문자(\n)는 CR(CarriageReturn) 과 LF(LineFeed) 조합이다.
// LF(Line Feed) : Dec(10) Hex(0x0a)
// CR(Carriage Return) : Dec(13) Hex(0x0d)
// fprintf(fp, "\n"); 하면 실제로는
// MAC 에서는 CR 코드 1바이트만 박힌다.
// UNIX 에서는 LF 코드 1바이트만 박힌다.
// Windows/DOS 에서는 CR 과 LF 코드 2바이트가 박힌다.
// Windows/DOS 에서는 파일 오픈시 text 모드일때 CRLF 중 LF 만 읽어온다.
// Windows/DOS 에서는 파일 오픈시 binary 모드일때 그대로 CRLF 를 읽어온다.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fp = NULL;
	int num_of_bytes = 0;
	char c = NULL;

	// 파일 쓰기
	fp = fopen("CRLF.txt", "w");
	fprintf(fp, "YOON BYOUNG HOON\n윤병훈\n尹秉勳\n");
	fclose(fp);

	// text 모드로 읽기
	fp = fopen("CRLF.txt", "rt");
	num_of_bytes = 0;
	while ((c = fgetc(fp)) != EOF)
	{
		num_of_bytes++;
	}
	fprintf(stdout, "[Text mode open] 파일크기(바이트개수):%d\n", num_of_bytes);
	fclose(fp);

	// binary 모드로 읽기
	fp = fopen("CRLF.txt", "rb");
	num_of_bytes = 0;
	while ((c = fgetc(fp)) != EOF)
	{
		num_of_bytes++;
	}
	fprintf(stdout, "[Binary mode open] 파일크기(바이트개수):%d\n", num_of_bytes);
	fclose(fp);

	return 0;
}
