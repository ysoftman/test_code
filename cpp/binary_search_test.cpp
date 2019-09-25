// ysoftman
// BinarySearch
#include <stdio.h>
#include <stdlib.h>

int cnt = 0;

// 이진 탐색(Condition : 정렬된 배열에 대해서만)
// parameter : arr - 배열, head - 배열시작(0), end - 배열끝, k - 찾을 데이터)
int BinarySearch(int arr[], int head, int end, int k)
{
	int mid;
	if (head > end)
	{
		printf("Head > End Error -> There Is No Target Number...\n");
		return 0;
	}
	mid = (head + end) / 2;
	printf("\n[Count %2d]Searching.... %2d", ++cnt, arr[mid]);
	if (arr[mid] == k)
	{
		printf("\nFound %d arr[%d]\n\n", k, mid);
		return mid;
	}
	else
	{
		if (arr[mid] > k)
		{
			return BinarySearch(arr, head, mid, k);
		}
		else
		{
			return BinarySearch(arr, mid, end, k);
		}
	}
}

// loop 방식
int BinarySearch2(int arr[], int length, int k)
{
	int cnt = 0;
	int i = length;
	int left = 0, right = length - 1;
	while (arr[i] != k)
	{
		i = (left + right) / 2;
		if (arr[i] < k)
		{
			left = i;
		}
		else
		{
			right = i;
		}
		printf("\n[Count %2d]Searching.... %2d", ++cnt, arr[i]);
	}
	printf("\nFound %d arr[%d]\n\n", k, i);
	return i;
}

int main()
{
	int array[10] = {25, 37, 56, 99, 120, 521, 590, 709, 1005, 2506};
	int i = 0;
	int target;
	printf("Data Array is ");
	int array_length = int(sizeof(array) / sizeof(int));
	for (i = 0; i < array_length; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\nArray length : %d", array_length);
	printf("\n\nInput Target Number : ");
	scanf("%d", &target);

	BinarySearch(array, 0, array_length - 1, target);
	BinarySearch2(array, array_length, target);
	return 0;
}
