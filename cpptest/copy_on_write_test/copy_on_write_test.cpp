////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// copy on write 테스트
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



