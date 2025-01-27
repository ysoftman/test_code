// ysoftman
// 윈도우의 콘솔 화면에 컬러 텍스트 출력
#if (defined _WIN32) || (defined _WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef _WIN32
#include <Wincon.h>
#include <windows.h>
#endif

#include <stdio.h>

int main() {
#if defined(_WIN32) || defined(_WIN64)
    // 현재 콘솔 창의 핸들 얻어 오기
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 현재 콘솔 화면 정보 저장해 놓기
    CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
    GetConsoleScreenBufferInfo(hConsole, &ScreenInfo);
    // 콘솔 텍스트 속성 설정
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED |
                                          BACKGROUND_GREEN | BACKGROUND_BLUE |
                                          BACKGROUND_INTENSITY);
    printf("TextColor\n");
    // 콘솔 텍스트 속성 설정
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED |
                                          BACKGROUND_GREEN | BACKGROUND_BLUE |
                                          BACKGROUND_INTENSITY);
    printf("TextColor\n");
    // 콘솔 텍스트 속성 설정
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED |
                                          BACKGROUND_GREEN | BACKGROUND_BLUE |
                                          BACKGROUND_INTENSITY);
    printf("TextColor\n");
    // 처음의 콘솔 텍스트 속성 설정
    SetConsoleTextAttribute(hConsole, ScreenInfo.wAttributes);
    printf("TextColor\n");
#else
    printf("This OS is not Windows NT\n");
#endif

    return 0;
}
