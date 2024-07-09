////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ☆ ~ OX Game ~ ★
////////////////////////////////////////////////////////////////////////////////////
//#pragma comment(linker, "/subsystem:console")	// 콘솔 프로그램 시작시
#pragma comment(linker, "/subsystem:windows")	// 윈도우 프로그램 시작시

#include <windows.h>
#include <time.h>

char *szO = "○";	//O
char *szX = "×";	//X
char *text=NULL;
char *BILL = "☆ ~ BILL, YOON ~ ☆";

unsigned int Owin=0;
unsigned int Xwin=0;
unsigned int GAME_NUM=0;

char win[100];
char gamenum[100];

bool BILL_FLAG= true;
bool RESET = true;
unsigned turn=0;
unsigned int OOO=0;
unsigned int XXX=1;
unsigned int choice=0;	//choice 0 or 1

//Initial Number : 3 -> Empty
unsigned int bingo[3][3] = {3, 3, 3,
							3, 3, 3,
							3, 3, 3};

//Empty or Used(false -> Empty, treu -> Used
bool flag[9] = {false, false, false,
				false, false, false,
				false, false, false};

void GAMERESTART0();
void GAMERESTART1();

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//Window Procedure
HINSTANCE g_hInst;	//Global Instance Declare
LPSTR lpszClass = "BILL's OX Game";	//This Window Program(Class) Name

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
		WS_POPUP,	//(WS_OVERLAPPEDWINDOW -> Basic Style)
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



LRESULT CALLBACK WndProc(HWND hWnd,	//Handle Of Window
						 UINT iMessage,	//Kind Of Message
						 WPARAM wParam,	//Message's Additional Information
						 LPARAM lParam)	//Message's Additional Information
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	//hFont1 -> O, X
	//hFont2 -> BILL, YOON
	//hFont3 -> O, X Wins
	
	HFONT hFont;
	HFONT hFont_temp; //DeleteObject함수로 hdc를 삭제하기 전에 hdc의 폰트를 대체하기 위해서


	static HANDLE hTimer;	//Timer Handle

	switch(iMessage)	//What Kind Of Message Occur
	{
	case WM_CREATE:	//Create Window Message
		//Make Timer...	Call WM_TIMER
		hTimer=(HANDLE)SetTimer(hWnd,	//Handle Of Window
							1,	//Timer Number
							50,	//Time -> 1/1000 second
							NULL);	//To Call Function, When Timer Occur

		//Set A Random Starting Point(Using Time Function For Seed Value)
		srand((unsigned int)time(NULL));	//1sec

		return 0;

	case WM_TIMER:	//When Timer Occur

		//WM_PAINT Message Transfer To Window(Call WM_PAINT)
		InvalidateRect(hWnd,	//Window To Erase
					NULL,	//Area To Erase(NULL->All Rect Area)
					FALSE);	//TRUE->After Erase Rect, FALSE->After Non Erase Rect
		
		if (RESET == true)
			InvalidateRect(hWnd, NULL, TRUE);	//Erase Screen

		return 0;


	case WM_PAINT:

		hdc=BeginPaint(hWnd,&ps);
		
		if (BILL_FLAG == true)
		{
			//////////////////////////////////////////////////////////////////////////////////////////////////
			//BILL YOON
			hFont=CreateFont(100,	//Font Height
							0,		//Font Width
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

			//Display BILL, YOON
			//SelectObject(hdc,hFont);
			hFont_temp = (HFONT)SelectObject(hdc, hFont);

			SetTextAlign(hdc, TA_CENTER);	//Aline Center...
			SetBkMode(hdc, TRANSPARENT);	//Background Color Mode -> Transparent
			SetTextColor(hdc,RGB(180,180,180));
			
			TextOut(hdc,
					(int)(GetSystemMetrics(SM_CXSCREEN)/2),
					//(int)(GetSystemMetrics(SM_CYSCREEN)-500),
					(int)(GetSystemMetrics(SM_CYSCREEN)*0.33)+50,
					BILL,
					strlen(BILL));

			SelectObject(hdc, hFont_temp);	// hFont를 지우기 위해서 hdc의 폰트를 hFont_temp로 바꿔준다.
			DeleteObject(hFont);


			//////////////////////////////////////////////////////////////////////////////////////////////////
			//O Wins X Wins Game Count
			hFont=CreateFont(30,	//Font Height
							0,		//Font Width
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

			//SelectObject(hdc,hFont);
			hFont_temp = (HFONT)SelectObject(hdc, hFont);

			SetTextAlign(hdc,TA_LEFT);
			
			//Display O Wins			
			wsprintf(win, "O Wins :   %u", Owin);
			SetTextColor(hdc,RGB(255,127,127));
			TextOut(hdc,
					0+10,
					0,
					(LPSTR)win,
					strlen(win));
			
			//Display X Wins
			wsprintf(win, "X Wins :   %u", Xwin);
			SetTextColor(hdc,RGB(127,127,255));	
			TextOut(hdc,
					(int)(GetSystemMetrics(SM_CXSCREEN)*0.33)+10,
					0,
					(LPSTR)win,
					strlen(win));

			//Display Game Conut
			wsprintf(gamenum, "Game Count :      %u", GAME_NUM);
			SetTextColor(hdc,RGB(180,180,180));
			TextOut(hdc,
					(int)(GetSystemMetrics(SM_CXSCREEN)*0.66)+10,
					0,
					(LPSTR)gamenum,
					strlen(gamenum));
			

			
			//Stop Game...
			//if (GAME_NUM == 10000)
			//{
			//	KillTimer(hWnd, 1);
			//	PostQuitMessage(0);
			//	return 0;
			//}

			BILL_FLAG = false;	//When Restart Game Redraw...

			RESET = false;


			//3 x 3 Draw Line
			MoveToEx(hdc, (int)(GetSystemMetrics(SM_CXSCREEN)*0.33), 0, NULL);
			LineTo(hdc, (int)(GetSystemMetrics(SM_CXSCREEN)*0.33), GetSystemMetrics(SM_CYSCREEN));
			MoveToEx(hdc, (int)(GetSystemMetrics(SM_CXSCREEN)*0.66), 0, NULL);
			LineTo(hdc, (int)(GetSystemMetrics(SM_CXSCREEN)*0.66), GetSystemMetrics(SM_CYSCREEN));


			MoveToEx(hdc, 0, (int)(GetSystemMetrics(SM_CYSCREEN)*0.33), NULL);
			LineTo(hdc, GetSystemMetrics(SM_CXSCREEN), (int)(GetSystemMetrics(SM_CYSCREEN)*0.33));
			MoveToEx(hdc, GetSystemMetrics(SM_CXSCREEN), (int)(GetSystemMetrics(SM_CYSCREEN)*0.66), NULL);
			LineTo(hdc, 0, (int)(GetSystemMetrics(SM_CYSCREEN)*0.66));

			SelectObject(hdc, hFont_temp);	// hFont를 지우기 위해서 hdc의 폰트를 hFont_temp로 바꿔준다.
			DeleteObject(hFont);
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////
		//Random Number
		hFont=CreateFont(30,	//Font Height
						0,		//Font Width
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

		char rNum[100];

		//SelectObject(hdc,hFont);
		hFont_temp = (HFONT)SelectObject(hdc, hFont);		

		SetBkMode(hdc, OPAQUE);
		SetTextAlign(hdc,TA_LEFT);
		
		wsprintf(rNum, "Random Number :  %u", rand());
		SetTextColor(hdc,RGB(180,180,180));
		
		//Display Rand Number
		TextOut(hdc,
				(int)(GetSystemMetrics(SM_CXSCREEN)*0.33)+10,
				(int)(GetSystemMetrics(SM_CYSCREEN)*0.33)+10,
				(LPSTR)rNum,
				strlen(rNum));
		
		SelectObject(hdc, hFont_temp);	// hFont를 지우기 위해서 hdc의 폰트를 hFont_temp로 바꿔준다.
		DeleteObject(hFont);

		//////////////////////////////////////////////////////////////////////////////////////////////////
		//Large O X 
		hFont=CreateFont(400,	//Font Height
						0,		//Font Width
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

		//SelectObject(hdc,hFont);
		hFont_temp = (HFONT)SelectObject(hdc, hFont);

		SetBkMode(hdc, TRANSPARENT);	//Background Color Mode -> Transparent		
		SetTextAlign(hdc,TA_CENTER);	//Aline Center...			
		
		//Update Turn
		if (turn == OOO)
		{
			turn = XXX;
			SetTextColor(hdc,RGB(127,127,255));
			text = szX;
		}
		else
		{
			turn = OOO;
			SetTextColor(hdc,RGB(255,127,127));
			text = szO;
		}



		//When O Turn
		if (turn == OOO)
		{
			//////////////////////////////////////////////////////
			//				Checking Bingo Area					//
			//						XXX							//
			//////////////////////////////////////////////////////
			while (1)
			{
				choice = rand()%9;	

				//Check Empty Or Used...
				if (flag[choice] == false)
					break;
			}

			////////////////////IF BINGO 0-1-2////////////////////
			if ((bingo[0][0] == XXX) && (bingo[0][1] == XXX) && (bingo[0][2] == 3))	//0-1-
			{
				choice = 2;
			}
			
			else if ((bingo[0][0] == XXX) && (bingo[0][1] == 3) && (bingo[0][2] == XXX))	//0- -2
			{
				choice = 1;
			}		
			
			else if ((bingo[0][0] == 3) && (bingo[0][1] == XXX) && (bingo[0][2] == XXX))	// -1-2
			{
				choice = 0;
			}		
			
			////////////////////IF BINGO 3-4-5////////////////////
			else if ((bingo[1][0] == XXX) && (bingo[1][1] == XXX) && (bingo[1][2] == 3))	//3-4-
			{
				choice = 5;
			}		

			else if ((bingo[1][0] == XXX) && (bingo[1][1] == 3) && (bingo[1][2] == XXX))	//3- -5
			{
				choice = 4;
			}		
			
			else if ((bingo[1][0] == 3) && (bingo[1][1] == XXX) && (bingo[1][2] == XXX))	// -4-5
			{
				choice = 3;
			}		
				
			////////////////////IF BINGO 6-7-8////////////////////
			else if ((bingo[2][0] == XXX) && (bingo[2][1] == XXX) && (bingo[2][2] == 3))	//6-7-
			{
				choice = 8;
			}

			else if ((bingo[2][0] == XXX) && (bingo[2][1] == 3) && (bingo[2][2] == XXX))	//6- -8
			{
				choice = 7;
			}
	
			else if ((bingo[2][0] == 3) && (bingo[2][1] == XXX) && (bingo[2][2] == XXX))	// -7-8
			{
				choice = 6;
			}


			////////////////////IF BINGO 0-3-6////////////////////
			else if ((bingo[0][0] == XXX) && (bingo[1][0] == XXX) && (bingo[2][0] == 3))	//0-3-
			{
				choice = 6;
			}

			else if ((bingo[0][0] == XXX) && (bingo[1][0] == 3) && (bingo[2][0] == XXX))	//0- -6
			{
				choice = 3;
			}

			else if ((bingo[0][0] == 3) && (bingo[1][0] == XXX) && (bingo[2][0] == XXX))	// -3-6
			{
				choice = 0;
			}

			////////////////////IF BINGO 1-4-7////////////////////
			else if ((bingo[0][1] == XXX) && (bingo[1][1] == XXX) && (bingo[2][1] == 3))	//1-4-
			{
				choice = 7;
			}

			else if ((bingo[0][1] == XXX) && (bingo[1][1] == 3) && (bingo[2][1] == XXX))	//1- -7
			{
				choice = 4;
			}

			else if ((bingo[0][1] == 3) && (bingo[1][1] == XXX) && (bingo[2][1] == XXX))	// -4-7
			{
				choice = 1;
			}

			////////////////////IF BINGO 2-5-8////////////////////
			else if ((bingo[0][2] == XXX) && (bingo[1][2] == XXX) && (bingo[2][2] == 3))	//2-5-
			{
				choice = 8;
			}

			else if ((bingo[0][2] == XXX) && (bingo[1][2] == 3) && (bingo[2][2] == XXX))	//2- -8
			{
				choice = 5;
			}

			else if ((bingo[0][2] == 3) && (bingo[1][2] == XXX) && (bingo[2][2] == XXX))	// -5-8
			{
				choice = 2;
			}


			////////////////////IF BINGO 0-4-8////////////////////
			else if ((bingo[0][0] == XXX) && (bingo[1][1] == XXX) && (bingo[2][2] == 3))	//0-4-
			{
				choice = 8;
			}

			else if ((bingo[0][0] == XXX) && (bingo[1][1] == 3) && (bingo[2][2] == XXX))	//0- -8
			{
				choice = 4;
			}

			else if ((bingo[0][0] == 3) && (bingo[1][1] == XXX) && (bingo[2][2] == XXX))	// -4-8
			{
				choice = 0;
			}

			////////////////////IF BINGO 2-4-6////////////////////
			else if ((bingo[0][2] == XXX) && (bingo[1][1] == XXX) && (bingo[2][0] == 3))	//2-4-
			{
				choice = 6;
			}

			else if ((bingo[0][2] == XXX) && (bingo[1][1] == 3) && (bingo[2][0] == XXX))	//2- -6
			{
				choice = 4;
			}

			else if ((bingo[0][2] == 3) && (bingo[1][1] == XXX) && (bingo[2][0] == XXX))	// -4-6
			{
				choice = 2;
			}

						
			switch (choice)
			{
			case 0:
				if (bingo[0][0]==XXX)
				{
					flag[0]=true;	//Used
				}
				else
				{
					//A	area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.16),							
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.3)-330,
							text,
							strlen(text));
					
					bingo[0][0]=OOO;
					flag[0]=true;	//Used
				}
				break;

			case 1:
				if (bingo[0][1]==XXX)
				{
					flag[1]=true;	//Used
				}
				else
				{
					//B area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.50),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.3)-330,
							text,
							strlen(text));


					bingo[0][1]=OOO;
					flag[1]=true;	//Used
				}
				break;

			case 2:
				if (bingo[0][2]==XXX)
				{
					flag[2]=true;	//Used
				}
				else
				{
					//C area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.82),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.3)-330,
							text,
							strlen(text));

					bingo[0][2]=OOO;
					flag[2]=true;	//Used
				}
				break;

			case 3:
				if (bingo[1][0]==XXX)
				{
					flag[3]=true;	//Used
				}
				else
				{
					//D area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.16),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.6)-300,
							text,
							strlen(text));

					bingo[1][0]=OOO;
					flag[3]=true;	//Used
				}
				break;

			case 4:
				if (bingo[1][1]==XXX)
				{
					flag[4]=true;	//Used
				}
				else
				{
					//E area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.50),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.6)-300,
							text,
							strlen(text));

					bingo[1][1]=OOO;
					flag[4]=true;	//Used
				}
				break;

			case 5:
				if (bingo[1][2]==XXX)
				{
					flag[5]=true;	//Used
				}
				else
				{
					//F area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.82),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.6)-300,
							text,
							strlen(text));

					bingo[1][2]=OOO;
					flag[5]=true;	//Used
				}
				break;

			case 6:
				if (bingo[2][0]==XXX)
				{
					flag[6]=true;	//Used
				}
				else
				{
					//G area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.16),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.9)-270,
							text,
							strlen(text));

					bingo[2][0]=OOO;
					flag[6]=true;	//Used
				}
				break;

			case 7:
				if (bingo[2][1]==XXX)
				{
					flag[7]=true;	//Used
				}
				else
				{
					//H area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.50),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.9)-270,
							text,
							strlen(text));

					bingo[2][1]=OOO;
					flag[7]=true;	//Used
				}
				break;

			case 8:
				if (bingo[2][2]==XXX)
				{
					flag[8]=true;	//Used
				}
				else
				{
					//I area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.82),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.9)-270,
							text,
							strlen(text));
						
					bingo[2][2]=OOO;
					flag[8]=true;	//Used
				}
				break;
			}	//End switch
		}	//End if
			
			
		//When X Turn
		if (turn == XXX)
		{	
			//////////////////////////////////////////////////////
			//				Checking Bingo Area					//
			//						OOO							//
			//////////////////////////////////////////////////////
			while (1)
			{
				choice = rand()%9;

				//Check Empty Or Used...
				if (flag[choice] == false)
					break;
			}

			////////////////////IF BINGO 0-1-2////////////////////
			if ((bingo[0][0] == OOO) && (bingo[0][1] == OOO) && (bingo[0][2] == 3))	//0-1-
			{
				choice = 2;
			}
			
			else if ((bingo[0][0] == OOO) && (bingo[0][1] == 3) && (bingo[0][2] == OOO))	//0- -2
			{
				choice = 1;
			}		
			
			else if ((bingo[0][0] == 3) && (bingo[0][1] == OOO) && (bingo[0][2] == OOO))	// -1-2
			{
				choice = 0;
			}		
			
			////////////////////IF BINGO 3-4-5////////////////////
			else if ((bingo[1][0] == OOO) && (bingo[1][1] == OOO) && (bingo[1][2] == 3))	//3-4-
			{
				choice = 5;
			}		

			else if ((bingo[1][0] == OOO) && (bingo[1][1] == 3) && (bingo[1][2] == OOO))	//3- -5
			{
				choice = 4;
			}		
			
			else if ((bingo[1][0] == 3) && (bingo[1][1] == OOO) && (bingo[1][2] == OOO))	// -4-5
			{
				choice = 3;
			}		
				
			////////////////////IF BINGO 6-7-8////////////////////
			else if ((bingo[2][0] == OOO) && (bingo[2][1] == OOO) && (bingo[2][2] == 3))	//6-7-
			{
				choice = 8;
			}

			else if ((bingo[2][0] == OOO) && (bingo[2][1] == 3) && (bingo[2][2] == OOO))	//6- -8
			{
				choice = 7;
			}
	
			else if ((bingo[2][0] == 3) && (bingo[2][1] == OOO) && (bingo[2][2] == OOO))	// -7-8
			{
				choice = 6;
			}


			////////////////////IF BINGO 0-3-6////////////////////
			else if ((bingo[0][0] == OOO) && (bingo[1][0] == OOO) && (bingo[2][0] == 3))	//0-3-
			{
				choice = 6;
			}

			else if ((bingo[0][0] == OOO) && (bingo[1][0] == 3) && (bingo[2][0] == OOO))	//0- -6
			{
				choice = 3;
			}

			else if ((bingo[0][0] == 3) && (bingo[1][0] == OOO) && (bingo[2][0] == OOO))	// -3-6
			{
				choice = 0;
			}

			////////////////////IF BINGO 1-4-7////////////////////
			else if ((bingo[0][1] == OOO) && (bingo[1][1] == OOO) && (bingo[2][1] == 3))	//1-4-
			{
				choice = 7;
			}

			else if ((bingo[0][1] == OOO) && (bingo[1][1] == 3) && (bingo[2][1] == OOO))	//1- -7
			{
				choice = 4;
			}

			else if ((bingo[0][1] == 3) && (bingo[1][1] == OOO) && (bingo[2][1] == OOO))	// -4-7
			{
				choice = 1;
			}

			////////////////////IF BINGO 2-5-8////////////////////
			else if ((bingo[0][2] == OOO) && (bingo[1][2] == OOO) && (bingo[2][2] == 3))	//2-5-
			{
				choice = 8;
			}

			else if ((bingo[0][2] == OOO) && (bingo[1][2] == 3) && (bingo[2][2] == OOO))	//2- -8
			{
				choice = 5;
			}

			else if ((bingo[0][2] == 3) && (bingo[1][2] == OOO) && (bingo[2][2] == OOO))	// -5-8
			{
				choice = 2;
			}


			////////////////////IF BINGO 0-4-8////////////////////
			else if ((bingo[0][0] == OOO) && (bingo[1][1] == OOO) && (bingo[2][2] == 3))	//0-4-
			{
				choice = 8;
			}

			else if ((bingo[0][0] == OOO) && (bingo[1][1] == 3) && (bingo[2][2] == OOO))	//0- -8
			{
				choice = 4;
			}

			else if ((bingo[0][0] == 3) && (bingo[1][1] == OOO) && (bingo[2][2] == OOO))	// -4-8
			{
				choice = 0;
			}

			////////////////////IF BINGO 2-4-6////////////////////
			else if ((bingo[0][2] == OOO) && (bingo[1][1] == OOO) && (bingo[2][0] == 3))	//2-4-
			{
				choice = 6;
			}

			else if ((bingo[0][2] == OOO) && (bingo[1][1] == 3) && (bingo[2][0] == OOO))	//2- -6
			{
				choice = 4;
			}

			else if ((bingo[0][2] == 3) && (bingo[1][1] == OOO) && (bingo[2][0] == OOO))	// -4-6
			{
				choice = 2;
			}
						
			switch (choice)
			{
			case 0:
				if (bingo[0][0]==OOO)
				{
					flag[0]=true;	//Used
				}
				else
				{
					//A	area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.16),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.3)-330,
							text,
							strlen(text));

					bingo[0][0]=XXX;
					flag[0]=true;	//Used
				}
				break;

			case 1:
				if (bingo[0][1]==OOO)
				{
					flag[1]=true;	//Used
				}
				else
				{			
					//B area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.50),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.3)-330,
							text,
							strlen(text));

					bingo[0][1]=XXX;
					flag[1]=true;	//Used
				}
				break;

			case 2:
				if (bingo[0][2]==OOO)
				{
					flag[2]=true;	//Used
				}
				else
				{
					//C area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.82),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.3)-330,
							text,
							strlen(text));

					bingo[0][2]=XXX;
					flag[2]=true;	//Used
				}
				break;

			case 3:
				if (bingo[1][0]==OOO)
				{
					flag[3]=true;	//Used
				}
				else
				{
					//D area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.16),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.6)-300,
							text,
							strlen(text));

					bingo[1][0]=XXX;
					flag[3]=true;	//Used
				}
				break;

			case 4:
				if (bingo[1][1]==OOO)
				{
					flag[4]=true;	//Used
				}
				else
				{
					//E area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.50),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.6)-300,
							text,
							strlen(text));

					bingo[1][1]=XXX;
					flag[4]=true;	//Used
				}
				break;

			case 5:
				if (bingo[1][2]==OOO)
				{
					flag[5]=true;	//Used
				}
				else
				{
					//F area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.82),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.6)-300,
							text,
							strlen(text));

					bingo[1][2]=XXX;
					flag[5]=true;	//Used
				}
				break;

			case 6:
				if (bingo[2][0]==OOO)
				{
					flag[6]=true;	//Used
				}
				else
				{
					//G area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.16),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.9)-270,
							text,
							strlen(text));

					bingo[2][0]=XXX;
					flag[6]=true;	//Used
				}
				break;

			case 7:
				if (bingo[2][1]==OOO)
				{
					flag[7]=true;	//Used
				}
				else
				{
					//H area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.50),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.9)-270,
							text,
							strlen(text));

					bingo[2][1]=XXX;
					flag[7]=true;	//Used
				}
				break;

			case 8:
				if (bingo[2][2]==OOO)
				{
					flag[8]=true;	//Used
				}
				else
				{
					//I area
					TextOut(hdc,
							(int)(GetSystemMetrics(SM_CXSCREEN)*0.82),
							(int)(GetSystemMetrics(SM_CYSCREEN)*0.9)-270,
							text,
							strlen(text));
						
					bingo[2][2]=XXX;
					flag[8]=true;	//Used
				}
				break;
			}	//End switch
		}	//End if


		//When OOO Wins
		////////////////////IF BINGO 0-1-2////////////////////
		if ((bingo[0][0] == OOO) && (bingo[0][1] == OOO) && (bingo[0][2] == OOO))
		{
			//PostQuitMessage(0);
			Owin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 3-4-5////////////////////
		else if ((bingo[1][0] == OOO) && (bingo[1][1] == OOO) && (bingo[1][2] == OOO))
		{
			//PostQuitMessage(0);
			Owin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 6-7-8////////////////////
		else if ((bingo[2][0] == OOO) && (bingo[2][1] == OOO) && (bingo[2][2] == OOO))
		{
			//PostQuitMessage(0);
			Owin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 0-3-6////////////////////
		else if ((bingo[0][0] == OOO) && (bingo[1][0] == OOO) && (bingo[2][0] == OOO))
		{
			//PostQuitMessage(0);
			Owin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 1-4-7////////////////////
		else if ((bingo[0][1] == OOO) && (bingo[1][1] == OOO) && (bingo[2][1] == OOO))
		{
			//PostQuitMessage(0);
			Owin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 2-5-8////////////////////
		else if ((bingo[0][2] == OOO) && (bingo[1][2] == OOO) && (bingo[2][2] == OOO))
		{
			//PostQuitMessage(0);
			Owin++;
			GAMERESTART1();
			//break;
		}


		////////////////////IF BINGO 0-4-8////////////////////
		else if ((bingo[0][0] == OOO) && (bingo[1][1] == OOO) && (bingo[2][2] == OOO))
		{
			//PostQuitMessage(0);
			Owin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 2-4-6////////////////////
		else if ((bingo[0][2] == OOO) && (bingo[1][1] == OOO) && (bingo[2][0] == OOO))
		{
			//PostQuitMessage(0);
			Owin++;
			GAMERESTART1();
			//break;
		}

		//When XXX Wins
		////////////////////IF BINGO 0-1-2////////////////////
		else if ((bingo[0][0] == XXX) && (bingo[0][1] == XXX) && (bingo[0][2] == XXX))
		{
			//PostQuitMessage(0);
			Xwin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 3-4-5////////////////////
		else if ((bingo[1][0] == XXX) && (bingo[1][1] == XXX) && (bingo[1][2] == XXX))
		{
			//PostQuitMessage(0);
			Xwin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 6-7-8////////////////////
		else if ((bingo[2][0] == XXX) && (bingo[2][1] == XXX) && (bingo[2][2] == XXX))
		{
			//PostQuitMessage(0);
			Xwin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 0-3-6////////////////////
		else if ((bingo[0][0] == XXX) && (bingo[1][0] == XXX) && (bingo[2][0] == XXX))
		{
			//PostQuitMessage(0);
			Xwin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 1-4-7////////////////////
		else if ((bingo[0][1] == XXX) && (bingo[1][1] == XXX) && (bingo[2][1] == XXX))
		{
			//PostQuitMessage(0);
			Xwin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 2-5-8////////////////////
		else if ((bingo[0][2] == XXX) && (bingo[1][2] == XXX) && (bingo[2][2] == XXX))
		{
			//PostQuitMessage(0);
			Xwin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 0-4-8////////////////////
		else if ((bingo[0][0] == XXX) && (bingo[1][1] == XXX) && (bingo[2][2] == XXX))
		{
			//PostQuitMessage(0);
			Xwin++;
			GAMERESTART1();
			//break;
		}

		////////////////////IF BINGO 2-4-6////////////////////
		else if ((bingo[0][2] == XXX) && (bingo[1][1] == XXX) && (bingo[2][0] == XXX))
		{
			//PostQuitMessage(0);
			Xwin++;
			GAMERESTART1();
			//break;
		}

		GAMERESTART0();
		
		SelectObject(hdc, hFont_temp);	// hFont를 지우기 위해서 hdc의 폰트를 hFont_temp로 바꿔준다.
		DeleteObject(hFont);

		EndPaint(hWnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		return 0;

	case WM_DESTROY:	//Destroy Window(Disappear From Memory, Alt+F4)
		KillTimer(hWnd,1);	//1 Timer Quit

		//Send WM_QUIT To GetMessage Function
		//GetMessage Return FALSE And Exit While-Loop. Therefore Quit Window Program
		PostQuitMessage(0);	
		return 0;	//Always Return 0, After Message Process
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));	//Default Message Process
}
		
//No Wins...
void GAMERESTART0()
{
		//Game End And Restart...
		if ((flag[0]==true) && (flag[1]==true) && (flag[2]==true) &&
			(flag[3]==true) && (flag[4]==true) && (flag[5]==true) &&
			(flag[6]==true) && (flag[7]==true) && (flag[8]==true))
		{
			int i=0;
			int j=0;
			
			//Set Flag To False...
			for (i=0;i<9;i++)
				flag[i] = false;

			//Set Bingo To 3... 3 -> Empty
			for (i=0;i<3;i++)
				for (j=0;j<3;j++)
					bingo[i][j] = 3;

			//BILL Text Flag Set To True
			BILL_FLAG = true;
			
			//Reset Game
			RESET = true;

			//Game Count;
			GAME_NUM++;
	
		}
}


//When O or X Wins
void GAMERESTART1()
{
	int i=0;
	int j=0;
			
	//Set Flag To False...
	for (i=0;i<9;i++)
		flag[i] = false;

	//Set Bingo To 3... 3 -> Empty
	for (i=0;i<3;i++)
		for (j=0;j<3;j++)
			bingo[i][j] = 3;

	//BILL Text Flag Set To True
	BILL_FLAG = true;
		
	//Reset Game
	RESET = true;

	//Game Count;
	GAME_NUM++;
}
