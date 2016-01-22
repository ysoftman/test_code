////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ����ڰ� #define ���� �����ϴ� ��ũ�οܿ� �����Ϸ��� �⺻������ �����ϴ� �̸� ���ǵ� ��ũ�ΰ� �ִ�.
// �̸� ���ǵ� ��ũ�δ� ����ڰ� �������� �� ����.
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

int main()
{	
	/////////////////////////////////////////////////////////////////////////
	// ANSI C �� �̸� ���ǵ� ��ũ��
	// __FILE__ : ���� �ҽ������� ��ü��� ���ϸ��� ��Ÿ����.
	printf("%s\n", __FILE__);
	// __LINE__ : ���� �ҽ������� __LINE__ �ִ� ���� �ٹ�ȣ�� ��Ÿ����.
	printf("%d\n", __LINE__);
	// __DATA__ : ���� �ҽ������� �������� ��¥�� ��Ÿ����.
	printf("%s\n", __DATE__);
	// __TIME__ : ���� �ҽ������� �������� �ð��� ��Ÿ����.
	printf("%s\n", __TIME__);
	// __TIMESTAMP__ : ���� �ҽ������� �������� ��¥�ð��� ��Ÿ����.
	printf("%s\n", __TIMESTAMP__);
	// __STDC__ : ���� �����Ϸ��� ǥ��(ANSI C)�� ���� ��� 1�� ���ǵǰ�, �׷��� ������ ���ǵ��� �ʴ´�.
#if defined(__STDC__)
	printf("defined __STDC__ = %d\n", __STDC__);
#else
	printf("not defined __STDC__\n");
#endif
	/////////////////////////////////////////////////////////////////////////
	// Microsoft C++ �� �̸� ���ǵ� ��ũ��
	// _DEBUG : ������� ��� 1�� ���ǵǰ�, �׷��� ������ ���ǵ��� �ʴ´�.
#if defined(_DEBUG)
	printf("defined _DEBUG = %d\n", _DEBUG);
#else
	printf("not defined _DEBUG\n");
#endif
	// _MSC_VER : Microsoft Compiler �ΰ�� �����Ϸ��� ���� ���� ��Ÿ����.
#if defined(_MSC_VER)
	printf("defined _MSC_VER = %d\n", _MSC_VER);
#else
	printf("not defined _MSC_VER\n");
#endif
	// _MFC_VER : MFC�� ����Ҽ� �ִٸ� MFC �� ���� ���� ��Ÿ����.
#if defined(_MFC_VER)
	printf("defined _MFC_VER = %d\n", _MFC_VER);
#else
	printf("not defined _MFC_VER\n");
#endif
	// _WIN32 : Win32 ȯ���̶�� 1�� ���ǵȴ�.
#if defined(_WIN32)
	printf("defined _WIN32 = %d\n", _WIN32);
#else
	printf("not defined _WIN32\n");
#endif
	// _WIN64 : Win64 ȯ���̶�� 1�� ���ǵȴ�.
#if defined(_WIN64)
	printf("defined _WIN64 = %d\n", _WIN64);
#else
	printf("not defined _WIN64\n");
#endif
	// _DLL : DLLȯ���� ����� �� �ִٸ� 1�� ���ǵȴ�.
#if defined(_DLL)
	printf("defined _DLL = %d\n", _DLL);
#else
	printf("not defined _DLL\n");
#endif
	// more ... : �̸����ǵ� ��ũ�δ� MSDN ����
	return 0;
}

