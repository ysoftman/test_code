////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// �ؽ�Ʈ ������ ����
// �ؽ�Ʈ ������ ���뺸��
// �ؽ�Ʈ ������ �� ���� ����
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[])
{
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;

	// ���� ���� ���
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
	// ���ϳ� ���� ����Ʈ �� ����
	else if (argc == 3 && strcmp(argv[1], "-b") == 0)
	{
		if ((fp1 = fopen(argv[2], "r")) == NULL)
		{
			printf("\nCan't find %s", argv[2]);
			exit(-1);
		}
		unsigned long cnt=0;
		int ch;
		// fgetc�Լ��� ���ϰ��� int���̴�
		// �ѱ� �ѹ��ڴ� 2����Ʈ ���� -> 2��
		while ((ch = fgetc(fp1)) != EOF)
		{
			// �ٹٲ�(Enter) ���ڴ� ����
			if (ch != '\n')
			{
				cnt++;
			}
		}
		printf("\nFile Character Count Result : %ld", cnt);

		fclose(fp1);
	}
	// ���� ����
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
		// ����� ǥ��
		printf("----- Usage -----\n");
		printf("[File View     ] %s -v File.txt\n", argv[0]);
		printf("[File ByteCount] %s -b File.txt\n", argv[0]);
		printf("[File Copy     ] %s -c SourceFile.txt DestinationFile.txt\n", argv[0]);
		exit(-1);
	}
}


