////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// copy on write �׽�Ʈ
////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include <iostream>

using namespace std;
int main()
{

	string strA = "ysoftman";
	// strB �� strA �� �����ϰ� �ִ�.
	string strB = strA;

	// ���� �޸𸮸� �����ϰ� �־� ���� ���ڿ��� ����Ѵ�.
	cout << strA.c_str() << endl;
	cout << strB.c_str() << endl;
	
	// STL string �� copy_on_write ����� �־�
	// �޸𸮸� �����ϴ� ������ ���縦 �ϰԵȴ�.
	// ���� strB �� "ysoftman" ���ڿ��� ���� ���� ����ȴ�.
	strB += " is a man";

	// strA �� strB �� ���� ������ �޸𸮸� ����Ѵ�.
	cout << strA.c_str() << endl;
	cout << strB.c_str() << endl;


	return 0;
}



