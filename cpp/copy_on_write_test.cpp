////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// copy on write 테스트
// 말 그대로 쓸려고 할때 복사를 수행한다는 의미로, 리소스(메모리)를 공유하고 있는 두 프로세스가 있다고 했을때
// 한쪽에서 메모리의 내용을 수정(write)하면 다른 프로세스에 영향을 주니 수정할 메모리 내용을 새로운 메모리에 복사하고
// 그 복사본에 쓰기 작업을 수행한다. os fork() 에서 자식 프로세스를 생성시 cow 가 사용된다
////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <iostream>

using namespace std;
int main()
{

	string strA = "ysoftman";
	// strB 는 strA 를 참조하고 있다.
	string strB = strA;

	// 같은 메모리를 참조하고 있어 같은 문자열을 출력한다.
	cout << strA.c_str() << endl;
	cout << strB.c_str() << endl;

	// STL string 은 copy_on_write 기능이 있어
	// 메모리를 변경하는 시점에 복사를 하게된다.
	// 따라서 strB 는 "ysoftman" 문자열이 복사 된후 변경된다.
	strB += " is a man";

	// strA 와 strB 는 이제 각각의 메모리를 사용한다.
	cout << strA.c_str() << endl;
	cout << strB.c_str() << endl;

	return 0;
}
