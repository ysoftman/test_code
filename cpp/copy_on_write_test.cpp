// ysoftman
// copy on write 테스트
// 말 그대로 쓸려고 할때 복사를 수행한다는 의미로, 리소스(메모리)를 공유하고 있는 두 프로세스가 있다고 했을때
// 한쪽에서 메모리의 내용을 수정(write)하면 다른 프로세스에 영향을 주니 수정할 메모리 내용을 새로운 메모리에 복사하고
// 그 복사본에 쓰기 작업을 수행한다. os fork() 에서 자식 프로세스를 생성시 cow 가 사용된다
// c++ 11 부터 string 에서 cow 기능은 사용하지 않는다.
#include <string>
#include <iostream>

using namespace std;
int main()
{
	string strA = "ysoftman";
	// strB 내부 버퍼는 strA 내부 버퍼를 참조하고 있다.
	string strB = strA;

	// 같은 버퍼를 참조하고 있어 같은 문자열을 출력한다.
	cout << &strA << "  " << strA << endl;
	cout << &strB << "  " << strB << endl;

	// STL string 은 copy_on_write 기능이 있어
	// string 객체 내부의 버퍼를 변경하는 시점에 복사를 하게된다.
	// 따라서 strB 의 내부 버퍼는 "ysoftman" 문자열이 복사 된후 변경된다.
	strB = "bill";

	// strA 와 strB 는 이제 각각의 메모리를 사용한다.
	cout << &strA << "  " << strA << endl;
	cout << &strB << "  " << strB << endl;

	return 0;
}
