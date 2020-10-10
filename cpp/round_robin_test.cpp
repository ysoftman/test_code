// ysoftman
// round robin
#include <stdio.h>

int main()
{
	int nArray[5] = {0, 1, 2, 3, 4};
	int i = 0;
	for (int nCnt = 0; nCnt < 100; ++nCnt)
	{
		if (i >= 5)
		{
			i = 0;
		}
		printf("nArray[%d]=%d\n", i, nArray[i]);
		++i;
	}
}
