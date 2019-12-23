// ysoftman
// BinarySearch
#include <stdio.h>
#include <stdlib.h>

int cnt = 0;

// 이진 탐색(Condition : 정렬된 배열에 대해서만)
// parameter : arr - 배열, left - 배열시작(0), right - 배열끝, k - 찾을 데이터)
int BinarySearch(int arr[], int left, int right, int k)
{
	int mid;
	mid = left + (right - left) / 2;
	if (left > right)
	{
		printf("There Is No Target Number...\n\n");
		return -1;
	}
	printf("left:%d mid:%d right:%d [Count %2d]Searching... %2d\n", left, mid, right, ++cnt, arr[mid]);
	if (arr[mid] == k)
	{
		printf("Found %d arr[%d]\n\n", k, mid);
		return mid;
	}
	else
	{
		if (arr[mid] > k)
		{
			return BinarySearch(arr, left, mid - 1, k);
		}
		else
		{
			return BinarySearch(arr, mid + 1, right, k);
		}
	}
}

// loop 방식
int BinarySearch2(int arr[], int length, int k)
{
	int cnt = 0;
	int mid = 0;
	int left = 0, right = length - 1;
	while (1)
	{
		mid = left + (right - left) / 2;
		if (left > right)
		{
			printf("There Is No Target Number...\n\n");
			return -1;
		}
		printf("left:%d mid:%d right:%d ", left, mid, right);
		printf("[Count %2d]Searching... %2d\n", ++cnt, arr[mid]);
		if (arr[mid] == k)
		{
			break;
		}
		if (arr[mid] < k)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	printf("Found %d arr[%d]\n\n", k, mid);
	return mid;
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
	printf("\nArray length : %d\n", array_length);
	printf("Input Target Number : ");
	scanf("%d", &target);

	BinarySearch(array, 0, array_length - 1, target);
	BinarySearch2(array, array_length, target);
	return 0;
}
