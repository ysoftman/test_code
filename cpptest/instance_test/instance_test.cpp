////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// ���� �ν��Ͻ��� ���� �ν��Ͻ��� ����
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

class MyClass
{
public:
	MyClass() {};
	~MyClass() {};
	void Func1()
	{
		printf("MyClass-Func1() called\n");
	};
};

void main()
{
	// ���� �ν��Ͻ�
	// ���ÿ� ���̱� ������ ����� Ŭ��� ���� �����÷ο� �߻�
	MyClass inst1;
	inst1.Func1();
	// ���� �ν��Ͻ�
	// delete �������� ��� �޸� ���� ����
	MyClass *inst2 = new MyClass();
	inst2->Func1();
	delete inst2;
}

