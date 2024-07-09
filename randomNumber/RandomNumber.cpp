////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Random Number Display Program
////////////////////////////////////////////////////////////////////////////////////
//#pragma comment(linker, "/subsystem:console")	// 콘솔 프로그램 시작시
#pragma comment(linker, "/subsystem:windows")	// 윈도우 프로그램 시작시

#include <windows.h>
#include <time.h>
#include <stdlib.h>

char RandNum[100];

long Rnum;
long pre_Rnum;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//Window Procedure
HINSTANCE g_hInst;	//Global Instance Declare
LPSTR lpszClass = "BILL's Basic Windows";	//This Window Program(Class) Name

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
		"BYOUNG HOON's Window",	//Window Title Bar Name
		WS_MAXIMIZE | WS_POPUP | WS_BORDER,		//(WS_OVERLAPPEDWINDOW -> Basic Style)
		CW_USEDEFAULT,	//X Vertex(Location)
		CW_USEDEFAULT,	//Y Vertex(Location)
		820,
		500,	
		NULL,	//Parent Window And Child Window Handle(When Use MDI Window Program)
		(HMENU)NULL,	//Window Menu(If Value Is NULL, WndClass Use)
		hInstance,	//Window Program Handle
		NULL);	//CREATESTRUCT Struct Address For Special Purpose(Usually NULL)
	
	
	// Show Window
	ShowWindow(hWnd,	//A Handle To Show Window
			nCmdShow);	//Show Window Method(SW_HIDE, SW_MINIMIZE, SW_RESTORE, SW_SHOW, SW_SHOWNORMAL)

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
	return Message.wParam;	//Return Message's Additional Information(exit(0) In DOS)
	
}

//Window Procedure Function Call By OS  -> We Called 'CALLBACK Function'
LRESULT CALLBACK WndProc(HWND hWnd,	//Handle Of Window
						 UINT iMessage,	//Kind Of Message
						 WPARAM wParam,	//Message's Additional Information
						 LPARAM lParam)	//Message's Additional Information
{
	static HANDLE hTimer;
	RECT rect;
	switch(iMessage)	//What Kind Of Message Occur
	{
	case WM_CREATE:	//Create Window Message
		hTimer=(HANDLE)SetTimer(hWnd,	//Handle Of Window
							1,	//Timer Number
							50,	//Time -> 1/1000 second
							NULL);	//To Call Function, When Timer Occur

		srand((unsigned int)time(NULL));	//1sec
		SetWindowPos(hWnd,
					HWND_BOTTOM,
					(GetSystemMetrics(SM_CXSCREEN)/2)-410,
					(GetSystemMetrics(SM_CYSCREEN)/2)-250,
					820,
					500,
					SWP_NOSIZE);

		return 0;

	case WM_TIMER:
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;
		HFONT hFont, hFont_temp;

		hdc=BeginPaint(hWnd, &ps);
		hFont=CreateFont(100,	//Font Height
						0,	//Font Width
						NULL,	//Font Escapement
						NULL,	//Font Orientation
						500,	//Font Weight	0,100,200,... 900
						FALSE,	//Font Italic
						FALSE,	//Font Underline
						FALSE,	//Font StrikeOut
						ANSI_CHARSET,	//Font Character Set
						OUT_DEFAULT_PRECIS,	//Font Output Precision
						CLIP_DEFAULT_PRECIS,	//Font Clip Presision
						DEFAULT_QUALITY,	//Font Quality
						FF_DECORATIVE,	//Font Pitch And Family
						"Times New Roman");	//Font Name

		GetClientRect(hWnd, &rect);

		SetTextAlign(hdc,TA_CENTER);	//Aline Center...
		SetBkMode(hdc, TRANSPARENT);	//Background Color Mode -> Transparent
		hFont_temp = (HFONT)SelectObject(hdc,hFont);

		SetTextColor(hdc,RGB(120,120,120));

		TextOut(hdc, rect.right/2, rect.bottom/3, "★ Random Number ★", strlen("★ Random Number ★"));

		Rnum = rand()%101;

		SetTextColor(hdc,RGB(255,50,50));
		wsprintf(RandNum, "%ld", Rnum);
		TextOut(hdc, rect.right/2, rect.bottom/2, (LPCTSTR)RandNum, strlen(RandNum));

		SelectObject(hdc, hFont_temp);
		DeleteObject(hFont);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		SetCapture(hWnd);	// Out of Window Rect Capture
		KillTimer(hWnd, 1);
		return 0;
		
	case WM_LBUTTONUP: 
		ReleaseCapture();	// ReleaseCapture
		hTimer=(HANDLE)SetTimer(hWnd,	//Handle Of Window
			1,	//Timer Number
			50,	//Time -> 1/1000 second
			NULL);	//To Call Function, When Timer Occur
		
		srand((unsigned int)time(NULL));	//1sec
		return 0;

	case WM_DESTROY:	//Destroy Window(Disappear From Memory, Alt+F4)
		KillTimer(hWnd, 1);
		//Send WM_QUIT To GetMessage Function
		//GetMessage Return FALSE And Exit While-Loop. Therefore Quit Window Program
		PostQuitMessage(0);	
		return 0;	//Always Return 0, After Message Process
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));	//Default Message Process
}
