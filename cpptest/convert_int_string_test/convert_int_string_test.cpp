////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// int -> string, string -> int 로 변환하기
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
	int num = 0;

	// Numeric Type (int, float, double)을 string으로 변환해주기 위한 객체
	ostringstream ostr;
	for (num = 1; num <= 10; num++)
	{
		// 초기화
		ostr.str("");
		// int를 string으로 변환
		ostr << num;
		printf("[int -> string] ostr = %s\n", ostr.str().c_str());
	}

	// atoi 로 string 형을 int 로 변환
	string str = "12345";
	num = atoi(str.c_str());
	printf("[string -> int] num = %d\n", num);


	// double 형을 string 으로 변환
	double a = 0.0000000000000123456789;
	ostringstream ss;
	ss << "a:" << a;
	string str1 = ss.str();
	cout << str1 << endl;

	double b = 0.0000000000012345678912345678912346;
	ostringstream ss2;
	ss2 << "b:" << fixed << b;
	string str2 = ss2.str();
	cout << str2 << endl;

	return 0;
}
