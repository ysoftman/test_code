////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// C++ casting
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
class Parent {
	virtual void f(){};
};
class Child : public Parent {
	virtual void f(){};
};
int main()
{
	long long lNumber = 123456789123456789;
	const int CONST_NUMBER = 123;
	double fNumber = 3.141592;
	char *szStr = "ysoftman";
	int nNumber = 0;
	
	printf("lNumber = %lld\n", lNumber);
	printf("CONST_NUMBER = %lld\n", CONST_NUMBER);
	printf("fNumber = %f\n", fNumber);
	printf("szStr = %s\n", szStr);
	printf("nNumber = %lld\n", nNumber);
	printf("\n");

	// C : 무조건 캐스팅됨
	nNumber = (int)lNumber;
	printf("nNumber = %lld\n", nNumber);
	nNumber = (int)CONST_NUMBER;
	printf("nNumber = %lld\n", nNumber);
	nNumber = (int)fNumber;
	printf("nNumber = %lld\n", nNumber);
	nNumber = (int)szStr;
	printf("nNumber = %lld\n", nNumber);
	printf("\n");

	// C++ static_cast : 논리적으로 맞을때만 변환 가능
	nNumber = static_cast<int>(lNumber);
	printf("nNumber = %lld\n", nNumber);
	nNumber = static_cast<int>(CONST_NUMBER);
	printf("nNumber = %lld\n", nNumber);
	nNumber = static_cast<int>(fNumber);
	printf("nNumber = %lld\n", nNumber);
	//nNumber = static_cast<int>(szStr);	// 포인터 타입을 다른 타입으로 변환 안됨
	//printf("nNumber = %lld\n", nNumber);
	printf("\n");

	// C++ const_cast : 상수성를 비상수로 변환할때
	//nNumber = const_cast<int&>(lNumber);	// 비상수 변환 안됨
	//printf("nNumber = %lld\n", nNumber);
	nNumber = const_cast<int&>(CONST_NUMBER);
	printf("nNumber = %lld\n", nNumber);
	//nNumber = const_cast<int&>(fNumber);	// 비상수 변환 안됨
	//printf("nNumber = %lld\n", nNumber);
	//nNumber = static_cast<int&>(szStr);	// 비상수 변환 안됨
	//printf("nNumber = %lld\n", nNumber);
	printf("\n");

	// C++ reinterpret_cast : 포인터끼리 또는 포인터와 값간에 변환할때
	int *pNumber = NULL;
	pNumber = reinterpret_cast<int*>(lNumber);
	printf("pNumber = %lld\n", pNumber);
	pNumber = reinterpret_cast<int*>(CONST_NUMBER);
	printf("pNumber = %lld\n", pNumber);
	//pNumber = reinterpret_cast<int*>(fNumber);	// 정수 <-> 실수 변환 안됨
	//printf("pNumber = %lld\n", pNumber);
	pNumber = reinterpret_cast<int*>(szStr);
	printf("pNumber = %s\n", pNumber);
	pNumber = reinterpret_cast<int*>(77777);	// 값을 포인터형으로 변환 가능
	printf("pNumber = %lld\n", pNumber);
	printf("\n");

	// C++ dynamic_cast : 상속관계에서 upcasting 변환 가능 downcasting 은 안됨
	Parent *pParent = new Parent();
	Parent *pParent2 = NULL;
	Child *pChild = new Child();
	Child *pChild2 = NULL;
	pParent2 = dynamic_cast<Parent*>(pChild);	// upcasting ok
	printf("pParent = %x\n", pParent2);
	pChild2 = dynamic_cast<Child*>(pParent);	// downcasting null
	printf("pChild = %x\n", pChild2);

	return 0;
}

