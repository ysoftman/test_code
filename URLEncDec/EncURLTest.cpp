////////////////////////////////////////////////////////////////////////////////////
// title : EncURLTest
// desc : URL ���ڵ�/���ڵ� �׽�Ʈ
// author : ysoftman
// os : Windows, Linux
////////////////////////////////////////////////////////////////////////////////////

#include "EncURL.h"

int main()
{
	//char *pInput = "�ѱ� qwer 1234 QWER !@#$";
	char szInput[100] = "�ѱ� qwer 1234 QWER !@#$";
	char *pInput = szInput;

	string Result;
	
	fprintf(stdout, "input = %s\n", pInput);
	
	Result = URLEncoding(pInput);
	fprintf(stdout, "[URL Encoding] = %s\n", Result.c_str());
	
	Result = URLDecoding((char*)Result.c_str());
	fprintf(stdout, "[URL Decoding] = %s\n", Result.c_str());

	return 0;
}

