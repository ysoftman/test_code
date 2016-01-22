////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 함수 포인터
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

typedef int (*func1)(int, int);

int add(int num1, int num2)
{
	return num1 + num2;
}

int main()
{
	func1 myFunc1;
	myFunc1 = add;
	
	int (*func2)(int a, int b);
	func2 = add;
	
	int result = 0;
	result = myFunc1(111, 222);
	printf("add : %x myFunc1 : %x result : %d\n", add, myFunc1, result);
	result = func2(333, 444);
	printf("add : %x func2 : %x result : %d\n", add, func2, result);

	return 0;
}


