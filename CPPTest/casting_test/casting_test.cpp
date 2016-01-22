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

	// C : ������ ĳ���õ�
	nNumber = (int)lNumber;
	printf("nNumber = %lld\n", nNumber);
	nNumber = (int)CONST_NUMBER;
	printf("nNumber = %lld\n", nNumber);
	nNumber = (int)fNumber;
	printf("nNumber = %lld\n", nNumber);
	nNumber = (int)szStr;
	printf("nNumber = %lld\n", nNumber);
	printf("\n");

	// C++ static_cast : �������� �������� ��ȯ ����
	nNumber = static_cast<int>(lNumber);
	printf("nNumber = %lld\n", nNumber);
	nNumber = static_cast<int>(CONST_NUMBER);
	printf("nNumber = %lld\n", nNumber);
	nNumber = static_cast<int>(fNumber);
	printf("nNumber = %lld\n", nNumber);
	//nNumber = static_cast<int>(szStr);	// ������ Ÿ���� �ٸ� Ÿ������ ��ȯ �ȵ�
	//printf("nNumber = %lld\n", nNumber);
	printf("\n");

	// C++ const_cast : ������� ������ ��ȯ�Ҷ�
	//nNumber = const_cast<int&>(lNumber);	// ���� ��ȯ �ȵ�
	//printf("nNumber = %lld\n", nNumber);
	nNumber = const_cast<int&>(CONST_NUMBER);
	printf("nNumber = %lld\n", nNumber);
	//nNumber = const_cast<int&>(fNumber);	// ���� ��ȯ �ȵ�
	//printf("nNumber = %lld\n", nNumber);
	//nNumber = static_cast<int&>(szStr);	// ���� ��ȯ �ȵ�
	//printf("nNumber = %lld\n", nNumber);
	printf("\n");

	// C++ reinterpret_cast : �����ͳ��� �Ǵ� �����Ϳ� ������ ��ȯ�Ҷ�
	int *pNumber = NULL;
	pNumber = reinterpret_cast<int*>(lNumber);
	printf("pNumber = %lld\n", pNumber);
	pNumber = reinterpret_cast<int*>(CONST_NUMBER);
	printf("pNumber = %lld\n", pNumber);
	//pNumber = reinterpret_cast<int*>(fNumber);	// ���� <-> �Ǽ� ��ȯ �ȵ�
	//printf("pNumber = %lld\n", pNumber);
	pNumber = reinterpret_cast<int*>(szStr);
	printf("pNumber = %s\n", pNumber);
	pNumber = reinterpret_cast<int*>(77777);	// ���� ������������ ��ȯ ����
	printf("pNumber = %lld\n", pNumber);
	printf("\n");

	// C++ dynamic_cast : ��Ӱ��迡�� upcasting ��ȯ ���� downcasting �� �ȵ�
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

