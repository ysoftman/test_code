////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// stl map �׽�Ʈ
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <map>

using namespace std;

int main()
{
	map<int, int> mapTest;


	printf("-- map ���� �� �׽�Ʈ --\n");
	int index = 1000;
	for (int i = 0; i<index; i++)
	{
		mapTest[i] = i;
	}
	printf("mapTest[%d] ~ [%d] ���� �Ϸ�\n", index-1, mapTest[index-1]);
	printf("mapTest[%d] = %d ������ ��\n", index-1, mapTest[index-1]);
	// set ���� ���� ���� NULL �� �Ǿ��ִ�.
	printf("mapTest[%d] = %d �̼����� ���� ����Ʈ NULL(0) �� �߰�\n", index, mapTest[index+1]);

	printf("\n");
	printf("-- map find() �׽�Ʈ --\n");
	// map find() ���� ���� ���ɼ� �׽�Ʈ
	map<int, int>::iterator iter;

	int key = 5;
	iter = mapTest.find(key);
	printf("mapTest.find(%d) .. %d\n", key, iter->second);

	mapTest.erase(key);
	printf("mapTest.erase(%d) .. ok\n", key);

	iter = mapTest.find(key);
	// iter ���� invalid
	//printf("mapTest.find(%d) .. %d\n", key, iter->second);

	return 0;
}

