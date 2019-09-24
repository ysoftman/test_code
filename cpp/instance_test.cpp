// ysoftman
// 정적 인스턴스와 동적 인스턴스의 차이
#include <stdio.h>

class MyClass
{
public:
	MyClass(){};
	~MyClass(){};
	void Func1()
	{
		printf("MyClass-Func1() called\n");
	};
};

int main()
{
	// 정적 인스턴스
	// 스택에 쌓이기 때문에 사이즈가 클경우 스택 오버플로우 발생
	MyClass inst1;
	inst1.Func1();
	// 동적 인스턴스
	// delete 전까지는 계속 메모리 힙에 존재
	MyClass *inst2 = new MyClass();
	inst2->Func1();
	delete inst2;

	return 0;
}
