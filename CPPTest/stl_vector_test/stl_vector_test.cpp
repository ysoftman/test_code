////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// stl vector �� ��(Ŭ����) ���� �׽�Ʈ
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <vector>

class Dummy
{
public:
	Dummy()
	{
		a = 1;
		printf("Dummy()\n");
	};
	~Dummy()
	{
		a = 0;
		printf("~Dummy()\n");
	};
	int a;
};

int main()
{
	Dummy dummy1;
	printf("dummy1.a = %d\n", dummy1.a);
	Dummy *dummy2 = new Dummy();
	printf("dummy2.a = %d\n", dummy2->a);
	delete dummy2;

	printf("\n\n");
	
	std::vector<Dummy> vecDummy1;
	for (int i=0; i<5; i++)
	{
		Dummy dummy3;
		vecDummy1.push_back(dummy3);
	}
	// �Ҹ��� ����� ȣ��(������ ���� �ʹ� ���� ȣ��ȴ�)
	vecDummy1.clear();

	printf("\n\n");

	std::vector<Dummy*> vecDummy2;
	for (int i=0; i<5; i++)
	{
		Dummy *dummy4 = new Dummy();
		vecDummy2.push_back(dummy4);
	}
	// �Ҹ��� ȣ�� �ȵ�
	// Ŭ���� ���� �����͸� ���������� ���� Ŭ������ �޸𸮴� �������� �ʴ´�.
	//vecDummy2.clear();

	// ���� ������ Ŭ������ �����ؾ� �Ѵ�.
	// ���1
	while (!vecDummy2.empty())
	{
		delete vecDummy2.back();
		vecDummy2.pop_back();
	}
	// ���2
	std::vector<Dummy*>::iterator iter;
	std::vector<Dummy*>::iterator iterTemp;
	for (iter = vecDummy2.begin(); iter != vecDummy2.end();)
	{
		iterTemp = iter;
		// ������ delete �Ѵ�.
		delete (*iterTemp);
		// ���� ����
		iter = vecDummy2.erase(iter++);
	}
	
	printf("\n\n");
}

