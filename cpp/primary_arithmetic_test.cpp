////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Primary Arithmetic
// 두 수의 덧셈에서 자리올림(각 단위의 합이 10이 넘을 경우 carry 발생)의 발생 알려주기
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int main()
{
	// 두 수의 단위 자리는 최대 10자리로 제한
	int num1[10];
	int num2[10];

	int i1, i2, d1, d2, carry, carrycnt;
	char line[256];
	char *c;
	

	printf("Primary Arithmetic...\n");
	printf("[Input 0 0 to Exit]\n");
	while (1)
	{
		printf("Input Two Num : ");
		// 입력된 두 수의 각 단위 당 수를 각각 num1와 num2에 얻어오기
		gets(line);
		i1 = 0;
		i2 = 0;
		c = line;
		// 공백은 무시하기
		while (*c == ' ')
		{
			c++;
		}
		// 첫 번째 수 읽어 오기
		while (*c >= '0' && *c <= '9')
		{
			num1[i1++] = *(c++) - '0';
		}
		// 공백은 무시하기
		while (*c == ' ')
		{
			c++;
		}
		// 두 번째 수 읽어 오기
		while (*c >= '0' && *c <= '9')
		{
			num2[i2++] = *(c++) - '0';
		}
		// 아무수도 입력된 것이 없으면 종료
		if (num1[0] == 0 && num2[0] == 0)
		{
			printf ("Exit Program...\n");
			break;
		}
		
		carry = 0;
		carrycnt = 0;

		// 두 수의 일의 자리 부터 시작
		// 마지막에 들어간 배열의 수 일의 자리이다.
		i1--;
		i2--;

		while (i1 >= 0 || i2 >= 0)
		{
			// 두 수의 같은 자리에서 수를 얻어오기
			d1 = (i1 >= 0 ? num1[i1] : 0);
			d2 = (i2 >= 0 ? num2[i2] : 0);
			// 더해서 10이 넘으면 발생
			// 이전 자리에서 캐리가 올라올 수 있기 때문에 항상 케리를 고려해야함(더한다)
			if (d1 + d2 + carry >= 10)
			{
				carry = 1;
				carrycnt++;
			}
			else
			{
				carry = 0;
			}
			i1--;
			i2--;
		}

		// 출력하기
		if (carrycnt >= 1)
		{
			printf("%d Carry Operation.\n", carrycnt);
		}
		else
		{
			printf("No Carry Operation.\n");
		}
	} // End of while (1)

	return 0;
}

