// ysoftman
// Visual Leak Detector(VLD) for Visual C++  �׽�Ʈ
// �ٿ�ε� https://vld.codeplex.com/
#include <crtdbg.h>
// ������Ʈ�� vld ��� ����
#include <vld.h>	// VLD �� �̿��� �޸� ����

int main()
{
	/*
	// crtdbg �� �̿��� �⺻ �޸� ����
	// _CRTDBG_ALLOC_MEM_DF ==> _CLIENT_BLOCK �� �޸𸮸� �Ҵ翡 ���ؼ� ����
	// _CRTDBG_LEAK_CHECK_DF ==> ���α׷��� ����� �� �ڵ����� _CrtDumpMemoryLeaks() �� ȣ���Ͽ� �޸� ������ ����
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// ���� �ȵǴ� new �� ���ϰ� ���μ��� �ľ��Ѵ�.
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
	// �޸� ������ ��ϼ��ڰ�(���â��{1234})�� �ָ� �޸� ������ Ȯ���ϴ� ������ �극��ũ����Ʈ�� �ɸ���.
	//_CrtSetBreakAlloc(226381);
	*/

	int *pTest = new int[100];
	//delete pTest;
}

