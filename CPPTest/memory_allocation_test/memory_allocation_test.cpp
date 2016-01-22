////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// 64bit 에서는 4GB 이상 힙 메모리 할당이 가능하다.
// 윈도우의 경우 페이지 파일이 실제 메모리이상으로 설정되어야 한다.
// 시스템속성 -> 고급 -> 성능 -> 고급 -> 가상메모리 -> c: -> 시스템이 관리하는 크기로 설정
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main()
{
#if defined(_WIN64)
	// 64bit 모드에선 size_t 가 8byte
	printf("_WIN64 size_t -> %d bytes\n", sizeof(size_t));
#else //_WIN32
	// 32bit 모드에선 size_t 가 4byte
	printf("_WIN32 size_t -> %d bytes\n", sizeof(size_t));
#endif

	const int cnt = 10000;
	const int size = 1024 * 1024;
	unsigned int total_size = 0;
	char *pHeap[cnt];

	// 32bit 빌드가 2GB까지 할당
	// (32bit 윈도우에서 4GB 메모리를 인식하고 이중 2GB 커널모드공간, 2GB는 유저모드 공간 즉 응용프로그램에서 사용한다.)
	// 64bit 빌드시 10GB까지 모두 할당
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

