// ysoftman
// fwrite 쓰기 읽기
#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fp = fopen("fwriteTest.txt", "wb");
	float set = 123.45;
	//fprintf(fp, "%f", set);
	fwrite(&set, sizeof(float), 1, fp);
	float get = 0.0f;
	fclose(fp);
	fp = fopen("fwriteTest.txt", "rb");
	fread(&get, sizeof(float), 1, fp);
	printf("%f", get);
	fclose(fp);

	return 0;
}
