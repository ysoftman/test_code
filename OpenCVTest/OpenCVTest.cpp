////////////////////////////////////////////
// ysoftman
// OpenCV �׽�Ʈ - �̹��� ���� ����
////////////////////////////////////////////
//#pragma comment(linker, "/subsystem:console")	// �ܼ� ���α׷� ���۽�
#pragma comment(linker, "/subsystem:windows")	// ������ ���α׷� ���۽�

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

// http://opencv.org �ٿ�޾� ./opencv �� .h .lib .dll �� ��ġ��Ų��. 
// OpenCV Library ���� ��� ���� �߰�.
#include "./opencv/cv.h"
#include "./opencv/cxcore.h"
#include "./opencv/highgui.h"

// OpenCV Library ���� ���̺귯�� �߰�
// lib �� ���ؼ� dll �� �����Ѵ�.
// dll ���ϵ��� exe �� ���� �־�� �Ѵ�.
#ifdef _DEBUG
#pragma comment(lib, "./opencv/cxcore200d.lib")
#pragma comment(lib, "./opencv/cv200d.lib")
#pragma comment(lib, "./opencv/highgui200d.lib")
#else
#pragma comment(lib, "./opencv/cxcore200.lib")
#pragma comment(lib, "./opencv/cv200.lib")
#pragma comment(lib, "./opencv/highgui200.lib")
#endif



#define	ID_STATIC_COMMENT			200
#define ID_BUTTON_SET_LEFT_TOP		300
#define ID_BUTTON_SET_RIGHT_BOTTOM	310
#define ID_BUTTON_START				400
#define ID_BUTTON_END				410
#define ID_BUTTON_CAPTURE_FRAME		500
#define ID_BUTTON_TO_FIND_OBJECT	600

HWND hStaticComment = NULL;
HWND hButtonSetLeftTop = NULL;
HWND hButtonSetRightBottom = NULL;
HWND hButtonStart = NULL;
HWND hButtonEnd = NULL;
HWND hButtonCaptureFrame = NULL;
HWND hButtonToFindObject = NULL;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//Window Procedure
HINSTANCE g_hInst;	//Global Instance Declare

LRESULT CALLBACK ViewWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



int OpenCV_ViewImage(IplImage *pImage)
{
	if (pImage != NULL)
	{
		char *pWindowName = "View Image";
		// �̹��� â ����
		cvNamedWindow(pWindowName, CV_WINDOW_AUTOSIZE);
		// �̹��� â�� �̹��� �Ѹ��� 
		cvShowImage(pWindowName, pImage);

		// Ű���� �Է� ��ٸ���
		cvWaitKey(0);

		// â �ݱ�
		cvDestroyWindow(pWindowName);
	}

	return 0;
}

IplImage *OpenCV_BitmapToIplImage(HDC hMemDC, BITMAPINFO bmi, HBITMAP hBitmap)
{
	IplImage *pImage = NULL;
	pImage = cvCreateImage(cvSize(bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight), IPL_DEPTH_8U, 3);
	pImage->origin = 1;
	GetDIBits(hMemDC, hBitmap, 0, bmi.bmiHeader.biHeight, pImage->imageData, &bmi, DIB_RGB_COLORS);

	if (pImage != NULL)
	{
		return pImage;
	}

	return NULL;
}

RECT OpenCV_FindObject(IplImage *pTargetImage, IplImage *pToFindObject)
{
	RECT rt;
	rt.left = 0;
	rt.top = 0;
	rt.right = 0;
	rt.bottom = 0;
	int MatchWidth = (pTargetImage->width - pToFindObject->width) + 1;
	int MatchHeight = (pTargetImage->height - pToFindObject->height) + 1;

	// ��ġ�Ǵ� �κ��� ã�� ���� ���Ǵ� ����
	IplImage *pMatch = cvCreateImage(cvSize(MatchWidth, MatchHeight), IPL_DEPTH_32F, 1);
	
	// ��ġ�غ���
	//#define  CV_TM_SQDIFF        0
	//#define  CV_TM_SQDIFF_NORMED 1
	//#define  CV_TM_CCORR         2
	//#define  CV_TM_CCORR_NORMED  3
	//#define  CV_TM_CCOEFF        4
	//#define  CV_TM_CCOEFF_NORMED 5
	cvMatchTemplate(pTargetImage, pToFindObject, pMatch, 5);

	double min = 0;
	double max = 0;
	CvPoint left_top;
	// ���� ũ�� ��ġ�Ǵ� �κ��� left top ��ġ ã��
	cvMinMaxLoc(pMatch, &min, &max, NULL, &left_top);

	cvReleaseImage(&pMatch);

	rt.left = left_top.x;
	rt.top = left_top.y;
	return rt;
}


int OpenCV_GetImageFromVideo(char *pVideoFileName)
{
	IplImage *pImage;
	CvCapture *cap = cvCreateFileCapture(pVideoFileName);
	if (cap != NULL)
	{
		// �������̹��� ���
		pImage = cvRetrieveFrame(cap);
		if (pImage != NULL)
		{
			char *pWindowName = "Video Test";
			// �̹��� â ����
			cvNamedWindow(pWindowName, CV_WINDOW_AUTOSIZE);
			// �̹��� â�� �̹��� �Ѹ��� 
			cvShowImage(pWindowName, pImage);

			// Ű���� �Է� ��ٸ���
			cvWaitKey(0);

			// ���ҽ� ����
			cvReleaseImage(&pImage);

			// â �ݱ�
			cvDestroyWindow(pWindowName);
		}


		//capture.PosMsec = 1000 * 60 * (i + 1);      // 1�и��� �ϳ��� 15��.
		//Cv.QueryFrame(capture).ToBitmap().Save("test" + i.ToString() + ".jpg");	// �̹����� ����

		cvReleaseCapture(&cap);
		return 0;
	}
	return -1;
}


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
	WndClass.hbrBackground=(HBRUSH)GetStockObject(DKGRAY_BRUSH);	//Window Background Color(Using GetStockObject Function)
	WndClass.lpszMenuName=NULL;	//When Use Menu, Menu Name. If Non Menu, NULL
	WndClass.lpszClassName=(LPSTR)"OpenCV Test";;	//Window Class Name
	if (!RegisterClass(&WndClass))	//Register Window Class For OS
	{
		MessageBox(NULL, "Register MainWindow Class error", "Error", MB_OK);
	}
	
	// Create Window
	hMainWnd=CreateWindow((LPSTR)("OpenCV Test"),	//Windows Class Name
		(LPSTR)("OpenCV Test Window"),	//Window Title Bar Name
		//WS_OVERLAPPEDWINDOW,	//Window Style(WS_OVERLAPPEDWINDOW -> Basic Style)
		WS_BORDER | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT,	//X Vertex(Location)
		CW_USEDEFAULT,	//Y Vertex(Location)
		800,	//Window Width(Scale)
		600,	//Window Height(Scale)
		NULL,	//Parent Window And Child Window Handle(When Use MDI Window Program)
		(HMENU)NULL,	//Window Menu(If Value Is NULL, WndClass Use)
		hInstance,	//Window Program Handle
		NULL);	//CREATESTRUCT Struct Address For Special Purpose(Usually NULL)
	
	ShowWindow(hMainWnd,nCmdShow);

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
	static char szStaticRect[1024];
	memset(szStaticRect, 0, 1024);

	static char szFindObjectRect[1024];
	memset(szFindObjectRect, 0, 1024);

	static RECT rtTarget;

	static RECT rtTargetView;
	rtTargetView.left = 5;
	rtTargetView.top = 5;
	rtTargetView.right = 305;
	rtTargetView.bottom = 505;

	static RECT rtTargetText;
	rtTargetText.left = 350;
	rtTargetText.top = 5;
	rtTargetText.right = rtTargetText.left + 1000;
	rtTargetText.bottom = rtTargetText.top + 20;

	static RECT rtFindObject;
	static RECT rtFindObjectText;
	rtFindObjectText.left = 350;
	rtFindObjectText.top = 30;
	rtFindObjectText.right = rtFindObjectText.left + 1000;
	rtFindObjectText.bottom = rtFindObjectText.top + 20;

	static bool bSetLeftTop = false;
	static bool bSetRightBottom = false;
	static bool bSetStart = false;

	static IplImage *pToFindObject = NULL;
	static IplImage *pTargetImage = NULL;

	POINT pt;
	PAINTSTRUCT ps;
	HDC hDC;
	HDC hDesktopDC;
	HDC hMemDC;
	BITMAPINFO bmi;
	HBITMAP hBitmap;
	HGDIOBJ oldhBitmap;

	HBRUSH		MyBrush,OldBrush;
	//HPEN		Mypen,OldPen;


	switch(iMessage)	//What Kind Of Message Occur
	{
	case WM_CREATE:	//Create Window Message
		hButtonSetLeftTop = CreateWindow((LPCTSTR)"button", "Set Left Top", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 50, 120, 50, hWnd, (HMENU)ID_BUTTON_SET_LEFT_TOP, g_hInst, NULL);
		hButtonSetRightBottom = CreateWindow((LPCTSTR)"button", "Set Right Bottom", WS_CHILD | WS_VISIBLE | WS_BORDER, 500, 50, 120, 50, hWnd, (HMENU)ID_BUTTON_SET_RIGHT_BOTTOM, g_hInst, NULL);

		hButtonCaptureFrame = CreateWindow((LPCTSTR)"button", "Capture Frame", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 110, 120, 50, hWnd, (HMENU)ID_BUTTON_CAPTURE_FRAME, g_hInst, NULL);
		hButtonToFindObject = CreateWindow((LPCTSTR)"button", "To Find Object", WS_CHILD | WS_VISIBLE | WS_BORDER, 500, 110, 120, 50, hWnd, (HMENU)ID_BUTTON_TO_FIND_OBJECT, g_hInst, NULL);

		hButtonStart = CreateWindow((LPCTSTR)"button", "Start", WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 170, 120, 50, hWnd, (HMENU)ID_BUTTON_START, g_hInst, NULL);
		hButtonEnd = CreateWindow((LPCTSTR)"button", "End", WS_CHILD | WS_VISIBLE | WS_BORDER, 500, 170, 120, 50, hWnd, (HMENU)ID_BUTTON_END, g_hInst, NULL);

		hStaticComment = CreateWindow((LPCTSTR)"static", "OpenCV Test By ysoftman\n�����\n1.��� ���� ����\n2.ã�� ��ü����\n3.�����ϱ�\n4.�����ϱ�",
									WS_CHILD | WS_VISIBLE | WS_BORDER, 350, 300, 250, 100, hWnd, (HMENU)ID_STATIC_COMMENT, g_hInst, NULL);

		::EnableWindow(hButtonSetLeftTop, true);
		::EnableWindow(hButtonSetRightBottom, true);

		::EnableWindow(hButtonCaptureFrame, true);
		::EnableWindow(hButtonToFindObject, true);

		::EnableWindow(hButtonStart, false);
		::EnableWindow(hButtonEnd, false);

		// Ÿ�̸� ����
		SetTimer(hWnd, 1, 100, NULL);	
		break;

	case WM_TIMER:
		InvalidateRect(hWnd, &rtTargetView, false);

		// ã�� ���� ����ǥ���ϴ� �κ�
		InvalidateRect(hWnd, &rtFindObjectText, false);
		break;


	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		
		if (rtTarget.left != 0 && rtTarget.top != 0 && rtTarget.right != 0 && rtTarget.bottom != 0)
		{
			// ��ü ȭ�鿡 ���� DC ����
			hDesktopDC = ::GetDC(NULL);

			// �޸� DC ����
			hMemDC = ::CreateCompatibleDC(hDesktopDC);

			// �ش��ϴ� ũ��� ��Ʈ�� ����
			hBitmap = ::CreateCompatibleBitmap(hDesktopDC, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

			// �޸� DC ����
			oldhBitmap = ::SelectObject(hMemDC, hBitmap);

			// �޸� DC �� �׸���
			::BitBlt(hMemDC, 0, 0, rtTargetView.right-rtTargetView.left, rtTargetView.bottom-rtTargetView.top, hDesktopDC, rtTarget.left, rtTarget.top, SRCCOPY);

			// ȭ�鿡 �׸���
			::BitBlt(hDC, rtTargetView.left, rtTargetView.top, rtTargetView.right-rtTargetView.left, rtTargetView.bottom-rtTargetView.top, hMemDC, 0, 0, SRCCOPY);


			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biBitCount = 24;
			bmi.bmiHeader.biWidth = (rtTargetView.right-rtTargetView.left);
			bmi.bmiHeader.biHeight = (rtTargetView.bottom-rtTargetView.top);
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biCompression = BI_RGB;

			if (pTargetImage != NULL)
			{
				cvReleaseImage(&pTargetImage);
			}
			pTargetImage = OpenCV_BitmapToIplImage(hMemDC, bmi, hBitmap);

			if (bSetStart && pToFindObject != NULL)
			{
				rtFindObject = OpenCV_FindObject(pTargetImage, pToFindObject);

				// OpenCV ���� �̹����� �ݴ��
				rtFindObject.top = pTargetImage->height - rtFindObject.top - pToFindObject->height;
				rtFindObject.right += rtFindObject.left + pToFindObject->width;
				rtFindObject.bottom += rtFindObject.top + pToFindObject->height;

				//MyBrush = (HBRUSH)GetStockObject(WHITE_PEN);
				MyBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
				OldBrush = (HBRUSH)SelectObject(hDC, MyBrush);
				//Mypen = CreatePen(NULL, 1, RGB(255,0,0));
				//Mypen = CreatePen(PS_DOT, 1, RGB(255,0,0));
				//OldPen = (HPEN)SelectObject(hDC, Mypen);

				Rectangle(hDC, rtFindObject.left, rtFindObject.top, rtFindObject.right, rtFindObject.bottom);

				//SelectObject(hDC, OldPen);
				SelectObject(hDC, OldBrush);			

			}
			

			::SelectObject(hMemDC, oldhBitmap);
			::ReleaseDC(NULL, hDesktopDC);
			::DeleteDC(hMemDC);
			::DeleteObject(oldhBitmap);
			::DeleteObject(hBitmap);

		}

		//SetBkMode(hdc, OPAQUE);
		//SetBkMode(hdc, TRANSPARENT);
		// ���� ����
		//SetBkColor(hdc, RGB(255,255,255));
		// ���ڻ� ����
		//SetTextColor(hdc, RGB(0,0,0));
		memset(szStaticRect, 0, 1024);
		sprintf(szStaticRect, "Target Rect : %5d %5d %5d %5d", rtTarget.left, rtTarget.top, rtTarget.right, rtTarget.bottom);
		TextOut(hDC, rtTargetText.left, rtTargetText.top, szStaticRect, strlen(szStaticRect));

		memset(szFindObjectRect, 0, 1024);
		sprintf(szFindObjectRect, "Find Object Rect : %5d %5d %5d %5d", rtFindObject.left, rtFindObject.top, rtFindObject.right, rtFindObject.bottom);
		TextOut(hDC, rtFindObjectText.left, rtFindObjectText.top, szFindObjectRect, strlen(szFindObjectRect));


		::ReleaseDC(NULL, hDC);


		EndPaint(hWnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:
		
		if (bSetLeftTop)
		{
			GetCursorPos(&pt);
			rtTarget.left = pt.x;
			rtTarget.top = pt.y;

			InvalidateRect(hWnd, &rtTargetText, true);
		}
		else if (bSetRightBottom)
		{
			GetCursorPos(&pt);
			rtTarget.right = pt.x;
			rtTarget.bottom = pt.y;

			InvalidateRect(hWnd, &rtTargetText, true);
		}

		break;

	//case WM_MOUSEMOVE:
	//	if (GetCapture() == hWnd)
	//	{
	//		GetCursorPos(&pt);
	//		if (bSetLeftTop)
	//		{
	//			GetCursorPos(&pt);
	//			rtTarget.left = pt.x;
	//			rtTarget.top = pt.y;
	//		}
	//		else if (bSetRightBottom)
	//		{
	//			GetCursorPos(&pt);
	//			rtTarget.right = pt.x;
	//			rtTarget.bottom = pt.y;
	//		}
	//		InvalidateRect(hWnd, &rtTargetText, true);
	//	}
	//	break;

	case WM_LBUTTONUP:
		if (bSetLeftTop || bSetRightBottom)
		{
			ReleaseCapture();
			bSetLeftTop = false;
			bSetRightBottom = false;
		}
		break;

	case WM_KEYDOWN:
		if (wParam == 'a' || wParam == 'A') MessageBox(hWnd, "aaa", "ysoftman", MB_OK);
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))	// ��Ʈ�� ID
		{
		case ID_BUTTON_SET_LEFT_TOP:
			SetCapture(hWnd);
			bSetLeftTop = true;
			break;

		case ID_BUTTON_SET_RIGHT_BOTTOM:
			SetCapture(hWnd);
			bSetRightBottom = true;
			break;

		case ID_BUTTON_CAPTURE_FRAME:
			if (pTargetImage != NULL)
			{
				OpenCV_ViewImage(pTargetImage);
			}
			break;

		case ID_BUTTON_TO_FIND_OBJECT:
			if (pToFindObject != NULL)
			{
				cvReleaseImage(&pToFindObject);
			}
			pToFindObject = cvLoadImage("TargetObject.png", CV_LOAD_IMAGE_COLOR);
			OpenCV_ViewImage(pToFindObject);
			::EnableWindow(hButtonStart, true);
			break;

		case ID_BUTTON_START:
			bSetStart = true;
			::EnableWindow(hButtonEnd, true);
			break;

		case ID_BUTTON_END:
			SetFocus(hWnd);	// WM_KEYDOWN �� ���� �� �ֵ��� �ϱ� ���ؼ� 
			bSetStart = false;
			cvReleaseImage(&pTargetImage);
			pTargetImage = NULL;
			cvReleaseImage(&pToFindObject);
			pToFindObject = NULL;

			::EnableWindow(hButtonStart, false);
			::EnableWindow(hButtonEnd, false);
			break;

		}
		break;



	case WM_DESTROY:	//Destroy Window(Disappear From Memory, Alt+F4)
		//Send WM_QUIT To GetMessage Function
		//GetMessage Return FALSE And Exit While-Loop. Therefore Quit Window Program
		PostQuitMessage(0);	
		return 0;	//Always Return 0, After Message Process
	}
	return (DefWindowProc(hWnd,iMessage,wParam,lParam));	//Default Message Process
}
