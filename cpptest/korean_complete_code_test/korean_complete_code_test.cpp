////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// �ϼ��� �ѱ� �ڵ� ��� �� �˻�
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

void make_KOR_COM_CODE_2350()
{
	char ch[3] = "��";
	int i;
	int j;
	int cnt=0;
	FILE *fp;
	fp = fopen("kor_com_code_2350.txt", "w");
	// KS X 1001 �ѱ� 2350�� EUC-KR
	// http://ko.wikipedia.org/wiki/KS_X_1001_%ED%95%9C%EA%B8%80_%EB%B6%80%EB%B6%84_%ED%91%9C
	// '�c' '��'  �ڿ� ���� ���� �ѱ��� ����
	// ù��° ����Ʈ ����
	//0xb0 = 176 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 176-256=-80
	//0xc8 = 200 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 200-256=-56
	// �ι�° ����Ʈ ����
	//0xa1 = 161 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 161-256=-95
	//0xfe = 254 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 254-256=-2
	for (i=-80; i<=-56; i++)
	{
		for (j=-95; j<=-2; j++)
		{
			ch[0] = i;
			ch[1] = j;
			printf("%s\n", ch);
			fprintf(fp, "%s\n", ch);
			cnt++;
		}
	}
	printf("�ѱ��ڼ�:%d\n", cnt);
	fprintf(fp, "�ѱ��ڼ�:%d\n", cnt);
	fclose(fp);
}

void make_KOR_COM_CODE_8822()
{
	char ch[3] = "��";
	int i;
	int j;
	int cnt=0;
	FILE *fp;
	fp = fopen("kor_com_code_8822.txt", "w");
	// CP949
	// http://ko.wikipedia.org/wiki/%EC%BD%94%EB%93%9C_%ED%8E%98%EC%9D%B4%EC%A7%80_949
	// https://msdn.microsoft.com/ko-kr/goglobal/cc305154.aspx
	// CP949 �� 2350�� �� 8822�� (2350 + 8822 = 11172) 
	// ù��° ����Ʈ ����
	//0x81 = 129 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 129-256=-127
	//0xc5 = 197 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 197-256=-59
	// �ι�° ����Ʈ ����
	//0x41 = 65
	//0x5a = 90
	
	// ù��° ����Ʈ ����
	//0x81 = 129 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 129-256=-127
	//0xc5 = 197 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 197-256=-59
	// �ι�° ����Ʈ ����
	//0x61 = 97
	//0x7a = 122

	// ù��° ����Ʈ ����
	//0x81 = 129 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 129-256=-127
	//0xc5 = 197 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 197-256=-59
	// �ι�° ����Ʈ ����(ù° ����Ʈ�� 161(161-256=-95) �̻��� ��� KS X 1001���� �浹�� ���� ���� ��° ����Ʈ�� 161 �̻��� �� �� ����.)
	//0x81 = 129 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 129-256=-127
	//0xfe = 254 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 254-256=-2

	// ù��° ����Ʈ ����	
	//0xc6 = 198 : signed 1����Ʈ�� �о� ���� �����÷ο�, ���� 198-256=-58
	// �ι�° ����Ʈ ����
	//0x41 = 65
	//0x52 = 82
	for (i=-127; i<=-59; i++)
	{
		for (j=65; j<=90; j++)
		{
			ch[0] = i;
			ch[1] = j;
			printf("%s\n", ch);
			fprintf(fp, "%s\n", ch);
			cnt++;
		}
		for (j=97; j<=122; j++)
		{
			ch[0] = i;
			ch[1] = j;
			printf("%s\n", ch);
			fprintf(fp, "%s\n", ch);
			cnt++;
		}
		for (j=-127; j<=-2; j++)
		{
			if (i>=-95 && j>=-95)
			{
				break;
			}
			ch[0] = i;
			ch[1] = j;
			printf("%s\n", ch);
			fprintf(fp, "%s\n", ch);
			cnt++;
		}
	}
	for (j=65; j<=82; j++)
	{
		ch[0] = -58;
		ch[1] = j;
		printf("%s\n", ch);
		fprintf(fp, "%s\n", ch);
		cnt++;
	}
	printf("�ѱ��ڼ�:%d\n", cnt);
	fprintf(fp, "�ѱ��ڼ�:%d\n", cnt);
	fclose(fp);
}

void main(int argc, char *argv[])
{
	// �ϼ��� �ڵ� ���
	make_KOR_COM_CODE_2350();
	make_KOR_COM_CODE_8822();


	if (argc != 2)
	{
		printf("usage:\n%s xxx.txt\n", argv[0]);
		return;
	}
	const int MAX_LEN = 50;
	char target[MAX_LEN];
	char targettype[MAX_LEN];
	memset(target, 0, sizeof(char)*MAX_LEN);
	memset(targettype, 0, sizeof(char)*MAX_LEN);
		
	FILE *fpIn = fopen(argv[1], "r");
	
	string outputfilename;
	outputfilename = argv[1];
	outputfilename += "_check_korcode.txt";
	FILE *fpOut = fopen(outputfilename.c_str(), "w");
	
	int len = 0;
	int i = 0;
	int unkonwcnt = 0;
	int logincnt = 0;
	while (fscanf(fpIn, "%d %s", &logincnt, target) != EOF)
	{
		len = strlen(target);
		// �ؽ�Ʈ ������ ���ڰ� ASCII / �ϼ��� �ڵ尡 �ƴѰ�� üũ
		for (i = 0; i < len; i++)
		{
			if (target[i] >= 0 && target[i] <= 127)
			{
				sprintf(targettype, "ASCII");
			}
			else if (target[i] >=-80 && target[i] < -55)
			{
				i++;
				if (i < len && target[i] >=-95 && target[i] < -1)
				{
					sprintf(targettype, "KOR_COM");
				}
			}
			else
			{
				sprintf(targettype, "UNKNOWN_CODE");
				unkonwcnt++;
				break;
			}
		}
		fprintf(fpOut, "%d\t%s\t%s\n", logincnt, target, targettype);
		memset(target, 0, sizeof(char)*MAX_LEN);
		memset(targettype, 0, sizeof(char)*MAX_LEN);
	}
	fprintf(fpOut, "unkowncnt : %d\n", unkonwcnt);
	fclose(fpIn);
	fclose(fpOut);
}

