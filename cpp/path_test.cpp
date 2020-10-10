// ysoftman
// 현재 경로 파악 및 설정
#if (defined _WIN32) || (defined _WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>
#include <conio.h>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
	char curpath[100];
	memset(curpath, 0, sizeof(char) * 100);
#ifdef _WIN32
	// 현재 경로 파악
	GetCurrentDirectory(100, curpath);
	fprintf(stderr, "CurrentPath = %s\n", curpath);
	// 현재 경로 재 설정
	SetCurrentDirectory("../");
	GetCurrentDirectory(100, curpath);
	fprintf(stderr, "CurrentPath = %s\n", curpath);
	// 현재 모듈 경로 파악
	GetModuleFileName(0, curpath, 1024);
	fprintf(stderr, "CurrentPath = %s\n", curpath);
#endif
}
