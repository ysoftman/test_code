// ysoftman
// Sort
// BigO Complexity
// O(1) < O(logN) < O(N) < O(NlogN) < O(N^2) < O(2^N) < O(N!)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <algorithm>  // sort()
#include <ctime>
#include <map>
#include <vector>

using namespace std;

// Maximum Size
const int MAX = 10000;

int swap_cnt = 0;

void Swap(int *a, int *b);
void BubbleSort(int arr[], int size);
void SelectionSort(int arr[], int size);
void InsertionSort(int arr[], int size);
void RadixSort(int arr[], int size);
void MergeSort(int arr[], int left, int right);
void QuickSort(int arr[], int left, int right);
void QuickSort2(int arr[], int left, int right);
void HeapSort(int arr[], int size);

// 배열 출력
void Print(FILE *fp, int arr[], int size, const char *msg) {
    int i = 0;
    fprintf(stdout, "writing %s result to file...", msg);
    fprintf(fp, "%s\n[ ", msg);
    for (i = 0; i < size; i++) {
        fprintf(fp, "%d ", arr[i]);
    }
    fprintf(fp, "]\n");
    fprintf(stdout, "end\n\n");
}

bool validate_by_std_quick_sort(int arr1[], int arr2[]) {
    for (int i = 0; i < MAX; i++) {
        if (arr1[i] != arr2[i]) {
            printf("validate => failed\n");
            return false;
        }
    }
    printf("validate => passed\n");
    return true;
}

int main() {
    int i = 0;
    int input[MAX];
    srand((unsigned int)time(NULL));
    FILE *fp = fopen("sort_test_result.txt", "w");

    clock_t start = clock();
    for (i = 0; i < MAX; i++) {
        input[i] = rand() % MAX;
    }
    printf("Random Number(%d) Elapsed Time %f\n", MAX, double(clock() - start) / CLOCKS_PER_SEC);
    Print(fp, input, MAX, "Random Number");

    // c++ quick sort
    start = clock();
    int c_std_quick_sort[MAX];
    memcpy(c_std_quick_sort, input, sizeof(int) * MAX);
    std::sort(c_std_quick_sort, c_std_quick_sort + MAX);
    printf("----- C++ quick sort -----\n");
    printf("elapsed time : %f\n", double(clock() - start) / CLOCKS_PER_SEC);
    Print(fp, c_std_quick_sort, MAX, "C++ quick sort");

    // Bubble Sort
    start = clock();
    swap_cnt = 0;
    int bubble_sort[MAX];
    memcpy(bubble_sort, input, sizeof(int) * MAX);
    BubbleSort(bubble_sort, MAX);
    printf("----- Bubble Sort -----\n");
    printf("swap_cnt : %d\n", swap_cnt);
    printf("elapsed time : %f\n", double(clock() - start) / CLOCKS_PER_SEC);
    validate_by_std_quick_sort(c_std_quick_sort, bubble_sort);
    Print(fp, bubble_sort, MAX, "Bubble Sort");

    // Selection Sort
    start = clock();
    swap_cnt = 0;
    int selection_sort[MAX];
    memcpy(selection_sort, input, sizeof(int) * MAX);
    SelectionSort(selection_sort, MAX);
    printf("----- Selection Sort -----\n");
    printf("swap_cnt : %d\n", swap_cnt);
    printf("elapsed time : %f\n", double(clock() - start) / CLOCKS_PER_SEC);
    validate_by_std_quick_sort(c_std_quick_sort, selection_sort);
    Print(fp, selection_sort, MAX, "Selection Sort");

    // Insertion Sort
    start = clock();
    swap_cnt = 0;
    int insertion_sort[MAX];
    memcpy(insertion_sort, input, sizeof(int) * MAX);
    InsertionSort(insertion_sort, MAX);
    printf("----- Insertion Sort -----\n");
    printf("swap_cnt : %d\n", swap_cnt);
    printf("elapsed time : %f\n", double(clock() - start) / CLOCKS_PER_SEC);
    validate_by_std_quick_sort(c_std_quick_sort, insertion_sort);
    Print(fp, insertion_sort, MAX, "Insertion Sort");

    // Radix Sort
    start = clock();
    swap_cnt = 0;
    int radix_sort[MAX];
    memcpy(radix_sort, input, sizeof(int) * MAX);
    RadixSort(radix_sort, MAX);
    printf("----- Radix Sort -----\n");
    printf("swap_cnt : %d\n", swap_cnt);
    printf("elapsed time : %f\n", double(clock() - start) / CLOCKS_PER_SEC);
    validate_by_std_quick_sort(c_std_quick_sort, radix_sort);
    Print(fp, radix_sort, MAX, "Radix Sort");

    // Merge Sort
    start = clock();
    swap_cnt = 0;
    int merge_sort[MAX];
    memcpy(merge_sort, input, sizeof(int) * MAX);
    MergeSort(merge_sort, 0, MAX - 1);
    printf("----- Merge Sort -----\n");
    printf("swap_cnt : %d\n", swap_cnt);
    printf("elapsed time : %f\n", double(clock() - start) / CLOCKS_PER_SEC);
    validate_by_std_quick_sort(c_std_quick_sort, merge_sort);
    Print(fp, merge_sort, MAX, "Merge Sort");

    // Quick Sort
    start = clock();
    swap_cnt = 0;
    int quick_sort[MAX];
    memcpy(quick_sort, input, sizeof(int) * MAX);
    QuickSort(quick_sort, 0, MAX - 1);
    printf("----- Quick Sort -----\n");
    printf("swap_cnt : %d\n", swap_cnt);
    printf("elapsed time : %f\n", double(clock() - start) / CLOCKS_PER_SEC);
    validate_by_std_quick_sort(c_std_quick_sort, quick_sort);
    Print(fp, quick_sort, MAX, "Quick Sort");

    // Quick Sort
    start = clock();
    swap_cnt = 0;
    int quick_sort2[MAX];
    memcpy(quick_sort2, input, sizeof(int) * MAX);
    QuickSort2(quick_sort2, 0, MAX - 1);
    printf("----- Quick Sort 2 -----\n");
    printf("swap_cnt : %d\n", swap_cnt);
    printf("elapsed time : %f\n", double(clock() - start) / CLOCKS_PER_SEC);
    validate_by_std_quick_sort(c_std_quick_sort, quick_sort2);
    Print(fp, quick_sort2, MAX, "Quick Sort 2");

    // Heap Sort
    start = clock();
    swap_cnt = 0;
    int heap_sort[MAX];
    memcpy(heap_sort, input, sizeof(int) * MAX);
    HeapSort(heap_sort, MAX);
    printf("----- Heap Sort -----\n");
    printf("swap_cnt : %d\n", swap_cnt);
    printf("elapsed time : %f\n", double(clock() - start) / CLOCKS_PER_SEC);
    validate_by_std_quick_sort(c_std_quick_sort, heap_sort);
    Print(fp, heap_sort, MAX, "Heap Sort");

    fclose(fp);
    return 0;
}

// Swap
void Swap(int *a, int *b) {
    int temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
    ++swap_cnt;
}

// Bubble Sort - best: O(N) average: O(N^2) worst: O(N^2)
// (N*N)/2 의 시간이 걸리지만 빅오표기법은 계수(1/2)와 낮은 항은 제외 시켜야 함으로 N*N = O(N^2) 가
// 된다.
void BubbleSort(int arr[], int size) {
    bool bSwap = false;
    for (int i = 0; i < size - 1; i++) {
        bSwap = false;
        // 이 루프가 끝나면 마지막 원소는 가장 큰 값이 되기 때문에 다음 루프에서는 정렬 대상에서
        // 제외 시킨다.
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                Swap(&arr[j], &arr[j + 1]);
                bSwap = true;
            }
        }
        // 현재 루프에서 교환이 발생하지 않으면 정렬이 완료되었음으로 끝낸다.
        if (bSwap == false) {
            break;
        }
    }
}

// Selection Sort - best: O(N^2) average: O(N^2) worst: O(N^2)
// 평균적으로, bubble sort 보다 swap 이 적게 발생해 빠르다
void SelectionSort(int arr[], int size) {
    int i = 0, j = 0, MinIdx = 0;
    for (i = 0; i < size - 1; i++) {
        MinIdx = i;
        // 현재 원소를 기준으로 현재원소의 뒤에 있는 모든 원소중 가장 작은 원소를 찾는다.
        for (j = i + 1; j < size; j++) {
            if (arr[MinIdx] > arr[j]) {
                MinIdx = j;
            }
        }
        // 현재 원소를 가장 작은 원소와 교환한다.
        Swap(&arr[i], &arr[MinIdx]);
    }
}

// Insertsion Sort - best: O(N^2) average: O(N^2) worst: O(N^2)
void InsertionSort(int arr[], int size) {
    int i = 0, j = 0, cur_val = 0;
    for (i = 0; i < size; i++) {
        cur_val = arr[i];
        // cur_val 값을 현재이전(j-1)~0까지 차례로 비교해나가면서 알맞은 위치에 삽입한다.
        for (j = i - 1; j >= 0;) {
            if (arr[j] > cur_val) {
                // 현재값을 오른쪽으로 한칸 이동
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = cur_val;
    }
}

// Radix Sort (bucket sort 라고도 한다.) - best: O(N*M) average: O(N*M) worst: O(N*M)
void RadixSort(int arr[], int size) {
    int i = 0, j = 0;
    // 10진수(radix)라 0~9의 버킷 준비
    map<int, vector<int>> bucket;

    int digit_cnt = 1;
    int temp = MAX;
    while (temp >= 10) {
        temp /= 10;
        ++digit_cnt;
    }
    // printf("digit_cnt = %d\n", digit_cnt);
    // 1의 자리 부터 max 번째 자리수 만큼
    for (i = 0; i < digit_cnt; ++i) {
        for (j = 0; j < size; ++j) {
            temp = arr[j];
            int digit_num = 0;
            // 현재 숫자의 i 번째 자리수를 키로 현재 숫자 저장
            for (int k = 0; k < i; k++) {
                digit_num = temp % 10;
                temp /= 10;
            }
            bucket[digit_num].push_back(arr[j]);
        }

        memset(arr, 0, sizeof(int) * MAX);
        int k = 0;
        // buket 에 저장된 순서대로 꺼내서 arr 를 다시 구성
        // 현재 digit 별
        for (auto m : bucket) {
            for (auto val : m.second) {
                arr[k++] = val;
            }
        }
        bucket.clear();
    }
}

void Merge(int arr[], int left, int mid, int right) {
    // 임시 배열 생성1 left ... mid
    // 임시 배열 생성2 mid+1 ... right
    int size1 = mid - left + 1;
    int size2 = right - mid;
    int arr1[size1];
    int arr2[size2];
    for (int i = 0; i < size1; ++i) {
        arr1[i] = arr[left + i];
    }
    for (int i = 0; i < size2; ++i) {
        arr2[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;
    // arr1 와 arr2 의 처음부터 크기를 비교해서 작은쪽의 값을
    // 원래 배열인 arr 처음부터 할당해 나간다.
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            arr[k] = arr1[i];
            ++i;
        } else {
            arr[k] = arr2[j];
            ++j;
        }
        ++k;
        ++swap_cnt;
    }

    // 위 arr1 i 진행 이후 값을 arr 에 할당.
    for (; i < size1; ++i) {
        arr[k] = arr1[i];
        ++k;
    }
    // 위 arr2 j 진행 이후 값을 arr 에 할당.
    for (; j < size2; ++j) {
        arr[k] = arr2[j];
        ++k;
    }
}

// Merge Sort - best: O(NlogN) average: O(NlogN) worst: O(NlogN)
void MergeSort(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + ((right - left) / 2);
    MergeSort(arr, left, mid);
    MergeSort(arr, mid + 1, right);
    Merge(arr, left, mid, right);
}

// Quick Sort - best: O(NlogN) average: O(NlogN) worst: O(N^2)
void QuickSort(int arr[], int left, int right) {
    // 왼쪽과 오른쪽이 교차되면 재귀를 빠져 나간다.
    if (left >= right) {
        return;
    }
    int i = left;
    for (int j = left; j < right; ++j) {
        // 가장 오른쪽 원소의 값을 기준값으로 삼는다.
        // 기준값보다 작은원소값들이 왼쪽으로 위치하도록 한다.
        if (arr[j] < arr[right]) {
            Swap(&arr[i], &arr[j]);
            // 최종 i 위치는 기준값이 들어갈 자리이다.
            // i 왼쪽의 원소값들은 모두 i 보다 작은 값을 가진것들만 존재하게 된다.
            i++;
        }
    }
    // 위에서 찾은 i 번째의 원소값과 기준값을 교환한다.
    Swap(&arr[i], &arr[right]);
    // i 를 기준으로 왼쪽부분과 오른쪽부분에 대해 반복 수행한다.(분할 정복)
    QuickSort(arr, left, i - 1);
    QuickSort(arr, i + 1, right);
}

void QuickSort2(int *arr, int start, int end) {
    if (start >= end) {
        return;
    }
    // pivot 값으로 보통 왼쪽, 중간, 오른쪽 값을 취한다.
    // int pivot_idx = start;
    // int pivot_idx = start + ((end - start) / 2);
    int pivot_idx = end;
    int pivot_val = arr[pivot_idx];
    int left = start, right = end;
    while (left <= right) {
        while (arr[left] < pivot_val) {
            left++;
        }
        while (arr[right] > pivot_val) {
            right--;
        }
        if (left <= right) {
            Swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    }
    // left=right 에서 스왑수 left++로 left 가 마지막 index 를 넘어 가는 경우 계속 같은 파티션에서
    // recursion 되는것 막기
    if (left > end) {
        left--;
    }

    QuickSort2(arr, start, left - 1);
    QuickSort2(arr, left, end);
}

// MakeMaxHeap for Heap Sort
void MakeMaxHeap(int arr[], int CurIdx, int EndIdx) {
    int MaxChildIdx = 0;
    bool done = false;

    // 참고
    // 배열 원소(노드)는 0부터 시작할때
    // 현재 노드의 왼쪽 자식 노드 위치는 현재노드*2+1
    // 현재 노드의 오른쪽 자식 노드 위치는 현재노드*2+1+1

    // 다음의 조건을 만족할때까지만 동작한다.
    // 현재 원소의 2배+1 이상되는 원소부터는 말단노드기 때문에 진행하지 않는다.
    // 더이상 교환할 원소가 없다면 진행하지 않는다.
    while ((CurIdx * 2 + 1 <= EndIdx) && (!done)) {
        // 현재의 왼쪽 자식노드가 현재 배열의 끝 원소(노드)라면 왼쪽 자식노드 하나만 존재하는 것으로
        // 왼쪽 자식노드가 큰 값을 갖는 자식 노드가 된다.
        if (CurIdx * 2 + 1 == EndIdx) {
            MaxChildIdx = EndIdx;
        }
        // 2개의 자식 노드가 모두 있는 경우, 왼쪽자식 노드와 오른쪽 자식 노드중 큰 쪽을 선택한다.
        else if (arr[CurIdx * 2 + 1] > arr[CurIdx * 2 + 1 + 1]) {
            MaxChildIdx = CurIdx * 2 + 1;
        } else {
            MaxChildIdx = CurIdx * 2 + 1 + 1;
        }

        // 이제 현재 노드와 위에서 선출한 작은 자식 노드 값을 비교한다.
        // 자식 노드가 크다면 현재(부모)노드와 값을 교환한다.
        if (arr[CurIdx] < arr[MaxChildIdx]) {
            Swap(&arr[CurIdx], &arr[MaxChildIdx]);
            // 교환후 현재 노드를 MaxChildIdx 로 갱신한다.
            CurIdx = MaxChildIdx;
        }
        // 교환할 필요가 없으면 종료한다.
        else {
            done = true;
        }
    }
}

// Heap Sort - best: O(NlogN) average: O(NlogN) worst: O(NlogN)
void HeapSort(int arr[], int size) {
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
    // size/2 원소부터 시작하는 이유는 size/2 뒤 원소는 모두 자식 노드가 없기 말단 노드이기
    // 때문이다.
    for (i = (size / 2) - 1; i >= 0; i--) {
        MakeMaxHeap(arr, i, size - 1);
    }
    // Max Heap 상태가 되면 가장 큰 원소 값의 root(배열[0])노드에 위치하게 된다.
    for (i = size - 1; i >= 0; i--) {
        // 가장 끝 노드값과 root 노드 값을 교환한다.
        Swap(&arr[0], &arr[i]);

        // 교환후 맨 마지막은 가장 큰 값이 자리한다.
        // 따라서 이 원소는 정렬 대상에서 제외시키기 위해 i-1 를 끝으로 잡는다.
        MakeMaxHeap(arr, 0, i - 1);
    }
}
