////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// BinarySearch
////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

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
	
	mid = (head+end) / 2;	
	
	printf("\n[Count %2d]Searching.... %2d", ++cnt, arr[mid]);
	
	if (arr[mid] == k)
	{
		printf("\nFound %d\n\n", k);
		return mid;
	}
	
	else
	{
		if (arr[mid] > k)
		{
			return BinarySearch(arr,head,mid-1,k);
		}
		else
		{
			return BinarySearch(arr,mid+1,end,k);
		}
	}
}

void main()
{	
	int array[10] = {25, 37, 56, 99, 120, 521, 590, 709, 1005, 2506};
	int i = 0;
	int target;
	printf("Data Arrary is ");
	for (i=0; i<=9; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n\nInput Target Number : ");
	scanf("%d", &target);

	BinarySearch(array, 0, 9, target);
}


