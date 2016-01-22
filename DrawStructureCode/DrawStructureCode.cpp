#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Structure Code 읽어서 그리기
// center.rst 파일에서 구조코드(5개)를 읽어와서
// 1획으로 표현하기
// 20061127 시작
// Programming By YoonByoungHoon
////////////////////////////////////////////////////////////////////////////////////
//#pragma comment(linker, "/subsystem:console")	// 콘솔 프로그램 시작시
#pragma comment(linker, "/subsystem:windows")	// 윈도우 프로그램 시작시

//Basic Include Windows Header File
#include <windows.h>
#include <stdio.h>
#include <math.h>

#define		WINDOWSIZEX		100
#define		WINDOWSIZEY		100
#define		BLACK	(RGB(0,0,0))
#define		WHITE	(RGB(255,255,255))
#define		RED		(RGB(255,0,0))
#define		GREEN	(RGB(0,255,0))
#define		BLUE	(RGB(0,0,255))
#define		PI		3.14


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//Window Procedure
HINSTANCE g_hInst;	//Global Instance Declare
LPSTR lpszClass = "DrawStructureCode";	//This Window Program(Class) Name
LPSTR szEditBoardClass	= "EditBoardClass";
HWND	hEditBoard[64];

typedef struct _Data {
	int index;
	float Distance;
	float Straighness;
	float Direction;
	float Real;
	float Rotation;
} t_Data;

t_Data g_Data[64];

int ConsumeLine(FILE *fp);
int LoadFile();
void DrawStroke(HDC hdc, t_Data data);
void CreateEditBoard(HWND hParent, short x, short y, short width, short height, int i);
LRESULT CALLBACK EditBoardProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DisplayData(HWND hwnd, t_Data Data, COLORREF bg);
void DrawCircle(HDC hdc, int x, int y);

//Program Start Point(Entry)
int APIENTRY WinMain(HINSTANCE hInstance,	//Window Program Instance Handle
					 HINSTANCE hPreInstance,	//PreExecute Window Program Instance Handle
					 LPSTR lpszCmdParam,	//Command Input Parameter ('argv' in DOS)
					 int nCmdShow)	//When Window Program Execute, Window's Shape
{
	g_hInst = hInstance;	//WinMain's Instance -> Global Instance
	HWND hMainWnd;	//This Window Handle(available in WinMain Function)
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
	if (!RegisterClass(&WndClass))	//Register Window Class For OS
	{
		MessageBox(NULL, "Register MainWindow Class error", "Error", MB_OK);
	}

	//WndClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
	WndClass.lpfnWndProc = (WNDPROC)EditBoardProc;
    WndClass.lpszClassName = (LPSTR)szEditBoardClass;
    if (!RegisterClass(&WndClass))
	{
		MessageBox(NULL, "Register EditBoard Class error", "Error", MB_OK);
	}
	
	// Create Window
	hMainWnd=CreateWindow(lpszClass,	//Windows Class Name
		"DrawStructureCode Window",	//Window Title Bar Name
		//WS_OVERLAPPEDWINDOW,	//Window Style(WS_OVERLAPPEDWINDOW -> Basic Style)
		WS_BORDER | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,	//X Vertex(Location)
		CW_USEDEFAULT,	//Y Vertex(Location)
		825,	//Window Width(Scale)
		850,	//Window Height(Scale)
		NULL,	//Parent Window And Child Window Handle(When Use MDI Window Program)
		(HMENU)NULL,	//Window Menu(If Value Is NULL, WndClass Use)
		hInstance,	//Window Program Handle
		NULL);	//CREATESTRUCT Struct Address For Special Purpose(Usually NULL)
	
	
	// Show Window
	ShowWindow(hMainWnd,	//A Handle To Show Window
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
	return Message.wParam;	//Return Message's Addtional Information(exit(0) In DOS)
	
}

//Window Procedure Function Call By OS  -> We Called 'CALLBACK Function'
LRESULT CALLBACK WndProc(HWND hWnd,	//Handle Of Window
						 UINT iMessage,	//Kind Of Message
						 WPARAM wParam,	//Message's Additional Information
						 LPARAM lParam)	//Message's Additional Information
{
	int EDIT_X=5, EDIT_Y=5;
	int i;
	switch(iMessage)	//What Kind Of Message Occur
	{
	case WM_CREATE:	//Create Window Message
		LoadFile();
		for (i=0;i<64;i++)
		{
			CreateEditBoard(hWnd, EDIT_X, EDIT_Y, WINDOWSIZEX, WINDOWSIZEY, i);
			EDIT_X += WINDOWSIZEX+1;
			if ((i+1)%8 == 0)
			{
				EDIT_X = 5;
				EDIT_Y += WINDOWSIZEY+1;
			}
		}
		return 0;

	case WM_PAINT:

		for (i=0;i<64;i++)
		{
			DisplayData(hEditBoard[i], g_Data[i], GREEN);
		}
		return 0;

	case WM_DESTROY:	//Destroy Window(Disappear From Memory, Alt+F4)
		//Send WM_QUIT To GetMessage Function
		//GetMessage Return FALSE And Exit While-Loop. Therefore Quit Window Program
		PostQuitMessage(0);	
		return 0;	//Always Retrun 0, After Message Process
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));	//Default Message Process
}

void CreateEditBoard(HWND hParent, short x, short y, short width, short height, int i)
{
	hEditBoard[i] = CreateWindow(szEditBoardClass, "EditBoard", WS_CHILD | WS_BORDER | WS_VISIBLE, (int)x, (int)y, (int)width, (int)height, hParent, NULL, g_hInst, NULL);
}

LRESULT CALLBACK EditBoardProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static HDC		hdc;
	switch	( message )
	{
	case WM_CREATE:
		break;
		
	case WM_DESTROY:
		break;
		
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
		
	case WM_COMMAND:
		break;
	default:
		return(DefWindowProc(hWnd, message, wParam, lParam));
	}
	
	return 0L;
}

void DrawStroke(HDC hdc, t_Data Data)
{
	int startx = 0;
	int starty = 0;
	int endx = 0;
	int endy = 0;
	int Size;
	float	sDis, Rad;
	// bhyoon, 20060429
	HPEN		Mypen,OldPen;
	//Rectangle(hdc, 0, 0, 10, 10);
	if (Data.Real == 1)
	{
		Mypen = CreatePen(PS_SOLID, 1, BLACK);		
	}
	else
	{
		Mypen = CreatePen(PS_DOT, 1, BLACK);
	}

	OldPen = (HPEN)SelectObject(hdc, Mypen);
	startx = WINDOWSIZEX/2;
	starty = WINDOWSIZEY/2;
	//startx = 0;
	//starty = 0;
	
	Size = 90;

	sDis = Data.Distance/(Data.Straighness/100);
	if(sDis >= (Size/2))
		sDis = Size/2;
	Rad = (Data.Direction*PI) / 180.0;
	// 마지막점을 찾는다.
	endx = startx + (float)cos((double)Rad)*sDis;
	endy = starty + (float)sin((double)Rad)*sDis;

	MoveToEx(hdc, startx, starty, NULL);

	DrawCircle(hdc, startx, starty);
	LineTo(hdc, endx, endy);

	SelectObject(hdc, OldPen);

	if (DeleteObject(Mypen) == 0)	// 실패하면
	{
		OutputDebugString("\nDeleteObject...  Fail.");
	}
	else
	{
		OutputDebugString("\nDeleteObject...  Success.");
	}
}


void DisplayData(HWND hwnd, t_Data Data, COLORREF bg) 
{
	//선택한 윈도우의 바탕을 bg색으로 표시하여 Rowdata를 보여줌
	PAINTSTRUCT ps;
	HDC 		hdc;
	HBRUSH		SelectBrush, OldBrush;
	
	char str[3];

	hdc = BeginPaint(hwnd, &ps);
	SelectBrush=CreateSolidBrush(bg); //바탕색은 bg
	OldBrush=(HBRUSH)SelectObject(hdc,SelectBrush);

	sprintf(str, "%2d", Data.index);
	TextOut(hdc, 0, 0, str, 2);
	
	SelectObject(hdc, OldBrush);
	DeleteObject(SelectBrush);
	
	DrawStroke(hdc, Data);
	EndPaint(hwnd,&ps);
}

void DrawCircle(HDC hdc, int x, int y)
{
	SetPixel(hdc,x-1,y-1,RED);
	SetPixel(hdc,x-1,y,RED);
	SetPixel(hdc,x,y-1,RED);
	SetPixel(hdc,x+1,y,RED);
	SetPixel(hdc,x,y+1,RED);
	SetPixel(hdc,x+1,y+1,RED);
	SetPixel(hdc,x+1,y-1,RED);
	SetPixel(hdc,x-1,y+1,RED);
	SetPixel(hdc,x,y,RED);
	SetPixel(hdc,x+2,y,RED);
	SetPixel(hdc,x,y-2,RED);
	SetPixel(hdc,x-2,y,RED);
	SetPixel(hdc,x+2,y,RED);
}

int ConsumeLine(FILE *fp)
{
	int	c;
	while ((c = getc(fp)) != EOF && c != '\n');
	if (c != EOF)
		return(TRUE);
	else
		return(FALSE);
}


int LoadFile()
{
	FILE *fp;
	int cnt=0;
	if ((fp = fopen("center.rst", "r")) == NULL)
	{
		MessageBox(NULL, "File Open Error", "Error", MB_OK);
		return 1;
	}
	while (1)
	{
		fscanf(fp, "%d", &g_Data[cnt].index);
		fscanf(fp, "%f", &g_Data[cnt].Distance);
		fscanf(fp, "%f", &g_Data[cnt].Straighness);
		fscanf(fp, "%f", &g_Data[cnt].Direction);
		fscanf(fp, "%f", &g_Data[cnt].Real);
		fscanf(fp, "%f", &g_Data[cnt].Rotation);
		cnt++;
		if (ConsumeLine(fp) == FALSE)
		{
			break;
		}
	}
	for (cnt=0; cnt<64; cnt++)
	{
		g_Data[cnt];
	}
	fclose(fp);

	return 0;
}

