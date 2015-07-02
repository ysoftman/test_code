////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// URL 인코딩/디코딩 테스트
////////////////////////////////////////////////////////////////////////////////////

#include "EncURL.h"

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

