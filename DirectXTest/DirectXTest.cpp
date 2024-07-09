////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Direct SDK ��ġ�� ��ġ�Ǿ� �־�� ��
// DirectX �׽�Ʈ
////////////////////////////////////////////////////////////////////////////////////
#pragma comment(linker, "/subsystem:windows")	// ������ ���α׷� ���۽�

#include <windows.h>
#include <time.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9shape.h>	// ���� mesh(shape) �� ����ϱ� ���ؼ�

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//Window Procedure
HINSTANCE g_hInst;	//Global Instance Declare
LPSTR lpszClass = "BILL's Basic Windows";	//This Window Program(Class) Name
HWND				g_hWnd			= NULL;

// DX ����� ���� ����
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

	// GetMessage �� �޽����� �߻��Ҷ����� ����ϱ⶧���� ��� �������ϱ� ���ؼ� ������� �ʰ� PeekMessage()�� ����ϵ��� �Ѵ�.
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


// DirectX 3D �ʱ�ȭ
void InitDX3D()
{
	// direct3d ��ü ����
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DDISPLAYMODE d3ddm;
	// ����� ���÷��� ��� �ľ�
	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;

	// ���߹��۸�����
	// front buffer �� ���� ȭ�鿡 �ѷ��� ����
	// back buffer �� front buffer �� �����ϱ� ���� ����
	// ���߹��۸��� ����� ������� page flipping ��� ����
	// �׷���ī�忡�� front buffer �� back buffer �� ���� ��Ȱ�� �ٲ㰡�� ����ϵ��� �Ѵ�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// ���÷��̸� �ϱ� ���� ��ġ ����
	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice);



	// ī�޶�
	D3DXVECTOR3 vecEye(-5.0f, 5.0f, -10.0f);	// ���� ��ġ
	D3DXVECTOR3 vecAt(0.0f, 0.0f, 0.0f);	// ��� ��ü�� ��ġ
	D3DXVECTOR3 vecUp(0.0f, 1.0f, 0.0f);	// ���� ������ ��Ÿ��(���� y��� ��ġ��Ŵ)
	D3DXMATRIX matView;
	// �޼� ��ǥ�迡�� ��Ʈ���� ����
	D3DXMatrixLookAtLH(&matView, &vecEye, &vecAt, &vecUp);
	// ī�޶� ����
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	
	// ����(����)
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,
								D3DXToRadian(45.0f),	// �þ߰�
								1.0f,	// ��Ⱦ��(�ʺ�/����)
								1.0f,	// ����� �Ÿ�(����� �� ���� ������ �׸��� �ʴ´�.)
								200.0f	// �հŸ�(�հŸ� ���� �� ��� �׸��� �ʴ´�.)
								);
	// ���� ����
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);



	// ����Ʈ ����(���� �����ϴ� ���� �ƴ� �״���� ���� ǥ���ϱ� ����)
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING,  FALSE);
	//g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);
	// ���̾����������� �������ϱ�
	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// �ø�(�ĸ��� �����ϰ� �׸���)���� �ʱ�
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ���� �޽� ����
	//D3DXCreateBox(g_pd3dDevice, 1.0f, 1.0f, 1.0f, &g_pMBox, NULL);

	// ������ �޽� ����
	D3DXCreateTeapot(g_pd3dDevice, &g_pMTeapot, NULL);
	

}

// DirectX 3D ����
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

// �������ϱ�
void Render()
{
	if (g_pd3dDevice == NULL)
	{
		return;
	}
	// back buffer �����
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f), 1.0f, 0);

	// ȭ�� ����
	g_pd3dDevice->BeginScene();


	// ����ϱ�
	if (g_pMBox != NULL)
	{
		g_pMBox->DrawSubset(0);
	}
	if (g_pMTeapot != NULL)
	{
		g_pMTeapot->DrawSubset(0);
	}

	// ȸ��
	D3DXMATRIX matRot;
	D3DXMatrixRotationYawPitchRoll(&matRot, D3DXToRadian(g_fSpinX), D3DXToRadian(g_fSpinY), D3DXToRadian(g_fSpinZ));
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matRot);


	// ȭ�� ����
	g_pd3dDevice->EndScene();

	// page flipping ����̱� ������ back buffer �� front buffer �� ��Ȱ�� �ٲ۴�.
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
