////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Register Editor
////////////////////////////////////////////////////////////////////////////////////
#if (defined _WIN32) || (defined _WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
	HKEY r_key;
	r_key = NULL;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon",
		NULL,
		KEY_ALL_ACCESS,
		&r_key);
	RegSetValueEx(r_key,
		"LegalNoticeCaption",
		NULL,
		REG_SZ,
		(unsigned char*)"★ysoftman★",
		10);
	RegSetValueEx(r_key,
		"LegalNoticeText",
		NULL,
		REG_SZ,
		(unsigned char*)"공지 테스트입니다.... 윤병훈", 
		1000);
	RegCloseKey(r_key);
	return 0;
#endif
}

