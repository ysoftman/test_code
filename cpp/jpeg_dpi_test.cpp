// ysoftman
// jpeg 헤더의 dpi 정보를 바꾼다.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 20101203 ysoftman
// 파일의 크기를 파악한다.
int GetFileSize(FILE *fp)
{
	// fp 를 파일의 맨 끝으로 옮긴다.
	fseek(fp, 0, SEEK_END);
	// 파일의 맨 처음부터의 거리를 바이트로 알아본다.
	int size = ftell(fp);
	// fp 를 파일의 맨 처음으로 돌려 놓는다.
	fseek(fp, 0, SEEK_SET);
	return size;
}

// 20101203 ysoftman
// jpeg 파일의 DPI 정보를 바꿔준다.
int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		fprintf(stderr, "[argc = %d] argument error...\n", argc);
		fprintf(stderr, "ex) JpegDpiSet 200 input.jpg output.jpg\n");
		exit(-1);
	}

	// 입력 jpg 파일
	FILE *fpIn = fopen(argv[2], "rb");
	if (fpIn == NULL)
	{
		fprintf(stderr, "can't open %s file...\n", argv[2]);
		exit(-1);
	}
	// 출력 jpg 파일
	FILE *fpOut = fopen(argv[3], "wb");
	if (fpOut == NULL)
	{
		fprintf(stderr, "can't open %s file...\n", argv[3]);
		exit(-1);
	}
	// 설정할 dpi 값
	int dpi = atoi(argv[1]);
	if (dpi < 0 || dpi > 200)
	{
		dpi = 200;
	}
	// 입력 파일크기 얻기
	int size = GetFileSize(fpIn);
	char *pBuffer = (char *)malloc(sizeof(char) * size);
	memset(pBuffer, 0, sizeof(char) * size);
	// 입력 파일 메모리로 복사하기
	fread(pBuffer, sizeof(char) * size, 1, fpIn);

	char readbyte = 0;

	// 수평 해상도
	readbyte = pBuffer[15];
	pBuffer[15] = dpi;
	// 수직 해상도
	readbyte = pBuffer[17];
	pBuffer[17] = dpi;

	// 출력 파일 만들기
	fwrite(pBuffer, sizeof(char) * size, 1, fpOut);
	fprintf(stderr, "%s(%d) -> %s(%d) dpi Completed.\n", argv[2], readbyte, argv[3], dpi);

	free(pBuffer);
	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
