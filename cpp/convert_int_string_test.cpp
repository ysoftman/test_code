// ysoftman
// int -> string, string -> int 로 변환하기
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <sstream>

using namespace std;

string number2string(long num)
{
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
	// double -> string
	// Numeric Type (int, float, double)을 string으로 변환해주기 위한 객체
	// double a = 12.3456789;
	ostringstream ss;
	ss << num;
	cout << "ostringstream:" << ss.str() << endl;

	return s.str();
}

long string2number(string str)
{
	// 문자 -> 숫자
	// 방법1
	// string -> int
	long num = atoi(str.c_str());
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

	return new_num_int;
}

int main()
{
	cout << "input number(to convert to string) : ";
	long num;
	cin >> num;
	cout << "number:" << num << endl;
	string str = number2string(num);
	long num2 = string2number(str);
	return 0;
}
