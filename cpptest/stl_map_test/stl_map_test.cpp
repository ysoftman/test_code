////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// stl map 테스트
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <map>

using namespace std;

int main()
{
	map<int, int> mapTest;


	printf("-- map 설정 값 테스트 --\n");
	int index = 1000;
	for (int i = 0; i<index; i++)
	{
		mapTest[i] = i;
	}
	printf("mapTest[%d] ~ [%d] 설정 완료\n", index-1, mapTest[index-1]);
	printf("mapTest[%d] = %d 설정된 값\n", index-1, mapTest[index-1]);
	// set 하지 않은 곳은 NULL 로 되어있다.
	printf("mapTest[%d] = %d 미설정시 값은 디폴트 NULL(0) 로 추가\n", index, mapTest[index+1]);

	printf("\n");
	printf("-- map find() 테스트 --\n");
	// map find() 무한 루프 가능성 테스트
	map<int, int>::iterator iter;

	int key = 5;
	iter = mapTest.find(key);
	printf("mapTest.find(%d) .. %d\n", key, iter->second);

	mapTest.erase(key);
	printf("mapTest.erase(%d) .. ok\n", key);

	iter = mapTest.find(key);
	// iter 값이 invalid
	//printf("mapTest.find(%d) .. %d\n", key, iter->second);

	return 0;
}

