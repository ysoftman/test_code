////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// NumberTalk
////////////////////////////////////////////////////////////////////////////////////
//#pragma comment(linker, "/subsystem:console")	// 콘솔 프로그램 시작시
#pragma comment(linker, "/subsystem:windows")	// 윈도우 프로그램 시작시

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass = "BILL's NumberTalk Windows";

#define MAX_LENGTH 1024

HWND hRadio1 = NULL;
HWND hRadio2 = NULL;
HWND hEditBoxInput = NULL;
HWND hEditBoxOutput = NULL;
HWND hStaticBox = NULL;

char szInput[MAX_LENGTH];
char szTemp[MAX_LENGTH];
char szOutput[MAX_LENGTH];
int nMode = 1;

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
		"BYOUNG HOON's NumberTalk",	//Window Title Bar Name
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,	//For Full Screen Window Non System Menu and etc...(WS_OVERLAPPEDWINDOW -> Basic Style)
		CW_USEDEFAULT,	//X Vertex(Location)
		CW_USEDEFAULT,	//Y Vertex(Location)
		800,	//Window Width(Scale)
		250,	//Window Height(Scale)
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
#define ID_RADIO1 100
#define ID_RADIO2 101
#define ID_EDITBOX1 110
#define ID_EDITBOX2 111
#define ID_STATIC1 120
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)	//Message's Additional Information
{
	switch(iMessage)
	{
	case WM_CREATE:	
		// 첫번째 라이오 버튼에 WS_GROUP 를 명시하면 그 뒤의 라이오버튼은 하나의 그룹이 된다.
		hRadio1 = CreateWindow((LPCTSTR)"button", "모드1(문자->숫자)", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_AUTORADIOBUTTON | WS_GROUP, 10, 10, 250, 25, hWnd, (HMENU)ID_RADIO1, g_hInst, NULL);
		hRadio2 = CreateWindow((LPCTSTR)"button", "모드2(숫자->문자)", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_AUTORADIOBUTTON, 300, 10, 250, 25, hWnd, (HMENU)ID_RADIO2, g_hInst, NULL);

		hEditBoxInput = CreateWindow((LPCTSTR)"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 40, 750, 25, hWnd, (HMENU)ID_EDITBOX1, g_hInst, NULL);
		hEditBoxOutput = CreateWindow((LPCTSTR)"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 10, 70, 750, 25, hWnd, (HMENU)ID_EDITBOX2, g_hInst, NULL);

		hStaticBox = CreateWindow((LPCTSTR)"static", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 110, 750, 80, hWnd, (HMENU)ID_STATIC1, g_hInst, NULL);
		SetWindowText(hStaticBox, "★ 숫자대화 프로그램 사용방법 ★\n-ABC ...  는 각각 ASCII 로 65 66 67 ...  에 해당된다.\n-변환모드를 선택하고 입력란에 입력한다.\n-HyunA Zzang!!! 은 72 121 117 110 65 32 90 122 97 110 103 33 33 33  와 같다");

		CheckRadioButton(hWnd, ID_RADIO1, ID_RADIO2, ID_RADIO1);
		return 0;

	case WM_COMMAND:
		switch(LOWORD(wParam))	// 컨트롤 ID
		{
		case ID_RADIO1:
			{
				nMode = 1;
			}
			return 0;
		case ID_RADIO2:
			{
				nMode = 2;
			}
			return 0;
		case ID_EDITBOX1:
			switch (HIWORD(wParam))		// 통지 코드
			{
			case EN_CHANGE:
				GetWindowText(hEditBoxInput, szInput, MAX_LENGTH);

				// 출력 초기화
				memset(szOutput, 0, MAX_LENGTH);
				int i = 0;
				int j = 0;
				int num = 0;
				while (szInput[i] != NULL)
				{
					memset(szTemp, 0, MAX_LENGTH);
					// 문자를 숫자로바꾸기
					if (nMode == 1)
					{
						// ASCII 일경우
						if (szInput[i] >=0 && szInput[i] <= 255)
						{
							sprintf_s(szTemp, MAX_LENGTH, "%d ", szInput[i]);
						}
						i++;
					}
					// 숫자를 문자로바꾸기
					else if (nMode == 2)
					{
						j = 0;
						while (szInput[i] != 32 && szInput[i] != NULL)
						{
							szTemp[j] = szInput[i];
							j++, i++;
							szTemp[j] = NULL;
						}
						if (szInput[i] != NULL)
						{
							i++;
						}
						// 문자를 숫자로바꾸기(참고로 문자라면 숫자로 바꿀수 없다.)
						num = atoi(szTemp);

						// 10진수 숫자를 영어로 바꾸기
						sprintf_s(szTemp, MAX_LENGTH, "%c", num);
					}
					// 결과 스트링에 추가하기
					strcat_s(szOutput, MAX_LENGTH, szTemp);
				}
				SetWindowText(hEditBoxOutput, szOutput);
			}
			return 0;
		case ID_EDITBOX2:
			{
			}
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
