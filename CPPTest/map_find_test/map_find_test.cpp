////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// map find test
////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <map>

using namespace std;

void FindNumInMap(std::map<int,int> mapTemp, int num)
{
	cout << "map size : " << mapTemp.size() << endl;
	if (mapTemp.find(num) == mapTemp.end())
	{
		cout << "can't find the " << num << endl;
	}
	else
	{
		cout << "found the " << num << endl;
	}
}

void main()
{
	std::map<int, int> mapTemp;

	int num = 123;

	FindNumInMap(mapTemp, 123);
	mapTemp[123] = 999;
	FindNumInMap(mapTemp, 123);

}

