////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// stack �޸� �׽�Ʈ
////////////////////////////////////////////////////////////////////////////////////
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
	printf("%s this(0x%X)\n", __FUNCTION__, this);
	a = -1;
	b = -2;
}

Dummy::~Dummy()
{
	printf("%s this(0x%X)\n", __FUNCTION__, this);
}

Dummy g_RootDummy;
int g_Cnt = 0;

void setRootDummy()
{
	printf("%s\n", __FUNCTION__);

	// Dummy �ν��Ͻ��� ���ð����� ����
	Dummy dum;
	dum.a = ++g_Cnt;
	dum.b = dum.a + 1;
	printf("dum(0x%X) a(%d) b(%d)\n", &dum, dum.a, dum.b);

	// �� ����
	g_RootDummy = dum;
	printf("g_RootDummy(0x%X) a(%d) b(%d)\n", &g_RootDummy, g_RootDummy.a, g_RootDummy.b);

	// dum�� ���� �޸𸮷� �Լ� ������ �Ҹ��� ȣ��
}

int main()
{
	printf("%s\n", __FUNCTION__);

	printf("g_RootDummy(0x%X) a(%d) b(%d)\n", &g_RootDummy, g_RootDummy.a, g_RootDummy.b);
	printf("test...\n\n");

	for (int i=0; i<5; ++i)
	{
		setRootDummy();
		printf("\n");
	}

	printf("g_RootDummy(0x%X) a(%d) b(%d)\n", &g_RootDummy, g_RootDummy.a, g_RootDummy.b);
	return 0;
}

