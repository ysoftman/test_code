// ysoftman
// 사용자가 #define 으로 정의하는 매크로외에 컴파일러가 기본적으로 제공하는 미리 정의된 매크로가 있다.
// 미리 정의된 매크로는 사용자가 재정의할 수 없다.
#include <stdio.h>

int main()
{
	// ANSI C 에 미리 정의된 매크로
	// __FILE__ : 현재 소스파일의 전체경로 파일명을 나타낸다.
	printf("%s\n", __FILE__);
	// __LINE__ : 현재 소스파일의 __LINE__ 있는 곳의 줄번호를 나타낸다.
	printf("%d\n", __LINE__);
	// __DATA__ : 현재 소스파일을 컴파일한 날짜를 나타낸다.
	printf("%s\n", __DATE__);
	// __TIME__ : 현재 소스파일을 컴파일한 시간을 나타낸다.
	printf("%s\n", __TIME__);
	// __TIMESTAMP__ : 현재 소스파일의 컴파일한 날짜시간을 나타낸다.
	printf("%s\n", __TIMESTAMP__);
	// __STDC__ : 현재 컴파일러가 표준(ANSI C)을 따를 경우 1로 정의되고, 그렇지 않으면 정의되지 않는다.
#if defined(__STDC__)
	printf("defined __STDC__ = %d\n", __STDC__);
#else
	printf("not defined __STDC__\n");
#endif

	// Microsoft C++ 에 미리 정의된 매크로
	// _DEBUG : 디버그인 경우 1로 정의되고, 그렇지 않으면 정의되지 않는다.
#if defined(_DEBUG)
	printf("defined _DEBUG = %d\n", _DEBUG);
#else
	printf("not defined _DEBUG\n");
#endif
	// _MSC_VER : Microsoft Compiler 인경우 컴파일러의 버전 값을 나타낸다.
#if defined(_MSC_VER)
	printf("defined _MSC_VER = %d\n", _MSC_VER);
#else
	printf("not defined _MSC_VER\n");
#endif
	// _MFC_VER : MFC를 사용할수 있다면 MFC 의 버전 값을 나타낸다.
#if defined(_MFC_VER)
	printf("defined _MFC_VER = %d\n", _MFC_VER);
#else
	printf("not defined _MFC_VER\n");
#endif
	// _WIN32 : Win32 환경이라면 1로 정의된다.
#if defined(_WIN32)
	printf("defined _WIN32 = %d\n", _WIN32);
#else
	printf("not defined _WIN32\n");
#endif
	// _WIN64 : Win64 환경이라면 1로 정의된다.
#if defined(_WIN64)
	printf("defined _WIN64 = %d\n", _WIN64);
#else
	printf("not defined _WIN64\n");
#endif
	// _DLL : DLL환경을 사용할 수 있다면 1로 정의된다.
#if defined(_DLL)
	printf("defined _DLL = %d\n", _DLL);
#else
	printf("not defined _DLL\n");
#endif
	// more ... : 미리정의된 매크로는 MSDN 참고
	return 0;
}
