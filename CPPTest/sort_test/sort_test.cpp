////////////////////////////////////////////////////////////////////////////////////
// ysoftman
// Sort
////////////////////////////////////////////////////////////////////////////////////
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

// �迭 ���
void Print(FILE *fp, int arr[], int size, char *msg)
{
	int i = 0;
	fprintf(stderr, "file writting..........");
	fprintf(fp, "%s = { ", msg);
	for (i = 0; i < size; i++)
	{
		fprintf (fp, "%d ", arr[i]);
	}
	fprintf(fp, "}\n");
	fprintf(stderr, "end\n");
}


void main()
{
	int i = 0;
	int input[MAX];
	int temp[MAX];
	memset(temp, 0, sizeof(int)*MAX);
	
	srand((unsigned int)time(NULL));

	FILE *fp = fopen("sort.txt", "w");

#if defined(_WIN32) || defined(_WIN64)
	DWORD start=0, end=0;
#endif

	// ���� ���� ����
#if defined(_WIN32) || defined(_WIN64)
	start = GetTickCount();
#endif
	for (i = 0; i < MAX ; i++)
	{
		input[i] = rand()%MAX;
	}
#if defined(_WIN32) || defined(_WIN64)
	end = GetTickCount();
	printf("Random Number(%d) Elapsed Time %f\n", MAX, (float)(end-start)/(float)1000);
#endif
	Print(fp, input, MAX, "Random  Number");
	memcpy(temp, input, sizeof(int)*MAX);
	

	// Bubble Sort
#if defined(_WIN32) || defined(_WIN64)
	start = GetTickCount();
#endif
	BubbleSort(temp, MAX);
#if defined(_WIN32) || defined(_WIN64)
	end = GetTickCount();
	printf("Bubble Sort Elapsed Time %f\n", (float)(end-start)/(float)1000);
#endif
	Print(fp, temp, MAX, "Bubble    Sort");
	memcpy(temp, input, sizeof(int)*MAX);


	// Selection Sort
#if defined(_WIN32) || defined(_WIN64)
	start = GetTickCount();
#endif
	SelectionSort(temp, MAX);
#if defined(_WIN32) || defined(_WIN64)
	end = GetTickCount();
	printf("Selection Sort Elapsed Time %f\n", (float)(end-start)/(float)1000);
#endif
	Print(fp, temp, MAX, "Selection Sort");
	memcpy(temp, input, sizeof(int)*MAX);


	// Quick Sort
#if defined(_WIN32) || defined(_WIN64)
	start = GetTickCount();
#endif
	QuickSort(temp, 0, MAX-1);
#if defined(_WIN32) || defined(_WIN64)
	end = GetTickCount();
	printf("Quick Sort Elapsed Time %f\n", (float)(end-start)/(float)1000);
#endif
	Print(fp, temp, MAX, "Quick     Sort");
	memcpy(temp, input, sizeof(int)*MAX);

	// Heap Sort
#if defined(_WIN32) || defined(_WIN64)
	start = GetTickCount();
#endif
	HeapSort(temp, MAX);
#if defined(_WIN32) || defined(_WIN64)
	end = GetTickCount();
	printf("Heap Sort Elapsed Time %f\n", (float)(end-start)/(float)1000);
#endif
	Print(fp, temp, MAX, "Heap      Sort");
	memcpy(temp, input, sizeof(int)*MAX);

	fclose(fp);
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
		for (j = 0; j < size-1; j++)
		{
			if (arr[j] > arr[j+1])
			{
				Swap(&arr[j], &arr[j+1]);
				bSwap = true;
			}
		}
		// ���� �������� ��ȯ�� �߻����� ������ ������ �Ϸ�Ǿ������� ������.
		if (bSwap == false)
		{
			break;
		}
	}
}

// Selection Sort
void SelectionSort(int arr[], int size)
{
	int i = 0, j = 0, MinIdx=0;
	for (i = 0; i < size-1; i++)
	{
		MinIdx = i;
		// ���� ���Ҹ� �������� ��������� �ڿ� �ִ� ��� ������ ���� ���� ���Ҹ� ã�´�.
		for (j = i+1; j < size; j++)
		{
			if (arr[MinIdx] > arr[j])
			{
				MinIdx = j;
			}
		}
		// ���� ���Ҹ� ���� ���� ���ҿ� ��ȯ�Ѵ�.
		Swap(&arr[i], &arr[MinIdx]);
	}
}

// Quick Sort
void QuickSort(int arr[], int left, int right)
{
	int i = 0, j = 0, k = 0;
	// ���ʰ� �������� �����Ǹ� ��͸� ���� ������.
	if (right - left < 1)
	{
		return;
	}
	// ���� ���� ������ ������ ���� �������� ��´�.
	k = arr[right];
	i = left;
	j = right - 1;
	for (;;)
	{
		// ���ʺ��� ������ �������� ���ذ� ���� ū ���Ҹ� ã�´�.
		while (arr[i] < k) i++;
		// �����ʺ��� ���� �������� ���ذ� ���� ���� ���Ҹ� ã�´�.
		while (arr[j] > k) j--;
		// ū ���� ���� ���� ���� ������ ũ�ų� ������ ���� ������ ����������.
		if (i >= j)
		{
			break;
		}
		// ���� ���� ���� ū ���� ������ ũ�� ���� ��ȯ�Ѵ�.
		Swap(&arr[i], &arr[j]);
		// ū ���� ���� ���� ���� ������ Ŭ������ �ݺ��Ѵ�.
		i++;
		j--;
	}
	// ������ ã�� i ��° ���� ���� ���� ������ ������ ���� ��ȯ�Ѵ�.
	Swap(&arr[i], &arr[right]);
	// ���� �������� ���ʺκа� �����ʺκп� ���ؼ� �ݺ� �����Ѵ�.(���� ����)
	QuickSort(arr, left, i-1);
	QuickSort(arr, i+1, right);
}

// MakeMaxHeap for Heap Sort
void MakeMaxHeap(int arr[], int CurIdx, int EndIdx)
{
	int MaxChildIdx = 0;
	bool done = false;
	
	// ����
	// �迭 ����(���)�� 0���� �����Ҷ�
	// ���� ����� ���� �ڽ� ��� ��ġ�� ������*2+1
	// ���� ����� ������ �ڽ� ��� ��ġ�� ������*2+1+1

	// ������ ������ �����Ҷ������� �����Ѵ�.
	// ���� ������ 2��+1 �̻�Ǵ� ���Һ��ʹ� ���ܳ��� ������ �������� �ʴ´�.
	// ���̻� ��ȯ�� ���Ұ� ���ٸ� �������� �ʴ´�.
	while ((CurIdx*2+1 <= EndIdx) && (!done))
	{
		// ������ ���� �ڽĳ�尡 ���� �迭�� �� ����(���)��� ���� �ڽĳ�� �ϳ��� �����ϴ� ������
		// ���� �ڽĳ�尡 ū ���� ���� �ڽ� ��尡 �ȴ�.
		if (CurIdx*2+1 == EndIdx)
		{
			MaxChildIdx = EndIdx;
		}
		// 2���� �ڽ� ��尡 ��� �ִ� ���, �����ڽ� ���� ������ �ڽ� ����� ū ���� �����Ѵ�.
		else if (arr[CurIdx*2+1] > arr[CurIdx*2+1+1])
		{
			MaxChildIdx = CurIdx*2+1;
		}
		else
		{
			MaxChildIdx = CurIdx*2+1+1;
		}

		// ���� ���� ���� ������ ������ ���� �ڽ� ��� ���� ���Ѵ�.
		// �ڽ� ��尡 ũ�ٸ� ����(�θ�)���� ���� ��ȯ�Ѵ�.
		if (arr[CurIdx] < arr[MaxChildIdx])
		{
			Swap(&arr[CurIdx], &arr[MaxChildIdx]);
			// ��ȯ�� ���� ��带 MaxChildIdx �� �����Ѵ�.
			CurIdx = MaxChildIdx;
		}
		// ��ȯ�� �ʿ䰡 ������ �����Ѵ�.
		else
		{
			done = true;
		}
	}
}

// Heap Sort
void HeapSort(int arr[], int size)
{
	// Heap Sort �� �迭�� ���� Ʈ���� ��Ī�Ѵ�.
	// �迭 1 2 3 4 5 �� ������ ������ ���� ���� Ʈ���� �����Ѵ�.
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

	// �켱 Max Heap ���¸� �����.
	// size/2 ���Һ��� �����ϴ� ������ size/2 �� ���Ҵ� ��� �ڽ� ��尡 ���� ���� ����̱� �����̴�.
	for (i = (size/2)-1; i >= 0; i--)
	{
		MakeMaxHeap(arr, i, size-1);
	}
	// Max Heap ���°� �Ǹ� ���� ū ���� ���� root(�迭[0])��忡 ��ġ�ϰ� �ȴ�.
	for (i = size-1; i >= 0; i--)
	{
		// ���� �� ��尪�� root ��� ���� ��ȯ�Ѵ�.
		Swap(&arr[0], &arr[i]);
		
		// ��ȯ�� �� �������� ���� ū ���� �ڸ��Ѵ�.
		// ���� �� ���Ҵ� ���� ��󿡼� ���ܽ�Ű�� ���� i-1 �� ������ ��´�.
		MakeMaxHeap(arr, 0, i-1);
	}
}


