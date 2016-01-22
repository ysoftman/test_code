////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// DoReMe
////////////////////////////////////////////////////////////////////////////////////
//#pragma comment(linker, "/subsystem:console")	// 콘솔 프로그램 시작시
#pragma comment(linker, "/subsystem:windows")	// 윈도우 프로그램 시작시

#include "DoReMe.h"

#define ID_RADIO1 100
#define ID_RADIO2 101
#define ID_BUTTON_A 110
#define ID_BUTTON_W 111
#define ID_BUTTON_S 112
#define ID_BUTTON_E 113
#define ID_BUTTON_D 114
#define ID_BUTTON_F 115
#define ID_BUTTON_U 116
#define ID_BUTTON_J 117
#define ID_BUTTON_I 118
#define ID_BUTTON_K 119
#define ID_BUTTON_O 120
#define ID_BUTTON_L 121
#define ID_BUTTON_SEMICOLON 122
#define ID_STATIC_UP 130
#define ID_STATIC_DOWN 131
#define ID_STATIC1 150

#define C	523		//Do
#define Cs	554		//Do_Sharp
#define D	587		//Re
#define Ds	622		//Re_Sharp
#define E	659		//Me
#define F	698		//Fa
#define Fs	740		//Fa_Sharp
#define G	784		//So
#define Gs	831		//So_Sharp
#define A	880		//La
#define As	932		//La_Sharp
#define B	988		//Ti
#define C2	1046	//Do2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// mmsystem.h 이 사용하는 winmm.lib 파일 추가
#pragma comment(lib, "winmm")

// PlaySound 함수를 사용하기위해 필요한 헤더 파일
#include <mmsystem.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass = "BILL's DoReMe Windows";

#define MAX_LENGTH 1024

HWND hRadio1 = NULL;
HWND hRadio2 = NULL;
HWND hButtonA = NULL;
HWND hButtonW = NULL;
HWND hButtonS = NULL;
HWND hButtonE = NULL;
HWND hButtonD = NULL;
HWND hButtonF = NULL;
HWND hButtonU = NULL;
HWND hButtonJ = NULL;
HWND hButtonI = NULL;
HWND hButtonK = NULL;
HWND hButtonO = NULL;
HWND hButtonL = NULL;
HWND hButtonSemiColon = NULL;
HWND hStaticBox = NULL;
HWND hStaticUp = NULL;
HWND hStaticDown = NULL;

int nSoundType = 1;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	g_hInst = hInstance;	//WinMain's Instance -> Global Instance
	HWND hWnd;	//This Window Handle(available in WinMain Function)
	MSG Message;	//Message Declare For Message Event
	WNDCLASS WndClass;	//Window Class Register
	WndClass.style=CS_HREDRAW | CS_VREDRAW;	//Window Style(When Horizon And Vertical Move, Redraw Window)
	WndClass.lpfnWndProc=(WNDPROC)WndProc;	//Window Message Process Function
	WndClass.cbClsExtra=0;	//Extra Area
	WndClass.cbWndExtra=0;	//Extra Area
	WndClass.hInstance=hInstance;	//Instance(Windows Class Register)
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//Load Icon(Using LoadIcon Function)
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//Load Cursor(Using LoadCursor Function)
	//WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);	//Window Background Color(Using GetStockObject Function)
	WndClass.hbrBackground=(HBRUSH)GetStockObject(LTGRAY_BRUSH);	//Window Background Color(Using GetStockObject Function)
	WndClass.lpszMenuName=NULL;	//When Use Menu, Menu Name. If Non Menu, NULL
	WndClass.lpszClassName=lpszClass;	//Window Class Name
	RegisterClass(&WndClass);	//Register Window Class For OS

	hWnd=CreateWindow(lpszClass,	//Windows Class Name
		"BYOUNG HOON's DoReMe",	//Window Title Bar Name
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,	//For Full Screen Window Non System Menu and etc...(WS_OVERLAPPEDWINDOW -> Basic Style)
		CW_USEDEFAULT,	//X Vertex(Location)
		CW_USEDEFAULT,	//Y Vertex(Location)
		490,	//Window Width(Scale)
		260,	//Window Height(Scale)
		NULL,	//Parent Window And Child Window Handle(When Use MDI Window Program)
		(HMENU)NULL,	//Window Menu(If Value Is NULL, WndClass Use)
		hInstance,	//Window Program Handle
		NULL);	//CREATESTRUCT Struct Address For Special Purpose(Usually NULL)

	ShowWindow(hWnd, nCmdShow);	//Show Window Method(SW_HIDE, SW_MINIMIZE, SW_RESTORE, SW_SHOW, SW_SHOWNORMAL)

	while(GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);	//WM_KEYDOWN Message Occur, Make WM_CHAR
		DispatchMessage(&Message);	//Message Transfer To WndPro(Window Procedure)
	}
	return Message.wParam;	//Return Message's Addtional Information(exit(0) In DOS)
}

int PlayDoReMi(int key)
{
	switch(key)
	{
	case ID_BUTTON_A:
		{
			if (nSoundType == 1)
			{
				PlaySound((LPCSTR)MAKEINTRESOURCE(IDR_WAVE_DO), NULL, SND_ASYNC | SND_RESOURCE);	
			}
			else if (nSoundType == 2)
			{
				Beep(C, 100);
			}
		}
		return 0;
	case ID_BUTTON_W:
		{
			if (nSoundType == 1)
			{
			}
			else if (nSoundType == 2)
			{
				Beep(Cs, 100);
			}	
		}
		return 0;
	case ID_BUTTON_S:
		{
			if (nSoundType == 1)
			{
				PlaySound((LPCSTR)MAKEINTRESOURCE(IDR_WAVE_RE), NULL, SND_ASYNC | SND_RESOURCE);
			}
			else if (nSoundType == 2)
			{
				Beep(D, 100);
			}
		}
		return 0;
	case ID_BUTTON_E:
		{
			if (nSoundType == 1)
			{
			}	
			else if (nSoundType == 2)
			{
				Beep(Ds, 100);
			}
		}
		return 0;
	case ID_BUTTON_D:
		{
			if (nSoundType == 1)
			{
				PlaySound((LPCSTR)MAKEINTRESOURCE(IDR_WAVE_ME), NULL, SND_ASYNC | SND_RESOURCE);
			}
			else if (nSoundType == 2)
			{
				Beep(E, 100);
			}
		}
		return 0;
	case ID_BUTTON_F:
		{
			if (nSoundType == 1)
			{
				PlaySound((LPCSTR)MAKEINTRESOURCE(IDR_WAVE_FA), NULL, SND_ASYNC | SND_RESOURCE);
			}
			else if (nSoundType == 2)
			{
				Beep(F, 100);
			}	
		}
		return 0;
	case ID_BUTTON_U:
		{
			if (nSoundType == 1)
			{
			}
			else if (nSoundType == 2)
			{
				Beep(Fs, 100);
			}	
		}
		return 0;
	case ID_BUTTON_J:
		{
			if (nSoundType == 1)
			{
				PlaySound((LPCSTR)MAKEINTRESOURCE(IDR_WAVE_SO), NULL, SND_ASYNC | SND_RESOURCE);
			}
			else if (nSoundType == 2)
			{
				Beep(G, 100);
			}
		}
		return 0;
	case ID_BUTTON_I:
		{
			if (nSoundType == 1)
			{
			}
			else if (nSoundType == 2)
			{
				Beep(Gs, 100);
			}
		}
		return 0;
	case ID_BUTTON_K:
		{
			if (nSoundType == 1)
			{
				PlaySound((LPCSTR)MAKEINTRESOURCE(IDR_WAVE_LA), NULL, SND_ASYNC | SND_RESOURCE);
			}
			else if (nSoundType == 2)
			{
				Beep(A, 100);
			}
		}
		return 0;
	case ID_BUTTON_O:
		{
			if (nSoundType == 1)
			{
			}
			else if (nSoundType == 2)
			{
				Beep(As, 100);
			}
		}
		return 0;
	case ID_BUTTON_L:
		{
			if (nSoundType == 1)
			{
				PlaySound((LPCSTR)MAKEINTRESOURCE(IDR_WAVE_TI), NULL, SND_ASYNC | SND_RESOURCE);
			}	
			else if (nSoundType == 2)
			{
				Beep(B, 100);
			}
		}
		return 0;
	case ID_BUTTON_SEMICOLON:
		{
			if (nSoundType == 1)
			{
				PlaySound((LPCSTR)MAKEINTRESOURCE(IDR_WAVE_DO), NULL, SND_ASYNC | SND_RESOURCE);
			}	
			else if (nSoundType == 2)
			{
				Beep(C2, 100);
			}
		}
		return 0;
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)	//Message's Additional Information
{
	switch(iMessage)
	{
	case WM_CREATE:	
		hButtonA = CreateWindow((LPCTSTR)"button", "A", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 80, 40, 40, hWnd, (HMENU)ID_BUTTON_A, g_hInst, NULL);
		hButtonW = CreateWindow((LPCTSTR)"button", "W", WS_CHILD | WS_VISIBLE | WS_BORDER, 40, 30, 40, 40, hWnd, (HMENU)ID_BUTTON_W, g_hInst, NULL);
		hButtonS = CreateWindow((LPCTSTR)"button", "S", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 80, 40, 40, hWnd, (HMENU)ID_BUTTON_S, g_hInst, NULL);
		hButtonE = CreateWindow((LPCTSTR)"button", "E", WS_CHILD | WS_VISIBLE | WS_BORDER, 100, 30, 40, 40, hWnd, (HMENU)ID_BUTTON_E, g_hInst, NULL);
		hButtonD = CreateWindow((LPCTSTR)"button", "D", WS_CHILD | WS_VISIBLE | WS_BORDER, 130, 80, 40, 40, hWnd, (HMENU)ID_BUTTON_D, g_hInst, NULL);
		hButtonF = CreateWindow((LPCTSTR)"button", "F", WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 80, 40, 40, hWnd, (HMENU)ID_BUTTON_F, g_hInst, NULL);
		hButtonU = CreateWindow((LPCTSTR)"button", "U", WS_CHILD | WS_VISIBLE | WS_BORDER, 220, 30, 40, 40, hWnd, (HMENU)ID_BUTTON_U, g_hInst, NULL);
		hButtonJ = CreateWindow((LPCTSTR)"button", "J", WS_CHILD | WS_VISIBLE | WS_BORDER, 250, 80, 40, 40, hWnd, (HMENU)ID_BUTTON_J, g_hInst, NULL);
		hButtonI = CreateWindow((LPCTSTR)"button", "I", WS_CHILD | WS_VISIBLE | WS_BORDER, 280, 30, 40, 40, hWnd, (HMENU)ID_BUTTON_I, g_hInst, NULL);
		hButtonK = CreateWindow((LPCTSTR)"button", "K", WS_CHILD | WS_VISIBLE | WS_BORDER, 310, 80, 40, 40, hWnd, (HMENU)ID_BUTTON_K, g_hInst, NULL);
		hButtonO = CreateWindow((LPCTSTR)"button", "O", WS_CHILD | WS_VISIBLE | WS_BORDER, 340, 30, 40, 40, hWnd, (HMENU)ID_BUTTON_O, g_hInst, NULL);
		hButtonL = CreateWindow((LPCTSTR)"button", "L", WS_CHILD | WS_VISIBLE | WS_BORDER, 370, 80, 40, 40, hWnd, (HMENU)ID_BUTTON_L, g_hInst, NULL);
		hButtonSemiColon = CreateWindow((LPCTSTR)"button", ";", WS_CHILD | WS_VISIBLE | WS_BORDER, 430, 80, 40, 40, hWnd, (HMENU)ID_BUTTON_SEMICOLON, g_hInst, NULL);

		hStaticUp = CreateWindow((LPCTSTR)"static", NULL, WS_CHILD | WS_VISIBLE, 50, 5, 320, 20, hWnd, (HMENU)ID_STATIC_UP, g_hInst, NULL);
		SetWindowText(hStaticUp, "도#        레#                         파#        솔#        라#");

		hStaticDown = CreateWindow((LPCTSTR)"static", NULL, WS_CHILD | WS_VISIBLE, 20, 125, 450, 20, hWnd, (HMENU)ID_STATIC_DOWN, g_hInst, NULL);
		SetWindowText(hStaticDown, "도            레           미           파           솔           라           시          도");

		// 첫번째 라이오 버튼에 WS_GROUP 를 명시하면 그 뒤의 라이오버튼은 하나의 그룹이 된다.
		hRadio1 = CreateWindow((LPCTSTR)"button", "음성", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_AUTORADIOBUTTON | WS_GROUP, 10, 180, 85, 25, hWnd, (HMENU)ID_RADIO1, g_hInst, NULL);
		hRadio2 = CreateWindow((LPCTSTR)"button", "Beep", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_AUTORADIOBUTTON, 10, 205, 85, 25, hWnd, (HMENU)ID_RADIO2, g_hInst, NULL);

		hStaticBox = CreateWindow((LPCTSTR)"static", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 180, 350, 50, hWnd, (HMENU)ID_STATIC1, g_hInst, NULL);
		SetWindowText(hStaticBox, "★ 어린이를 위한 키보드 피아노 사용법★\n - 음성 또는 Beep 눌러 선택한다.\n - 마우스로 클릭하거나 해당키를 누른다.");

		CheckRadioButton(hWnd, ID_RADIO1, ID_RADIO2, ID_RADIO1);

		ShowWindow(hButtonW, SW_HIDE);
		ShowWindow(hButtonE, SW_HIDE);
		ShowWindow(hButtonU, SW_HIDE);
		ShowWindow(hButtonI, SW_HIDE);
		ShowWindow(hButtonO, SW_HIDE);
		ShowWindow(hStaticUp, SW_HIDE);

		SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
		return 0;

	case WM_KEYDOWN:
		if (wParam == 'a' || wParam == 'A') PlayDoReMi(ID_BUTTON_A);
		if (wParam == 'w' || wParam == 'W') PlayDoReMi(ID_BUTTON_W);
		if (wParam == 's' || wParam == 'S') PlayDoReMi(ID_BUTTON_S);
		if (wParam == 'e' || wParam == 'E') PlayDoReMi(ID_BUTTON_E);
		if (wParam == 'd' || wParam == 'D') PlayDoReMi(ID_BUTTON_D);
		if (wParam == 'f' || wParam == 'F') PlayDoReMi(ID_BUTTON_F);
		if (wParam == 'u' || wParam == 'U') PlayDoReMi(ID_BUTTON_U);
		if (wParam == 'j' || wParam == 'J') PlayDoReMi(ID_BUTTON_J);
		if (wParam == 'i' || wParam == 'I') PlayDoReMi(ID_BUTTON_I);
		if (wParam == 'k' || wParam == 'K') PlayDoReMi(ID_BUTTON_K);
		if (wParam == 'o' || wParam == 'O') PlayDoReMi(ID_BUTTON_O);
		if (wParam == 'l' || wParam == 'L') PlayDoReMi(ID_BUTTON_L);
		if (wParam == 186) PlayDoReMi(ID_BUTTON_SEMICOLON);

		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam))	// 컨트롤 ID
		{
		case ID_RADIO1:
			{
				nSoundType = 1;
				ShowWindow(hButtonW, SW_HIDE);
				ShowWindow(hButtonE, SW_HIDE);
				ShowWindow(hButtonU, SW_HIDE);
				ShowWindow(hButtonI, SW_HIDE);
				ShowWindow(hButtonO, SW_HIDE);
				ShowWindow(hStaticUp, SW_HIDE);
			}
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_RADIO2:
			{
				nSoundType = 2;
				ShowWindow(hButtonW, SW_SHOW);
				ShowWindow(hButtonE, SW_SHOW);
				ShowWindow(hButtonU, SW_SHOW);
				ShowWindow(hButtonI, SW_SHOW);
				ShowWindow(hButtonO, SW_SHOW);
				ShowWindow(hStaticUp, SW_SHOW);
			}
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_A:
			PlayDoReMi(ID_BUTTON_A);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_W:
			PlayDoReMi(ID_BUTTON_W);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_S:
			PlayDoReMi(ID_BUTTON_S);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_E:
			PlayDoReMi(ID_BUTTON_E);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_D:
			PlayDoReMi(ID_BUTTON_D);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_F:
			PlayDoReMi(ID_BUTTON_F);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_U:
			PlayDoReMi(ID_BUTTON_U);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_J:
			PlayDoReMi(ID_BUTTON_J);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_I:
			PlayDoReMi(ID_BUTTON_I);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_K:
			PlayDoReMi(ID_BUTTON_K);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_O:
			PlayDoReMi(ID_BUTTON_O);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_L:
			PlayDoReMi(ID_BUTTON_L);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		case ID_BUTTON_SEMICOLON:
			PlayDoReMi(ID_BUTTON_SEMICOLON);
			SetFocus(hWnd);	// WM_KEYDOWN 를 받을 수 있도록 하기 위해서 
			return 0;
		}
	case WM_DESTROY:		
		//Send WM_QUIT To GetMessage Function
		//GetMessage Return FALSE And Exit While-Loop. Therefore Quit Window Program
		PostQuitMessage(0);	//WM_QUIT	
		return 0;
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));	//Default Message Process
}
