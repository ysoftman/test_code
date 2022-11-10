////////////////////////////////////////////////////////////////////////////////////
// title : EncURL
// desc : URL ���ڵ�/���ڵ� �Լ� ����
// author : ysoftman
// os : Windows, Linux
////////////////////////////////////////////////////////////////////////////////////

#include "EncURL.h"

// 16���� ���ڰ��� 10���� ���ڰ����� ��ȯ
char hex2int(char input)
{
	// ����
	if (input >= '0' && input <= '9')
	{
		return input - '0';
	}
	// �빮��
	else if (input >= 'A' && input <= 'Z')
	{
		return input - 'A' + 10;
	}
	// �ҹ���
	else if (input >= 'a' && input <= 'z')
	{
		return input - 'a' + 10;
	}
	return 0;
}

// 10���� ���ڰ��� 16���� ���ڰ����� ��ȯ
char int2hex(char input)
{
	char hex[17] = "0123456789abcdef";
	return hex[0x0f & input];
}

// URL ���ڵ� �Ѵ�.
string URLEncoding(char *pIn)
{
	if (pIn == 0)
	{
		return 0;
	}

	string result;
	char temp = 0;
	while (*pIn != 0)
	{
		temp = *pIn;
		// ASCII ��ҹ��ڿ� ������ ��츸 �״�� ����
		if ((temp>= '0' && temp <= '9') ||
			(temp >= 'a' && temp <= 'z') ||
			(temp >= 'A' && temp <= 'Z'))
		{
			result += temp;
		}
		// ������ + ��
		else if (temp == ' ')
		{
			result += "+";
		}
		// �ƴϸ� % �� 2�ڸ� 16���� ���ڰ����� ����� ����
		else
		{
			result += "%";
			result += int2hex(temp >> 4);
			result += int2hex(temp);
		}
		pIn++;
	}

	return result;
}

// URL ���ڵ� �Ѵ�.
string URLDecoding(char *pIn)
{
	if (pIn == 0)
	{
		return 0;
	}

	string result;
	char temp = 0;
	while (*pIn != 0)
	{
		temp = *pIn;
		// ASCII ��ҹ��ڿ� ������ ��츸 �״�� ����
		if ((temp >= '0' && temp <= '9') ||
			(temp >= 'a' && temp <= 'z') ||
			(temp >= 'A' && temp <= 'Z'))
		{
			result += temp;
		}
		// + �� �������� ����
		else if (temp == '+')
		{
			result += " ";
		}
		// % �� ���۵Ǹ� % ���� 2�ڸ� 16���� ���ڰ��� 10���� ���ڰ����� �����Ͽ� ����
		else if (temp == '%')
		{
			char buf = 0;
			pIn++;
			temp = *pIn;
			buf = hex2int(temp);
			
			pIn++;
			temp = *pIn;
			buf = buf << 4 | hex2int(temp);

			result += buf;			
		}
		pIn++;
	}

	return result;
}

