////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// jpeg ����� dpi ������ �ٲ۴�.
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 20101203 ysoftman
// ������ ũ�⸦ �ľ��Ѵ�.
int GetFileSize(FILE *fp)
{
	// fp �� ������ �� ������ �ű��.
	fseek(fp, 0, SEEK_END);
	// ������ �� ó�������� �Ÿ��� ����Ʈ�� �˾ƺ���.
	int size = ftell(fp);
	// fp �� ������ �� ó������ ���� ���´�.
	fseek(fp, 0, SEEK_SET);
	return size;
}

// 20101203 ysoftman
// jpeg ������ DPI ������ �ٲ��ش�.
int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		fprintf(stderr, "[argc = %d] argument error...\n", argc);
		fprintf(stderr, "ex) JpegDpiSet 200 input.jpg output.jpg\n");
		exit(-1);
	}

	// �Է� jpg ����
	FILE *fpIn = fopen(argv[2], "rb");
	if (fpIn == NULL)
	{
		fprintf(stderr, "can't open %s file...\n", argv[2]);
		exit(-1);
	}
	// ��� jpg ����
	FILE *fpOut = fopen(argv[3], "wb");
	if (fpOut == NULL)
	{
		fprintf(stderr, "can't open %s file...\n", argv[3]);
		exit(-1);
	}
	// ������ dpi ��
	int dpi = atoi(argv[1]);
	if (dpi < 0 || dpi > 200)
	{
		dpi = 200;
	}
	// �Է� ����ũ�� ���
	int size = GetFileSize(fpIn);
	char *pBuffer = (char*)malloc(sizeof(char)*size);
	memset(pBuffer, 0, sizeof(char)*size);
	// �Է� ���� �޸𸮷� �����ϱ�
	fread(pBuffer, sizeof(char)*size, 1, fpIn);

	char readbyte = 0;

	// ���� �ػ�
	readbyte = pBuffer[15];
	pBuffer[15] = dpi;
	// ���� �ػ�
	readbyte = pBuffer[17];
	pBuffer[17] = dpi;

	// ��� ���� �����
	fwrite(pBuffer, sizeof(char)*size, 1, fpOut);
	fprintf(stderr, "%s(%d) -> %s(%d) dpi Completed.\n", argv[2], readbyte, argv[3], dpi);

	free(pBuffer);
	fclose(fpIn);
	fclose(fpOut);

	return 0;
}


