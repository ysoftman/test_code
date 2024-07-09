// ysoftman
// stack 메모리 테스트
#include <stdio.h>

class Dummy
{
public:
	Dummy();
	~Dummy();
	int a;
	int b;
};

Dummy::Dummy()
{
	printf("%s this(0x%p)\n", __FUNCTION__, this);
	a = -1;
	b = -2;
}

Dummy::~Dummy()
{
	printf("%s this(0x%p)\n", __FUNCTION__, this);
}

Dummy g_RootDummy;
int g_Cnt = 0;

void setRootDummy()
{
	printf("%s\n", __FUNCTION__);

	// Dummy 인스턴스를 스택공간에 생성
	Dummy dummy;
	dummy.a = ++g_Cnt;
	dummy.b = dummy.a + 1;
	printf("dummy(0x%p) a(%d) b(%d)\n", &dummy, dummy.a, dummy.b);

	// 값 복사
	g_RootDummy = dummy;
	printf("g_RootDummy(0x%p) a(%d) b(%d)\n", &g_RootDummy, g_RootDummy.a, g_RootDummy.b);

	// dummy은 스택 메모리로 함수 끝나면 소멸자 호출
}

int main()
{
	printf("%s\n", __FUNCTION__);

	printf("g_RootDummy(0x%p) a(%d) b(%d)\n", &g_RootDummy, g_RootDummy.a, g_RootDummy.b);
	printf("test...\n\n");

	for (int i = 0; i < 5; ++i)
	{
		setRootDummy();
		printf("\n");
	}

	printf("g_RootDummy(0x%p) a(%d) b(%d)\n", &g_RootDummy, g_RootDummy.a, g_RootDummy.b);
	return 0;
}
