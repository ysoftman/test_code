// ysoftman
// c++ cout 소수점 고정 출력 테스트
#include <iostream>

using namespace std;

int main()
{
	double a = 12.3456789;
	// 자리수 1개로 줄이면 지수로 표현해서 출력
	cout.precision(1);
	cout << "a:" << a << endl;

	// 자리수 3개로 고정 -> 12.3 출력
	cout.precision(3);
	cout << "a:" << a << endl;

	// fixed 는 소수점을 기준으로 고정
	cout << fixed;
	// fixed 때문에 소수점 부터 자리수 3개로 고정 -> 12.346 출력
	cout.precision(3);
	cout << "a:" << a << endl;


	// fixed 설정 해제, 3자리까지 출력 -> 12.3
	cout.unsetf(ios::fixed);
	cout << "a:" << a << endl;

	return 0;
}
