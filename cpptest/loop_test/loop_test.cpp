// ysoftman
// C++ 에서 반복 사용 방법들 테스트
#include <iostream>
#include <vector>
#include <algorithm>	// for_each

using namespace std;

// add 함수 객체
struct Add {
	Add()
	{
		result = 0;
	}
	// operator() 를 사용하여 객체(class, struct)를 함수처럼 사용한다.
	void operator() (int n)
	{
		result = result + n;
	}
	int result;
};


int main()
{
	// 1~100 까지 더하기를 다양한 반복문을 사용해서 처리해보기

	// for
	int result = 0;
	for (int i=1; i<=100; ++i)
	{
		result = result + i;
	}
	cout << "for result : " << result << endl;


	// std::for_each
	// STL <algorithm> 에 인클루드하여 사용 가능하다.
	vector<int> vecNums;
	for (int i=1; i<=100; i++)
	{
		vecNums.push_back(i);
	}
	// Add객체를 함수처럼(함수 객체) Add() 로 호출할 수 있다.
	Add add = for_each(vecNums.begin(), vecNums.end(), Add());
	cout << "std::for_each result : " << add.result << endl;


	// foreach 
	// 표준 C++ 스펙이 아니다. visual studio 2010 이상 에서만 사용 가능하다.
	int numlist[101];
	numlist[0] = 0;
	for (int i=1; i<=100; ++i)
	{
		numlist[i]=i;
	}
	result = 0;
	for each (int i in numlist)
	{
		result = result + i;
		//cout << "for each result : " << result << "   i: " << i << endl;
	}
	cout << "for each result : " << result << endl;
	return 0;
}

