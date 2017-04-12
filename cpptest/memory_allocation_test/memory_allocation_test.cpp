////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 64bit ������ 4GB �̻� �� �޸� �Ҵ��� �����ϴ�.
// �������� ��� ������ ������ ���� �޸��̻����� �����Ǿ�� �Ѵ�.
// �ý��ۼӼ� -> ��� -> ���� -> ��� -> ����޸� -> c: -> �ý����� �����ϴ� ũ��� ����
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main()
{
#if defined(_WIN64)
	// 64bit ��忡�� size_t �� 8byte
	printf("_WIN64 size_t -> %d bytes\n", sizeof(size_t));
#else //_WIN32
	// 32bit ��忡�� size_t �� 4byte
	printf("_WIN32 size_t -> %d bytes\n", sizeof(size_t));
#endif

	const int cnt = 10000;
	const int size = 1024 * 1024;
	unsigned int total_size = 0;
	char *pHeap[cnt];

	// 32bit ���尡 2GB���� �Ҵ�
	// (32bit �����쿡�� 4GB �޸𸮸� �ν��ϰ� ���� 2GB Ŀ�θ�����, 2GB�� ������� ���� �� �������α׷����� ����Ѵ�.)
	// 64bit ����� 10GB���� ��� �Ҵ�
	for (int i=0; i<cnt; ++i)
	{
		pHeap[i] = new char[size];
		memset(pHeap[i], 0, size);
		total_size += size;
		printf("%lld bytes Allocated.\n", total_size);
		_sleep(1);
	}

	printf("Press any key to exit...\n");
	_getch();
	for (int i=0; i<cnt; ++i)
	{
		delete[] pHeap[i];
	}
}

