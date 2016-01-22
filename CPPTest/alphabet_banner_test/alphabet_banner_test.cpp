////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// �빮�� ���ĺ� �ϳ��� �Է� �Ǿ��� �� ���ڸ� �迭�Ͽ� 
// �Էµ� ���ڸ� �׷������� ǥ���ϴ� ����� ���� => BANNER
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>

// �ڵ忡 �°� ����ϱ�
void Draw(char code[])
{
	int i;
	int j;
	int k;

	// ù��° ���� ���� �� 
	for (i=0; i<code[0]; i++)
	{
		// �ι��� �����ʹ� ���θ��� ����� X ǥ���ϱ�
		for (j=1; j<20; j++)
		{
			if (code[j] == NULL)
			{
				break;
			}
			
			// ���� ����
			if (code[j] == 'x')
			{
				// ��� ���� ���ΰ�?
				for (k=0; k<code[j+1]; k++)
				{
					printf("x");
				}
			}
			if (code[j] == 'b')
			{
				for (k=0; k<code[j+1]; k++)
				{
					printf(" ");
				}
			}
		}

		printf("\n");
	}
}

// �ڵ� �ʱ�ȭ
void InitCode(char code[])
{
	int i;

	for (i=0; i<20; i++)
	{
		code[i] = NULL;
	}
}

void main()
{
	char code[20];
	char str;

	printf("\nInput Character I: ");
	scanf("%c", &str);

	switch(str)
	{
	case 'I':
		code[0] = 3;	// ���� ��
		code[1] = 'x';	// ���� ����
		code[2] = 9;	// ��� ���� ���ΰ�?
		Draw(code);
		InitCode(code);
		code[0] = 6;
		code[1] = 3;
		code[2] = 'b';
		code[3] = 3;
		code[4] = 'x';
		code[5] = 3;
		code[7] = 'b';
		Draw(code);
		InitCode(code);
		code[0] = 3;
		code[1] = 'x';
		code[2] = 9;
		Draw(code);
		InitCode(code);
		break;
	}	
}

