// ysoftman
// 실인수(argument) 와 가인수(parameter) 구분
// 인수를 말할 때 용어를 구별해서 사용해야 한다.
// 호출하는 곳, 실제값을 주어지는 곳으로 실인수 즉 argument 라는 말을 쓴다.
// 반면 호출받는 곳, 값을 받는 곳으로 parameter 라는 말을 사용한다.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a 는 parameter
void func(int a)
{
	printf("%d\n", a);
}

int main()
{
	// 10 은 argument
	func(10);
	return 0;
}
