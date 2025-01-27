// ysoftman
// sizeof 함수 제대로 알기
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int arr[5];
    printf("%lu %lu %lu\n", sizeof(arr), sizeof(arr[0]), sizeof(arr[5]));

    // 배열의 길이 파악
    printf("sizeof(arr): %lu\n", sizeof(arr));
    printf("sizeof(*arr): %lu\n", sizeof(*arr));
    printf("length of array: %lu\n", sizeof(arr) / sizeof(*arr));

    // 포인터인경우 sizeof  로 길이를 파악 할 수 없다.
    int *p = new int[10];
    printf("sizeof(p): %lu\n", sizeof(p));
    printf("sizeof(*p): %lu\n", sizeof(*p));
    printf("length of point arrar: %lu ---> wrong.\n", sizeof(p) / sizeof(*p));

    return 0;
}
