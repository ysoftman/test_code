////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ���� ���Ͽ� ���� �б�
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fp = NULL;
	char str[3] = {0,};

	fp = fopen("hanja.txt", "w");
	fprintf(fp, "%s", "ʫ");
	fclose(fp);

	fp = fopen("hanja.txt", "r");
	fscanf(fp, "%s", str);
	printf("%s\n", str);
	fclose(fp);

	return 0;
}


