////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Direct SDK 설치가 설치되어 있어야 함
// DirectX 테스트
////////////////////////////////////////////////////////////////////////////////////
#pragma comment(linker, "/subsystem:windows")	// 윈도우 프로그램 시작시

#include <windows.h>
#include <time.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9shape.h>	// 도형 mesh(shape) 을 사용하기 위해서

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//Window Procedure
HINSTANCE g_hInst;	//Global Instance Declare
LPSTR lpszClass = "BILL's Basic Windows";	//This Window Program(Class) Name
HWND				g_hWnd			= NULL;

// DX 사용을 위한 변수
LPDIRECT3D9				g_pD3D			= NULL;
LPDIRECT3DDEVICE9		g_pd3dDevice	= NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
LPDIRECT3DTEXTURE9      g_pTexture      = NULL;


LPD3DXMESH				g_pMBox			= NULL;
LPD3DXMESH				g_pMTeapot		= NULL;


float					g_fSpinX		= 0.0f;
float					g_fSpinY		= 0.0f;
float					g_fSpinZ		= 0.0f;

void InitDX3D();
void ReleaseDX3D();
void Render();

//Program Start Point(Entry)
int APIENTRY WinMain(HINSTANCE hInstance,	//Window Program Instance Handle
					 HINSTANCE hPreInstance,	//PreExecute Window Program Instance Handle
					 LPSTR lpszCmdParam,	//Command Input Parameter ('argv' in DOS)
					 int nCmdShow)	//When Window Program Execute, Window's Shape
{
	g_hInst = hInstance;	//WinMain's Instance -> Global Instance
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
	g_hWnd=CreateWindow(lpszClass,	//Windows Class Name
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
	ShowWindow(g_hWnd,	//A Handle To Show Window
			nCmdShow);	//Show Window Method(SW_HIDE, SW_MINIMIZE, SW_RESTORE, SW_SHOW, SW_SHOWNORMAL)



	InitDX3D();

	// GetMessage 는 메시지가 발생할때까지 대기하기때문에 계속 렌더링하기 위해서 사용하지 않고 PeekMessage()를 사용하도록 한다.
	//while(GetMessage(&Message, NULL, 0, 0))
	while (1)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&Message);	//WM_KEYDOWN Message Occur, Make WM_CHAR
			DispatchMessage(&Message);	//Message Transfer To WndPro(Window Procedure)
		}
		else
		{
			Render();
		}
	}


	ReleaseDX3D();


	return Message.wParam;	//Return Message's Additional Information(exit(0) In DOS)
	
}

//Window Procedure Function Call By OS  -> We Called 'CALLBACK Function'
LRESULT CALLBACK WndProc(HWND hWnd,	//Handle Of Window
						 UINT iMessage,	//Kind Of Message
						 WPARAM wParam,	//Message's Additional Information
						 LPARAM lParam)	//Message's Additional Information
{
	static HANDLE hTimer;
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
		//InvalidateRect(hWnd, NULL, TRUE);
		g_fSpinX += 1.0f;
		g_fSpinY +=	1.0f;
		g_fSpinZ += 1.0f;
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


// DirectX 3D 초기화
void InitDX3D()
{
	// direct3d 객체 생성
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DDISPLAYMODE d3ddm;
	// 어댑터 디스플레이 모드 파악
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;

	// 이중버퍼링에서
	// front buffer 는 실제 화면에 뿌려지 버퍼
	// back buffer 는 front buffer 에 복사하기 위한 버퍼
	// 이중버퍼링과 비슷한 방법으로 page flipping 방법 선택
	// 그래픽카드에서 front buffer 와 back buffer 가 서로 역활을 바꿔가며 출력하도록 한다
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// 디스플레이를 하기 위한 장치 생성
	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice);



	// 카메라
	D3DXVECTOR3 vecEye(-5.0f, 5.0f, -10.0f);	// 보는 위치
	D3DXVECTOR3 vecAt(0.0f, 0.0f, 0.0f);	// 대상 물체의 위치
	D3DXVECTOR3 vecUp(0.0f, 1.0f, 0.0f);	// 위쪽 방향을 나타냄(보통 y축과 일치시킴)
	D3DXMATRIX matView;
	// 왼손 좌표계에서 매트릭스 생성
	D3DXMatrixLookAtLH(&matView, &vecEye, &vecAt, &vecUp);
	// 카메라 적용
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	
	// 투영(시점)
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,
								D3DXToRadian(45.0f),	// 시야각
								1.0f,	// 종횡비(너비/높이)
								1.0f,	// 가까운 거리(가까운 것 보다 가까운면 그리지 않는다.)
								200.0f	// 먼거리(먼거리 보다 먼 경우 그리지 않는다.)
								);
	// 투영 적용
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);



	// 라이트 끄기(빛에 반응하는 색이 아닌 그대로의 색을 표현하기 위함)
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING,  FALSE);
	//g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);
	// 와이어프레임으로 렌더링하기
	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// 컬링(후면은 제외하고 그리기)하지 않기
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 상자 메시 생성
	//D3DXCreateBox(g_pd3dDevice, 1.0f, 1.0f, 1.0f, &g_pMBox, NULL);

	// 주전자 메시 생성
	D3DXCreateTeapot(g_pd3dDevice, &g_pMTeapot, NULL);
	

}

// DirectX 3D 해제
void ReleaseDX3D()
{
	if (g_pMBox != NULL)
	{
		g_pMBox->Release();
		g_pMBox = NULL;
	}
	if (g_pMTeapot != NULL)
	{
		g_pMTeapot->Release();
		g_pMTeapot = NULL;
	}
	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
	if (g_pTexture != NULL)
	{
		g_pTexture->Release();
		g_pTexture = NULL;
	}
	if (g_pd3dDevice != NULL)
	{
		g_pd3dDevice->Release();
	}
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
	}
}

// 렌더링하기
void Render()
{
	if (g_pd3dDevice == NULL)
	{
		return;
	}
	// back buffer 지우기
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f), 1.0f, 0);

	// 화면 시작
	g_pd3dDevice->BeginScene();


	// 출력하기
	if (g_pMBox != NULL)
	{
		g_pMBox->DrawSubset(0);
	}
	if (g_pMTeapot != NULL)
	{
		g_pMTeapot->DrawSubset(0);
	}

	// 회전
	D3DXMATRIX matRot;
	D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(g_fSpinX), D3DXToRadian(g_fSpinY), D3DXToRadian(g_fSpinZ));
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matRot);


	// 화면 종료
	g_pd3dDevice->EndScene();

	// page flipping 방식이기 때문에 back buffer 와 front buffer 의 역활을 바꾼다.
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
