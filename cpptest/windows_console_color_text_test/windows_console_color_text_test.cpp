////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// �������� �ܼ� ȭ�鿡 �÷� �ؽ�Ʈ ���
////////////////////////////////////////////////////////////////////////////////////
#if (defined _WIN32) || (defined _WIN64)
#define _CRT_SECURE_NO_WARNINGS
#endif


#ifdef _WIN32
#include <windows.h>
#include <Wincon.h>
#endif

#include <stdio.h>

void main()
{
#if defined(_WIN32) || defined(_WIN64)
	// ���� �ܼ� â�� �ڵ� ��� ����
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// ���� �ܼ� ȭ�� ���� ������ ����
	CONSOLE_SCREEN_BUFFER_INFO ScreenInfo;
	GetConsoleScreenBufferInfo(hConsole, &ScreenInfo);
	// �ܼ� �ؽ�Ʈ �Ӽ� ����
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	printf("TextColor\n");
	// �ܼ� �ؽ�Ʈ �Ӽ� ����
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	printf("TextColor\n");
	// �ܼ� �ؽ�Ʈ �Ӽ� ����
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	printf("TextColor\n");
	// ó���� �ܼ� �ؽ�Ʈ �Ӽ� ����
	SetConsoleTextAttribute(hConsole, ScreenInfo.wAttributes);
	printf("TextColor\n");
#else
	printf("This OS is not Windows NT\n");
#endif
}


