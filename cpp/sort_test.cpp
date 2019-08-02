// ysoftman
// Sort
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif

// Maximum Size
const int MAX = 50000;

void Swap(int *a, int *b);
void BubbleSort(int arr[], int size);
void SelectionSort(int arr[], int size);
void QuickSort(int arr[], int left, int right);
void HeapSort(int arr[], int size);

// 배열 출력
void Print(FILE *fp, int arr[], int size, const char *msg)
{
	int i = 0;
	fprintf(stderr, "file writting..........");
	fprintf(fp, "%s = { ", msg);
	for (i = 0; i < size; i++)
	{
		fprintf(fp, "%d ", arr[i]);
	}
	fprintf(fp, "}\n");
	fprintf(stderr, "end\n");
}

int main()
{
	int i = 0;
	int input[MAX];
	int temp[MAX];
	memset(temp, 0, sizeof(int) * MAX);

	srand((unsigned int)time(NULL));

	FILE *fp = fopen("sort.txt", "w");

#if defined(_WIN32) || defined(_WIN64)
	DWORD start = 0, end = 0;
#endif

	// 랜덤 숫자 생성
#if defined(_WIN32) || defined(_WIN64)
	start = GetTickCount();
#endif
	for (i = 0; i < MAX; i++)
	{
		input[i] = rand() % MAX;
	}
#if defined(_WIN32) || defined(_WIN64)
	end = GetTickCount();
	printf("Random Number(%d) Elapsed Time %f\n", MAX, (float)(end - start) / (float)1000);
#endif
	Print(fp, input, MAX, "Random  Number");
	memcpy(temp, input, sizeof(int) * MAX);

	// Bubble Sort
#if defined(_WIN32) || defined(_WIN64)
	start = GetTickCount();
#endif
	BubbleSort(temp, MAX);
#if defined(_WIN32) || defined(_WIN64)
	end = GetTickCount();
	printf("Bubble Sort Elapsed Time %f\n", (float)(end - start) / (float)1000);
#endif
	Print(fp, temp, MAX, "Bubble    Sort");
	memcpy(temp, input, sizeof(int) * MAX);

	// Selection Sort
#if defined(_WIN32) || defined(_WIN64)
	start = GetTickCount();
#endif
	SelectionSort(temp, MAX);
#if defined(_WIN32) || defined(_WIN64)
	end = GetTickCount();
	printf("Selection Sort Elapsed Time %f\n", (float)(end - start) / (float)1000);
#endif
	Print(fp, temp, MAX, "Selection Sort");
	memcpy(temp, input, sizeof(int) * MAX);

	// Quick Sort
#if defined(_WIN32) || defined(_WIN64)
	start = GetTickCount();
#endif
	QuickSort(temp, 0, MAX - 1);
#if defined(_WIN32) || defined(_WIN64)
	end = GetTickCount();
	printf("Quick Sort Elapsed Time %f\n", (float)(end - start) / (float)1000);
#endif
	Print(fp, temp, MAX, "Quick     Sort");
	memcpy(temp, input, sizeof(int) * MAX);

	// Heap Sort
#if defined(_WIN32) || defined(_WIN64)
	start = GetTickCount();
#endif
	HeapSort(temp, MAX);
#if defined(_WIN32) || defined(_WIN64)
	end = GetTickCount();
	printf("Heap Sort Elapsed Time %f\n", (float)(end - start) / (float)1000);
#endif
	Print(fp, temp, MAX, "Heap      Sort");
	memcpy(temp, input, sizeof(int) * MAX);

	fclose(fp);

	return 0;
}

// Swap
void Swap(int *a, int *b)
{
	int temp = 0;
	temp = *a;
	*a = *b;
	*b = temp;
}

// Bubble Sort
void BubbleSort(int arr[], int size)
{
	int i = 0, j = 0;
	bool bSwap = false;
	for (i = 0; i < size; i++)
	{
		bSwap = false;
		for (j = 0; j < size - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&arr[j], &arr[j + 1]);
				bSwap = true;
			}
		}
		// 현재 루프에서 교환이 발생하지 않으면 정렬이 완료되었음으로 끝낸다.
		if (bSwap == false)
		{
			break;
		}
	}
}

// Selection Sort
void SelectionSort(int arr[], int size)
{
	int i = 0, j = 0, MinIdx = 0;
	for (i = 0; i < size - 1; i++)
	{
		MinIdx = i;
		// 현재 원소를 기준으로 현재원소의 뒤에 있는 모든 원소중 가장 작은 원소를 찾는다.
		for (j = i + 1; j < size; j++)
		{
			if (arr[MinIdx] > arr[j])
			{
				MinIdx = j;
			}
		}
		// 현재 원소를 가장 작은 원소와 교환한다.
		Swap(&arr[i], &arr[MinIdx]);
	}
}

// Quick Sort
void QuickSort(int arr[], int left, int right)
{
	int i = 0, j = 0, k = 0;
	// 왼쪽과 오른쪽이 교차되면 재귀를 빠져 나간다.
	if (right - left < 1)
	{
		return;
	}
	// 현재 가장 오른쪽 원소의 값을 기준으로 삼는다.
	k = arr[right];
	i = left;
	j = right - 1;
	for (;;)
	{
		// 왼쪽부터 오른쪽 방향으로 기준값 보다 큰 원소를 찾는다.
		while (arr[i] < k)
			i++;
		// 오른쪽부터 왼쪽 방향으로 기준값 보다 작은 원소를 찾는다.
		while (arr[j] > k)
			j--;
		// 큰 원소 값이 작은 원소 값보다 크거나 같으면 현재 루프를 빠져나간다.
		if (i >= j)
		{
			break;
		}
		// 작은 원소 값이 큰 원소 값보다 크면 둘을 교환한다.
		Swap(&arr[i], &arr[j]);
		// 큰 원소 값이 작은 원소 값보다 클때까지 반복한다.
		i++;
		j--;
	}
	// 위에서 찾은 i 번째 원소 값과 제일 오른쪽 원소의 값을 교환한다.
	Swap(&arr[i], &arr[right]);
	// 현재 시점에서 왼쪽부분과 오른쪽부분에 대해서 반복 수행한다.(분할 정복)
	QuickSort(arr, left, i - 1);
	QuickSort(arr, i + 1, right);
}

// MakeMaxHeap for Heap Sort
void MakeMaxHeap(int arr[], int CurIdx, int EndIdx)
{
	int MaxChildIdx = 0;
	bool done = false;

	// 참고
	// 배열 원소(노드)는 0부터 시작할때
	// 현재 노드의 왼쪽 자식 노드 위치는 현재노드*2+1
	// 현재 노드의 오른쪽 자식 노드 위치는 현재노드*2+1+1

	// 다음의 조건을 만족할때까지만 동작한다.
	// 현재 원소의 2배+1 이상되는 원소부터는 말단노드기 때문에 진행하지 않는다.
	// 더이상 교환할 원소가 없다면 진행하지 않는다.
	while ((CurIdx * 2 + 1 <= EndIdx) && (!done))
	{
		// 현재의 왼쪽 자식노드가 현재 배열의 끝 원소(노드)라면 왼쪽 자식노드 하나만 존재하는 것으로
		// 왼쪽 자식노드가 큰 값을 갖는 자식 노드가 된다.
		if (CurIdx * 2 + 1 == EndIdx)
		{
			MaxChildIdx = EndIdx;
		}
		// 2개의 자식 노드가 모두 있는 경우, 왼쪽자식 노드와 오른쪽 자식 노드중 큰 쪽을 선택한다.
		else if (arr[CurIdx * 2 + 1] > arr[CurIdx * 2 + 1 + 1])
		{
			MaxChildIdx = CurIdx * 2 + 1;
		}
		else
		{
			MaxChildIdx = CurIdx * 2 + 1 + 1;
		}

		// 이제 현재 노드와 위에서 선출한 작은 자식 노드 값을 비교한다.
		// 자식 노드가 크다면 현재(부모)노드와 값을 교환한다.
		if (arr[CurIdx] < arr[MaxChildIdx])
		{
			Swap(&arr[CurIdx], &arr[MaxChildIdx]);
			// 교환후 현재 노드를 MaxChildIdx 로 갱신한다.
			CurIdx = MaxChildIdx;
		}
		// 교환할 필요가 없으면 종료한다.
		else
		{
			done = true;
		}
	}
}

// Heap Sort
void HeapSort(int arr[], int size)
{
	// Heap Sort 는 배열을 이진 트리로 매칭한다.
	// 배열 1 2 3 4 5 가 들어오면 다음과 같은 이진 트리로 생각한다.
	//
	//       1
	//       |
	//    _______
	//    |     |
	//    2     3
	//    |
	// ______
	// |    |
	// 4    5

	int i = 0, j = 0;

	// 우선 Max Heap 상태를 만든다.
	// size/2 원소부터 시작하는 이유는 size/2 뒤 원소는 모두 자식 노드가 없기 말단 노드이기 때문이다.
	for (i = (size / 2) - 1; i >= 0; i--)
	{
		MakeMaxHeap(arr, i, size - 1);
	}
	// Max Heap 상태가 되면 가장 큰 원소 값의 root(배열[0])노드에 위치하게 된다.
	for (i = size - 1; i >= 0; i--)
	{
		// 가장 끝 노드값과 root 노드 값을 교환한다.
		Swap(&arr[0], &arr[i]);

		// 교환후 맨 마지막은 가장 큰 값이 자리한다.
		// 따라서 이 원소는 정렬 대상에서 제외시키기 위해 i-1 를 끝으로 잡는다.
		MakeMaxHeap(arr, 0, i - 1);
	}
}
