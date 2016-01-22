////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Palindrome
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>


int isPalindrome(char *str);

void main()
{
	char input_string[10];
	
	// 1 : Palindrome
	// 0 : not
	int chk_result = 0;	

	printf("Input String(length 10) to Verify Palindrome :  ");
	scanf("%s", input_string);

	chk_result = isPalindrome(input_string);

	if (chk_result == 1)
	{
		printf("\n\n[Result]%s is a Palindrome\n", input_string);
	}
	else if (chk_result == 0)
	{
		printf("\n\n[Result]%s is not a Palindrome\n.", input_string);
	}

}

int isPalindrome(char *str)
{
	int index;
	int str_len = strlen(str);
	int pivot = str_len / 2;

	for (index=0; index<pivot; index++)
	{
		// ���ڿ��� ó���� ���� �� -> ������ ������� �˻�
		if (str[index] == str[str_len-1-index])
		{
			printf("\n%c and %c are same", str[index], str[str_len-1-index]);
		}
		else
		{
			printf("\n%c and %c are different", str[index], str[str_len-1-index]);
			// �ٸ� ����  �߰� -> ���̻� �˻����� �ʰ� ����(�Ӹ������ �ƴ϶�� �Ǵ�)
			return 0;
		}
	}
	// �˻��� �Ӹ�����̴�
	return 1;
}


