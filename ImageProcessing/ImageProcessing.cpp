////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Digital Image Processing Lecture
// Programming By YoonByoungHoon
////////////////////////////////////////////////////////////////////////////////////
// #pragma comment(linker, "/subsystem:console")	// 콘솔 프로그램 시작시
#pragma comment(linker, "/subsystem:windows") // 윈도우 프로그램 시작시

#include "ImageProcessing.h"

#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// #define MAX_LOADSTRING 100

// DCT DATA
#define PI 3.141592653589793238462643383279
#define COEFF                                                                  \
  0.707106781186547524400844362105 // 1 /
                                   // ROOT2(1.4142135623730950488016887242097...)

// Image Array
#define M 256
#define N 256

// RAW Image Scale
#define ROW 256 // Height
#define COL 256 // Width

// RAW Frame Scale table tennis 74, table tennis 75
#define FROW 240 // Height
#define FCOL 352 // Width

#define szImageInputClass (LPSTR) "ImageInputClass"
#define szImageOutputClass (LPSTR) "ImageOutputClass"

#define szImageFrame1InputClass (LPSTR) "Frame1InputClass"
#define szImageFrame2InputClass (LPSTR) "Frame2InputClass"

#define szImageLPFClass (LPSTR) "LPFImageClass"
#define szImageHPFClass (LPSTR) "HPFImageClass"
#define szImageMFClass (LPSTR) "MFImageClass"
#define szImageHFEFClass (LPSTR) "HFEFImageClass"
#define szImageBNClass (LPSTR) "BNImageClass"
#define szImageWNClass (LPSTR) "WNImageClass"
#define szImageBWNClass (LPSTR) "BWNImageClass"
#define szImageErosionClass (LPSTR) "ErosionImageClass"
#define szImageDilationClass (LPSTR) "DilationImageClass"
#define szImageOpeningClass (LPSTR) "OpeningImageClass"
#define szImageClosingClass (LPSTR) "ClosingImageClass"
#define szImageBinaryClass (LPSTR) "BinaryImageClass"
#define szImageThinningClass (LPSTR) "ThinningImageClass"

#define szImageDCTClass (LPSTR) "DCTImageClass"
#define szImageIDCTClass (LPSTR) "IDCTImageClass"
#define szImageHARDAMARDClass (LPSTR) "HARDAMARDClass"
#define szImageIHARDAMARDClass (LPSTR) "IHARDAMARDClass"
#define szImageWAVELETClass (LPSTR) "WAVELETClass"
#define szImageIWAVELETClass (LPSTR) "IWAVELETClass"

// For JPEG
#define szImageDCT_JPEGClass (LPSTR) "DCT_JPEGClass"
#define szImageQuantization_JPEGClass (LPSTR) "Quantization_JPEGClass"
#define szImageIQuantization_JPEGClass (LPSTR) "IQuantization_JPEGClass"
#define szImageIDCT_JPEGClass (LPSTR) "IDCT_JPEGClass"

// Make Frame 1'
#define szImageMakeF1_Class (LPSTR) "MakeF1_Class"
// Make Frame 2 - Frame 1'
#define szImageMakeF2F1_Class (LPSTR) "MakeF2F1_Class"
// Make Result Frame
#define szImageMakeRFClass (LPSTR) "MakeRFClass"

// char buf[ROW][COL];	//For Load RAW Image
unsigned char buf[ROW][COL]; // For Load RAW Image(Original Image)

unsigned char f1_buf[FROW][FCOL]; // For Frame1 Image Input
unsigned char f2_buf[FROW][FCOL]; // For Frame2 Image Input

unsigned char TImage[ROW][COL]; // For Temp Image
unsigned char rgbtemp;          // For RGB Value

//////////////////////////////////////////////////////////////////////
// Input Image Buffer
unsigned char InputImage[ROW][COL];
// Output Image Buffer
unsigned char OutputImage[ROW][COL];
// Input Frame1 Image Buffer
unsigned char InputFrame1Image[FROW][FCOL];
// Input Frame2 Image Buffer
unsigned char InputFrame2Image[FROW][FCOL];

// LPF Image Buffer
unsigned char LPFImage[ROW][COL];
// HPF Image Buffer
unsigned char HPFImage[ROW][COL];
// MF Image Buffer
unsigned char MFImage[ROW][COL];
// HFEF Image Buffer
unsigned char HFEFImage[ROW][COL];
// BN Image Buffer
unsigned char BNImage[ROW][COL];
// WN Image Buffer
unsigned char WNImage[ROW][COL];
// BWN Image Buffer
unsigned char BWNImage[ROW][COL];
// Erosion Image Buffer
unsigned char ErosionImage[ROW][COL];
// Dilation Image Buffer
unsigned char DilationImage[ROW][COL];
// Opening Image Buffer
unsigned char OpeningImage[ROW][COL];
// Closing Image Buffer
unsigned char ClosingImage[ROW][COL];
// Thinning Image Buffer
unsigned char ThinningImage[ROW][COL];
// Binary Image
unsigned char BinaryImage[ROW][COL];
// HM Image
unsigned char HMImage[ROW][COL]; // Only Thinning (Hiss and Miss)

// DCT Image
// unsigned char DCTImage[ROW][COL];
double DCTImage[ROW][COL];
// IDCT Image
// unsigned char IDCTImage[ROW][COL];
double IDCTImage[ROW][COL];

// Hardamard Transform Image
double HARDAMARDImage[ROW][COL];
// IHardamard Transform Image
double IHARDAMARDImage[ROW][COL];

// Wavelet Transform Image
double WAVELETImage[ROW][COL];
// IWavelet Transform Image
double IWAVELETImage[ROW][COL];

// DCT_JPEG Image
double DCT_JPEGImage[ROW][COL];
// Quantization_JPEG Image
double Quantization_JPEGImage[ROW][COL];
// IQuantization_JPEG Image
double IQuantization_JPEGImage[ROW][COL];
// IDCT_JPEG Image
double IDCT_JPEGImage[ROW][COL];

// Make Frame 1'
double F1_Image[FROW][FCOL];
// Make Fraem 2 - Frame 1'
double F2F1_Image[FROW][FCOL];
// Make Result Frame
double RFImage[FROW][FCOL];

//////////////////////////////////////////////////////////////////////

// Image File Open
HANDLE hFile;

// Global Instanace
HINSTANCE g_hInst;

// Window Handle
HWND hMainWnd; // Main Window

HWND hc1;  // Open Image Window
HWND hc2;  // Output Image Window
HWND hcf1; // Open Frame1 Image Window
HWND hcf2; // Open Frame2 Image Window

HWND hc3;  // LPF Window
HWND hc4;  // HPF Window
HWND hc5;  // MF Window
HWND hc6;  // HFEF Window
HWND hc7;  // BlackNoise Window
HWND hc8;  // WhiteNoise Window
HWND hc9;  // Black & White Noise Window
HWND hc10; // Erosion Window
HWND hc11; // Dilation Window
HWND hc12; // Opening Window
HWND hc13; // Closing Window
HWND hc14; // Binary Image Window
HWND hc15; // Thinning Window
HWND hc16; // DCT Window
HWND hc17; // IDCT Window
HWND hc18; // Hardamard Window
HWND hc19; // IHardamard Window
HWND hc20; // Wavelet Window
HWND hc21; // IWavelet Window
HWND hc22; // DCT(For JPEG) Window
HWND hc23; // Quantization(For JPEG) Window
HWND hc24; // IQuantization(For JPEG) Window
HWND hc25; // IDCT(For JPEG) Window

HWND hc26; // f1' with Motion Vection(MV) Window
HWND hc27; // f2 - f1' Frame
HWND hc28; // Result Frame

LPCTSTR lpszClass = "Digital Image Processing - Yoon, Byoung Hoon";

// Raw Image File Open
void CreateImageInputWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageInputProc(HWND hWnd, UINT message, WPARAM wParam,
                                LPARAM lParam);

// Raw Image File Output
void CreateImageOutputWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageOutputProc(HWND hWnd, UINT message, WPARAM wParam,
                                 LPARAM lParam);

// Frame1 Image File Open
void CreateImageFrame1InputWindow(HWND hParent, int x, int y, int width,
                                  int height);
LRESULT CALLBACK ImageFrame1InputProc(HWND hWnd, UINT message, WPARAM wParam,
                                      LPARAM lParam);

// Frame2 Image File Open
void CreateImageFrame2InputWindow(HWND hParent, int x, int y, int width,
                                  int height);
LRESULT CALLBACK ImageFrame2InputProc(HWND hWnd, UINT message, WPARAM wParam,
                                      LPARAM lParam);

// LPF
void CreateImageLPFWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageLPFProc(HWND hWnd, UINT message, WPARAM wParam,
                              LPARAM lParam);

// HPF
void CreateImageHPFWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageHPFProc(HWND hWnd, UINT message, WPARAM wParam,
                              LPARAM lParam);

// MF
void CreateImageMFWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageMFProc(HWND hWnd, UINT message, WPARAM wParam,
                             LPARAM lParam);

// HFEF
void CreateImageHFEFWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageHFEFProc(HWND hWnd, UINT message, WPARAM wParam,
                               LPARAM lParam);

// BN
void CreateImageBNWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageBNProc(HWND hWnd, UINT message, WPARAM wParam,
                             LPARAM lParam);

// WN
void CreateImageWNWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageWNProc(HWND hWnd, UINT message, WPARAM wParam,
                             LPARAM lParam);

// BWN
void CreateImageBWNWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageBWNProc(HWND hWnd, UINT message, WPARAM wParam,
                              LPARAM lParam);

// Erosion
void CreateImageErosionWindow(HWND hParent, int x, int y, int width,
                              int height);
LRESULT CALLBACK ImageErosionProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam);

// Dilation
void CreateImageDilationWindow(HWND hParent, int x, int y, int width,
                               int height);
LRESULT CALLBACK ImageDilationProc(HWND hWnd, UINT message, WPARAM wParam,
                                   LPARAM lParam);

// Opening
void CreateImageOpeningWindow(HWND hParent, int x, int y, int width,
                              int height);
LRESULT CALLBACK ImageOpeningProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam);

// Closing
void CreateImageClosingWindow(HWND hParent, int x, int y, int width,
                              int height);
LRESULT CALLBACK ImageClosingProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam);

// Binary Image
void CreateImageBinaryWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageBinaryProc(HWND hWnd, UINT message, WPARAM wParam,
                                 LPARAM lParam);

// Thinning
void CreateImageThinningWindow(HWND hParent, int x, int y, int width,
                               int height);
LRESULT CALLBACK ImageThinningProc(HWND hWnd, UINT message, WPARAM wParam,
                                   LPARAM lParam);

// DCT
void CreateImageDCTWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageDCTProc(HWND hWnd, UINT message, WPARAM wParam,
                              LPARAM lParam);

// IDCT
void CreateImageIDCTWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageIDCTProc(HWND hWnd, UINT message, WPARAM wParam,
                               LPARAM lParam);

// HARDAMARD
void CreateImageHARDAMARDWindow(HWND hParent, int x, int y, int width,
                                int height);
LRESULT CALLBACK ImageHARDAMARDProc(HWND hWnd, UINT message, WPARAM wParam,
                                    LPARAM lParam);

// IHARDAMARD
void CreateImageIHARDAMARDWindow(HWND hParent, int x, int y, int width,
                                 int height);
LRESULT CALLBACK ImageIHARDAMARDProc(HWND hWnd, UINT message, WPARAM wParam,
                                     LPARAM lParam);

// WAVELET
void CreateImageWAVELETWindow(HWND hParent, int x, int y, int width,
                              int height);
LRESULT CALLBACK ImageWAVELETProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam);

// IWAVELET
void CreateImageIWAVELETWindow(HWND hParent, int x, int y, int width,
                               int height);
LRESULT CALLBACK ImageIWAVELETProc(HWND hWnd, UINT message, WPARAM wParam,
                                   LPARAM lParam);

// DCT_JPEG
void CreateImageDCT_JPEGWindow(HWND hParent, int x, int y, int width,
                               int height);
LRESULT CALLBACK ImageDCT_JPEGProc(HWND hWnd, UINT message, WPARAM wParam,
                                   LPARAM lParam);

// Quantization_JPEG
void CreateImageQuantization_JPEGWindow(HWND hParent, int x, int y, int width,
                                        int height);
LRESULT CALLBACK ImageQuantization_JPEGProc(HWND hWnd, UINT message,
                                            WPARAM wParam, LPARAM lParam);

// IQuantization_JPEG
void CreateImageIQuantization_JPEGWindow(HWND hParent, int x, int y, int width,
                                         int height);
LRESULT CALLBACK ImageIQuantization_JPEGProc(HWND hWnd, UINT message,
                                             WPARAM wParam, LPARAM lParam);

// IDCT_JPEG
void CreateImageIDCT_JPEGWindow(HWND hParent, int x, int y, int width,
                                int height);
LRESULT CALLBACK ImageIDCT_JPEGProc(HWND hWnd, UINT message, WPARAM wParam,
                                    LPARAM lParam);

// Make Frame 1'
void CreateImageMakeF1_Window(HWND hParent, int x, int y, int width,
                              int height);
LRESULT CALLBACK ImageMakeF1_Proc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam);

// Make Frame 2 - Frame 1'
void CreateImageMakeF2F1_Window(HWND hParent, int x, int y, int width,
                                int height);
LRESULT CALLBACK ImageMakeF2F1_Proc(HWND hWnd, UINT message, WPARAM wParam,
                                    LPARAM lParam);

// Result Frame
void CreateImageMakeRFWindow(HWND hParent, int x, int y, int width, int height);
LRESULT CALLBACK ImageMakeRFProc(HWND hWnd, UINT message, WPARAM wParam,
                                 LPARAM lParam);

// SetPixel 보다 빠르게 이미지 출력하기 위해
#define WIDTHBYTES(width, bitcount) ((((width * bitcount) + 31) & ~31) >> 3)
void DrawImage(HDC hdc, int width, int height, unsigned char (*pImage)[COL]) {
  // SetDIBitsToDevice 가 RGB 컬러만 지원하기 때문에 RGB 형태로 출력하도록 한다.
  int x = 0, y = 0;
  int widthbytes = WIDTHBYTES(width, 24);
  unsigned char *pBits = new unsigned char[height * widthbytes];
  memset(pBits, 0, (height * widthbytes) * sizeof(unsigned char));

  BITMAPINFO bmi;
  memset(&bmi, 0, sizeof(bmi));
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biBitCount = 24;
  bmi.bmiHeader.biWidth = width;
  bmi.bmiHeader.biHeight = -height;
  bmi.bmiHeader.biCompression = BI_RGB;
  bmi.bmiHeader.biSizeImage = height * widthbytes;
  bmi.bmiHeader.biClrUsed = 0;
  bmi.bmiHeader.biClrImportant = 0;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      pBits[y * widthbytes + (x * 3) + 0] = pImage[y][x]; // Blue
      pBits[y * widthbytes + (x * 3) + 1] = pImage[y][x]; // Green
      pBits[y * widthbytes + (x * 3) + 2] = pImage[y][x]; // Red
    }
  }

  SetDIBitsToDevice(hdc, 0, 0, width, height, 0, 0, 0, height,
                    (const void *)pBits, &bmi, DIB_RGB_COLORS);
  delete[] pBits;
}

void DrawImage2(HDC hdc, int width, int height, unsigned char (*pImage)[FCOL]) {
  // SetDIBitsToDevice 가 RGB 컬러만 지원하기 때문에 RGB 형태로 출력하도록 한다.
  int x = 0, y = 0;
  int widthbytes = WIDTHBYTES(width, 24);
  unsigned char *pBits = new unsigned char[height * widthbytes];
  memset(pBits, 0, (height * widthbytes) * sizeof(unsigned char));

  BITMAPINFO bmi;
  memset(&bmi, 0, sizeof(bmi));
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biBitCount = 24;
  bmi.bmiHeader.biWidth = width;
  bmi.bmiHeader.biHeight = -height;
  bmi.bmiHeader.biCompression = BI_RGB;
  bmi.bmiHeader.biSizeImage = height * widthbytes;
  bmi.bmiHeader.biClrUsed = 0;
  bmi.bmiHeader.biClrImportant = 0;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      pBits[y * widthbytes + (x * 3) + 0] = pImage[y][x]; // Blue
      pBits[y * widthbytes + (x * 3) + 1] = pImage[y][x]; // Green
      pBits[y * widthbytes + (x * 3) + 2] = pImage[y][x]; // Red
    }
  }

  SetDIBitsToDevice(hdc, 0, 0, width, height, 0, 0, 0, height,
                    (const void *)pBits, &bmi, DIB_RGB_COLORS);
  delete[] pBits;
}

// Global Variables:
// HINSTANCE hInst;	// Current instance
// TCHAR szTitle[MAX_LOADSTRING];	// The title bar text
// TCHAR szWindowClass[MAX_LOADSTRING];	// The title bar text

// Forward declarations of functions included in this code module:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow) {
  HACCEL hAccelTable;
  hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_ImageProcessing);

  if (!hAccelTable) {
    MessageBox(NULL, "Accelerator Load Fail", "Error", MB_OK);
  }

  // HWND hWnd;
  MSG Message;
  WNDCLASS WndClass;

  g_hInst = hInstance;

  // Common Window Class
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  // WndClass.hIcon=LoadIcon(NULL,IDI_ImageProcessing);
  WndClass.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_ImageProcessing);
  WndClass.hInstance = hInstance;
  WndClass.lpfnWndProc = (WNDPROC)WndProc; // Main Window Class Register
  WndClass.lpszClassName = lpszClass;
  // WndClass.lpszMenuName=MAKEINTRESOURCE(IDC_ImageProcessing);
  WndClass.lpszMenuName = (LPCSTR)IDC_ImageProcessing;
  WndClass.style = CS_HREDRAW | CS_VREDRAW;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register Main Window Error", "Error", MB_OK);
  }

  // Create Main Window
  hMainWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                          // GetSystemMetrics(SM_CXSCREEN),	//Get Max Width
                          CW_USEDEFAULT,
                          // GetSystemMetrics(SM_CYSCREEN),	//Get Max Height
                          NULL, (HMENU)NULL, hInstance, NULL);

  // Maximized Window
  ShowWindow(hMainWnd, SW_NORMAL);

  // Input File Image Class Register
  WndClass.lpfnWndProc = (WNDPROC)ImageInputProc;
  WndClass.lpszClassName = (LPSTR)szImageInputClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageInputClass Error", "Error", MB_OK);
  }

  // Output Image Class Register
  WndClass.lpfnWndProc = (WNDPROC)ImageOutputProc;
  WndClass.lpszClassName = (LPSTR)szImageOutputClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageOutputClass Error", "Error", MB_OK);
  }

  // Frame1 Input File Image Class Register
  WndClass.lpfnWndProc = (WNDPROC)ImageFrame1InputProc;
  WndClass.lpszClassName = (LPSTR)szImageFrame1InputClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageFrame1InputClass Error", "Error", MB_OK);
  }

  // Frame2 Input File Image Class Register
  WndClass.lpfnWndProc = (WNDPROC)ImageFrame2InputProc;
  WndClass.lpszClassName = (LPSTR)szImageFrame2InputClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageFrame2InputClass Error", "Error", MB_OK);
  }

  // LPF Image Class Register
  WndClass.lpfnWndProc = (WNDPROC)ImageLPFProc;
  WndClass.lpszClassName = (LPSTR)szImageLPFClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageLPFClass Error", "Error", MB_OK);
  }

  // HPF Image Class Register
  WndClass.lpfnWndProc = (WNDPROC)ImageHPFProc;
  WndClass.lpszClassName = (LPSTR)szImageHPFClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageHPFClass Error", "Error", MB_OK);
  }

  // MF Image Class Register
  WndClass.lpfnWndProc = (WNDPROC)ImageMFProc;
  WndClass.lpszClassName = (LPSTR)szImageMFClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageMFClass Error", "Error", MB_OK);
  }

  // HFEF Image Class Register
  WndClass.lpfnWndProc = (WNDPROC)ImageHFEFProc;
  WndClass.lpszClassName = (LPSTR)szImageHFEFClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageHFEFClass Error", "Error", MB_OK);
  }

  // BN
  WndClass.lpfnWndProc = (WNDPROC)ImageBNProc;
  WndClass.lpszClassName = (LPSTR)szImageBNClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageBNClass Error", "Error", MB_OK);
  }

  // WN
  WndClass.lpfnWndProc = (WNDPROC)ImageWNProc;
  WndClass.lpszClassName = (LPSTR)szImageWNClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageWNClass Error", "Error", MB_OK);
  }

  // BWN
  WndClass.lpfnWndProc = (WNDPROC)ImageBWNProc;
  WndClass.lpszClassName = (LPSTR)szImageBWNClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageBWNClass Error", "Error", MB_OK);
  }

  // Erosion
  WndClass.lpfnWndProc = (WNDPROC)ImageErosionProc;
  WndClass.lpszClassName = (LPSTR)szImageErosionClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageErosionClass Error", "Error", MB_OK);
  }

  // Dilation
  WndClass.lpfnWndProc = (WNDPROC)ImageDilationProc;
  WndClass.lpszClassName = (LPSTR)szImageDilationClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageDilationClass Error", "Error", MB_OK);
  }

  // Opening
  WndClass.lpfnWndProc = (WNDPROC)ImageOpeningProc;
  WndClass.lpszClassName = (LPSTR)szImageOpeningClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageOpeningClass Error", "Error", MB_OK);
  }

  // Closing
  WndClass.lpfnWndProc = (WNDPROC)ImageClosingProc;
  WndClass.lpszClassName = (LPSTR)szImageClosingClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageClosingClass Error", "Error", MB_OK);
  }

  // Binary Image
  WndClass.lpfnWndProc = (WNDPROC)ImageBinaryProc;
  WndClass.lpszClassName = (LPSTR)szImageBinaryClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register Binary Image Class Error", "Error", MB_OK);
  }

  // Thinning
  WndClass.lpfnWndProc = (WNDPROC)ImageThinningProc;
  WndClass.lpszClassName = (LPSTR)szImageThinningClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageThinningClass Error", "Error", MB_OK);
  }

  // DCT
  WndClass.lpfnWndProc = (WNDPROC)ImageDCTProc;
  WndClass.lpszClassName = (LPSTR)szImageDCTClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageDCTClass Error", "Error", MB_OK);
  }

  // IDCT
  WndClass.lpfnWndProc = (WNDPROC)ImageIDCTProc;
  WndClass.lpszClassName = (LPSTR)szImageIDCTClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageIDCTClass Error", "Error", MB_OK);
  }

  // HARDAMARD
  WndClass.lpfnWndProc = (WNDPROC)ImageHARDAMARDProc;
  WndClass.lpszClassName = (LPSTR)szImageHARDAMARDClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageHARDAMARDClass Error", "Error", MB_OK);
  }

  // IHARDAMARD
  WndClass.lpfnWndProc = (WNDPROC)ImageIHARDAMARDProc;
  WndClass.lpszClassName = (LPSTR)szImageIHARDAMARDClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageIHARDAMARDClass Error", "Error", MB_OK);
  }

  // WAVELET
  WndClass.lpfnWndProc = (WNDPROC)ImageWAVELETProc;
  WndClass.lpszClassName = (LPSTR)szImageWAVELETClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageWAVELETClass Error", "Error", MB_OK);
  }

  // IWAVELET
  WndClass.lpfnWndProc = (WNDPROC)ImageIWAVELETProc;
  WndClass.lpszClassName = (LPSTR)szImageIWAVELETClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageIWAVELETClass Error", "Error", MB_OK);
  }

  // DCT_JPEG
  WndClass.lpfnWndProc = (WNDPROC)ImageDCT_JPEGProc;
  WndClass.lpszClassName = (LPSTR)szImageDCT_JPEGClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageDCT_JPEGClass Error", "Error", MB_OK);
  }

  // Quantization_JPEG
  WndClass.lpfnWndProc = (WNDPROC)ImageQuantization_JPEGProc;
  WndClass.lpszClassName = (LPSTR)szImageQuantization_JPEGClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageQuantization_JPEGClass Error", "Error",
               MB_OK);
  }

  // IQuantization_JPEG
  WndClass.lpfnWndProc = (WNDPROC)ImageIQuantization_JPEGProc;
  WndClass.lpszClassName = (LPSTR)szImageIQuantization_JPEGClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageIQuantization_JPEGClass Error", "Error",
               MB_OK);
  }

  // IDCT_JPEG
  WndClass.lpfnWndProc = (WNDPROC)ImageIDCT_JPEGProc;
  WndClass.lpszClassName = (LPSTR)szImageIDCT_JPEGClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageIDCT_JPEGClass Error", "Error", MB_OK);
  }

  // Make Frame 1'
  WndClass.lpfnWndProc = (WNDPROC)ImageMakeF1_Proc;
  WndClass.lpszClassName = (LPSTR)szImageMakeF1_Class;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageMakeF1_Class Error", "Error", MB_OK);
  }

  // Make Frame 2 - Frame 1'
  WndClass.lpfnWndProc = (WNDPROC)ImageMakeF2F1_Proc;
  WndClass.lpszClassName = (LPSTR)szImageMakeF2F1_Class;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageMakeF2F1_Class Error", "Error", MB_OK);
  }

  // Make Result Frame
  WndClass.lpfnWndProc = (WNDPROC)ImageMakeRFProc;
  WndClass.lpszClassName = (LPSTR)szImageMakeRFClass;
  WndClass.lpszMenuName = NULL;
  if (!RegisterClass(&WndClass)) {
    MessageBox(NULL, "Register ImageMakeRFClass Error", "Error", MB_OK);
  }

  // Main message loop:
  while (GetMessage(&Message, 0, 0, 0)) {
    TranslateMessage(&Message);
    DispatchMessage(&Message);
    // Translate Accelerator Key To Window Message...
    TranslateAccelerator(hMainWnd, hAccelTable, &Message);
  }
  return Message.wParam;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
// Main Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
  DWORD dwRead;

  // char lpstrFile[MAX_PATH]="";

  int wmId;
  // int wmEvent;

  PAINTSTRUCT ps;
  HDC hdc;
  HFONT hFont;

  char *szMsg = "★ ~ BILL, YOON ~ ★";

  // TCHAR szHello[MAX_LOADSTRING];
  // LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

  switch (message) {
  case WM_CREATE:
    // Disable Menu
    // File Menu
    EnableMenuItem(GetMenu(hWnd), IDM_OUTPUT, MF_GRAYED | MF_BYCOMMAND);

    EnableMenuItem(GetMenu(hWnd), IDM_F2INPUT, MF_GRAYED | MF_BYCOMMAND);

    // Image Processing Menu
    EnableMenuItem(GetMenu(hWnd), IDM_LPF, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_HPF, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_MF, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_HFEF, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_BN, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_WN, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_BWN, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_EROSION, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_DILATION, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_OPENING, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_CLOSING, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_BINARY, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_THINNING, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_DCT, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_IDCT, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_HARDAMARD, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_IHARDAMARD, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_WAVELET, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_IWAVELET, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_DCT_JPEG, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_QUANTIZATION_JPEG,
                   MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_IQUANTIZATION_JPEG,
                   MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_IDCT_JPEG, MF_GRAYED | MF_BYCOMMAND);

    EnableMenuItem(GetMenu(hWnd), IDM_MAKEF1_, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_MAKEF2F1_, MF_GRAYED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hWnd), IDM_MAKERF, MF_GRAYED | MF_BYCOMMAND);

    // Apply Menu
    EnableMenuItem(GetMenu(hWnd), IDM_APPLY, MF_GRAYED | MF_BYCOMMAND);

    // MessageBox(hWnd, "A Moment...", "TEST", MB_OK);

    break;

  case WM_COMMAND:

    wmId = LOWORD(wParam);
    // wmEvent = HIWORD(wParam);

    // Parse the menu selections:
    switch (wmId) {

      // Exit Main Window
    case IDM_EXIT:
      // When Quit Main Window
      PostQuitMessage(0);

      // DestroyWindow justFunction Call WM_DESTROY
      // DestroyWindow(hWnd);
      // return 0;
      break;

      // Image Input(File Open)
    case IDM_INPUT:

      hFile = CreateFile("ImageProcessing_lenna.raw",
                         // hFile = CreateFile("test_binary.raw",
                         GENERIC_READ, 0, NULL, OPEN_EXISTING,
                         FILE_ATTRIBUTE_NORMAL, NULL);

      if (hFile != INVALID_HANDLE_VALUE) {
        ReadFile(hFile, buf, 256 * 256, &dwRead, NULL);
        CloseHandle(hFile);
      }

      // CreateImageInputWindow(hWnd,0,0,256,256);
      CreateImageInputWindow(hWnd, 0, 0, 263, 289);

      // return 0;
      break;

      // Image Output
    case IDM_OUTPUT:
      // CreateImageOutputWindow(hWnd,260,0,256,256);
      CreateImageOutputWindow(hWnd, 260, 0, 263, 289);
      // return 0;
      break;

      // Image Frame1 Input
    case IDM_F1INPUT:
      hFile = CreateFile("ImageProcessing_tabletennis74.raw", GENERIC_READ, 0,
                         NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

      if (hFile != INVALID_HANDLE_VALUE) {
        ReadFile(hFile, f1_buf, 352 * 240, &dwRead, NULL);
        CloseHandle(hFile);
      }

      CreateImageFrame1InputWindow(hWnd, 10, 10, 360, 275);
      break;

      // Image Frame2 Input
    case IDM_F2INPUT:
      hFile = CreateFile("ImageProcessing_tabletennis75.raw", GENERIC_READ, 0,
                         NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

      if (hFile != INVALID_HANDLE_VALUE) {
        ReadFile(hFile, f2_buf, 352 * 240, &dwRead, NULL);
        CloseHandle(hFile);
      }

      CreateImageFrame2InputWindow(hWnd, 400, 10, 360, 275);
      break;

      // LPF
    case IDM_LPF:
      // MessageBox(hWnd, "Test", "LPF", MB_OK);
      // CreateImageLPFWindow(hWnd,520,0,256,256);
      CreateImageLPFWindow(hWnd, 520, 0, 263, 289);
      // return 0;
      break;

      // HPF
    case IDM_HPF:
      // CreateImageHPFWindow(hWnd,780,0,256,256);
      CreateImageHPFWindow(hWnd, 780, 0, 263, 289);
      // return 0;
      break;

      // MF
    case IDM_MF:
      // CreateImageMFWindow(hWnd,0,260,256,256);
      CreateImageMFWindow(hWnd, 0, 260, 263, 289);
      // return 0;
      break;

      // HFEF
    case IDM_HFEF:
      // CreateImageHFEFWindow(hWnd,260,260,256,256);
      CreateImageHFEFWindow(hWnd, 260, 260, 263, 289);
      // return 0;
      break;

      // Black NOISE(pepper)
    case IDM_BN:
      // CreateImageBNWindow(hWnd,520,260,256,256);
      CreateImageBNWindow(hWnd, 520, 260, 263, 289);
      // return 0;
      break;

      // White NOISE(salt)
    case IDM_WN:
      // CreateImageWNWindow(hWnd,780,260,256,256);
      CreateImageWNWindow(hWnd, 780, 260, 263, 289);
      // return 0;
      break;

      // Black and White Noise(pepper and salt)
    case IDM_BWN:
      // CreateImageBWNWindow(hWnd,0,520,256,256);
      CreateImageBWNWindow(hWnd, 0, 520, 263, 289);
      // return 0;
      break;

      // Erosion
    case IDM_EROSION:
      // CreateImageErosionWindow(hWnd,260,520,256,256);
      CreateImageErosionWindow(hWnd, 260, 520, 263, 289);
      // return 0;
      break;

      // Dilation
    case IDM_DILATION:
      // CreateImageDilationWindow(hWnd,520,520,256,256);
      CreateImageDilationWindow(hWnd, 520, 520, 263, 289);
      // return 0;
      break;

      // Opening
    case IDM_OPENING:
      // CreateImageOpeningWindow(hWnd,780,520,256,256);
      CreateImageOpeningWindow(hWnd, 780, 520, 263, 289);
      // return 0;
      break;

      // Closing
    case IDM_CLOSING:
      // CreateImageClosingWindow(hWnd,800,500,256,256);
      CreateImageClosingWindow(hWnd, 800, 500, 263, 289);
      // return 0;
      break;

      // Binary Image
    case IDM_BINARY:
      // CreateImageBinaryWindow(hWnd,300,0,256,256);
      CreateImageBinaryWindow(hWnd, 300, 0, 263, 289);
      // return 0;
      break;

      // Thinning
    case IDM_THINNING:
      // CreateImageThinningWindow(hWnd,600,0,256,256);
      CreateImageThinningWindow(hWnd, 600, 0, 263, 289);
      break;

      // DCT
    case IDM_DCT:
      // CreateImageDCTWindow(hWnd,300,200,256,256);
      CreateImageDCTWindow(hWnd, 300, 200, 263, 289);
      break;

      // IDCT
    case IDM_IDCT:
      // CreateImageIDCTWindow(hWnd,600,200,256,256);
      CreateImageIDCTWindow(hWnd, 600, 200, 263, 289);
      break;

      // HARDAMARD
    case IDM_HARDAMARD:
      // CreateImageHARDAMARDWindow(hWnd, 300, 500, 256, 256);
      CreateImageHARDAMARDWindow(hWnd, 300, 500, 263, 289);
      break;

      // IHARDAMARD
    case IDM_IHARDAMARD:
      // CreateImageIHARDAMARDWindow(hWnd, 600, 500, 256, 256);
      CreateImageIHARDAMARDWindow(hWnd, 600, 500, 263, 289);
      break;

      // WAVELET
    case IDM_WAVELET:
      // CreateImageWAVELETWindow(hWnd, 300, 0, 256, 256);
      CreateImageWAVELETWindow(hWnd, 300, 0, 263, 289);
      break;

      // IWAVELET
    case IDM_IWAVELET:
      // CreateImageIWAVELETWindow(hWnd, 300, 0, 256, 256);
      CreateImageIWAVELETWindow(hWnd, 600, 0, 263, 289);
      break;

      // DCT_JPEG
    case IDM_DCT_JPEG:
      CreateImageDCT_JPEGWindow(hWnd, 0, 300, 263, 289);
      break;

      // Quantizatin_JPEG
    case IDM_QUANTIZATION_JPEG:
      CreateImageQuantization_JPEGWindow(hWnd, 270, 300, 263, 289);
      break;

      // IQuantization_JPEG
    case IDM_IQUANTIZATION_JPEG:
      CreateImageIQuantization_JPEGWindow(hWnd, 540, 300, 263, 289);
      break;

      // IDCT_JPEG
    case IDM_IDCT_JPEG:
      CreateImageIDCT_JPEGWindow(hWnd, 810, 300, 263, 289);
      break;

      // Make Frame 1'
    case IDM_MAKEF1_:
      CreateImageMakeF1_Window(hWnd, 10, 310, 360, 275);
      break;

      // Make Frame 2 - Frame 1'
    case IDM_MAKEF2F1_:
      CreateImageMakeF2F1_Window(hWnd, 400, 310, 360, 275);
      break;

      // Make Result Frame
    case IDM_MAKERF:
      CreateImageMakeRFWindow(hWnd, 800, 310, 360, 275);
      break;

      // Reset
    case IDM_RESET:
      // Close Windows
      DestroyWindow(hc1);
      DestroyWindow(hc2);
      DestroyWindow(hcf1); // Frame1 Window
      DestroyWindow(hcf2); // Frame2 Window

      DestroyWindow(hc3);
      DestroyWindow(hc4);
      DestroyWindow(hc5);
      DestroyWindow(hc6);
      DestroyWindow(hc7);
      DestroyWindow(hc8);
      DestroyWindow(hc9);
      DestroyWindow(hc10);
      DestroyWindow(hc11);
      DestroyWindow(hc12);
      DestroyWindow(hc13);
      DestroyWindow(hc14);
      DestroyWindow(hc15);
      DestroyWindow(hc16);
      DestroyWindow(hc17);
      DestroyWindow(hc18);
      DestroyWindow(hc19);
      DestroyWindow(hc20);
      DestroyWindow(hc21);
      DestroyWindow(hc22);
      DestroyWindow(hc23);
      DestroyWindow(hc24);
      DestroyWindow(hc25);

      DestroyWindow(hc26);
      DestroyWindow(hc27);
      DestroyWindow(hc28);

      // Disable Menu
      // File Menu
      EnableMenuItem(GetMenu(hWnd), IDM_OUTPUT, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_F2INPUT, MF_GRAYED | MF_BYCOMMAND);

      // Image Processing Menu
      EnableMenuItem(GetMenu(hWnd), IDM_LPF, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_HPF, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_MF, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_HFEF, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_BN, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_WN, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_BWN, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_EROSION, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_DILATION, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_OPENING, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_CLOSING, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_BINARY, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_THINNING, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_DCT, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_IDCT, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_HARDAMARD, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_IHARDAMARD, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_WAVELET, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_IWAVELET, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_DCT_JPEG, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_QUANTIZATION_JPEG,
                     MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_IQUANTIZATION_JPEG,
                     MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_IDCT_JPEG, MF_GRAYED | MF_BYCOMMAND);

      EnableMenuItem(GetMenu(hWnd), IDM_MAKEF1_, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_MAKEF2F1_, MF_GRAYED | MF_BYCOMMAND);
      EnableMenuItem(GetMenu(hWnd), IDM_MAKERF, MF_GRAYED | MF_BYCOMMAND);

      // Apply Menu
      EnableMenuItem(GetMenu(hWnd), IDM_APPLY, MF_GRAYED | MF_BYCOMMAND);
      break;

      // Apply
    case IDM_APPLY:

      InvalidateRect(NULL,   // NULL -> All Window Handle
                     NULL,   // NULL -> All Rect Area
                     FALSE); // FALSE -> Do Not Erase Background
      break;

      // About Dialog
    case IDM_ABOUT:
      DialogBox(g_hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
      break;

    default:
      return DefWindowProc(hWnd, message, wParam,
                           lParam); // Else Default Message Return
    }
    break;

  case WM_PAINT:
    // TODO: Add any drawing code here...
    // RECT rt;
    // GetClientRect(hWnd, &rt);
    // DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);

    hdc = BeginPaint(hWnd, &ps);
    hFont = CreateFont(70,                  // Font Height
                       0,                   // Font Width
                       NULL,                // Font Escapement
                       NULL,                // Font Orientation
                       900,                 // Font Weight	0,100,200,... 900
                       FALSE,               // Font Italic
                       FALSE,               // Font Underline
                       FALSE,               // Font StrikeOut
                       ANSI_CHARSET,        // Font Character Set
                       OUT_DEFAULT_PRECIS,  // Font Output Precision
                       CLIP_DEFAULT_PRECIS, // Font Clip Presision
                       DEFAULT_QUALITY,     // Font Quality
                       FF_DECORATIVE,       // Font Pitch And Family
                       "Times New Roman");  // Font Name

    SelectObject(hdc, hFont);
    SetTextAlign(hdc, TA_CENTER);

    SetBkMode(hdc, TRANSPARENT);

    SetTextColor(hdc, RGB(127, 127, 127));

    RECT rtClient;
    ::GetClientRect(hWnd, &rtClient);
    // TextOut(Handle Of DC, x, y, String To Output, Length Of SetColor);
    TextOut(hdc,
            // GetSystemMetrics(SM_CXSCREEN)/2,
            rtClient.right / 2,
            // GetSystemMetrics(SM_CYSCREEN)/3,
            rtClient.bottom / 3,
            szMsg, // ★ ~ BILL, YOON ~ ★
            strlen(szMsg));

    DeleteObject(hFont);

    EndPaint(hWnd, &ps);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    PostQuitMessage(0); // Quit Main Window
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
  case WM_INITDIALOG:
    return TRUE;

  case WM_COMMAND:
    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
      EndDialog(hDlg, LOWORD(wParam));
      return TRUE;
    }
    break;
  }
  return FALSE;
}

// Input Image(Open File)
void CreateImageInputWindow(HWND hParent, int x, int y, int width, int height) {
  if (hc1)
    MessageBox(hc1, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc1 =
        CreateWindow(szImageInputClass, "Input Image(Original Image)",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     // WS_POPUPWINDOW | WS_BORDER | WS_SYSMENU | WS_CAPTION |
                     // WS_VISIBLE,	//POPUP WINDOW
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);

    if (!hc1) {
      MessageBox(hc1, "Non Image File...", "Open Error", MB_OK);
    }
  }
}

// Input Image Processing(Open File)
LRESULT CALLBACK ImageInputProc(HWND hWnd, UINT message, WPARAM wParam,
                                LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  switch (message) {
  case WM_CREATE:

    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // For InputImage Output
        InputImage[row][col] = buf[row][col];
      }
    }
    MessageBox(hWnd, "First Of All, You Must Select Image(Click Image)",
               "INPUT IMAGE OPEN", MB_OK);
    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // for(row = 0; row < ROW; row++)
    //{
    //	for(col = 0; col < COL; col++)
    //	{
    //
    //		rgbtemp = InputImage[row][col];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, InputImage);

    EndPaint(hWnd, &ps);
    break;

    // Input Image -> Temp Image
  case WM_LBUTTONDOWN:

    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // Using TImage For Image Processing
        TImage[row][col] = InputImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    // Enable Menu...
    // File Menu
    EnableMenuItem(GetMenu(hMainWnd), IDM_OUTPUT, MF_ENABLED | MF_BYCOMMAND);
    // Image Processing Menu
    EnableMenuItem(GetMenu(hMainWnd), IDM_LPF, MF_ENABLED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hMainWnd), IDM_HPF, MF_ENABLED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hMainWnd), IDM_MF, MF_ENABLED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hMainWnd), IDM_HFEF, MF_ENABLED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hMainWnd), IDM_BN, MF_ENABLED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hMainWnd), IDM_WN, MF_ENABLED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hMainWnd), IDM_BWN, MF_ENABLED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hMainWnd), IDM_EROSION, MF_ENABLED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hMainWnd), IDM_DILATION, MF_ENABLED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hMainWnd), IDM_OPENING, MF_ENABLED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hMainWnd), IDM_CLOSING, MF_ENABLED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hMainWnd), IDM_BINARY, MF_ENABLED | MF_BYCOMMAND);
    EnableMenuItem(GetMenu(hMainWnd), IDM_THINNING, MF_ENABLED | MF_BYCOMMAND);

    EnableMenuItem(GetMenu(hMainWnd), IDM_DCT, MF_ENABLED | MF_BYCOMMAND);
    // IDCT Menu Enable When DCT Window Executed...
    // EnableMenuItem(GetMenu(hMainWnd), IDM_IDCT, MF_ENABLED | MF_BYCOMMAND);

    EnableMenuItem(GetMenu(hMainWnd), IDM_HARDAMARD, MF_ENABLED | MF_BYCOMMAND);
    // Inverse HARDAMARD Menu Enable When HARDAMARD Window Executed...
    // EnableMenuItem(GetMenu(hMainWnd), IDM_IHARDAMARD, MF_ENABLED |
    // MF_BYCOMMAND);

    EnableMenuItem(GetMenu(hMainWnd), IDM_WAVELET, MF_ENABLED | MF_BYCOMMAND);
    // Inverse Wavelet Menu Enable When Wavelet Window Executed...
    // EnableMenuItem(GetMenu(hMainWnd), IDM_IWAVELET, MF_ENABLED |
    // MF_BYCOMMAND);

    EnableMenuItem(GetMenu(hMainWnd), IDM_DCT_JPEG, MF_ENABLED | MF_BYCOMMAND);
    // When DCT_JPEG Window Executed...
    // EnableMenuItem(GetMenu(hMainWnd), IDM_QUANTIZATION_JPEG, MF_ENABLED |
    // MF_BYCOMMAND); When QUATIZATION_JPEG Window Executed...
    // EnableMenuItem(GetMenu(hMainWnd), IDM_IQUANTIZATION_JPEG, MF_ENABLED |
    // MF_BYCOMMAND); When IQUATIZATION_JPEG Window Executed...
    // EnableMenuItem(GetMenu(hMainWnd), IDM_IDCT_JPEG, MF_ENABLED |
    // MF_BYCOMMAND);

    // Apply Menu
    EnableMenuItem(GetMenu(hMainWnd), IDM_APPLY, MF_ENABLED | MF_BYCOMMAND);

    MessageBox(hWnd, "You Select Input Image...", "SELECT IMAGE", MB_OK); // hc1
    break;

  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc1
    hc1 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// Output Image
void CreateImageOutputWindow(HWND hParent, int x, int y, int width,
                             int height) {
  if (hc2)
    MessageBox(hc2, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc2 =
        CreateWindow(szImageOutputClass, "Output Image(Image Copy)",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc2) {
      MessageBox(hc2, "Non Image Output...", "Error", MB_OK);
    }
  }
}

// Output Image Processing
LRESULT CALLBACK ImageOutputProc(HWND hWnd, UINT message, WPARAM wParam,
                                 LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  switch (message) {
  case WM_CREATE:

    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // for(row = 0; row < ROW; row++)
    //{
    //	for(col = 0; col < COL; col++)
    //	{
    //		OutputImage[row][col] = TImage[row][col];
    //		rgbtemp = OutputImage[row][col];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, TImage);

    EndPaint(hWnd, &ps);
    break;

    // Output Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = OutputImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select Output Image...", "SELECT IMAGE", MB_OK);
    break;

  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc2
    hc2 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// Input Frame1 Image(Open File)
void CreateImageFrame1InputWindow(HWND hParent, int x, int y, int width,
                                  int height) {
  if (hcf1)
    MessageBox(hcf1, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hcf1 =
        CreateWindow(szImageFrame1InputClass, "Input Frame1 Image",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);

    if (!hcf1) {
      MessageBox(hcf1, "Non Image File...", "Open Error", MB_OK);
    }
  }
}

// Input Frame1 Image Processing(Open File)
LRESULT CALLBACK ImageFrame1InputProc(HWND hWnd, UINT message, WPARAM wParam,
                                      LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int frow, fcol;

  switch (message) {
  case WM_CREATE:

    for (frow = 0; frow < FROW; frow++) {
      for (fcol = 0; fcol < FCOL; fcol++) {
        // For Input Frame1 Image Output
        InputFrame1Image[frow][fcol] = f1_buf[frow][fcol];
      }
    }
    MessageBox(hWnd, "You Must Select Frame1(Click Image)",
               "INPUT Frame1 IMAGE OPEN", MB_OK);
    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // for(frow = 0; frow < FROW; frow++)
    //{
    //	for(fcol = 0; fcol < FCOL; fcol++)
    //	{
    //		rgbtemp = InputFrame1Image[frow][fcol];
    //		SetPixel(hdc,fcol,frow,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage2(hdc, FCOL, FROW, InputFrame1Image);
    EndPaint(hWnd, &ps);
    break;

    // Input Frame1 Image -> Temp Image
  case WM_LBUTTONDOWN:

    for (frow = 0; frow < frow; frow++) {
      for (fcol = 0; fcol < fcol; fcol++) {
        // Using TImage For Image Processing
        TImage[frow][fcol] = InputFrame1Image[frow][fcol];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    // Enable Menu...
    EnableMenuItem(GetMenu(hMainWnd), IDM_F2INPUT, MF_ENABLED | MF_BYCOMMAND);

    // Image Processing Menu

    // IDCT Menu Enable When DCT Window Executed...

    // Inverse HARDAMARD Menu Enable When HARDAMARD Window Executed...

    // Inverse Wavelet Menu Enable When Wavelet Window Executed...

    // When DCT_JPEG Window Executed...

    // When QUATIZATION_JPEG Window Executed...

    // When IQUATIZATION_JPEG Window Executed...

    // Make Frame 1'

    // Apply Menu
    EnableMenuItem(GetMenu(hMainWnd), IDM_APPLY, MF_ENABLED | MF_BYCOMMAND);

    MessageBox(hWnd,
               "You Select Input Frame1 Image, Frame2 Input Menu Enabled...",
               "SELECT IMAGE", MB_OK);
    break;

  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hcf1
    hcf1 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// Input Frame2 Image(Open File)
void CreateImageFrame2InputWindow(HWND hParent, int x, int y, int width,
                                  int height) {
  if (hcf2)
    MessageBox(hcf2, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hcf2 =
        CreateWindow(szImageFrame2InputClass, "Input Frame2 Image",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);

    if (!hcf2) {
      MessageBox(hcf2, "Non Image File...", "Open Error", MB_OK);
    }
  }
}

// Input Frame2 Image Processing(Open File)
LRESULT CALLBACK ImageFrame2InputProc(HWND hWnd, UINT message, WPARAM wParam,
                                      LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int frow, fcol;

  switch (message) {
  case WM_CREATE:

    for (frow = 0; frow < FROW; frow++) {
      for (fcol = 0; fcol < FCOL; fcol++) {
        // For Input Frame2 Image Output
        InputFrame2Image[frow][fcol] = f2_buf[frow][fcol];
      }
    }
    MessageBox(hWnd, "You Must Select Frame2(Click Image)",
               "INPUT Frame2 IMAGE OPEN", MB_OK);
    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // for(frow = 0; frow < FROW; frow++)
    //{
    //	for(fcol = 0; fcol < FCOL; fcol++)
    //	{
    //		rgbtemp = InputFrame2Image[frow][fcol];
    //		SetPixel(hdc,fcol,frow,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage2(hdc, FCOL, FROW, InputFrame2Image);
    EndPaint(hWnd, &ps);
    break;

    // Input Frame2 Image -> Temp Image
  case WM_LBUTTONDOWN:

    for (frow = 0; frow < FROW; frow++) {
      for (fcol = 0; fcol < FCOL; fcol++) {
        // Using TImage For Image Processing
        TImage[frow][fcol] = InputFrame2Image[frow][fcol];
        // SetPixel(hdc,fcol,frow,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    // Enable Menu...

    // Image Processing Menu

    // IDCT Menu Enable When DCT Window Executed...

    // Inverse HARDAMARD Menu Enable When HARDAMARD Window Executed...

    // Inverse Wavelet Menu Enable When Wavelet Window Executed...

    // When DCT_JPEG Window Executed...

    // When QUATIZATION_JPEG Window Executed...

    // When IQUATIZATION_JPEG Window Executed...

    // Make Frame 1'
    EnableMenuItem(GetMenu(hMainWnd), IDM_MAKEF1_, MF_ENABLED | MF_BYCOMMAND);

    // Apply Menu
    EnableMenuItem(GetMenu(hMainWnd), IDM_APPLY, MF_ENABLED | MF_BYCOMMAND);

    MessageBox(hWnd,
               "You Select Input Frame2 Image, Make Frame 1' Menu Enabled.",
               "SELECT IMAGE", MB_OK);

    break;

  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hcf2
    hcf2 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// LPF Window
void CreateImageLPFWindow(HWND hParent, int x, int y, int width, int height) {
  if (hc3)
    MessageBox(hc3, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc3 =
        CreateWindow(szImageLPFClass, "LPF",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc3) {
      MessageBox(hc3, "Non Input Image", "LPF Error", MB_OK);
    }
  }
}

// LPF Image Processing
LRESULT CALLBACK ImageLPFProc(HWND hWnd, UINT message, WPARAM wParam,
                              LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  // Filter Mask -> 3x3
  // 1/9,  1/9,  1/9
  // 1/9,  1/9,  1/9
  // 1/9,  1/9,  1/9
  double LPFMask[3][3] = {0.11, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11, 0.11};

  // Filter Mask -> 5 x 5
  // 1/25, 1/25, 1/25, 1/25, 1/25,
  // 1/25, 1/25, 1/25, 1/25, 1/25,
  // 1/25, 1/25, 1/25, 1/25, 1/25,
  // 1/25, 1/25, 1/25, 1/25, 1/25,
  // 1/25, 1/25, 1/25, 1/25, 1/25,
  // float LPFMask[5][5] = {0.04, 0.04, 0.04, 0.04, 0.04,
  //						0.04, 0.04, 0.04, 0.04, 0.04,
  //						0.04, 0.04, 0.04, 0.04, 0.04,
  //						0.04, 0.04, 0.04, 0.04, 0.04,
  //						0.04, 0.04, 0.04, 0.04, 0.04};

  switch (message) {
  case WM_CREATE:

    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // rgbtemp=TImage[row][col] = buf[row][col];
        // rgbtemp = buf[row][col];
        // 3 x 3
        LPFImage[row + 1][col + 1] =
            (unsigned char)((TImage[row + 0][col + 0] * LPFMask[0][0]) +
                            (TImage[row + 0][col + 1] * LPFMask[0][1]) +
                            (TImage[row + 0][col + 2] * LPFMask[0][2]) +
                            (TImage[row + 1][col + 0] * LPFMask[1][0]) +
                            (TImage[row + 1][col + 1] * LPFMask[1][1]) +
                            (TImage[row + 1][col + 2] * LPFMask[1][2]) +
                            (TImage[row + 2][col + 0] * LPFMask[2][0]) +
                            (TImage[row + 2][col + 1] * LPFMask[2][1]) +
                            (TImage[row + 2][col + 2] * LPFMask[2][2]));

        // 5 x 5
        // LPFmage[row+1][col+1] = ((TImage[row+0][col+0] * LPFMask[0][0])+
        //	            (TImage[row+0][col+1] * LPFMask[0][1])+
        //				(TImage[row+0][col+2] * LPFMask[0][2])+
        //				(TImage[row+0][col+3] * LPFMask[0][3])+
        //				(TImage[row+0][col+4] * LPFMask[0][4])+
        //				(TImage[row+1][col+0] * LPFMask[1][0])+
        //				(TImage[row+1][col+1] * LPFMask[1][1])+
        //				(TImage[row+1][col+2] * LPFMask[1][2])+
        //				(TImage[row+1][col+3] * LPFMask[1][3])+
        //				(TImage[row+1][col+4] * LPFMask[1][4])+
        //				(TImage[row+2][col+0] * LPFMask[2][0])+
        //				(TImage[row+2][col+1] * LPFMask[2][1])+
        //				(TImage[row+2][col+2] * LPFMask[2][2])+
        //				(TImage[row+2][col+3] * LPFMask[2][3])+
        //				(TImage[row+2][col+4] * LPFMask[2][4])+
        //				(TImage[row+3][col+0] * LPFMask[3][0])+
        //				(TImage[row+3][col+1] * LPFMask[3][1])+
        //				(TImage[row+3][col+2] * LPFMask[3][2])+
        //				(TImage[row+3][col+3] * LPFMask[3][3])+
        //				(TImage[row+3][col+4] * LPFMask[3][4])+
        //				(TImage[row+4][col+0] * LPFMask[4][0])+
        //				(TImage[row+4][col+1] * LPFMask[4][1])+
        //				(TImage[row+4][col+2] * LPFMask[4][2])+
        //				(TImage[row+4][col+3] * LPFMask[4][3])+
        //				(TImage[row+4][col+4] * LPFMask[4][4]));
      }
    }
    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    // for(row = 0; row < ROW; row++)
    //{
    //	for(col = 0; col < COL; col++)
    //	{
    //		rgbtemp = LPFImage[row+1][col+1];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, LPFImage);

    EndPaint(hWnd, &ps);
    break;

    // LPF Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = LPFImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select LPF Image...", "SELECT IMAGE", MB_OK);
    break;

  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc3
    hc3 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }

  return 0;
}

// HPF Window
void CreateImageHPFWindow(HWND hParent, int x, int y, int width, int height) {
  if (hc4)
    MessageBox(hc4, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc4 =
        CreateWindow(szImageHPFClass, "HPF",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc4) {
      MessageBox(hc4, "Non Input Image", "HPF Error", MB_OK);
    }
  }
}

// HPF Image Processing
LRESULT CALLBACK ImageHPFProc(HWND hWnd, UINT message, WPARAM wParam,
                              LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  // Filter Mask -> 3 x 3
  //-1/9, -1/9, -1/9,
  //-1/9,  8/9, -1/9,
  //-1/9, -1/9, -1/9,
  double HPFMask[3][3] = {
      {-0.11, -0.11, -0.11}, {-0.11, 0.88, -0.11}, {-0.11, -0.11, -0.11}};

  // Filter Mask -> 5 x 5
  //-1/25, -1/25, -1/25, -1/25, -1/25,
  //-1/25, -1/25, -1/25, -1/25, -1/25,
  //-1/25, -1/25, 24/25, -1/25, -1/25,
  //-1/25, -1/25, -1/25, -1/25, -1/25,
  //-1/25, -1/25, -1/25, -1/25, -1/25,
  // float HPFMask[5][5] = {-0.04, -0.04, -0.04, -0.04, -0.04,
  //						-0.04, -0.04, -0.04, -0.04,
  //-0.04, 						-0.04, -0.04,  0.96, -0.04, -0.04, 						-0.04, -0.04, -0.04, -0.04, -0.04,
  //						-0.04, -0.04, -0.04, -0.04,
  //-0.04};

  switch (message) {
  case WM_CREATE:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // rgbtemp=TImage[row][col] = buf[row][col];
        // rgbtemp = buf[row][col];
        // 3 x 3
        HPFImage[row + 1][col + 1] =
            (unsigned char)((TImage[row + 0][col + 0] * HPFMask[0][0]) +
                            (TImage[row + 0][col + 1] * HPFMask[0][1]) +
                            (TImage[row + 0][col + 2] * HPFMask[0][2]) +
                            (TImage[row + 1][col + 0] * HPFMask[1][0]) +
                            (TImage[row + 1][col + 1] * HPFMask[1][1]) +
                            (TImage[row + 1][col + 2] * HPFMask[1][2]) +
                            (TImage[row + 2][col + 0] * HPFMask[2][0]) +
                            (TImage[row + 2][col + 1] * HPFMask[2][1]) +
                            (TImage[row + 2][col + 2] * HPFMask[2][2]));

        // 5 x 5
        // HPFImage[row+1][col+1] = ((TImage[row+0][col+0] * HPFMask[0][0])+
        //	            (TImage[row+0][col+1] * HPFMask[0][1])+
        //				(TImage[row+0][col+2] * HPFMask[0][2])+
        //				(TImage[row+0][col+3] * HPFMask[0][3])+
        //				(TImage[row+0][col+4] * HPFMask[0][4])+
        //				(TImage[row+1][col+0] * HPFMask[1][0])+
        //				(TImage[row+1][col+1] * HPFMask[1][1])+
        //				(TImage[row+1][col+2] * HPFMask[1][2])+
        //				(TImage[row+1][col+3] * HPFMask[1][3])+
        //				(TImage[row+1][col+4] * HPFMask[1][4])+
        //				(TImage[row+2][col+0] * HPFMask[2][0])+
        //				(TImage[row+2][col+1] * HPFMask[2][1])+
        //				(TImage[row+2][col+2] * HPFMask[2][2])+
        //				(TImage[row+2][col+3] * HPFMask[2][3])+
        //				(TImage[row+2][col+4] * HPFMask[2][4])+
        //				(TImage[row+3][col+0] * HPFMask[3][0])+
        //				(TImage[row+3][col+1] * HPFMask[3][1])+
        //				(TImage[row+3][col+2] * HPFMask[3][2])+
        //				(TImage[row+3][col+3] * HPFMask[3][3])+
        //				(TImage[row+3][col+4] * HPFMask[3][4])+
        //				(TImage[row+4][col+0] * HPFMask[4][0])+
        //				(TImage[row+4][col+1] * HPFMask[4][1])+
        //				(TImage[row+4][col+2] * HPFMask[4][2])+
        //				(TImage[row+4][col+3] * HPFMask[4][3])+
        //				(TImage[row+4][col+4] * HPFMask[4][4]));
      }
    }
    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // for(row = 0; row < ROW; row++)
    //{
    //	for(col = 0; col < COL; col++)
    //	{
    //		rgbtemp = HPFImage[row+1][col+1];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, HPFImage);

    EndPaint(hWnd, &ps);
    break;

    // HPF Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = HPFImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select HPF Image...", "SELECT IMAGE", MB_OK);
    break;

  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc4
    hc4 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// MF Window
void CreateImageMFWindow(HWND hParent, int x, int y, int width, int height) {
  if (hc5)
    MessageBox(hc5, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc5 =
        CreateWindow(szImageMFClass, "MF",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc5) {
      MessageBox(hc5, "Non Input Image", "MF Error", MB_OK);
    }
  }
}

// MF Image Processing
LRESULT CALLBACK ImageMFProc(HWND hWnd, UINT message, WPARAM wParam,
                             LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  // Filter -> 3 x 3
  // 0, 0, 0,
  // 0, 0, 0,
  // 0, 0, 0,
  double Median[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

  // Filter -> 5 x 5
  // 0, 0, 0, 0, 0,
  // 0, 0, 0, 0, 0,
  // 0, 0, 0, 0, 0,
  // 0, 0, 0, 0, 0,
  // 0, 0, 0, 0, 0,
  // float Median[25] = {0, 0, 0, 0, 0,
  //				0, 0, 0, 0, 0,
  //				0, 0, 0, 0, 0,
  //				0, 0, 0, 0, 0,
  //				0, 0, 0, 0, 0};

  int i, j;
  float temp;

  float Mvalue = 0; // Last Meidan Value

  switch (message) {
  case WM_CREATE:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // rgbtemp=TImage[row][col] = buf[row][col];
        // rgbtemp = buf[row][col];

        // 3 x 3
        Median[0] = TImage[row + 0][col + 0];
        Median[1] = TImage[row + 0][col + 1];
        Median[2] = TImage[row + 0][col + 2];
        Median[3] = TImage[row + 1][col + 0];
        Median[4] = TImage[row + 1][col + 1];
        Median[5] = TImage[row + 1][col + 2];
        Median[6] = TImage[row + 2][col + 0];
        Median[7] = TImage[row + 2][col + 1];
        Median[8] = TImage[row + 2][col + 2];

        // 5 x 5
        // Median[0] = TImage[row+0][col+0];
        // Median[1] = TImage[row+0][col+1];
        // Median[2] = TImage[row+0][col+2];
        // Median[3] = TImage[row+0][col+3];
        // Median[4] = TImage[row+0][col+4];

        // Median[5] = TImage[row+1][col+0];
        // Median[6] = TImage[row+1][col+1];
        // Median[7] = TImage[row+1][col+2];
        // Median[8] = TImage[row+1][col+3];
        // Median[9] = TImage[row+1][col+4];

        // Median[10] = TImage[row+2][col+0];
        // Median[11] = TImage[row+2][col+1];
        // Median[12] = TImage[row+2][col+2];
        // Median[13] = TImage[row+2][col+3];
        // Median[14] = TImage[row+2][col+4];

        // Median[15] = TImage[row+3][col+0];
        // Median[16] = TImage[row+3][col+1];
        // Median[17] = TImage[row+3][col+2];
        // Median[18] = TImage[row+3][col+3];
        // Median[19] = TImage[row+3][col+4];

        // Median[20] = TImage[row+4][col+0];
        // Median[21] = TImage[row+4][col+1];
        // Median[22] = TImage[row+4][col+2];
        // Median[23] = TImage[row+4][col+3];
        // Median[24] = TImage[row+4][col+4];

        // Median Filter Method(Sorting Pixel...) 3 x 3

        for (i = 0; i < 8; i++) {
          for (j = 0; j < 8; j++) {
            if (Median[j + 1] < Median[j]) {
              temp = (float)Median[j + 1];
              Median[j + 1] = Median[j];
              Median[j] = temp;
            }
          }
        }

        // Median Filter Method(Sorting Pixel...) 5 x 5
        // for (i = 0; i < 24; i++)
        //{
        //	for (j = 0; j < 24; j++)
        //	{
        //		if (Median[j+1] < Median[j])
        //		{
        //			temp = Median[j+1];
        //			Median[j+1] = Median[j];
        //			Median[j] = temp;
        //		}
        //	}
        // }

        MFImage[row + 1][col + 1] = (unsigned char)Median[4]; // When 3 x 3 mask

        // MFImage[row+1][col+1] = Median[12];	//When 5 x 5 mask
      }
    }
    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    // for(row = 0; row < ROW; row++)
    //{
    //	for(col = 0; col < COL; col++)
    //	{
    //		rgbtemp = MFImage[row+1][col+1];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, MFImage);
    EndPaint(hWnd, &ps);
    break;

    // MF Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = MFImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select MF Image...", "SELECT IMAGE", MB_OK);
    break;

  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc5
    hc5 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// HFEF Window
void CreateImageHFEFWindow(HWND hParent, int x, int y, int width, int height) {
  if (hc6)
    MessageBox(hc6, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc6 =
        CreateWindow(szImageHFEFClass, "HFEF",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc6) {
      MessageBox(hc6, "Non Input Image", "HFEF Error", MB_OK);
    }
  }
}

// HFEF Image Processing
LRESULT CALLBACK ImageHFEFProc(HWND hWnd, UINT message, WPARAM wParam,
                               LPARAM lParam) {
  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  // Filter Mask -> 3 x 3
  //-1/9, -1/9, -1/9,
  //-1/9,  x/9, -1/9,
  //-1/9, -1/9, -1/9,
  //   x = 17(1.88) or 19(2.11) or 21(2.33)
  double HFEFMask[3][3] = {-0.11, -0.11, -0.11, -0.11, 0.0,
                           -0.11, -0.11, -0.11, -0.11};

  HFEFMask[1][1] = 1.88; // x = 17

  // Filter Mask -> 5 x 5
  //-1/25, -1/25, -1/25, -1/25, -1/25,
  //-1/25, -1/25, -1/25, -1/25, -1/25,
  //-1/25, -1/25,  x/25, -1/25, -1/25,
  //-1/25, -1/25, -1/25, -1/25, -1/25,
  //-1/25, -1/25, -1/25, -1/25, -1/25,
  //   x = 49(1.96) or 51(2.04) or 53(2.12)
  // float HFEFMask[5][5] = {-0.04, -0.04, -0.04, -0.04, -0.04,
  //						-0.04, -0.04, -0.04, -0.04,
  //-0.04, 						-0.04, -0.04,     0, -0.04, -0.04, 						-0.04, -0.04, -0.04, -0.04, -0.04,
  //						-0.04, -0.04, -0.04, -0.04,
  //-0.04};

  // HFEFMask[2][2] = 1.96;	//x = 49

  switch (message) {
  case WM_CREATE:

    for (row = 0; row < ROW - 1; row++) {
      for (col = 0; col < COL - 1; col++) {
        // rgbtemp=TImage[row][col] = buf[row][col];
        // rgbtemp = buf[row][col];

        // 3 x 3
        HFEFImage[row + 1][col + 1] =
            (unsigned char)((TImage[row + 0][col + 0] * HFEFMask[0][0]) +
                            (TImage[row + 0][col + 1] * HFEFMask[0][1]) +
                            (TImage[row + 0][col + 2] * HFEFMask[0][2]) +
                            (TImage[row + 1][col + 0] * HFEFMask[1][0]) +
                            (TImage[row + 1][col + 1] * HFEFMask[1][1]) +
                            (TImage[row + 1][col + 2] * HFEFMask[1][2]) +
                            (TImage[row + 2][col + 0] * HFEFMask[2][0]) +
                            (TImage[row + 2][col + 1] * HFEFMask[2][1]) +
                            (TImage[row + 2][col + 2] * HFEFMask[2][2]));

        // 5 x 5
        // HFEFImage[row+1][col+1] = ((TImage[row+0][col+0] * HFEFMask[0][0])+
        //	            (TImage[row+0][col+1] * HFEFMask[0][1])+
        //				(TImage[row+0][col+2] * HFEFMask[0][2])+
        //				(TImage[row+0][col+3] * HFEFMask[0][3])+
        //				(TImage[row+0][col+4] * HFEFMask[0][4])+
        //				(TImage[row+1][col+0] * HFEFMask[1][0])+
        //				(TImage[row+1][col+1] * HFEFMask[1][1])+
        //				(TImage[row+1][col+2] * HFEFMask[1][2])+
        //				(TImage[row+1][col+3] * HFEFMask[1][3])+
        //				(TImage[row+1][col+4] * HFEFMask[1][4])+
        //				(TImage[row+2][col+0] * HFEFMask[2][0])+
        //				(TImage[row+2][col+1] * HFEFMask[2][1])+
        //				(TImage[row+2][col+2] * HFEFMask[2][2])+
        //				(TImage[row+2][col+3] * HFEFMask[2][3])+
        //				(TImage[row+2][col+4] * HFEFMask[2][4])+
        //				(TImage[row+3][col+0] * HFEFMask[3][0])+
        //				(TImage[row+3][col+1] * HFEFMask[3][1])+
        //				(TImage[row+3][col+2] * HFEFMask[3][2])+
        //				(TImage[row+3][col+3] * HFEFMask[3][3])+
        //				(TImage[row+3][col+4] * HFEFMask[3][4])+
        //				(TImage[row+4][col+0] * HFEFMask[4][0])+
        //				(TImage[row+4][col+1] * HFEFMask[4][1])+
        //				(TImage[row+4][col+2] * HFEFMask[4][2])+
        //				(TImage[row+4][col+3] * HFEFMask[4][3])+
        //				(TImage[row+4][col+4] *
        //HFEFMask[4][4]));
      }
    }
    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // for(row = 0; row < ROW-1; row++)
    //{
    //	for(col = 0; col < COL-1; col++)
    //	{
    //		rgbtemp = HFEFImage[row+1][col+1];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, HFEFImage);

    EndPaint(hWnd, &ps);
    break;

    // HFEF Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = HFEFImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select HFEF Image...", "SELECT IMAGE", MB_OK);
    break;

  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc6
    hc6 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// BN
void CreateImageBNWindow(HWND hParent, int x, int y, int width, int height) {
  if (hc7)
    MessageBox(hc7, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc7 =
        CreateWindow(szImageBNClass, "BN",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc7) {
      MessageBox(hc7, "Non Input Image", "BN Error", MB_OK);
    }
  }
}

// BN Procedure
LRESULT CALLBACK ImageBNProc(HWND hWnd, UINT message, WPARAM wParam,
                             LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  int x, y;

  switch (message) {
  case WM_CREATE:
    // Copy Temp Image To Black Noise Image
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        BNImage[row][col] = TImage[row][col];
      }
    }

    // Black Noise(Pepper)
    for (row = 0; row < ROW; row++) {
      x = rand() % COL;
      y = rand() % ROW;
      BNImage[y][x] = 0;
    }

    break;
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		rgbtemp = BNImage[row][col];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, BNImage);
    EndPaint(hWnd, &ps);
    break;

    // Black Noise Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = BNImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select BN Image...", "SELECT IMAGE", MB_OK);
    break;

  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc7
    hc7 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// WN
void CreateImageWNWindow(HWND hParent, int x, int y, int width, int height) {
  if (hc8)
    MessageBox(hc8, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc8 =
        CreateWindow(szImageWNClass, "WN",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc8) {
      MessageBox(hc8, "Non Input Image", "WN Error", MB_OK);
    }
  }
}

// WN Procedure
LRESULT CALLBACK ImageWNProc(HWND hWnd, UINT message, WPARAM wParam,
                             LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  int x, y;

  switch (message) {
  case WM_CREATE:
    // Copy Temp Image To White Noise Image
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        WNImage[row][col] = TImage[row][col];
      }
    }

    // White Noise(Pepper)
    for (row = 0; row < ROW; row++) {
      x = rand() % COL;
      y = rand() % ROW;
      WNImage[y][x] = 255;
    }
    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		rgbtemp = WNImage[row][col];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, WNImage);

    EndPaint(hWnd, &ps);
    break;

    // White Noise Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = WNImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select WN Image...", "SELECT IMAGE", MB_OK);
    break;

  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc8
    hc8 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// BWN
void CreateImageBWNWindow(HWND hParent, int x, int y, int width, int height) {
  if (hc9)
    MessageBox(hc9, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc9 =
        CreateWindow(szImageBWNClass, "BWN",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc9) {
      MessageBox(hc9, "Non Input Image", "BWN Error", MB_OK);
    }
  }
}

// BWN Procedure
LRESULT CALLBACK ImageBWNProc(HWND hWnd, UINT message, WPARAM wParam,
                              LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  int x, y, bw; // bw -> Choice Black or White

  switch (message) {
  case WM_CREATE:
    // Copy Original Image To Temp Image
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        BWNImage[row][col] = TImage[row][col];
      }
    }

    // Black and White Noise(Pepper and Salt)
    for (row = 0; row < ROW; row++) {
      x = rand() % 256;
      y = rand() % 256;
      bw = rand() % 2;
      if (bw == 0) {
        // SetPixel(hdc,x,y,(unsigned long)RGB(0,0,0));
        BWNImage[y][x] = 0;
      } else if (bw == 1) {
        // SetPixel(hdc,x,y,(unsigned long)RGB(255,255,255));
        BWNImage[y][x] = 255;
      }
    }
    break;
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		rgbtemp = BWNImage[row][col];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, BWNImage);
    EndPaint(hWnd, &ps);
    break;

    // Black and White Noise Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = BWNImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select BWN Image...", "SELECT IMAGE", MB_OK);
    break;

  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc9
    hc9 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// MAX Value Return
unsigned char MAX(unsigned char A, unsigned char B, unsigned char C) {
  if (A >= B) {
    if (A >= C)
      return (A);
    else
      return (C);
  } else {
    if (B >= C)
      return (B);
    else
      return (C);
  }
}

// MIN Value Return
unsigned char MIN(unsigned char A, unsigned char B, unsigned char C) {
  if (A <= B) {
    if (A <= C)
      return (A);
    else
      return (C);
  } else {
    if (B <= C)
      return (B);
    else
      return (C);
  }
}

// Erosion
void CreateImageErosionWindow(HWND hParent, int x, int y, int width,
                              int height) {
  if (hc10)
    MessageBox(hc10, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc10 =
        CreateWindow(szImageErosionClass, "Erosion",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc10) {
      MessageBox(hc10, "Non Input Image", "Erosion Error", MB_OK);
    }
  }
}

// Erosion Procedure
LRESULT CALLBACK ImageErosionProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  int EMask[3] = {0, 1, 2};

  switch (message) {
  case WM_CREATE:

    // Copy Original Image To Temp Image
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		ErosionImage[row][col] = TImage[row][col];
    //	}
    // }

    // Erosion
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        ErosionImage[row][col] =
            MIN(TImage[row][col + EMask[0]], TImage[row][col + EMask[1]],
                TImage[row][col + EMask[2]]);
      }
    }
    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		rgbtemp = ErosionImage[row][col];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, ErosionImage);

    EndPaint(hWnd, &ps);
    break;

    // Erosion Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = ErosionImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select Erosion Image...", "SELECT IMAGE", MB_OK);
    break;

  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc10
    hc10 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// Dilation
void CreateImageDilationWindow(HWND hParent, int x, int y, int width,
                               int height) {
  if (hc11)
    MessageBox(hc11, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc11 =
        CreateWindow(szImageDilationClass, "Dilation",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);

    if (!hc11) {
      MessageBox(hc11, "Non Input Image", "Dilation Error", MB_OK);
    }
  }
}

// Dilation Procedure
LRESULT CALLBACK ImageDilationProc(HWND hWnd, UINT message, WPARAM wParam,
                                   LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  int DMask[3] = {0, 1, 2};

  switch (message) {
  case WM_CREATE:
    // Copy Original Image To Temp Image
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		DilationImage[row][col] = TImage[row][col];
    //	}
    // }

    // Dilation
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        DilationImage[row][col] =
            MAX(TImage[row][col - DMask[0]], TImage[row][col - DMask[1]],
                TImage[row][col - DMask[2]]);
      }
    }
    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		rgbtemp = DilationImage[row][col];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, DilationImage);
    EndPaint(hWnd, &ps);

    break;

    // Dilation Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = DilationImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select Dilation Image...", "SELECT IMAGE", MB_OK);
    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc11
    hc11 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }

  return 0;
}

// Opening
void CreateImageOpeningWindow(HWND hParent, int x, int y, int width,
                              int height) {
  if (hc12)
    MessageBox(hc12, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc12 =
        CreateWindow(szImageOpeningClass, "Opening",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc12) {
      MessageBox(hc12, "Non Input Image", "Opening Error", MB_OK);
    }
  }
}

// Opening Procedure (Erosion -> Dilation)
LRESULT CALLBACK ImageOpeningProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;

  int row, col;

  int EMask[3] = {0, 1, 2};
  int DMask[3] = {0, 1, 2};

  // Eroded Image
  unsigned char ErodedImage[ROW][COL];

  switch (message) {
  case WM_CREATE:
    // Original Image
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		OpenginImage[row][col] = TImage[row][col];
    //		//SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }

    // Erosion
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // Eroded
        ErodedImage[row][col] =
            MIN(TImage[row][col + EMask[0]], TImage[row][col + EMask[1]],
                TImage[row][col + EMask[2]]);
      }
    }
    // Dilation
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        OpeningImage[row][col] = MAX(ErodedImage[row][col - DMask[0]],
                                     ErodedImage[row][col - DMask[1]],
                                     ErodedImage[row][col - DMask[2]]);
      }
    }
    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    // Opening(Erosion -> Dilation) Image Output
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		rgbtemp = OpeningImage[row][col];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, OpeningImage);

    EndPaint(hWnd, &ps);
    break;

    // Openging Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = OpeningImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select Opening Image...", "SELECT IMAGE", MB_OK);
    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc12
    // MessageBox(hWnd,"TEST","Testing",MB_OK);
    hc12 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// Closing
void CreateImageClosingWindow(HWND hParent, int x, int y, int width,
                              int height) {
  if (hc13)
    MessageBox(hc13, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc13 =
        CreateWindow(szImageClosingClass, "Closing",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc13) {
      MessageBox(hc13, "Non Input Image", "Closing Error", MB_OK);
    }
  }
}

// Closing Procedure (Dilation -> Erosion)
LRESULT CALLBACK ImageClosingProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  int EMask[3] = {0, 1, 2};
  int DMask[3] = {0, 1, 2};

  // Dilated Image
  unsigned char DilatedImage[ROW][COL];

  switch (message) {
  case WM_CREATE:
    // Original Image
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		ClosingImage[row][col] = TImage[row][col];
    //		//SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }

    // Dilation
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // Dilated
        DilatedImage[row][col] =
            MAX(TImage[row][col - DMask[0]], TImage[row][col - DMask[1]],
                TImage[row][col - DMask[2]]);
      }
    }

    // Erosion
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        ClosingImage[row][col] = MIN(DilatedImage[row][col + EMask[0]],
                                     DilatedImage[row][col + EMask[1]],
                                     DilatedImage[row][col + EMask[2]]);
      }
    }
    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // Closing(Dilation -> Erosion) Image Output
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		rgbtemp = ClosingImage[row][col];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, ClosingImage);

    EndPaint(hWnd, &ps);

    break;

    // Closing Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = ClosingImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select Closing Image...", "SELECT IMAGE", MB_OK);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc13
    hc13 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// Binary Image
void CreateImageBinaryWindow(HWND hParent, int x, int y, int width,
                             int height) {
  if (hc14)
    MessageBox(hc14, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc14 =
        CreateWindow(szImageBinaryClass, "Binary",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc14) {
      MessageBox(hc14, "Non Input Image", "Binary Image Error", MB_OK);
    }
  }
}

// Binary Image Procedure
LRESULT CALLBACK ImageBinaryProc(HWND hWnd, UINT message, WPARAM wParam,
                                 LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  // Decision(Black or White)
  unsigned int threshold = 0;

  unsigned int image_size = ROW * COL;

  unsigned long sum = 0;

  switch (message) {
  case WM_CREATE:
    // Sum For Binary
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {

        sum = sum + TImage[row][col];
      }
    }

    threshold = sum / image_size;

    // Make Binary Image
    // Boundary decision (0 or 255)
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {

        if (TImage[row][col] > threshold)
          BinaryImage[row][col] = 255; // White
        else
          BinaryImage[row][col] = 0; // Black
      }
    }
    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // Binary Image Output
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		rgbtemp = BinaryImage[row][col];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, BinaryImage);
    EndPaint(hWnd, &ps);

    break;

    // Binary Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = BinaryImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select Binary Image...", "SELECT IMAGE", MB_OK);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc14
    hc14 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// Hit and Miss Image Porcedure
// Input BinaryImage, Structure Element foreground, Structure Element foreground
void HitAndMiss(unsigned char B_IMAGE[ROW][COL], int SEf[3][3], int SEb[3][3]) {
  unsigned int row, col;
  unsigned int i;

  unsigned char InvertImage[ROW][COL];
  unsigned char Result1Image[ROW][COL];
  unsigned char Result2Image[ROW][COL];
  unsigned char Result3Image[ROW][COL];

  int flag[9];

  // Initialize
  for (row = 0; row < ROW; row++) {
    for (col = 0; col < COL; col++) {
      InvertImage[row][col] = 0;
      Result1Image[row][col] = 0;
      Result2Image[row][col] = 0;
      Result3Image[row][col] = 0;
    }
  }

  // HitAndMiss(Binary Image)
  //((binary)image - se's foreground) * (invert(binary)image - se's background)
  //				Result1				*
  //Result2

  ////////////////////////////////////////////////////
  // Result1 Image
  for (row = 0; row < ROW - 2; row++) {
    for (col = 0; col < COL - 2; col++) {
      // Result1Image[row+1][col+1]
      //	= ((B_IMAGE[row+0][col+0] * SEf[0][0])+
      //		(B_IMAGE[row+0][col+1] * SEf[0][1])+
      //		(B_IMAGE[row+0][col+2] * SEf[0][2])+
      //		(B_IMAGE[row+1][col+0] * SEf[1][0])+
      //		(B_IMAGE[row+1][col+1] * SEf[1][1])+
      //		(B_IMAGE[row+1][col+2] * SEf[1][2])+
      //		(B_IMAGE[row+2][col+0] * SEf[2][0])+
      //		(B_IMAGE[row+2][col+1] * SEf[2][1])+
      //		(B_IMAGE[row+2][col+2] * SEf[2][2]));

      // Reset Flag
      for (i = 0; i < 9; i++)
        flag[i] = 0;

      if ((B_IMAGE[row + 0][col + 0] * SEf[0][0]) == 1)
        flag[0] = 1;
      if ((B_IMAGE[row + 0][col + 1] * SEf[0][1]) == 1)
        flag[1] = 1;
      if ((B_IMAGE[row + 0][col + 2] * SEf[0][2]) == 1)
        flag[2] = 1;
      if ((B_IMAGE[row + 1][col + 0] * SEf[1][0]) == 1)
        flag[3] = 1;
      if ((B_IMAGE[row + 1][col + 1] * SEf[1][1]) == 1)
        flag[4] = 1;
      if ((B_IMAGE[row + 1][col + 2] * SEf[1][2]) == 1)
        flag[5] = 1;
      if ((B_IMAGE[row + 2][col + 0] * SEf[2][0]) == 1)
        flag[6] = 1;
      if ((B_IMAGE[row + 2][col + 1] * SEf[2][1]) == 1)
        flag[7] = 1;
      if ((B_IMAGE[row + 2][col + 2] * SEf[2][2]) == 1)
        flag[8] = 1;

      // check flag
      // SE1
      if (flag[4] == 1 && flag[6] == 1 && flag[7] == 1 && flag[8] == 1) {
        Result1Image[row + 1][col + 1] = 1;
      }
      // SE2
      else if (flag[3] == 1 && flag[4] == 1 && flag[7] == 1) {
        Result1Image[row + 1][col + 1] = 1;
      }
      // SE3
      else if (flag[0] == 1 && flag[3] == 1 && flag[4] == 1 && flag[6] == 1) {
        Result1Image[row + 1][col + 1] = 1;
      }
      // SE4
      else if (flag[1] == 1 && flag[3] == 1 && flag[4] == 1) {
        Result1Image[row + 1][col + 1] = 1;
      }
      // SE5
      else if (flag[0] == 1 && flag[1] == 1 && flag[2] == 1 && flag[4] == 1) {
        Result1Image[row + 1][col + 1] = 1;
      }
      // SE6
      else if (flag[1] == 1 && flag[4] == 1 && flag[5] == 1) {
        Result1Image[row + 1][col + 1] = 1;
      }
      // SE7
      else if (flag[2] == 1 && flag[4] == 1 && flag[5] == 1 && flag[8] == 1) {
        Result1Image[row + 1][col + 1] = 1;
      }
      // SE8
      else if (flag[4] == 1 && flag[5] == 1 && flag[7] == 1) {
        Result1Image[row + 1][col + 1] = 1;
      } else {
        Result1Image[row + 1][col + 1] = 0;
      }
    }
  }

  ////////////////////////////////////////////////////
  // Invert Image(binary image)
  for (row = 0; row < ROW; row++) {
    for (col = 0; col < COL; col++) {
      if (B_IMAGE[row][col] == 0)
        InvertImage[row][col] = 1;
      else
        InvertImage[row][col] = 0;
    }
  }

  ////////////////////////////////////////////////////
  // Result2 Image
  for (row = 0; row < ROW - 2; row++) {
    for (col = 0; col < COL - 2; col++) {
      // Result2Image[row+1][col+1]
      //	= ((InvertImage[row+0][col+0] * SEb[0][0])+
      //		(InvertImage[row+0][col+1] * SEb[0][1])+
      //		(InvertImage[row+0][col+2] * SEb[0][2])+
      //		(InvertImage[row+1][col+0] * SEb[1][0])+
      //		(InvertImage[row+1][col+1] * SEb[1][1])+
      //		(InvertImage[row+1][col+2] * SEb[1][2])+
      //		(InvertImage[row+2][col+0] * SEb[2][0])+
      //		(InvertImage[row+2][col+1] * SEb[2][1])+
      //		(InvertImage[row+2][col+2] * SEb[2][2]));

      // Reset Flag
      for (i = 0; i < 9; i++)
        flag[i] = 0;

      // Background Case
      if ((InvertImage[row + 0][col + 0] * SEb[0][0]) == 1)
        flag[0] = 1;
      if ((InvertImage[row + 0][col + 1] * SEb[0][1]) == 1)
        flag[1] = 1;
      if ((InvertImage[row + 0][col + 2] * SEb[0][2]) == 1)
        flag[2] = 1;
      if ((InvertImage[row + 1][col + 0] * SEb[1][0]) == 1)
        flag[3] = 1;
      if ((InvertImage[row + 1][col + 1] * SEb[1][1]) == 1)
        flag[4] = 1;
      if ((InvertImage[row + 1][col + 2] * SEb[1][2]) == 1)
        flag[5] = 1;
      if ((InvertImage[row + 2][col + 0] * SEb[2][0]) == 1)
        flag[6] = 1;
      if ((InvertImage[row + 2][col + 1] * SEb[2][1]) == 1)
        flag[7] = 1;
      if ((InvertImage[row + 2][col + 2] * SEb[2][2]) == 1)
        flag[8] = 1;

      // check flag
      // SE1
      if (flag[0] == 1 && flag[1] == 1 && flag[2] == 1) {
        Result2Image[row + 1][col + 1] = 1;
      }
      // SE2
      else if (flag[1] == 1 && flag[2] == 1 && flag[5] == 1) {
        Result2Image[row + 1][col + 1] = 1;
      }
      // SE3
      else if (flag[2] == 1 && flag[5] == 1 && flag[8] == 1) {
        Result2Image[row + 1][col + 1] = 1;
      }
      // SE4
      else if (flag[5] == 1 && flag[7] == 1 && flag[8] == 1) {
        Result2Image[row + 1][col + 1] = 1;
      }
      // SE5
      else if (flag[6] == 1 && flag[7] == 1 && flag[8] == 1) {
        Result2Image[row + 1][col + 1] = 1;
      }
      // SE6
      else if (flag[3] == 1 && flag[6] == 1 && flag[7] == 1) {
        Result2Image[row + 1][col + 1] = 1;
      }
      // SE7
      else if (flag[0] == 1 && flag[3] == 1 && flag[6] == 1) {
        Result2Image[row + 1][col + 1] = 1;
      }
      // SE8
      else if (flag[0] == 1 && flag[1] == 1 && flag[3] == 1) {
        Result2Image[row + 1][col + 1] = 1;
      }

      else {
        Result2Image[row + 1][col + 1] = 0;
      }
    }
  }

  ////////////////////////////////////////////////////
  // HM Image (Result1 AND Result2)
  for (row = 0; row < ROW; row++) {
    for (col = 0; col < COL; col++) {
      Result3Image[row][col] = Result1Image[row][col] * Result2Image[row][col];

      if ((HMImage[row][col] == 0) && (Result3Image[row][col] == 0)) {
        HMImage[row][col] = 0;
      } else {
        HMImage[row][col] = 1;
      }
    }
  }

  // Make Thinning Image
  // Method : image(Binary) - HitAndMiss((binary)image, se)
  // Thinning Image
  for (row = 0; row < ROW; row++) {
    for (col = 0; col < COL; col++) {
      // ThinningImage[row][col] = BinaryImage[row][col] * HMImage[row][col];
      if ((BinaryImage[row][col] == 1) && (HMImage[row][col] == 0))
        ThinningImage[row][col] = 1;
      else
        ThinningImage[row][col] = 0;
    }
  }
}

// Thinning
void CreateImageThinningWindow(HWND hParent, int x, int y, int width,
                               int height) {
  if (hc15)
    MessageBox(hc15, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc15 =
        CreateWindow(szImageThinningClass, "Thinning",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc15) {
      MessageBox(hc15, "Non Input Image", "Thinning Error", MB_OK);
    }
  }
}

// Thinning Procedure
// Original Image -> Binary Image -> Thinning Image(Original Image - HM Image)
LRESULT CALLBACK ImageThinningProc(HWND hWnd, UINT message, WPARAM wParam,
                                   LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  // Decision(Black or White)
  unsigned int threshold = 0;

  unsigned int image_size = ROW * COL;

  unsigned long sum = 0;

  int x = 0;

  // Structuring Element(f=foreground, b=background, x=don't care)
  int SE1f[3][3] = {x, x, x, x, 1, x, 1, 1, 1};

  int SE1b[3][3] = {1, 1, 1, x, x, x, x, x, x};

  ///////////////////////////
  int SE2f[3][3] = {x, x, x, 1, 1, x, x, 1, x};

  int SE2b[3][3] = {x, 1, 1, x, x, 1, x, x, x};

  ///////////////////////////
  int SE3f[3][3] = {1, x, x, 1, 1, x, 1, x, x};

  int SE3b[3][3] = {x, x, 1, x, x, 1, x, x, 1};

  ///////////////////////////
  int SE4f[3][3] = {x, 1, x, 1, 1, x, x, x, x};

  int SE4b[3][3] = {x, x, x, x, x, 1, x, 1, 1};

  ///////////////////////////
  int SE5f[3][3] = {1, 1, 1, x, 1, x, x, x, x};

  int SE5b[3][3] = {x, x, x, x, x, x, 1, 1, 1};

  ///////////////////////////
  int SE6f[3][3] = {x, 1, x, x, 1, 1, x, x, x};

  int SE6b[3][3] = {x, x, x, 1, x, x, 1, 1, x};

  ///////////////////////////
  int SE7f[3][3] = {x, x, 1, x, 1, 1, x, x, 1};

  int SE7b[3][3] = {1, x, x, 1, x, x, 1, x, x};

  ///////////////////////////
  int SE8f[3][3] = {x, x, x, x, 1, 1, x, 1, x};

  int SE8b[3][3] = {1, 1, x, 1, x, x, x, x, x};

  // unsigned char BinaryImage_Temp[ROW][COL];

  switch (message) {
  case WM_CREATE:

    // Sum For Binary
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        sum = sum + TImage[row][col];
      }
    }

    threshold = sum / image_size;

    // Make Binary Image
    // Boundary decision (0 or 255)
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        if (TImage[row][col] > threshold)
          BinaryImage[row][col] = 1; // White 1
        else
          BinaryImage[row][col] = 0; // Black 0
      }
    }

    // HMImage Reset to 0
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        HMImage[row][col] = 0;
        // HMImage[row][col] = BinaryImage[row][col];
      }
    }
    // ThinningImage Reset to 0
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        ThinningImage[row][col] = 0;
        // ThinningImage[row][col] = BinaryImage[row][col];
      }
    }

    // Copy Binary Image To Temp...
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		BinaryImage_Temp[row][col] = BinaryImage[row][col];
    //	}
    // }
    // First, Initialize
    // for (row = 0; row < 1; row++)
    //{
    //	HitAndMiss(BinaryImage, SE1f, SE1b);
    //	HitAndMiss(BinaryImage, SE2f, SE2b);
    //	HitAndMiss(BinaryImage, SE3f, SE3b);
    //	HitAndMiss(BinaryImage, SE4f, SE4b);
    //	HitAndMiss(BinaryImage, SE5f, SE5b);
    //	HitAndMiss(BinaryImage, SE6f, SE6b);
    //	HitAndMiss(BinaryImage, SE7f, SE7b);
    //	HitAndMiss(BinaryImage, SE8f, SE8b);
    // }

    // 반복하여 Thinning 이미지 만들어 나간다.
    for (row = 0; row < 80; row++) {
      HitAndMiss(ThinningImage, SE1f, SE1b);
      HitAndMiss(ThinningImage, SE2f, SE2b);
      HitAndMiss(ThinningImage, SE3f, SE3b);
      HitAndMiss(ThinningImage, SE4f, SE4b);
      HitAndMiss(ThinningImage, SE5f, SE5b);
      HitAndMiss(ThinningImage, SE6f, SE6b);
      HitAndMiss(ThinningImage, SE7f, SE7b);
      HitAndMiss(ThinningImage, SE8f, SE8b);
    }

    // Change Binary Image Temp Value 0 -> 0,   1 -> 255
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		if (BinaryImage_Temp[row][col] == 1)
    //			BinaryImage_Temp[row][col] = 255;
    //		else
    //			BinaryImage_Temp[row][col] = 0;
    //	}
    // }

    // Change Binary Image Value 0 -> 0,   1 -> 255
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        if (BinaryImage[row][col] == 1)
          BinaryImage[row][col] = 255;
        else
          BinaryImage[row][col] = 0;
      }
    }

    // Change Hit and Miss Image Value 0 -> 0,   1 -> 255
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        if (HMImage[row][col] == 1)
          HMImage[row][col] = 255;
        else
          HMImage[row][col] = 0;
      }
    }

    // Change Thinning Binary Image Value 0 -> 0,   1 -> 255
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        if (ThinningImage[row][col] == 1)
          ThinningImage[row][col] = 255;
        else
          ThinningImage[row][col] = 0;
      }
    }
    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // Tinning Image Output
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		//rgbtemp = BinaryImage[row][col];
    //		//rgbtemp = HMImage[row][col];
    //		rgbtemp = ThinningImage[row][col];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    DrawImage(hdc, COL, ROW, ThinningImage);
    EndPaint(hWnd, &ps);

    break;

    // Thinning Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        TImage[row][col] = ThinningImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select Thinning Image...", "SELECT IMAGE", MB_OK);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc15
    hc15 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// params : forward -> data to transform
// void DCT(unsigned char forward[M][N])	//256x256 Input Image
void DCT(unsigned char forward[M][N]) {
  int x, y;
  int u, v;

  // int temp;
  double accum;
  double twoM;
  double twoN;
  double scale;
  double cu = 1.0;
  double cv = 1.0;

  int jumpx; // x+8
  int jumpy; // y+8

  ////////////////////////////////////////////
  //	M -> 256  , N -> 256 , But divide To 8
  ////////////////////////////////////////////
  twoM = 2.0 * 8; // 2 * M array
  twoN = 2.0 * 8; // 2 * N array

  // sqrt -> for get ROOT ex) root 2 = 1.1414
  scale = 2.0 / sqrt((double)8 * (double)8); // sqprt (M*N)

  jumpx = 0;
  jumpy = 0;

  // 32 times DCT(256*256 image size)
  for (jumpx = 0; jumpx < M; jumpx += 8) {
    for (jumpy = 0; jumpy < N; jumpy += 8) {
      ///////////////////////////////////////////////////////
      for (u = 0; u < 8; u++) {
        for (v = 0; v < 8; v++) {
          accum = 0.0;
          for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++) {
              accum += (double)((double)forward[x + jumpx][y + jumpy] *
                                (double)cos(((2 * x + 1) * u * PI) / twoM) *
                                (double)cos(((2 * y + 1) * v * PI) / twoN));
            }
          }

          if (u == 0)
            cu = COEFF;

          else if (u > 0)
            cu = 1.0;

          else
            cu = 1.0;

          if (v == 0)
            cv = COEFF;

          else if (v > 0)
            cv = 1.0;

          else
            cv = 1.0;

          accum *= cu;
          accum *= cv;
          accum *= scale;

          DCTImage[u + jumpx][v + jumpy] = accum;
          // DCTImage[u][v] = forward[x][y];
        }
      }
      ///////////////////////////////////////////////////////
    }
  }
}

// DCT
void CreateImageDCTWindow(HWND hParent, int x, int y, int width, int height) {
  if (hc16)
    MessageBox(hc16, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc16 =
        CreateWindow(szImageDCTClass, "DCT",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc16) {
      MessageBox(hc16, "Non Input Image", "DCT Error", MB_OK);
    }
  }
}

// DCT Procedure
LRESULT CALLBACK ImageDCTProc(HWND hWnd, UINT message, WPARAM wParam,
                              LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;
  // double TempImage[ROW][COL];

  switch (message) {
  case WM_CREATE:
    // Copy (unsigned char)TImage To (double)TempImage
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		TempImage[ROW][COL] = TImage[ROW][COL];
    //	}
    // }

    // DCT
    DCT(TImage);

    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		if (DCTImage[row][col] <= 0)
    //			DCTImage[row][col] = 0;
    //		else
    //			DCTImage[row][col] = (DCTImage[row][col]*100);
    //	}
    // }
    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // DCT Image Output
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		//rgbtemp = (int)(DCTImage[row][col]*10);
    //		rgbtemp = (int)(DCTImage[row][col]);

    //		//if (DCTImage[row][col] <= 0)
    //		//	//DCTImage[row][col] = 0;
    //		//	rgbtemp = 0;
    //		//else
    //		//	//DCTImage[row][col] = (DCTImage[row][col]*100);
    //		//	rgbtemp *= 100;

    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));

    //		// 8x8 Grid
    //		//if (row%8 == 0 || col%8 == 0)
    //		//{
    //		//	//rgbtemp = 255;
    //		//	SetPixel(hdc,col,row,(unsigned long)RGB(0,180,0));
    //		//}
    //	}
    //}

    unsigned char DCTImageTemp[ROW][COL];
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        DCTImageTemp[row][col] = (int)(DCTImage[row][col]);
      }
    }
    DrawImage(hdc, COL, ROW, DCTImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // DCT Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // TImage[row][col] = (int)DCTImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select DCT Image, IDCT Menu Enabled....",
               "SELECT IMAGE", MB_OK);

    EnableMenuItem(GetMenu(hMainWnd), IDM_IDCT, MF_ENABLED | MF_BYCOMMAND);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc16
    hc16 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// params : dct -> transformed data
// void IDCT(unsigned char dct[M][N])
void IDCT(double dct[M][N]) {
  int x, y;
  int u, v;

  // int temp;
  double accum;
  double twoM;
  double twoN;
  double scale;
  double cu = 1.0;
  double cv = 1.0;

  int jumpx; // x+8
  int jumpy; // y+8

  ////////////////////////////////////////////
  //	M -> 256  , N -> 256 , But divide To 8
  ////////////////////////////////////////////
  twoM = 2.0 * 8; // 2 * M array
  twoN = 2.0 * 8; // 2 * N array

  // sqrt -> for get ROOT ex) root 2 = 1.1414
  scale = 2.0 / sqrt((double)8 * (double)8); // sqprt (M*N)

  // 32 times DCT(256*256 image size)
  for (jumpx = 0; jumpx < M; jumpx += 8) {
    for (jumpy = 0; jumpy < N; jumpy += 8) {
      ///////////////////////////////////////////////////////
      for (x = 0; x < 8; x++) {
        for (y = 0; y < 8; y++) {
          accum = 0.0;
          for (u = 0; u < 8; u++) {
            for (v = 0; v < 8; v++) {
              if (u == 0)
                cu = COEFF;

              else if (u > 0)
                cu = 1.0;
              else
                cu = 1.0;

              if (v == 0)
                cv = COEFF;

              else if (v > 0)
                cv = 1.0;

              else
                cu = 1.0;

              accum += (double)((double)cu * (double)cv *
                                (double)cos(((2 * x + 1) * u * PI) / twoM) *
                                (double)cos(((2 * y + 1) * v * PI) / twoN) *
                                (double)dct[u + jumpx][v + jumpy]);
            }
          }

          accum *= scale;

          IDCTImage[x + jumpx][y + jumpy] = accum;
        }
      }
      ///////////////////////////////////////////////////////
    }
  }
}

// IDCT
void CreateImageIDCTWindow(HWND hParent, int x, int y, int width, int height) {
  if (hc17)
    MessageBox(hc17, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc17 =
        CreateWindow(szImageIDCTClass, "IDCT",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc17) {
      MessageBox(hc17, "Non Input Image", "IDCT Error", MB_OK);
    }
  }
}

// IDCT Procedure
LRESULT CALLBACK ImageIDCTProc(HWND hWnd, UINT message, WPARAM wParam,
                               LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  switch (message) {
  case WM_CREATE:
    // Inverse DCT
    // IDCT(TImage);
    IDCT(DCTImage);

    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		if (IDCTImage[row][col] <= 0)
    //			IDCTImage[row][col] = 0;
    //		else
    //			IDCTImage[row][col] = (IDCTImage[row][col]*100);
    //	}
    // }
    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // IDCT Image Output
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		//rgbtemp = (int)(IDCTImage[row][col]*410);
    //		rgbtemp = (int)(IDCTImage[row][col]);

    //		//For Test Image
    //		//rgbtemp = (int)(IDCTImage[row][col]*620);

    //		//if (IDCTImage[row][col] <= 0)
    //		//	//IDCTImage[row][col] = 0;
    //		//	rgbtemp = 0;
    //		//else
    //		//	//IDCTImage[row][col] = (IDCTImage[row][col]*100);
    //		//	rgbtemp *= 100;

    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));

    //		// 8x8 Grid
    //		//if (row%8 == 0 || col%8 == 0)
    //		//{
    //		//	//rgbtemp = 255;
    //		//	SetPixel(hdc,col,row,(unsigned long)RGB(0,180,0));
    //		//}
    //	}
    //}

    unsigned char IDCTImageTemp[ROW][COL];
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        IDCTImageTemp[row][col] = (int)(IDCTImage[row][col]);
      }
    }
    DrawImage(hdc, COL, ROW, IDCTImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // IDCT Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // TImage[row][col] = (int)IDCTImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Can't Select IDCT Image...", "SELECT IMAGE", MB_OK);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc17
    hc17 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

//			 HARDAMARD
//		decimal		binary
//		0	->		000
//		1	->		001
//		2	->		010
//		3	->		011
//		4	->		100
//		5	->		101
//		6	->		110
//		7	->		111
// Decimal -> Binary, Return Binary Value
int BS(int r, int number) {

  unsigned int bin_number[3];

  // dec '0'
  if (number == 0) {
    bin_number[0] = 0;
    bin_number[1] = 0;
    bin_number[2] = 0;
  }
  // dec '1'
  else if (number == 1) {
    bin_number[0] = 0;
    bin_number[1] = 0;
    bin_number[2] = 1;

  }
  // dec '2'
  else if (number == 2) {
    bin_number[0] = 0;
    bin_number[1] = 1;
    bin_number[2] = 0;
  }
  // dec '3'
  else if (number == 3) {
    bin_number[0] = 0;
    bin_number[1] = 1;
    bin_number[2] = 1;
  }
  // dec '4'
  else if (number == 4) {
    bin_number[0] = 1;
    bin_number[1] = 0;
    bin_number[2] = 0;
  }
  // dec '5'
  else if (number == 5) {
    bin_number[0] = 1;
    bin_number[1] = 0;
    bin_number[2] = 1;
  }
  // dec '6'
  else if (number == 6) {
    bin_number[0] = 1;
    bin_number[1] = 1;
    bin_number[2] = 0;
  }
  // dec '7'
  else if (number == 7) {
    bin_number[0] = 1;
    bin_number[1] = 1;
    bin_number[2] = 1;
  }

  return bin_number[r];
}

// HARDAMARD TRANSFORM
void HARDAMARD(unsigned char In_Image[ROW][COL]) {
  double accum = 0.0;

  int x, y;
  int u, v;

  int jumpx = 0, jumpy = 0;
  int exp = 0;

  int i;
  int A, B, C, D;

  // if N(dec) -> n(bin)--> need 3 digit
  int number = 8;
  int digit = 3;

  for (jumpx = 0; jumpx < ROW; jumpx += 8) {
    for (jumpy = 0; jumpy < COL; jumpy += 8) {
      ////////////////////////////////////////////////
      for (u = 0; u < number; u++) {
        for (v = 0; v < number; v++) {
          accum = 0.0;
          for (x = 0; x < number; x++) {
            for (y = 0; y < number; y++) {
              exp = 0;
              //////////////////////////////////////////////////////////
              for (i = 0; i < digit; i++) {
                // BS(int r, int number)
                // exp += ( BS(i,x) * BS(i,u) ) + ( BS(i,y) * BS(i,v) );

                A = BS(i, x);
                B = BS(i, u);
                C = BS(i, y);
                D = BS(i, v);

                exp += (A * B) + (C * D);
              }
              //////////////////////////////////////////////////////////

              accum += (double)(In_Image[x + jumpx][y + jumpy]) *
                       (double)(pow(float(-1), exp));
            }
          }
          // HARDAMARDImage[u+jumpx][v+jumpy] = (1/number) * accum;
          HARDAMARDImage[u + jumpx][v + jumpy] = (double)(accum / number);
        }
      }
      ////////////////////////////////////////////////
    }
  }
}

// HARDAMARD
void CreateImageHARDAMARDWindow(HWND hParent, int x, int y, int width,
                                int height) {
  if (hc18)
    MessageBox(hc18, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc18 =
        CreateWindow(szImageHARDAMARDClass, "HARDAMARD",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc18) {
      MessageBox(hc18, "Non Input Image", "HARDAMARD Error", MB_OK);
    }
  }
}

// HARDAMARD Procedure
LRESULT CALLBACK ImageHARDAMARDProc(HWND hWnd, UINT message, WPARAM wParam,
                                    LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  switch (message) {
  case WM_CREATE:

    // Hardamard Transform
    HARDAMARD(TImage);

    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // HARDAMARD Image Output
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		rgbtemp = (int)(HARDAMARDImage[row][col]);
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //		// 8x8 Grid
    //		//if (row%8 == 0 || col%8 == 0)
    //		//{
    //		//	//rgbtemp = 255;
    //		//	SetPixel(hdc,col,row,(unsigned long)RGB(0,180,0));
    //		//}
    //	}
    // }

    unsigned char HARDAMARDImageTemp[ROW][COL];
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        HARDAMARDImageTemp[row][col] = (int)(HARDAMARDImage[row][col]);
      }
    }
    DrawImage(hdc, COL, ROW, HARDAMARDImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // HARDAMARD Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // TImage[row][col] = (int)HARDMARDImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Select HARDAMARD Image, IHARDAMARD Menu Enabled...",
               "SELECT IMAGE", MB_OK);

    EnableMenuItem(GetMenu(hMainWnd), IDM_IHARDAMARD,
                   MF_ENABLED | MF_BYCOMMAND);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc18
    hc18 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// IHARDAMARD(Inverse Hardamard) TRANSFORM
void IHARDAMARD(double HardamardedImage[ROW][COL]) {
  double accum = 0.0;
  int x, y;
  int u, v;

  int jumpx = 0, jumpy = 0;
  int exp = 0;
  int i;
  int A, B, C, D;

  // if N(dec) -> n(bin)--> need 3 digit
  int number = 8;
  int digit = 3;

  for (jumpx = 0; jumpx < 256; jumpx += 8) {
    for (jumpy = 0; jumpy < 256; jumpy += 8) {
      ////////////////////////////////////////////////
      for (x = 0; x < number; x++) {
        for (y = 0; y < number; y++) {
          accum = 0.0;
          for (u = 0; u < number; u++) {
            for (v = 0; v < number; v++) {
              exp = 0;
              //////////////////////////////////////////////////////////
              for (i = 0; i < digit; i++) {
                // BS(int r, int number)
                // exp += ( BS(i,x) * BS(i,u) ) + ( BS(i,y) * BS(i,v) );

                A = BS(i, x);
                B = BS(i, u);
                C = BS(i, y);
                D = BS(i, v);

                exp += (A * B) + (C * D);
              }
              accum += (double)(HardamardedImage[u + jumpx][v + jumpy]) *
                       (double)(pow(float(-1), exp));
              //////////////////////////////////////////////////////////
            }
          }
          // IHARDAMARDImage[x+jumpx][y+jumpy] = (1/number) * accum;
          IHARDAMARDImage[x + jumpx][y + jumpy] = (double)(accum / number);
        }
      }
      ////////////////////////////////////////////////
    }
  }
}

// IHARDAMARD(Inverse HARDAMARD)
void CreateImageIHARDAMARDWindow(HWND hParent, int x, int y, int width,
                                 int height) {
  if (hc19)
    MessageBox(hc19, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc19 =
        CreateWindow(szImageIHARDAMARDClass, "IHARDAMARD",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc19) {
      MessageBox(hc19, "Non Input Image", "IHARDAMARD Error", MB_OK);
    }
  }
}

// IHARDAMARD Procedure
LRESULT CALLBACK ImageIHARDAMARDProc(HWND hWnd, UINT message, WPARAM wParam,
                                     LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  switch (message) {
  case WM_CREATE:

    // Inverse Hardamard Transform
    IHARDAMARD(HARDAMARDImage);

    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // Inverse HARDAMARD Image Output
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		rgbtemp = (int)(IHARDAMARDImage[row][col]);
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //		// 8x8 Grid
    //		//if (row%8 == 0 || col%8 == 0)
    //		//{
    //		//	//rgbtemp = 255;
    //		//	SetPixel(hdc,col,row,(unsigned long)RGB(0,180,0));
    //		//}
    //	}
    // }

    unsigned char IHARDAMARDImageTemp[ROW][COL];
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        IHARDAMARDImageTemp[row][col] = (int)(IHARDAMARDImage[row][col]);
      }
    }
    DrawImage(hdc, COL, ROW, IHARDAMARDImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // IHARDAMARD Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // TImage[row][col] = (int)IHARDMARDImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Can't Select IHARDAMARD Image...", "SELECT IMAGE",
               MB_OK);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc19
    hc19 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

void WAVELET(unsigned char In_Image[ROW][COL]) {
  float lMask[2] = {0.5, 0.5};
  float hMask[2] = {0.5, -0.5};

  int x, y;

  float low = 0, high = 0;

  int move = 0;

  float TempImage[ROW][COL];

  ////////////////////////////////////////////////////////////////
  // Wavelet Transform ( Horizontal LH Pass -> Vertical LH Pass )//
  ////////////////////////////////////////////////////////////////

  // Horizontal LOW Pass, HIGH Pass
  //////////////////////////////////////////////////
  for (x = 0; x < ROW; x++) {
    move = 0;
    // LOW & HIGH
    for (y = 0; y < COL; y++) {
      low = (lMask[0] * (float)In_Image[x + 0][y + 0]) +
            (lMask[1] * (float)In_Image[x + 0][y + 1]);

      high = (hMask[0] * (float)In_Image[x + 0][y + 0]) +
             (hMask[1] * (float)In_Image[x + 0][y + 1]);

      if (y % 2 == 0) {
        TempImage[x][move++] = low;
        TempImage[x][move + 127] = high;

        // WAVELETImage[x][move++] = (double)low;
        // WAVELETImage[x][move+127] = (double)high;
      }
    }
  }
  //////////////////////////////////////////////////

  // Vertical LOW Pass, HIGH Pass
  //////////////////////////////////////////////////
  for (x = 0; x < ROW; x++) {
    move = 0;
    // LOW & HIGH
    for (y = 0; y < COL; y++) {
      low = (lMask[0] * TempImage[y + 0][x + 0]) +
            (lMask[1] * TempImage[y + 1][x + 0]);

      high = (hMask[0] * TempImage[y + 0][x + 0]) +
             (hMask[1] * TempImage[y + 1][x + 0]);

      if (y % 2 == 0) {
        WAVELETImage[move++][x] = low;
        WAVELETImage[move + 127][x] = high;
      }
    }
  }
  //////////////////////////////////////////////////
}

// WAVELET
void CreateImageWAVELETWindow(HWND hParent, int x, int y, int width,
                              int height) {
  if (hc20)
    MessageBox(hc20, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc20 =
        CreateWindow(szImageWAVELETClass, "WAVELET",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc20) {
      MessageBox(hc20, "Non Input Image", "WAVELET Error", MB_OK);
    }
  }
}

// WAVELET Procedure
LRESULT CALLBACK ImageWAVELETProc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  switch (message) {
  case WM_CREATE:

    // Wavelet Transform...
    WAVELET(TImage);

    break;

  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // WAVELET Image Output
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		rgbtemp = (int)(WAVELETImage[row][col]);
    //		//rgbtemp = TImage[row][col];
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }

    unsigned char WAVELETImageTemp[ROW][COL];
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        WAVELETImageTemp[row][col] = (int)(WAVELETImage[row][col]);
      }
    }
    DrawImage(hdc, COL, ROW, WAVELETImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // WAVELET Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // TImage[row][col] = (int)WAVELETImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd,
               "You Select Wavelet Image, Inverse Wavelet Menu Enabled...",
               "SELECT IMAGE", MB_OK);
    EnableMenuItem(GetMenu(hMainWnd), IDM_IWAVELET, MF_ENABLED | MF_BYCOMMAND);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc20
    hc20 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// Inverse WAVELET
void CreateImageIWAVELETWindow(HWND hParent, int x, int y, int width,
                               int height) {
  if (hc21)
    MessageBox(hc21, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc21 =
        CreateWindow(szImageIWAVELETClass, "IWAVELET",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc21) {
      MessageBox(hc21, "Non Input Image", "IWAVELET Error", MB_OK);
    }
  }
}

void IWAVELET(double WaveletedImage[ROW][COL]) {
  // float lMask[2] = {0.5, 0.5};
  // float hMask[2] = {0.5, -0.5};

  // float i_lMask[2] = {2, 2};
  // float i_hMask[2] = {2, -2};

  int x, y;

  // float low=0, high=0;

  float plus = 0, minus = 0;

  int move = 0;

  float TempImage[ROW][COL];

  ////////////////////////////////////////////////////////////////////////
  // Inverse Wavelet Transform ( Vertical LH Pass -> Horizontal LH Pass )//
  ////////////////////////////////////////////////////////////////////////

  // Inverse Vertical LOW Pass, HIGH Pass
  //////////////////////////////////////////////////
  for (x = 0; x < ROW; x++) {
    move = 0;
    // LOW & HIGH
    for (y = 0; y < 128; y++) {
      // low = (i_lMask[0] * (float)WaveletedImage[y+0][x+0])
      //	+ (i_lMask[1] * (float)WaveletedImage[y+127][x+0]);

      // high = (i_hMask[0] * (float)WaveletedImage[y+0][x+0])
      //	+ (i_hMask[1] * (float)WaveletedImage[y+127][x+0]);

      plus = ((float)WaveletedImage[y + 0][x + 0] +
              (float)WaveletedImage[y + 128][x + 0]);

      minus = ((float)WaveletedImage[y + 0][x + 0] -
               (float)WaveletedImage[y + 128][x + 0]);

      // if (x = 0)
      {
        TempImage[move][x] = plus;
        TempImage[++move][x] = minus;

        // IWAVELETImage[move][x] = (double)plus;
        // IWAVELETImage[++move][x] = (double)minus;
      }

      move++;
    }
  }
  //////////////////////////////////////////////////

  // Inverse Horizontal LOW Pass, HIGH Pass
  //////////////////////////////////////////////////
  for (x = 0; x < ROW; x++) {
    move = 0;
    // LOW & HIGH
    for (y = 0; y < 128; y++) {
      plus =
          ((float)TempImage[x + 0][y + 0] + (float)TempImage[x + 0][y + 128]);

      minus =
          ((float)TempImage[x + 0][y + 0] - (float)TempImage[x + 0][y + 128]);

      IWAVELETImage[x][move] = (double)plus;
      IWAVELETImage[x][++move] = (double)minus;

      move++;
    }
  }
  //////////////////////////////////////////////////
}

// Inverse WAVELET Procedure
LRESULT CALLBACK ImageIWAVELETProc(HWND hWnd, UINT message, WPARAM wParam,
                                   LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  switch (message) {
  case WM_CREATE:

    // Wavelet Transform...
    IWAVELET(WAVELETImage);

    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // WAVELET Image Output
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		rgbtemp = (int)(IWAVELETImage[row][col]);
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }

    unsigned char IWAVELETImageTemp[ROW][COL];
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        IWAVELETImageTemp[row][col] = (int)(IWAVELETImage[row][col]);
      }
    }
    DrawImage(hdc, COL, ROW, IWAVELETImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // Inverse WAVELET Image -> Temp Image
  case WM_LBUTTONDOWN:
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // TImage[row][col] = (int)IWAVELETImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd, "You Can't Select Inverse WAVELET Image...",
               "SELECT IMAGE", MB_OK);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    // PostQuitMessage(0);	//Quit Main Window
    // DestroyWindow(hWnd);	//hc21
    hc21 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// DCT_JPEG
void CreateImageDCT_JPEGWindow(HWND hParent, int x, int y, int width,
                               int height) {
  if (hc22)
    MessageBox(hc22, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc22 =
        CreateWindow(szImageDCT_JPEGClass, "DCT_JPEG",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc22) {
      MessageBox(hc22, "Non Input Image", "DCT_JPEG Error", MB_OK);
    }
  }
}

// DCT_JPEG Procedure
LRESULT CALLBACK ImageDCT_JPEGProc(HWND hWnd, UINT message, WPARAM wParam,
                                   LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;
  // double TempImage[ROW][COL];

  switch (message) {
  case WM_CREATE:
    // DCT
    DCT(TImage);

    // Copy DCTImage to DCT_JPEGImage
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        DCT_JPEGImage[row][col] = DCTImage[row][col];
      }
    }
    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // DCT Image Output
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		//rgbtemp = (int)(DCTImage[row][col]*10);
    //		rgbtemp = (unsigned char)(DCT_JPEGImage[row][col]);
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //		// 8x8 Grid
    //		//if (row%8 == 0 || col%8 == 0)
    //		//{
    //		//	//rgbtemp = 255;
    //		//	SetPixel(hdc,col,row,(unsigned long)RGB(0,180,0));
    //		//}
    //	}
    // }

    unsigned char DCT_JPEGImageTemp[ROW][COL];
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        DCT_JPEGImageTemp[row][col] = (int)(DCT_JPEGImage[row][col]);
      }
    }
    DrawImage(hdc, COL, ROW, DCT_JPEGImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // DCT_JPEG Image -> Temp Image
  case WM_LBUTTONDOWN:

    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // TImage[row][col] = (int)DCTImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }

    MessageBox(hWnd, "You Select DCT_JPEG Image, Quantization Menu Enabled....",
               "SELECT IMAGE", MB_OK);

    EnableMenuItem(GetMenu(hMainWnd), IDM_QUANTIZATION_JPEG,
                   MF_ENABLED | MF_BYCOMMAND);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    hc22 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// Quantization Processing
void Quantization_JPEG(double DCTedImage[ROW][COL]) {

  //////////////////////////////////////////////////////
  //			Quantization Table (In JPEG)			//
  //////////////////////////////////////////////////////
  unsigned char QUANT_TABLE[8][8] = {
      16, 11, 10, 16, 24,  40,  51,  61,  12, 12, 14, 19, 26,  58,  60,  66,
      14, 13, 16, 24, 40,  57,  69,  57,  14, 17, 22, 29, 51,  87,  80,  62,
      18, 22, 37, 56, 68,  109, 103, 77,  24, 36, 55, 64, 81,  104, 113, 92,
      49, 64, 78, 87, 103, 121, 120, 101, 72, 92, 95, 98, 112, 100, 130, 99};

  unsigned int row, col;
  unsigned int i, j;

  for (row = 0; row < ROW; row += 8) {
    for (col = 0; col < COL; col += 8) {
      for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
          Quantization_JPEGImage[i + row][j + col] =
              DCTedImage[i + row][j + col] / (QUANT_TABLE[i][j]);
        }
      }
    }
  }
}

// Quantization_JPEG
void CreateImageQuantization_JPEGWindow(HWND hParent, int x, int y, int width,
                                        int height) {
  if (hc23)
    MessageBox(hc23, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc23 =
        CreateWindow(szImageQuantization_JPEGClass, "Quantization_JPEG",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc23) {
      MessageBox(hc23, "Non Input Image", "Quantization_JPEG Error", MB_OK);
    }
  }
}

// Quantization_JPEG Procedure
LRESULT CALLBACK ImageQuantization_JPEGProc(HWND hWnd, UINT message,
                                            WPARAM wParam, LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  switch (message) {
  case WM_CREATE:
    // Initialize
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        Quantization_JPEGImage[row][col] = 0;
      }
    }
    // Quantization_JPEG
    Quantization_JPEG(DCT_JPEGImage);

    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // Quantization
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		//rgbtemp = (int)(Quantization_JPEGImage[row][col]);
    //		rgbtemp = (unsigned char)(Quantization_JPEGImage[row][col]);
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //		// 8x8 Grid
    //		//if (row%8 == 0 || col%8 == 0)
    //		//{
    //		//	//rgbtemp = 255;
    //		//	SetPixel(hdc,col,row,(unsigned long)RGB(0,180,0));
    //		//}
    //	}
    // }

    unsigned char Quantization_JPEGImageTemp[ROW][COL];
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        Quantization_JPEGImageTemp[row][col] =
            (int)(Quantization_JPEGImage[row][col]);
      }
    }
    DrawImage(hdc, COL, ROW, Quantization_JPEGImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // Quantization_JPEG Image -> Temp Image
  case WM_LBUTTONDOWN:

    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // TImage[row][col] = (int)DCTImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(hWnd,
               "You Select Quantization_JPEG Image, IQuantization_JPEG Menu "
               "Enabled....",
               "SELECT IMAGE", MB_OK);

    EnableMenuItem(GetMenu(hMainWnd), IDM_IQUANTIZATION_JPEG,
                   MF_ENABLED | MF_BYCOMMAND);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    hc23 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// Quantization Processing
void IQuantization_JPEG(double QuantizationedImage[ROW][COL]) {

  //////////////////////////////////////////////////////
  //			Quantization Table (In JPEG)			//
  //////////////////////////////////////////////////////
  unsigned char QUANT_TABLE[8][8] = {
      16, 11, 10, 16, 24,  40,  51,  61,  12, 12, 14, 19, 26,  58,  60,  66,
      14, 13, 16, 24, 40,  57,  69,  57,  14, 17, 22, 29, 51,  87,  80,  62,
      18, 22, 37, 56, 68,  109, 103, 77,  24, 36, 55, 64, 81,  104, 113, 92,
      49, 64, 78, 87, 103, 121, 120, 101, 72, 92, 95, 98, 112, 100, 130, 99};

  unsigned int row, col;
  unsigned int i, j;

  for (row = 0; row < ROW; row += 8) {
    for (col = 0; col < COL; col += 8) {
      for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
          IQuantization_JPEGImage[i + row][j + col] =
              QuantizationedImage[i + row][j + col] * (QUANT_TABLE[i][j]);
        }
      }
    }
  }
}

// IQuantization_JPEG
void CreateImageIQuantization_JPEGWindow(HWND hParent, int x, int y, int width,
                                         int height) {
  if (hc24)
    MessageBox(hc24, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc24 =
        CreateWindow(szImageIQuantization_JPEGClass, "IQuantization_JPEG",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc24) {
      MessageBox(hc24, "Non Input Image", "IQuantization_JPEG Error", MB_OK);
    }
  }
}

// IQuantization_JPEG Procedure
LRESULT CALLBACK ImageIQuantization_JPEGProc(HWND hWnd, UINT message,
                                             WPARAM wParam, LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  switch (message) {
  case WM_CREATE:
    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // IQuantization
    IQuantization_JPEG(Quantization_JPEGImage);

    // IQuantization
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		//rgbtemp = (int)(IQuantization_JPEGImage[row][col]);
    //		rgbtemp = (unsigned char)(IQuantization_JPEGImage[row][col]);
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //		// 8x8 Grid
    //		//if (row%8 == 0 || col%8 == 0)
    //		//{
    //		//	//rgbtemp = 255;
    //		//	SetPixel(hdc,col,row,(unsigned long)RGB(0,180,0));
    //		//}
    //	}
    // }
    unsigned char IQuantization_JPEGImageTemp[ROW][COL];
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        IQuantization_JPEGImageTemp[row][col] =
            (int)(IQuantization_JPEGImage[row][col]);
      }
    }
    DrawImage(hdc, COL, ROW, IQuantization_JPEGImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // IQuantization_JPEG Image -> Temp Image
  case WM_LBUTTONDOWN:

    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        // TImage[row][col] = (int)DCTImage[row][col];
        // SetPixel(hdc,col,row,(unsigned long)RGB(rgbtemp,rgbtemp,rgbtemp));
      }
    }
    MessageBox(
        hWnd, "You Select IQuantization_JPEG Image, IDCT_JPEG Menu Enabled....",
        "SELECT IMAGE", MB_OK);

    EnableMenuItem(GetMenu(hMainWnd), IDM_IDCT_JPEG, MF_ENABLED | MF_BYCOMMAND);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    hc24 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// IDCT_JPEG
void CreateImageIDCT_JPEGWindow(HWND hParent, int x, int y, int width,
                                int height) {
  if (hc25)
    MessageBox(hc25, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc25 =
        CreateWindow(szImageIDCT_JPEGClass, "IDCT_JPEG",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc25) {
      MessageBox(hc25, "Non Input Image", "IDCT_JPEG Error", MB_OK);
    }
  }
}

// IDCT_JPEG Procedure
LRESULT CALLBACK ImageIDCT_JPEGProc(HWND hWnd, UINT message, WPARAM wParam,
                                    LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int row, col;

  switch (message) {
  case WM_CREATE:
    // Inverse DCT
    // IDCT(TImage);
    IDCT(IQuantization_JPEGImage);

    // Copy IDCTImage to IDCT_JPEGImage
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        IDCT_JPEGImage[row][col] = IDCTImage[row][col];
      }
    }

    // Copy IDCTImage to IDCT_JPEGImage
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        IDCT_JPEGImage[row][col] = IDCTImage[row][col];
      }
    }
    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // IDCT Image Output
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		//rgbtemp = (int)(IDCTImage[row][col]*410);
    //		rgbtemp = (unsigned char)(IDCT_JPEGImage[row][col]);
    //		SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //		// 8x8 Grid
    //		//if (row%8 == 0 || col%8 == 0)
    //		//{
    //		//	//rgbtemp = 255;
    //		//	SetPixel(hdc,col,row,(unsigned long)RGB(0,180,0));
    //		//}
    //	}
    // }

    unsigned char IDCT_JPEGImageTemp[ROW][COL];
    for (row = 0; row < ROW; row++) {
      for (col = 0; col < COL; col++) {
        IDCT_JPEGImageTemp[row][col] = (int)(IDCT_JPEGImage[row][col]);
      }
    }
    DrawImage(hdc, COL, ROW, IDCT_JPEGImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // IDCT_JPEG Image -> Temp Image
  case WM_LBUTTONDOWN:
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		//TImage[row][col] = (int)IDCTImage[row][col];
    //		//SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    // MessageBox(hWnd, "You Can't Select IDCT Image...", "SELECT IMAGE",
    // MB_OK);
    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    hc25 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

void MakeF1_(unsigned char CF[FROW][FCOL], unsigned char RF[FROW][FCOL])
// Current Frame, Reference Frame...
{
  int frow, fcol;

  int k, l;

  int i, j;

  int mvi, mvj; // decision move vector i, j

  double sum_temp, sum;
  // double MAD;
  // double best;
  // double MM;

  // MM = 1 / (16*16);
  // for (frow = 0; frow < FROW; frow++)
  //{
  //	for (fcol = 0; fcol < FCOL; fcol++)
  //	{
  //		F1_Image[frow][fcol] = abs(CF[frow][fcol] - RF[frow][fcol]);
  //	}
  // }

  // Block Matching...
  // 352x240 Image...
  for (frow = 0; frow < FROW; frow += 16) {
    for (fcol = 0; fcol < FCOL; fcol += 16) {

      // sum's initial value is 100
      // why ? pixel differce 0~255 ... This 16x16(256)
      // so.. Maximum Value 255 * 256 = 65280
      sum = 65280;
      sum_temp = 0;

      //////////////////////////////////////////////////////////////////////
      //[+16, -16] Search Space
      for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {

          sum_temp = 0;
          //////////////////////////////////////////////////////////////////////
          // 16x16 Pixels(Macro Block)
          for (k = 0; k < 16; k++) {
            for (l = 0; l < 16; l++) {

              sum_temp +=
                  abs(CF[frow + k][fcol + l] - RF[frow + i + k][fcol + j + l]);
            }
          }
          //////////////////////////////////////////////////////////////////////

          // Least Value(Best Match Block)
          if (sum_temp <= sum) {
            sum = sum_temp;
            mvi = i;
            mvj = j;
          }

        } // Close j
      } // Close i
      //////////////////////////////////////////////////////////////////////

      for (k = 0; k < 16; k++) {
        for (l = 0; l < 16; l++) {

          F1_Image[frow + k][fcol + l] = RF[frow + mvi + k][fcol + mvj + l];
        }
      }

    } // Close fcol
  } // Close frow
}

// Make Frame 1'
void CreateImageMakeF1_Window(HWND hParent, int x, int y, int width,
                              int height) {
  if (hc26)
    MessageBox(hc26, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc26 =
        CreateWindow(szImageMakeF1_Class, "Make Frame 1'",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc26) {
      MessageBox(hc26, "Non Input Image", "MakeF1_ Error", MB_OK);
    }
  }
}

// Make Frame 1' With Motion Vector(MV) Procedure
LRESULT CALLBACK ImageMakeF1_Proc(HWND hWnd, UINT message, WPARAM wParam,
                                  LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int frow, fcol;

  switch (message) {
  case WM_CREATE:
    // Make Frame1 '
    MakeF1_(InputFrame2Image, InputFrame1Image);

    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // IDCT Image Output
    // for (frow = 0; frow < FROW; frow++)
    //{
    //	for (fcol = 0; fcol < FCOL; fcol++)
    //	{
    //		rgbtemp = (unsigned char)(F1_Image[frow][fcol]);
    //		SetPixel(hdc,fcol,frow,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //		// 8x8 Grid
    //		//if (row%8 == 0 || col%8 == 0)
    //		//{
    //		//	//rgbtemp = 255;
    //		//	SetPixel(hdc,col,row,(unsigned long)RGB(0,180,0));
    //		//}
    //	}
    // }

    unsigned char F1_ImageTemp[FROW][FCOL];
    for (frow = 0; frow < FROW; frow++) {
      for (fcol = 0; fcol < FCOL; fcol++) {
        F1_ImageTemp[frow][fcol] = (int)(F1_Image[frow][fcol]);
      }
    }
    DrawImage2(hdc, FCOL, FROW, F1_ImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // IDCT_JPEG Image -> Temp Image
  case WM_LBUTTONDOWN:
    // for (frow = 0; frow < FROW; frow++)
    //{
    //	for (fcol = 0; fcol < FCOL; fcol++)
    //	{
    //		//TImage[frow][fcol] = (int)IDCTImage[frow][fcol];
    //		//SetPixel(hdc,fcol,frow,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    // MessageBox(hWnd, "You Can't Select IDCT Image...", "SELECT IMAGE",
    // MB_OK);
    EnableMenuItem(GetMenu(hMainWnd), IDM_MAKEF2F1_, MF_ENABLED | MF_BYCOMMAND);
    MessageBox(
        hWnd,
        "You Clicked Make Frame 1' , Make Frame 2 - Frame 1' Menu Enabled",
        "SELEECT IMAGE", MB_OK);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    hc26 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// Make Result Frame
void CreateImageMakeF2F1_Window(HWND hParent, int x, int y, int width,
                                int height) {
  if (hc27)
    MessageBox(hc27, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc27 =
        CreateWindow(szImageMakeF2F1_Class, "Make Frame 2 - Frame 1'",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc27) {
      MessageBox(hc27, "Non Input Image", "Make Frame 2 - Frame 1' Error",
                 MB_OK);
    }
  }
}

// Make Result Frame
LRESULT CALLBACK ImageMakeF2F1_Proc(HWND hWnd, UINT message, WPARAM wParam,
                                    LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int frow, fcol;

  switch (message) {
  case WM_CREATE:
    // Frame 2 - Frame 1'
    for (frow = 0; frow < FROW; frow++) {
      for (fcol = 0; fcol < FCOL; fcol++) {
        F2F1_Image[frow][fcol] =
            InputFrame2Image[frow][fcol] - F1_Image[frow][fcol];
      }
    }
    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);

    // IDCT Image Output
    // for (frow = 0; frow < FROW; frow++)
    //{
    //	for (fcol = 0; fcol < FCOL; fcol++)
    //	{
    //		rgbtemp = (unsigned char)(F2F1_Image[frow][fcol]);
    //		SetPixel(hdc,fcol,frow,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //		// 8x8 Grid
    //		//if (row%8 == 0 || col%8 == 0)
    //		//{
    //		//	//rgbtemp = 255;
    //		//	SetPixel(hdc,col,row,(unsigned long)RGB(0,180,0));
    //		//}
    //	}
    // }

    unsigned char F2F1_ImageTemp[FROW][FCOL];
    for (frow = 0; frow < FROW; frow++) {
      for (fcol = 0; fcol < FCOL; fcol++) {
        F2F1_ImageTemp[frow][fcol] = (int)(F2F1_Image[frow][fcol]);
      }
    }
    DrawImage2(hdc, FCOL, FROW, F2F1_ImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // IDCT_JPEG Image -> Temp Image
  case WM_LBUTTONDOWN:
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		//TImage[row][col] = (int)IDCTImage[row][col];
    //		//SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    // MessageBox(hWnd, "You Can't Select IDCT Image...", "SELECT IMAGE",
    // MB_OK);

    EnableMenuItem(GetMenu(hMainWnd), IDM_MAKERF, MF_ENABLED | MF_BYCOMMAND);
    MessageBox(
        hWnd,
        "You Clicked Make Frame 2 - Frame 1' , Make Result Frame Menu Enabled",
        "SELEECT IMAGE", MB_OK);
    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    hc27 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}

// Make Result Frame
void CreateImageMakeRFWindow(HWND hParent, int x, int y, int width,
                             int height) {
  if (hc28)
    MessageBox(hc28, "Already Exist Window...", "Can't Create Window", MB_OK);
  else {
    hc28 =
        CreateWindow(szImageMakeRFClass, "Make Result Frame",
                     WS_OVERLAPPED | WS_CHILD | WS_BORDER | WS_SYSMENU |
                         WS_CAPTION | WS_VISIBLE,
                     x, y, width, height, hParent, (HMENU)NULL, g_hInst, NULL);
    if (!hc28) {
      MessageBox(hc28, "Non Input Image", "MakeRF Error", MB_OK);
    }
  }
}

// Make Result Frame
LRESULT CALLBACK ImageMakeRFProc(HWND hWnd, UINT message, WPARAM wParam,
                                 LPARAM lParam) {

  PAINTSTRUCT ps;
  HDC hdc;
  int frow, fcol;

  switch (message) {
  case WM_CREATE:
    // Result Frame  -> RFImage
    // RFImage = (Frame 2 - Frame 1') + Frame 1'
    for (frow = 0; frow < FROW; frow++) {
      for (fcol = 0; fcol < FCOL; fcol++) {
        RFImage[frow][fcol] = F2F1_Image[frow][fcol] + F1_Image[frow][fcol];
      }
    }
    break;

  case WM_PAINT:

    hdc = BeginPaint(hWnd, &ps);
    // IDCT Image Output
    // for (frow = 0; frow < FROW; frow++)
    //{
    //	for (fcol = 0; fcol < FCOL; fcol++)
    //	{
    //		rgbtemp = (unsigned char)(RFImage[frow][fcol]);
    //		SetPixel(hdc,fcol,frow,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //		// 8x8 Grid
    //		//if (row%8 == 0 || col%8 == 0)
    //		//{
    //		//	//rgbtemp = 255;
    //		//	SetPixel(hdc,col,row,(unsigned long)RGB(0,180,0));
    //		//}
    //	}
    // }

    unsigned char RFImageTemp[FROW][FCOL];
    for (frow = 0; frow < FROW; frow++) {
      for (fcol = 0; fcol < FCOL; fcol++) {
        RFImageTemp[frow][fcol] = (int)(RFImage[frow][fcol]);
      }
    }
    DrawImage2(hdc, FCOL, FROW, RFImageTemp);

    EndPaint(hWnd, &ps);

    break;

    // IDCT_JPEG Image -> Temp Image
  case WM_LBUTTONDOWN:
    // for (row = 0; row < ROW; row++)
    //{
    //	for (col = 0; col < COL; col++)
    //	{
    //		//TImage[row][col] = (int)IDCTImage[row][col];
    //		//SetPixel(hdc,col,row,(unsigned
    //long)RGB(rgbtemp,rgbtemp,rgbtemp));
    //	}
    // }
    // MessageBox(hWnd, "You Can't Select IDCT Image...", "SELECT IMAGE",
    // MB_OK);

    break;
  case WM_MOVE:
    InvalidateRect(hWnd, NULL, FALSE);
    break;
  case WM_DESTROY:
    hc28 = NULL;
    break;

  default:
    return (DefWindowProc(hWnd, message, wParam, lParam));
  }
  return 0;
}
