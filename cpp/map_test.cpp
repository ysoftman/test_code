/* 
author: ysoftman
title: map 관련 테스트
*/
#include <stdio.h>
#include <iostream>
#include <map>

using namespace std;

struct aa
{
	int a;
	long b;
};

struct aa my = {10, 200};

int main()
{
	int a = 10;
	printf("a=%d\n", a);
	std::cout << "a=" << a << std::endl;
	std::cout << "my.a:" << my.a << std::endl;
	std::cout << "my.b:" << my.b << std::endl;

	map<int, int> mymap;
	map<int, int>::iterator iter;
	mymap[0] = 1;
	mymap[1] = 2;
	mymap[2] = 3;

	// insert() 는 키가 존재한다면 추가하지 않는다.
	mymap.insert(make_pair(2, 5));

	// count() 는 맵의 키에 매칭되는 원소를 카운트하지만
	// map 의 키는 유니크해서 매칭되는 카운트는 1, 없으면 0만 올 수 있다.
	printf("mymap count elements : %lu\n", mymap.count(2));
	for (iter = mymap.begin(); iter != mymap.end(); iter++)
	{
		printf("mymap[%d] = %d\n", (*iter).first, (*iter).second);
	}
	return 0;
}
