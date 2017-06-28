////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 파일 내용 거꾸로 출력하기
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	char c = NULL;
	int i = 0;
	int length = 0;

	FILE *fp = NULL;

	fp = fopen("text.txt", "wb");
	fprintf(fp, "YoonByoungHoon\n");
	fclose(fp);

	if ((fp = fopen("text-reverse.txt", "rb")) == NULL)
	{
		printf("Can't open text-reverse.txt\n");
		exit(1);
	}
	
	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	printf("File Size : %d Bytes\n", length);

	while (1)
	{	
		c = fgetc(fp);
		fseek(fp, --i, SEEK_END);

		if (c == EOF)
		{
			continue;
		}
		printf("%c", c);
		if ((length - abs(i)) < 0)
		{
			break;
		}
	}
	printf("\n");
	fclose(fp);
}

