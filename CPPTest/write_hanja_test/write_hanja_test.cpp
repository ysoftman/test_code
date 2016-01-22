////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 한자 파일에 쓰기 읽기
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fp = NULL;
	char str[3] = {0,};

	fp = fopen("hanja.txt", "w");
	fprintf(fp, "%s", "家");
	fclose(fp);

	fp = fopen("hanja.txt", "r");
	fscanf(fp, "%s", str);
	printf("%s\n", str);
	fclose(fp);

	return 0;
}


