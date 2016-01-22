// ysoftman
// RandomName - 랜덤 이름 만들기(한글)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void make_KOR_COM_CODE()
{
	char ch[3] = "히";
	int i;
	int j;
	int a=0;

	FILE *fp;
	fp = fopen("kor_com_code.txt", "w");

	//0xb0 = 176 : 1바이트로 읽어 오면 오버플로우, 따라서 176-256=-80
	//0xc9 = 201 : 1바이트로 읽어 오면 오버플로우, 따라서 201-256=-55
	//0xa1 = 161 : 1바이트로 읽어 오면 오버플로우, 따라서 161-256=-95
	//0xff = 255 : 1바이트로 읽어 오면 오버플로우, 따라서 255-256=-1
	//for (i=0xb0; i<0xc9; i++)
	for (i=-80; i<-55; i++)
	{
		//for (j=0xa1; j<0xff; j++)
		for (j=-95; j<-1; j++)
		{
			ch[0] = i;
			ch[1] = j;

			printf("%s\n", ch);
			fprintf(fp, "%s\n", ch);

			a++;
		}
	}
	printf("%d", a);
	fclose(fp);
}

int main()
{
	//make_KOR_COM_CODE();

	char szFirstName[10];
	char szMiddleName[3];
	char szLastName[3];
	memset(szFirstName, 0, 10);
	memset(szMiddleName, 0, 3);
	memset(szLastName, 0, 3);

	printf("성 입력:");
	scanf("%s", &szFirstName);
	printf("중간글자 입력(랜덤생성을 원하면 0 입력):");
	scanf("%s", &szMiddleName);
	printf("마지막글자 입력(랜덤생성을 원하면 0 입력):");
	scanf("%s", &szLastName);

	bool bMiddleRandom = false;
	bool bLastRandom = false;
	if (szMiddleName[0] == '0')
	{
		bMiddleRandom = true;
	}
	if (szLastName[0] == '0')
	{
		bLastRandom = true;
	}
	srand(time(NULL));

	int num1, num2, num3, num4;


	FILE *fp;
	fp = fopen("name_output.txt", "w");


	//0xb0 = 176 : 1바이트로 읽어 오면 오버플로우, 따라서 176-256=-80
	//0xc9 = 201 : 1바이트로 읽어 오면 오버플로우, 따라서 201-256=-55
	//0xa1 = 161 : 1바이트로 읽어 오면 오버플로우, 따라서 161-256=-95
	//0xff = 255 : 1바이트로 읽어 오면 오버플로우, 따라서 255-256=-1
	for (int i = 0; i < 1000; i++)
	{

		if (bMiddleRandom)
		{
			while (true)
			{
				num1 = rand() * -1;
				if (num1>=-80 && num1<-55)
				{				
					break;
				}
			}
			while (true)
			{
				num2 = rand() * -1;
				if (num2>=-95 && num2<-1)
				{				
					break;
				}
			}
			szMiddleName[0] = num1;
			szMiddleName[1] = num2;
		}

		if (bLastRandom)
		{
			while (true)
			{
				num3 = rand() * -1;
				if (num3>=-80 && num3<-55)
				{
					break;
				}
			}
			while (true)
			{
				num4 = rand() * -1;

				if (num4>=-95 && num4<-1)
				{
					break;
				}
			}
			szLastName[0] = num3;
			szLastName[1] = num4;
		}

		//printf("%s%s(%d%d)%s(%d%d)\n", szFirstName, szMiddleName, num1,num2, szLastName, num3,num4);
		printf("%s%s%s\n", szFirstName, szMiddleName, szLastName);
		fprintf(fp, "%s%s%s\n", szFirstName, szMiddleName, szLastName);
	}

	fclose(fp);

	return true;


}

