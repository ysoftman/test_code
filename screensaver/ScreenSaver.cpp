////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// SCREEN SAVER
////////////////////////////////////////////////////////////////////////////////////
//#pragma comment(linker, "/subsystem:console")	// 콘솔 프로그램 시작시
#pragma comment(linker, "/subsystem:windows")	// 윈도우 프로그램 시작시

#include <windows.h>
#include <time.h>
#include <stdlib.h>

char *szMsg = "★ ~ BILL, YOON ~ ★";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//Window Procedure
HINSTANCE g_hInst;	//Global Instance Declare
LPSTR lpszClass = "BILL's SCRSAV Windows";	//This Window Program(Class) Name

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
		"BYOUNG HOON's SCREEN SAVER Window",	//Window Title Bar Name
		WS_POPUP,	//For Full Screen Window Non System Menu and etc...(WS_OVERLAPPEDWINDOW -> Basic Style)
		CW_USEDEFAULT,	//X Vertex(Location)
		CW_USEDEFAULT,	//Y Vertex(Location)
		GetSystemMetrics(SM_CXSCREEN),	//Window Width(Scale)
		GetSystemMetrics(SM_CYSCREEN),	//Window Height(Scale)
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
	static HANDLE hTimer;	//Timer Handle

	switch(iMessage)
	{	
	//Create Window Message
	case WM_CREATE:	
		//Make Timer...	Call WM_TIMER
		hTimer=(HANDLE)SetTimer(hWnd,	//Handle Of Window
							1,			//Timer Number
							10,			//Time -> 1/1000 second
							NULL);		//To Call Function, When Timer Occur
		//Set A Random Starting Point -> Using Time Function For Seed Value
		srand((unsigned int)time(NULL));
		return 0;

	//When Timer Occur
	case WM_TIMER:
		//WM_PAINT Message Transfer To Window(Call WM_PAINT)
		InvalidateRect(hWnd,	//Window To Erase
					NULL,		//Area To Erase(NULL->All Rect Area)
					FALSE);		//TRUE->After Erase Rect, FALSE->After Non Erase Rect
		return 0;

	//When Move Window, Resize Window, etc... And Call By Invalidate Function
	case WM_PAINT:
		//Output Text - Redraw
		HDC hdc;
		PAINTSTRUCT ps;
		//hdc=BeginPaint(hWnd,&ps);
		if ((hdc=BeginPaint(hWnd,&ps)) == NULL)
		{
			MessageBox(NULL, "BeginPaint 함수 실패!!!", "Error", MB_OK);
			OutputDebugString("\nBeginPaint 함수 실패!!!");
		}
		
		//OutputDebugString("\nBeginPaint 함수 성공");
		HFONT hFont;
		HFONT hFont_temp;	//  hFont를 지우기전에 hdc에 폰트를 주기위해서 임시 저장(복구를 위해서)
		hFont=CreateFont(rand()%72,	//Font Height
						0,	//Font Width
						rand(),	//Font Escapement
						NULL,	//Font Orientation
						rand()%900,	//Font Weight	0,100,200,... 900
						FALSE,	//Font Italic
						FALSE,	//Font Underline
						FALSE,	//Font StrikeOut
						ANSI_CHARSET,	//Font Character Set
						OUT_DEFAULT_PRECIS,	//Font Output Precision
						CLIP_DEFAULT_PRECIS,	//Font Clip Presision
						DEFAULT_QUALITY,	//Font Quality
						FF_DECORATIVE,	//Font Pitch And Family
						"Times New Roman");	//Font Name
						

		SetTextAlign(hdc,TA_CENTER);
		SetBkMode(hdc, TRANSPARENT);

		//SelectObject(hdc,hFont);
		hFont_temp = (HFONT)SelectObject(hdc, hFont);
		SetTextColor(hdc,RGB(rand()%255,rand()%255,rand()%255));

		//TextOut(Handle Of DC, x, y, String To Output, Length Of SetColor);
		TextOut(hdc, rand()%GetSystemMetrics(SM_CXSCREEN), rand()%GetSystemMetrics(SM_CYSCREEN), szMsg, strlen(szMsg));		

		SelectObject(hdc, hFont_temp);
		DeleteObject(hFont);

		EndPaint(hWnd,&ps);	//Quit DC
		
		return 0;
	//When Mouse Left Button Click, Exit
	case WM_LBUTTONDOWN:
		SendMessage(hWnd,	//Handle Of Window
			WM_DESTROY,		//To Send Window Message
			NULL,			//wParam(Additional Information)
			NULL);			//lParam(Additional Information)

		return 0;

	//Destroy Window(Disappear From Memory, Alt+F4)
	case WM_DESTROY:		
		KillTimer(hWnd,1);	//1 Timer Quit
		//Send WM_QUIT To GetMessage Function
		//GetMessage Return FALSE And Exit While-Loop. Therefore Quit Window Program
		PostQuitMessage(0);	//WM_QUIT	
		return 0;	//Always Return 0, After Message Process
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));	//Default Message Process
}
