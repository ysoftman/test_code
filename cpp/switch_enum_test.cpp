// ysoftman
#include <stdio.h>
#include <string> // string, hash<>

enum myenum
{
	my_enum_1 = 1,
	my_enum_2,
	my_enum_3,
};

int main()
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
