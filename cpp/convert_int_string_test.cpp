////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// int -> string, string -> int 로 변환하기
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
	long num;
	cin >> num, cout << "number:" << num << endl;

	// 숫자 -> 문자
	// 방법1
	// long -> string
	string str = std::to_string(num);
	cout << "std::to_string():" << str << endl;

	// 방법2
	// long -> string
	stringstream s;
	s << num;
	cout << "stringstream:" << s.str() << endl;

	// 방법3
	
	double a = 12.3456789;
	// 자리수 3개로 고정 -> 12.3 출력
	cout.precision(3);
	cout << "a:" << a << endl;
	// double -> string
	ostringstream ss;
	ss << a;
	cout << "ostringstream:" << ss.str() << endl;

	// double b = 12.3456789123456789;
	// ostringstream ss2;
	// ss2 << "b:" << fixed << b;
	// cout.precision(1);
	// cout << "ostringstream:" << ss2.str() << endl;


	/////////////////////////////

	// 문자 -> 숫자
	// 방법1
	// string -> int
	num = atoi(str.c_str());
	printf("atoi number:%ld\n", num);

	// 방법2
	// string -> long
	int new_num_int = std::stoi(str, nullptr);
	cout << "std::stoi():" << new_num_int << endl;
	// string -> long
	long new_num_long = std::stol(str, nullptr);
	cout << "std::stol():" << new_num_long << endl;
	// string -> float
	float new_num_float = std::stof(str, nullptr);
	cout << "std::stof():" << new_num_float << endl;
	// string -> double
	double new_num_double = std::stod(str, nullptr);
	cout << "std::stod():" << new_num_double << endl;



	int int_num = 0;
	// Numeric Type (int, float, double)을 string으로 변환해주기 위한 객체
	ostringstream ostr;
	for (int_num = 1; int_num <= 10; int_num++)
	{
		// 초기화
		ostr.str("");
		// int를 string으로 변환
		ostr << int_num;
		printf("[int -> string] ostr = %s\n", ostr.str().c_str());
	}

	return 0;
}
