////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// URL 인코딩/디코딩
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string>

using namespace std;

// 16진수 문자값을 10진수 문자값으로 변환
char hex2int(char input)
{
	// 숫자
	if (input >= '0' && input <= '9')
	{
		return input - '0';
	}
	// 대문자
	else if (input >= 'A' && input <= 'Z')
	{
		return input - 'A' + 10;
	}
	// 소문자
	else if (input >= 'a' && input <= 'z')
	{
		return input - 'a' + 10;
	}
	return 0;
}

// 10진수 문자값을 16진수 문자값으로 변환
char int2hex(char input)
{
	char hex[17] = "0123456789abcdef";
	return hex[0x0f & input];
}

// URL 인코딩 한다.
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
		// ASCII 대소문자와 숫자인 경우만 그대로 저장
		if ((temp>= '0' && temp <= '9') ||
			(temp >= 'a' && temp <= 'z') ||
			(temp >= 'A' && temp <= 'Z'))
		{
			result += temp;
		}
		// 공백은 + 로
		else if (temp == ' ')
		{
			result += "+";
		}
		// 아니면 % 와 2자리 16진수 문자값으로 만들어 저장
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

// URL 디코딩 한다.
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
		// ASCII 대소문자와 숫자인 경우만 그대로 저장
		if ((temp >= '0' && temp <= '9') ||
			(temp >= 'a' && temp <= 'z') ||
			(temp >= 'A' && temp <= 'Z'))
		{
			result += temp;
		}
		// + 는 공백으로 저장
		else if (temp == '+')
		{
			result += " ";
		}
		// % 로 시작되면 % 빼고 2자리 16진수 문자값을 10진수 문자값으로 변경하여 저장
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

int main()
{
	//char *pInput = "한글 qwer 1234 QWER !@#$";
	char szInput[100] = "한글 qwer 1234 QWER !@#$";
	char *pInput = szInput;

	string Result;
	
	fprintf(stdout, "input = %s\n", pInput);
	
	Result = URLEncoding(pInput);
	fprintf(stdout, "[URL Encoding] = %s\n", Result.c_str());
	
	Result = URLDecoding((char*)Result.c_str());
	fprintf(stdout, "[URL Decoding] = %s\n", Result.c_str());

	return 0;
}

