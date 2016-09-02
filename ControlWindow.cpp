////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ControlWindows Program
////////////////////////////////////////////////////////////////////////////////////
//#pragma comment(linker, "/subsystem:console")	// 콘솔 프로그램 시작시
#pragma comment(linker, "/subsystem:windows")	// 윈도우 프로그램 시작시

#include <windows.h>
#include <stdio.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//Window Procedure
LRESULT CALLBACK MakeButtonProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void MakeButton(LPCTSTR TitleName, int x, int y, int width, int height, HWND hParent, HMENU id);

HINSTANCE g_hInst;	//Global Instance Declare
LPSTR lpszClass = "BILL's CW Windows";	//This Window Program(Class) Name

//Program Start Point(Entry)
int APIENTRY WinMain(HINSTANCE hInstance,	//Window Program Instance Handle
					 HINSTANCE hPreInstance,	//PreExecute Window Program Instance Handle
					 LPSTR lpszCmdParam,	//Command Input Parameter ('argv' in DOS)
					 int nCmdShow)	//When Window Program Execute, Window's Shape
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
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);	//Window Background Color(Using GetStockObject Function)
	WndClass.lpszMenuName=NULL;	//When Use Menu, Menu Name. If Non Menu, NULL
	WndClass.lpszClassName=lpszClass;	//Window Class Name
	RegisterClass(&WndClass);	//Register Window Class For OS

	// Create Window
	hWnd=CreateWindow(lpszClass,	//Windows Class Name
		"Contorl Window v1.0 by ysoftman",	//Window Title Bar Name
		WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX,	//(WS_OVERLAPPEDWINDOW -> Basic Style)
		CW_USEDEFAULT,	//X Vertex(Location)
		CW_USEDEFAULT,	//Y Vertex(Location)
		406,	//Window Width(Scale)
		530,	//Window Height(Scale)
		NULL,	//Parent Window And Child Window Handle(When Use MDI Window Program)
		(HMENU)NULL,	//Window Menu(If Value Is NULL, WndClass Use)
		hInstance,	//Window Program Handle
		NULL);	//CREATESTRUCT Struct Address For Special Purpose(Usually NULL)
	
	// Show Window
	ShowWindow(hWnd,	//A Handle To Show Window
			nCmdShow);	//Show Window Method(SW_HIDE, SW_MINIMIZE, SW_RESTORE, SW_SHOW, SW_SHOWNORMAL)

	// 항상 최상위에 보이도록 하기
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);

	//Start Message Loop Until WM_QUIT(EXIT Window) Occur
	//GetMessage() Read Message From Message Queue
	while(GetMessage(&Message,	//Address Of MSG Structure
					NULL,	//Handle Of Window
					0,	//First Message
					0))	//Last Message
	{
		TranslateMessage(&Message);	//WM_KEYDOWN Message Occur, Make WM_CHAR
		DispatchMessage(&Message);	//Message Transfer To WndPro(Window Procedure)
	}
	return Message.wParam;	//Return Message's Addtional Information(exit(0) In DOS)
	
}

//메인윈도우 클라이언트 영역에 버튼 생성
void MakeButton(LPCTSTR TitleName, int x, int y, int width, int height, HWND hParent, HMENU id)
{
	CreateWindow((LPCTSTR)"BUTTON", (LPCTSTR)TitleName, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x, y, width, height, hParent, (HMENU)id, g_hInst, NULL);
}

//Window Procedure Function Call By OS  -> We Called 'CALLBACK Function'
LRESULT CALLBACK WndProc(HWND hWnd,	//Handle Of Window
						 UINT iMessage,	//Kind Of Message
						 WPARAM wParam,	//Message's Additional Information
						 LPARAM lParam)	//Message's Additional Information
{
	RECT rt;
	int x, y;
	int i = 0;
	char mesg[1024];
	static POINT pt;
	
	switch(iMessage)	//What Kind Of Message Occur
	{
	case WM_CREATE:	//Create Window Message
		GetClientRect(hWnd, &rt);
		x = rt.left;
		y = rt.top;
		
		MakeButton("윈도우 잠금", x, y,200, 50, hWnd, (HMENU)1);
		MakeButton("작업 관리자", x+200, y,200, 50, hWnd, (HMENU)2);
		
		MakeButton("탐색기", x, y+50, 200, 50, hWnd, (HMENU)3);
		MakeButton("실행", x+200, y+50, 200, 50, hWnd, (HMENU)4);

		MakeButton("모든창 최소화", x, y+100, 200, 50, hWnd, (HMENU)5);
		MakeButton("최소화 창 복구", x+200, y+100, 200, 50, hWnd, (HMENU)6);

		MakeButton("화면 캡쳐", x, y+150, 200, 50, hWnd, (HMENU)7);
		MakeButton("그림판", x+200, y+150, 200, 50, hWnd, (HMENU)8);
		
		MakeButton("계산기", x, y+200, 200, 50, hWnd, (HMENU)9);
		MakeButton("시스템 등록정보", x+200, y+200, 200, 50, hWnd, (HMENU)10);

		MakeButton("메모장", x, y+250, 200, 50, hWnd, (HMENU)11);
		MakeButton("인터넷 네이버", x+200, y+250, 200, 50, hWnd, (HMENU)12);

		MakeButton("날짜 및 시간", x, y+300, 200, 50, hWnd, (HMENU)13);
		MakeButton("프로그램 삭제/추가", x+200, y+300, 200, 50, hWnd, (HMENU)14);

		MakeButton("C 드라이브 열기", x, y+350, 200, 50, hWnd, (HMENU)15);
		MakeButton("D 드라이브 열기", x+200, y+350, 200, 50, hWnd, (HMENU)16);

		MakeButton("30분 후 시스템 종료", x, y+400, 200, 50, hWnd, (HMENU)17);
		MakeButton("시스템 종료 취소", x+200, y+400, 200, 50, hWnd, (HMENU)18);

		MakeButton("마우스 클릭 좌표 설정", x, y+450, 200, 50, hWnd, (HMENU)19);
		MakeButton("마우스 100회 클릭 수행", x+200, y+450, 200, 50, hWnd, (HMENU)20);

		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case 1:
			// 윈도우 잠금(WindowsKey + L)
			keybd_event(VK_LWIN, 0, 0, 0);					// 왼쪽 윈도우 키를 누른다
			keybd_event((BYTE)'L', 0, 0, 0);				// L 키를 누른다
			keybd_event((BYTE)'L', 0, KEYEVENTF_KEYUP, 0);	// L 키를 띈다
			keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);	// 왼쪽 윈도우 키를 띈다
			return 0;

		case 2:
			// 작업 관리자(Ctrl + Shift + Esc)
			keybd_event(VK_LCONTROL, 0, 0, 0);				// 왼쪽 Ctrl 키를 누른다
			keybd_event(VK_LSHIFT, 0, 0, 0);				// 왼쪽 Shift 키를 누른다
			keybd_event(VK_ESCAPE, 0, 0, 0);				// Esc 키를 누른다.
			keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);	// Esc 키를 띈다
			keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);	// 왼쪽 Shift 키를 띈다
			keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);// 왼쪽 Ctrl 키를 띈다	
			return 0;

		case 3:
			// 탐색기(WindowsKey + E)
			keybd_event(VK_LWIN, 0, 0, 0);					// 왼쪽 윈도우 키를 누른다
			keybd_event((BYTE)'E', 0, 0, 0);				// E 키를 누른다
			keybd_event((BYTE)'E', 0, KEYEVENTF_KEYUP, 0);	// E 키를 띈다
			keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);	// 왼쪽 윈도우 키를 띈다
			return 0;
		
		case 4:
			// 실행(WindowsKey + R)
			keybd_event(VK_LWIN, 0, 0, 0);					// 왼쪽 윈도우 키를 누른다
			keybd_event((BYTE)'R', 0, 0, 0);				// R 키를 누른다
			keybd_event((BYTE)'R', 0, KEYEVENTF_KEYUP, 0);	// R 키를 띈다
			keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);	// 왼쪽 윈도우 키를 띈다
			return 0;

		case 5:
			// 모든창 최소화(WindowsKey + M)
			keybd_event(VK_LWIN, 0, 0, 0);					// 왼쪽 윈도우 키를 누른다
			keybd_event((BYTE)'M', 0, 0, 0);				// M 키를 누른다
			keybd_event((BYTE)'M', 0, KEYEVENTF_KEYUP, 0);	// M 키를 띈다
			keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);	// 왼쪽 윈도우 키를 띈다
			return 0;

		case 6:
			// 최소화 창 복구(WindowsKey + Shift + M)
			keybd_event(VK_LWIN, 0, 0, 0);					// 왼쪽 윈도우 키를 누른다
			keybd_event(VK_LSHIFT, 0, 0, 0);				// 왼쪽 Shift 키를 누른다
			keybd_event((BYTE)'M', 0, 0, 0);				// M 키를 누른다.
			keybd_event((BYTE)'M', 0, KEYEVENTF_KEYUP, 0);	// M 키를 띈다
			keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);	// 왼쪽 Shift 키를 띈다
			keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);	// 왼쪽 윈도우 키를 띈다	
			return 0;

		case 7:
			// 화면 캡쳐(PrintScreen)
			keybd_event(VK_SNAPSHOT, 0, 0, 0);				// PrintScreen 키를 누른다
			keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0);// PrintScreen 키를 띈다	
			return 0;

		case 8:
			// 그림판(mspaint.exe)
			WinExec("mspaint.exe", SW_SHOW);
			return 0;

		case 9:
			// 계산기(calc.exe)
			WinExec("calc.exe", SW_SHOW);
			return 0;

		case 10:
			// 시스템등록정보(sysdm.cpl)
			WinExec("rundll32.exe shell32.dll Control_RunDLL sysdm.cpl", SW_SHOW);
			return 0;

		case 11:
			// 메모장(notepad.exe)
			WinExec("notepad.exe", SW_SHOW);
			return 0;

		case 12:
			// 네이버(http://www.naver.com)
			//WinExec("http://www.naver.com", SW_SHOW);
			ShellExecute(NULL, "open", "http://www.naver.com", NULL, NULL, NULL);
			return 0;

		case 13:
			// 날짜및시간(timedate.cpl)
			WinExec("rundll32.exe shell32.dll Control_RunDLL timedate.cpl", SW_SHOW);
			return 0;

		case 14:
			// 프로그램삭제추가(appwiz.cpl)
			WinExec("rundll32.exe shell32.dll Control_RunDLL appwiz.cpl", SW_SHOW);
			return 0;

		case 15:
			// C 드라이브 열기(c:\)
			WinExec("explorer c:\\", SW_SHOW);
			return 0;

		case 16:
			// D 드라이브 열기(d:\)
			WinExec("explorer d:\\", SW_SHOW);
			return 0;

		case 17:
			// 30분 후 시스템 종료(shutdown.exe -s -t 1800)
			WinExec("shutdown.exe -s -t 1800", SW_SHOW);
			return 0;
		
		case 18:
			// 시스템 종료 취소(shutdown.exe -a)
			WinExec("shutdown.exe -a", SW_SHOW);
			return 0;

		case 19:
			MessageBox(hWnd, "확인 후 클릭할 위치에서 마우스 왼쪽 버튼을 클릭하세요~", "설정방법", MB_OK);
			SetCapture(hWnd);
			return 0;

		case 20:
			sprintf_s(mesg, "x = %d\ny = %d\n에 마우스 클릭질 시작하겠습니다.", pt.x, pt.y);
			MessageBox(hWnd, mesg, "cursor position", MB_OK);
			SetCursorPos(pt.x, pt.y);
			for (i = 0; i<100; i++)
			{
				// 마우스 무한 클릭
				mouse_event(MOUSEEVENTF_LEFTDOWN, pt.x, pt.y, 0, GetMessageExtraInfo());	// 마우스 왼쪽 버튼 down
				mouse_event(MOUSEEVENTF_LEFTUP, pt.x, pt.y, 0, GetMessageExtraInfo());		// 마우스 왼쪽 버튼 up
				Sleep(50);
			}
			return 0;

		}
	case WM_LBUTTONDOWN:
		GetCursorPos(&pt);
		return 0;
		
	case WM_LBUTTONUP:
		GetCursorPos(&pt);

		sprintf_s(mesg, "x = %d\ny = %d\n로 마우스 위치가 설정 되었습니다.", pt.x, pt.y);
		MessageBox(hWnd, mesg, "cursor position", MB_OK);

		ReleaseCapture();
		return 0;
	case WM_DESTROY:	//Destroy Window(Disappear From Memory, Alt+F4)
		//Send WM_QUIT To GetMessage Function
		//GetMessage Return FALSE And Exit While-Loop. Therefore Quit Window Program
		PostQuitMessage(0);	
		return 0;
	}
	//Default Message Process
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}
