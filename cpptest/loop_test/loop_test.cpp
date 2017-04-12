// ysoftman
// C++ ���� �ݺ� ��� ����� �׽�Ʈ
#include <iostream>
#include <vector>
#include <algorithm>	// for_each

using namespace std;

// add �Լ� ��ü
struct Add {
	Add()
	{
		result = 0;
	}
	// operator() �� ����Ͽ� ��ü(class, struct)�� �Լ�ó�� ����Ѵ�.
	void operator() (int n)
	{
		result = result + n;
	}
	int result;
};


int main()
{
	// 1~100 ���� ���ϱ⸦ �پ��� �ݺ����� ����ؼ� ó���غ���

	// for
	int result = 0;
	for (int i=1; i<=100; ++i)
	{
		result = result + i;
	}
	cout << "for result : " << result << endl;


	// std::for_each
	// STL <algorithm> �� ��Ŭ����Ͽ� ��� �����ϴ�.
	vector<int> vecNums;
	for (int i=1; i<=100; i++)
	{
		vecNums.push_back(i);
	}
	// Add��ü�� �Լ�ó��(�Լ� ��ü) Add() �� ȣ���� �� �ִ�.
	Add add = for_each(vecNums.begin(), vecNums.end(), Add());
	cout << "std::for_each result : " << add.result << endl;


	// foreach 
	// ǥ�� C++ ������ �ƴϴ�. visual studio 2010 �̻� ������ ��� �����ϴ�.
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

