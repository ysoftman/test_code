// ysoftman
// 배열 테스트
#include <stdio.h>

// 배열은 포인터의 일종으로 [] 는 참조 파라미터가됨
int modifyarry(int arValue[]) {
    arValue[0] = -1;
    arValue[1] = 10;
    return 0;
}

// 배열은 포인터의 일종으로 * 포인터형으로 받아됨
int modifyarry2(int *arValue) {
    arValue[0] = 7;
    arValue[1] = 99;
    return 0;
}

// c99 에서는 n 값을 먼저 선언후 matrix[][n] 파라미터 값으로 사용할 수 있다.
// gcc -std=c99 array_test.c && ./a.out
// 하지만 c++ 에선 에러 발생한다.
// void print2darray(int m, int n, int matrix[][n])
void print2darray(int matrix[][3], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// 1차원 배열로 전달 받아 2차원으로 계산해서 출력한다.
void print2darray2(int matrix[], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[m * i + j]);
        }
        printf("\n");
    }
}

int main() {
    int arr[3];
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;

    // arr[3] = 3; // <- 런타임 에러 발생
    for (int i = 0; i < 3; i++) {
        printf("arr[%d]: %d\n", i, arr[i]);
    }
    modifyarry(arr);
    printf("after modifyarry(arr)\n");

    for (int i = 0; i < 3; i++) {
        printf("arr[%d]: %d\n", i, arr[i]);
    }
    modifyarry2(arr);
    printf("after modifyarry2(arr)\n");
    for (int i = 0; i < 3; i++) {
        printf("arr[%d]: %d\n", i, arr[i]);
    }

    // 2차원 배열 생성시 첫번째 라인은 개수는 생략할 수 있다.
    int matrix[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // c99 로 컴파일 할때
    // print2darray(3, 3, matrix);
    // 일반적인 방법
    print2darray(matrix, 3, 3);
    // 첫번째 원소의 주소값을 전달
    print2darray2(&matrix[0][0], 3, 3);

    return 0;
}
