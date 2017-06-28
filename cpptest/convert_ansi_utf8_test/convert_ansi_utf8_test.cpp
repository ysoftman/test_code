////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// MultiByte UTF8 <-> MultiByte ANSI(cp949, euc-kr, euc-jp...) 변환
////////////////////////////////////////////////////////////////////////////////////
#if (defined _WIN32) || (defined _WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <windows.h>

char *UTF8ToANSI(char *pUTF8)
{
	if (pUTF8 == NULL)
	{
		return NULL;
	}
	char *pResult = NULL;
#if defined(_WIN32) || defined(_WIN64)
	// CP_ACP (current Windows ANSI code page) 는 영어 윈도우에서는 ascii, 한글 윈도우에서는 euc-kr, 일본 윈도우에서는 euc-jp 로 작동
	// 인코딩 방법 : utf-8(멀티바이트) -> 유니코드 -> ANSI(euc-kr, euc-kr...) (멀티바이트)
	// multibyte UTF8 의 크기 파악
	int nwcUTF8Size = MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, NULL, NULL);
	// multibyte UTF8 을 widechar UTF8 로 변환
	WCHAR *pwcUTF8 = new WCHAR[nwcUTF8Size];
	memset(pwcUTF8, 0, sizeof(WCHAR)*nwcUTF8Size);
	MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, pwcUTF8, nwcUTF8Size);
	// widechar UTF8 이 NULL 로 끝나도록 
	pwcUTF8[nwcUTF8Size-1] = L'\0';
	// widechar UTF8 크기 파악
	int nANSISize = WideCharToMultiByte(CP_ACP, 0, pwcUTF8, -1, NULL, NULL, NULL, NULL);
	char *pANSI = new char[nANSISize];
	memset(pANSI, 0, sizeof(char)*(nANSISize));
	// widechar UTF8 을 multibyte ANSI(euc-kr, euc-kr...) 로 변환
	if (WideCharToMultiByte(CP_ACP, 0, pwcUTF8, -1, pANSI, nANSISize, NULL, NULL) == 0)
	{
		delete[] pANSI;
		pANSI = NULL;
	}
	delete[] pwcUTF8;
	pResult = pANSI;
#else
#endif
	return pResult;
}

char *ANSIToUTF8(char *pANSI)
{
	if (pANSI == NULL)
	{
		return NULL;
	}
	char *pResult = NULL;
#if defined(_WIN32) || defined(_WIN64)
	// CP_ACP (current Windows ANSI code page) 는 영어 윈도우에서는 ascii, 한글 윈도우에서는 euc-kr, 일본 윈도우에서는 euc-jp 로 작동
	// 인코딩 방법 : ANSI(euc-kr, euc-kr...) (멀티바이트) -> 유니코드 -> utf-8(멀티바이트)
	// multibyte ANSI(euc-kr, euc-kr...) 의 크기 파악
	int nwcANSISize = MultiByteToWideChar(CP_ACP, 0, pANSI, -1, NULL, NULL);
	// multibyte ANSI(euc-kr, euc-kr...) 을 widechar ANSI(euc-kr, euc-kr...) 로 변환
	WCHAR *pwcANSI = new WCHAR[nwcANSISize];
	memset(pwcANSI, 0, sizeof(WCHAR)*nwcANSISize);
	MultiByteToWideChar(CP_ACP, 0, pANSI, -1, pwcANSI, nwcANSISize);
	// widechar ANSI(euc-kr, euc-kr...) 이 NULL 로 끝나도록 
	pwcANSI[nwcANSISize-1] = L'\0';
	// widechar ANSI(euc-kr, euc-kr...) 크기 파악
	int UTF8Size = WideCharToMultiByte(CP_UTF8, 0, pwcANSI, -1, NULL, NULL, NULL, NULL);
	char *pUTF8 = new char[UTF8Size];
	memset(pUTF8, 0, sizeof(char)*(UTF8Size));
	// widechar ANSI(euc-kr, euc-kr...) 을 multibyte UTF8 로 변환
	if (WideCharToMultiByte(CP_UTF8, 0, pwcANSI, -1, pUTF8, UTF8Size, NULL, NULL) == 0)
	{
		delete[] pUTF8;
		pUTF8 = NULL;
	}
	delete[] pwcANSI;
	pResult = pUTF8;
#else
#endif
	return pResult;
}

int main()
{
	FILE *fp = fopen("EncodingTest.txt", "w");

	char TestString[50] = "Yoon,ByoungHoon 윤병훈 인코딩 테스트...";
	char *pTestString = TestString;
	printf("Default: %s\n", pTestString);
	fprintf(fp, "%s\n", pTestString);

	char *pANSI = UTF8ToANSI(pTestString);
	printf("ANSI   : %s\n", pANSI);
	fprintf(fp, "ANSI: %s\n", pANSI);

	char *pUTF8 = ANSIToUTF8(pANSI);
	printf("UTF8   : %s\n", pUTF8);
	fprintf(fp, "UTF8: %s\n", pUTF8);

	delete[] pUTF8;
	delete[] pANSI;

	fclose(fp);

	return 0;
}


