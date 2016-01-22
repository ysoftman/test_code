// ysoftman
// Visual Leak Detector(VLD) for Visual C++  테스트
// 다운로드 https://vld.codeplex.com/
#include <crtdbg.h>
// 프로젝트에 vld 경로 설정
#include <vld.h>	// VLD 를 이용한 메모릭 감지

int main()
{
	/*
	// crtdbg 를 이용한 기본 메모릭 감지
	// _CRTDBG_ALLOC_MEM_DF ==> _CLIENT_BLOCK 에 메모리를 할당에 대해서 덤프
	// _CRTDBG_LEAK_CHECK_DF ==> 프로그램이 종료될 때 자동으로 _CrtDumpMemoryLeaks() 를 호출하여 메모리 누수시 덤프
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// 해제 안되는 new 의 파일과 라인수를 파악한다.
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
	// 메모리 누수시 블록숫자값(출력창의{1234})을 주면 메모리 공간을 확보하는 시점에 브레이크포인트가 걸린다.
	//_CrtSetBreakAlloc(226381);
	*/

	int *pTest = new int[100];
	//delete pTest;
}

