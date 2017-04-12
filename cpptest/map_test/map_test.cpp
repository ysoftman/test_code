/* 
author: ysoftman
title: map 관련 테스트
*/
#include <stdio.h>
#include <iostream>
#include <map>

using namespace std;

struct aa {
	int a;
	long b;
};

struct aa my = {10, 200};

int main()
{
	int a = 10;
	printf ("a=%d\n", a);
	std::cout << "a=" << a << std::endl;
	std::cout << "my.a:" << my.a << std::endl;
	std::cout << "my.b:" << my.b << std::endl;

	map<int, int> mymap;
	map<int, int>::iterator iter;
	mymap[0] = 1;
	mymap[1] = 2;
	for (iter = mymap.begin(); iter!= mymap.end(); iter++)
	{
		printf("mymap[%d] = %d\n", (*iter).first, (*iter).second);
	}
	return 0;
}
