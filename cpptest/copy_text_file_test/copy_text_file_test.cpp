////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 텍스트 파일의 복사
// 텍스트 파일의 내용보기
// 텍스트 파일의 총 문자 갯수
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;

	// 파일 내용 출력
	if (argc == 3 && strcmp(argv[1], "-v") == 0)
	{
		if	((fp1 = fopen(argv[2], "r")) == NULL)
		{
			printf("\nCan't find %s", argv[2]);
			exit(-1);
		}
		int ch;
		while ((ch = fgetc(fp1)) != EOF)
		{
			printf("%c", ch);
		}
		fclose(fp1);
	}
	// 파일내 문자 바이트 수 세기
	else if (argc == 3 && strcmp(argv[1], "-b") == 0)
	{
		if ((fp1 = fopen(argv[2], "r")) == NULL)
		{
			printf("\nCan't find %s", argv[2]);
			exit(-1);
		}
		unsigned long cnt=0;
		int ch;
		// fgetc함수는 리턴값이 int형이다
		// 한글 한문자는 2바이트 차지 -> 2개
		while ((ch = fgetc(fp1)) != EOF)
		{
			// 줄바꿈(Enter) 문자는 제외
			if (ch != '\n')
			{
				cnt++;
			}
		}
		printf("\nFile Character Count Result : %ld", cnt);

		fclose(fp1);
	}
	// 파일 복사
	else if (argc == 4 && strcmp(argv[1], "-c") == 0)
	{
		if ((fp1 = fopen(argv[2], "r")) == NULL)
		{
			printf("\nCan't find %s", argv[2]);
			exit(-1);
		}
			
		if ((fp2 = fopen(argv[3], "w")) == NULL)
		{
			printf("\nCan't find %s", argv[3]);
			exit(-1);
		}
		int ch;
		while ((ch = fgetc(fp1)) != EOF)
		{
			if (fputc(ch, fp2) == EOF)
			{
				break;
			}
		}
		fclose(fp1);
		fclose(fp2);
	}
	else
	{
		// 사용방법 표시
		printf("----- Usage -----\n");
		printf("[File View     ] %s -v File.txt\n", argv[0]);
		printf("[File ByteCount] %s -b File.txt\n", argv[0]);
		printf("[File Copy     ] %s -c SourceFile.txt DestinationFile.txt\n", argv[0]);
		exit(-1);
	}

	return 0;
}
