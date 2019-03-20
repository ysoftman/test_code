////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// switch 문안에서 변수선언과 동시에 초기화 하려면 {}로 범위를 지정해 줘야 한다.
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>


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



	enum myenum {
		my_enum_1 = 1,
		my_enum_2,
		my_enum_3,
	};
	myenum var1 = my_enum_3;
	switch(var1)
	{
		case my_enum_1: printf("return 1\n"); return 1;
		case my_enum_2: printf("return 2\n"); return 2;
		case my_enum_3: printf("return 3\n"); return 3;
		// enum 을 switch 할때 컴파일러에 따라 default 를 사용하거나 case 마다 break 를 써야 한다.
		// c++ warning: enumeration value not handled in switch [-Wswitch]
		default:
			break;
	}

	return 0;
}

