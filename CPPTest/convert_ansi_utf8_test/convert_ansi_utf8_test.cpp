////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// MultiByte UTF8 <-> MultiByte ANSI(cp949, euc-kr, euc-jp...) ��ȯ
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
	// CP_ACP (current Windows ANSI code page) �� ���� �����쿡���� ascii, �ѱ� �����쿡���� euc-kr, �Ϻ� �����쿡���� euc-jp �� �۵�
	// ���ڵ� ��� : utf-8(��Ƽ����Ʈ) -> �����ڵ� -> ANSI(euc-kr, euc-kr...) (��Ƽ����Ʈ)
	// multibyte UTF8 �� ũ�� �ľ�
	int nwcUTF8Size = MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, NULL, NULL);
	// multibyte UTF8 �� widechar UTF8 �� ��ȯ
	WCHAR *pwcUTF8 = new WCHAR[nwcUTF8Size];
	memset(pwcUTF8, 0, sizeof(WCHAR)*nwcUTF8Size);
	MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, pwcUTF8, nwcUTF8Size);
	// widechar UTF8 �� NULL �� �������� 
	pwcUTF8[nwcUTF8Size-1] = L'\0';
	// widechar UTF8 ũ�� �ľ�
	int nANSISize = WideCharToMultiByte(CP_ACP, 0, pwcUTF8, -1, NULL, NULL, NULL, NULL);
	char *pANSI = new char[nANSISize];
	memset(pANSI, 0, sizeof(char)*(nANSISize));
	// widechar UTF8 �� multibyte ANSI(euc-kr, euc-kr...) �� ��ȯ
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
	// CP_ACP (current Windows ANSI code page) �� ���� �����쿡���� ascii, �ѱ� �����쿡���� euc-kr, �Ϻ� �����쿡���� euc-jp �� �۵�
	// ���ڵ� ��� : ANSI(euc-kr, euc-kr...) (��Ƽ����Ʈ) -> �����ڵ� -> utf-8(��Ƽ����Ʈ)
	// multibyte ANSI(euc-kr, euc-kr...) �� ũ�� �ľ�
	int nwcANSISize = MultiByteToWideChar(CP_ACP, 0, pANSI, -1, NULL, NULL);
	// multibyte ANSI(euc-kr, euc-kr...) �� widechar ANSI(euc-kr, euc-kr...) �� ��ȯ
	WCHAR *pwcANSI = new WCHAR[nwcANSISize];
	memset(pwcANSI, 0, sizeof(WCHAR)*nwcANSISize);
	MultiByteToWideChar(CP_ACP, 0, pANSI, -1, pwcANSI, nwcANSISize);
	// widechar ANSI(euc-kr, euc-kr...) �� NULL �� �������� 
	pwcANSI[nwcANSISize-1] = L'\0';
	// widechar ANSI(euc-kr, euc-kr...) ũ�� �ľ�
	int UTF8Size = WideCharToMultiByte(CP_UTF8, 0, pwcANSI, -1, NULL, NULL, NULL, NULL);
	char *pUTF8 = new char[UTF8Size];
	memset(pUTF8, 0, sizeof(char)*(UTF8Size));
	// widechar ANSI(euc-kr, euc-kr...) �� multibyte UTF8 �� ��ȯ
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

	char *szTestString = "Yoon,ByoungHoon ������ ���ڵ� �׽�Ʈ...";
	printf("Default: %s\n", szTestString);
	fprintf(fp, "%s\n", szTestString);

	char *szUTF8 = ANSIToUTF8(szTestString);
	printf("UTF8   : %s\n", szUTF8);
	fprintf(fp, "UTF8: %s\n", szUTF8);

	char *szANSI = UTF8ToANSI(szUTF8);
	printf("ANSI   : %s\n", szANSI);
	fprintf(fp, "ANSI: %s\n", szANSI);

	delete[] szUTF8;
	delete[] szANSI;

	fclose(fp);

	return 0;
}


