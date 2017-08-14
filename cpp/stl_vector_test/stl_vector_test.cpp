////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// stl vector 의 값(클래스) 삭제 테스트
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
	// 소멸자 제대로 호출(하지만 많이 너무 많이 호출된다)
	vecDummy1.clear();

	printf("\n\n");

	std::vector<Dummy*> vecDummy2;
	for (int i=0; i<5; i++)
	{
		Dummy *dummy4 = new Dummy();
		vecDummy2.push_back(dummy4);
	}
	// 소멸자 호출 안됨
	// 클래스 원소 포인터를 삭제하지만 실제 클래스의 메모리는 삭제하지 않는다.
	//vecDummy2.clear();

	// 따라서 일일히 클래스를 삭제해야 한다.
	// 방법1
	while (!vecDummy2.empty())
	{
		delete vecDummy2.back();
		vecDummy2.pop_back();
	}
	// 방법2
	std::vector<Dummy*>::iterator iter;
	std::vector<Dummy*>::iterator iterTemp;
	for (iter = vecDummy2.begin(); iter != vecDummy2.end();)
	{
		iterTemp = iter;
		// 일일히 delete 한다.
		delete (*iterTemp);
		// 원소 삭제
		iter = vecDummy2.erase(iter++);
	}
	
	printf("\n\n");
}

