// ysoftman
// switch 문안에서 변수선언과 동시에 초기화 하려면 {}로 범위를 지정해 줘야 한다.
#include <stdio.h>
#include <iostream>
#include <string> // string, hash<>

int switch_string_func();
int switch_enum_test_func();

int main()
{
	int a = 1;
	switch (a)
	{
		// switch case/default 영역 밖은 처리안됨
		// 컴파을은 되지만 warning 발생
		// printf("aaa");
	case 1:
		// 아래 주석처리된 코드는 컴파일 에러(선언된 변수의 초기화가 생략)가 난다.
		//int b = 100;

		// 따라서 변수 선언후 초기화를 한다.
		//int b;
		//b = 100;
		//printf("b = %d\n", b);

		// 아니면 {} 로 묶어 준다.
		{
			int b = 100;
			printf("b = %d\n", b);
		}
		break;
	case 2:
		break;
	default:
		break;
	}

	switch_enum_test_func();
	switch_string_func();

	return 0;
}

enum myenum
{
	my_enum_1 = 1,
	my_enum_2,
	my_enum_3,
};

int switch_enum_test_func()
{
	myenum var1 = my_enum_1;
	switch (var1)
	{
	case my_enum_1:
		printf("return 1\n");
		return 1;
	case my_enum_2:
		printf("return 2\n");
		return 2;
	// enum 을 switch 할때 enum 의 모든 경우를 case 로 만들지 않으면 다음과 같은 경고 메시지가 나온다.
	// c++ warning: enumeration value not handled in switch [-Wswitch]
	// enum 의 값에 대한 case 를 만들던가 default 를 사용하면 된다.
	default:
		break;
	}

	return 0;
}

int switch_string_func()
{
	// 문자 하는 integer 로 표현되서 switch 사용할 수 있다.
	// a == 97
	char c = 'a';
	switch (c)
	{
	case 'a':
		printf("case a\n");
		break;
	case 'b':
		printf("case b\n");
		break;
	default:
		printf("case default\n");
		break;
	}

	// switch 는 문자열을 허용하지 않는다.
	// 그래서 쓰고 싶다면 hash 값을 정수로 변경해서 써야 한다.
	std::string str = "a";
	std::hash<std::string> hash_fn;
	size_t sz = hash_fn(str);
	std::cout << sz << std::endl;
	switch (sz)
	{
	case 2603192927274642682:
		printf("case a(2603192927274642682)\n");
		break;
	case 999:
		printf("case 999\n");
		break;
	default:
		printf("case default\n");
		break;
	}
	return 0;
}
