////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Number Yagu Game
////////////////////////////////////////////////////////////////////////////////////
//#pragma comment(linker, "/subsystem:console")	// 콘솔 프로그램 시작시
#pragma comment(linker, "/subsystem:windows")	// 윈도우 프로그램 시작시

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ID_BUTTON_STARAT 100
#define ID_BUTTON_INPUT 101
#define ID_EDITBOX1 110
#define ID_STATIC1 120

#define MAX_LENGTH 1024
#define NUMBER_LENGTH 4

HWND hButtonStart = NULL;
HWND hButtonInput = NULL;
HWND hEditBoxInput = NULL;
HWND hStaticOutput = NULL;


char szInput[MAX_LENGTH];
char szStatus[MAX_LENGTH];
char szWinLose[MAX_LENGTH];

int nCorrectNumber[NUMBER_LENGTH];
int nUserNumber[NUMBER_LENGTH];
int nCnt = 0;
int nWin = 0;
int nLose = 0;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass = "Number Yagu Game";

HWND hMainWindow = NULL;
WNDPROC wndprocEditBox;
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
		lpszClass,	//Window Title Bar Name
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,	//For Full Screen Window Non System Menu and etc...(WS_OVERLAPPEDWINDOW -> Basic Style)
		CW_USEDEFAULT,	//X Vertex(Location)
		CW_USEDEFAULT,	//Y Vertex(Location)
		290,	//Window Width(Scale)
		670,	//Window Height(Scale)
		NULL,	//Parent Window And Child Window Handle(When Use MDI Window Program)
		(HMENU)NULL,	//Window Menu(If Value Is NULL, WndClass Use)
		hInstance,	//Window Program Handle
		NULL);	//CREATESTRUCT Struct Address For Special Purpose(Usually NULL)

	// 기본윈도우 핸들 전역변수에 저장
	hMainWindow = hWnd;
	ShowWindow(hWnd, nCmdShow);	//Show Window Method(SW_HIDE, SW_MINIMIZE, SW_RESTORE, SW_SHOW, SW_SHOWNORMAL)

	while(GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);	//WM_KEYDOWN Message Occur, Make WM_CHAR
		DispatchMessage(&Message);	//Message Transfer To WndPro(Window Procedure)
	}
	return Message.wParam;	//Return Message's Additional Information(exit(0) In DOS)
}

// EditBox 용 프로시져
LRESULT CALLBACK EditBoxProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)	//Message's Additional Information
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		// 엔터 처리
		if (wParam == VK_RETURN)
		{
			// 입력버튼 이벤트로 처리한다.
			SendMessage(hMainWindow, WM_COMMAND, ID_BUTTON_INPUT, NULL);
		}
		return 0;
	}
	return CallWindowProc(wndprocEditBox, hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)	//Message's Additional Information
{
	switch(iMessage)
	{
	case WM_CREATE:	
		hButtonStart = CreateWindow((LPCTSTR)"button", "시작!", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 10, 250, 30, hWnd, (HMENU)ID_BUTTON_STARAT, g_hInst, NULL);
		hStaticOutput = CreateWindow((LPCTSTR)"static", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 50, 250, 540, hWnd, (HMENU)ID_STATIC1, g_hInst, NULL);
		hEditBoxInput = CreateWindow((LPCTSTR)"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 600, 150, 25, hWnd, (HMENU)ID_EDITBOX1, g_hInst, NULL);
		hButtonInput = CreateWindow((LPCTSTR)"button", "입력", WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 600, 80, 25, hWnd, (HMENU)ID_BUTTON_INPUT, g_hInst, NULL);

		// EditBox 용 프로시져 등록
		wndprocEditBox = (WNDPROC)SetWindowLong(hEditBoxInput, GWL_WNDPROC, (LONG)EditBoxProc);

		// 초기화
		memset(szInput, 0, sizeof(char)*MAX_LENGTH);
		memset(nCorrectNumber, 0, sizeof(int)*NUMBER_LENGTH);
		memset(nUserNumber, 0, sizeof(int)*NUMBER_LENGTH);
		memset(szStatus, 0, sizeof(char)*MAX_LENGTH);
		memset(szWinLose, 0, sizeof(char)*MAX_LENGTH);
		nCnt = 0;
		nWin = 0;
		nLose = 0;

		sprintf_s(szWinLose, MAX_LENGTH, "이겼다 : %d\n졌 다 : %d\n", nWin, nLose);
		SetWindowText(hStaticOutput, szWinLose);
		SetWindowText(hEditBoxInput, "");
		EnableWindow(hButtonInput, false);
		EnableWindow(hEditBoxInput, false);
		SetWindowText(hStaticOutput, "1~9, 4자리 숫자를 찾아봐~^^\n숫자기 있으면 ball 이고,\n자리까지 맞으면 strike, 알지?");
		
		return 0;

	case WM_COMMAND:
		switch(LOWORD(wParam))	// 컨트롤 ID
		{
		case ID_BUTTON_STARAT:
			{
				while (1)
				{
					// 랜덤 넘버 생성을 위한 씨드값 설정
					srand((unsigned int)time(NULL));
					// 4자리 랜덤 넘버 생성
					nCorrectNumber[0] = rand()%9 + 1;
					nCorrectNumber[1] = rand()%9 + 1;
					nCorrectNumber[2] = rand()%9 + 1;
					nCorrectNumber[3] = rand()%9 + 1;
					// 각 자리수의 모두 달라야 한다. 
					if (nCorrectNumber[0] != nCorrectNumber[1] &&
						nCorrectNumber[0] != nCorrectNumber[2] &&
						nCorrectNumber[0] != nCorrectNumber[3] &&
						nCorrectNumber[1] != nCorrectNumber[2] &&
						nCorrectNumber[1] != nCorrectNumber[3] &&
						nCorrectNumber[2] != nCorrectNumber[3])
					{
						strcpy_s(szStatus, MAX_LENGTH, "");
						// 정답이 잘 생성 돼었는지 확인하기 위해서
						//sprintf_s(szStatus, MAX_LENGTH, "%d%d%d%d 이 생성되었습니다.\n", nCorrectNumber[0], nCorrectNumber[1], nCorrectNumber[2], nCorrectNumber[3]);
						
						SetWindowText(hStaticOutput, "숫자가 정했졌어. 시작~^^ 홧팅~");
						EnableWindow(hButtonInput, true);
						EnableWindow(hEditBoxInput, true);

						break;
					}
				}
			}
			return 0;

		case ID_BUTTON_INPUT:
			{
				int num = 0;
				GetWindowText(hEditBoxInput, szInput, MAX_LENGTH);
				num = atoi(szInput);
				if (num < 1000 || num > 9999)
				{
					MessageBox(hWnd,"4자리 수를 입력해야돼~^^;", "잠깐~", MB_OK);
					return 0;
				}
				// 다음 입력을 편하게 하기위해서 입력란은 깨끗이 하기 
				SetWindowText(hEditBoxInput, "");

				char temp[5] = {0,}, a=0;
				sprintf_s(temp, 5, "%d", num);
				a = temp[0];
				nUserNumber[0] = atoi(&a);
				a = temp[1];
				nUserNumber[1] = atoi(&a);
				a = temp[2];
				nUserNumber[2] = atoi(&a);
				a = temp[3];
				nUserNumber[3] = atoi(&a);

				if (nUserNumber[0] == nUserNumber[1] ||
					nUserNumber[0] == nUserNumber[2] ||
					nUserNumber[0] == nUserNumber[3] ||
					nUserNumber[1] == nUserNumber[2] ||
					nUserNumber[1] == nUserNumber[3] ||
					nUserNumber[2] == nUserNumber[3])
				{
					MessageBox(hWnd, "겹치는 숫자가 있어서는 안돼~^^;", "잠깐~", MB_OK);
					return 0;
				}

				// 여기서 부터 자리 숫자를 비교해 보면서 정답인지, 스트라이크읹, 볼인지.. 등의 정보를 준다.
				int strike = 0, ball = 0;
				// 스트라이크 찾기
				for (int i=0; i<=3; i++)
				{
					if (nCorrectNumber[i] == nUserNumber[i])
					{
						strike++;
					}
				}
				// 볼 찾기
				for (int i=0; i<=3; i++)
				{
					for (int j=0; j<=3; j++)
					{
						if (i == j)
						{
							continue;
						}
						if (nCorrectNumber[i] == nUserNumber[j])
						{
							ball++;
						}
					}
				}

				nCnt++;

				char msg[100] = {0, };
				// 정답일 경우
				if (strike == 4)
				{
					sprintf_s(msg, 100, "%d%d%d%d -> 맞았습니다^^ (%d)\n", nUserNumber[0], nUserNumber[1], nUserNumber[2], nUserNumber[3], nCnt);
					strcat_s(szStatus, MAX_LENGTH, msg);
					SetWindowText(hStaticOutput, szStatus);
					nWin++;

					MessageBox(hWnd, "추카추카~ 정답이야 ^^;; 야구겜 짱 잘하네~", "성공~", MB_OK);
					//this->OnInitDialog();
					return 0;
				}
				// 그밖의 경우 힌트를 준다.
				else
				{
					sprintf_s(msg, 100, "%d%d%d%d -> %d strike %d ball (%d)\n", nUserNumber[0], nUserNumber[1], nUserNumber[2], nUserNumber[3], strike, ball, nCnt);
					strcat_s(szStatus, MAX_LENGTH, msg);
					SetWindowText(hStaticOutput, szStatus);

					if (nCnt > 20)
					{
						nLose++;
						sprintf_s(msg, 100, "겜 오버~ 정답은 %d%d%d%d \n", nCorrectNumber[0], nCorrectNumber[1], nCorrectNumber[2], nCorrectNumber[3]);
						strcat_s(szStatus, msg);
						SetWindowText(hStaticOutput, szStatus);

						MessageBox(hWnd, "20번넘어서~ 겜 오버야 ㅠㅠ", "실패ㅠㅠ", MB_OK);
						//this->OnInitDialog();
						return 0;
					}
				}
				SetFocus(hEditBoxInput);
			}
			return 0;
		case ID_EDITBOX1:
			switch (HIWORD(wParam))		// 통지 코드
			{
			case EN_CHANGE:
				{
				//GetWindowText(hEditBoxInput, szInput, MAX_LENGTH);
				}
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
