// ysoftman
// K-Means Clustering
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN(a, b) a > b ? b : a

const int MAX_SET = 10;

struct DOT {
    int x;      // x 좌표
    int y;      // y 좌표
    int group;  // 현재 점이 속한 그룹(클래스)
};

bool KMeansClustering(DOT *pInput, int nClass);

int  main() {
    srand((unsigned int)time(NULL));
    DOT *pInput = new DOT[MAX_SET];
    // 입력으로 사용할 점들을 랜덤하게 만든다.
    for (int i = 0; i < MAX_SET; i++) {
        pInput[i].x     = rand() % 10;
        pInput[i].y     = rand() % 10;
        pInput[i].group = 0;
        fprintf(stderr, "pInput[%3d] = (%3d,%3d)\n", i, pInput[i].x, pInput[i].y);
    }
    // 군집화 시킨다.
    KMeansClustering(pInput, 3);

    delete[] pInput;
}

bool KMeansClustering(DOT *pInput, int nClass) {
    int  i = 0, j = 0, PreDist = 0, CurDist = 0, Cnt = 0;
    bool bFind      = false;

    DOT *pCenterDot = new DOT[nClass];
    // 초기의 각 클래스를 대표할 중점은 입력 샘플로 부터 선택한다.
    for (int i = 0; i < nClass; i++) {
        pCenterDot[i].x     = pInput[i].x;
        pCenterDot[i].y     = pInput[i].y;
        pCenterDot[i].group = 0;
    }

    // 반복시 중점을 다시 계산하기 위해서
    DOT *pNewCenterDot = new DOT[nClass];
    memset(pNewCenterDot, 0, sizeof(DOT) * nClass);

    while (true) {
        // 현재 중점 값 출력
        for (j = 0; j < nClass; j++) {
            fprintf(stderr, "pCenterDot[%3d] = (%3d,%3d)\n", j, pCenterDot[j].x, pCenterDot[j].y);
        }
        // 주어진 중점과의 거리를 기반으로 입력데이터를 classify
        for (i = 0; i < MAX_SET; i++) {
            PreDist = 99999;
            for (j = 0; j < nClass; j++) {
                // 입력데이터 점들이 현재 중점과의 이전 중점 중 작은 곳의 클래스를 선택한다.
                CurDist = 0;
                CurDist += abs(pCenterDot[j].x - pInput[i].x) + abs(pCenterDot[j].y - pInput[i].y);
                if (PreDist > CurDist) {
                    pInput[i].group = j;
                }
                PreDist = MIN(PreDist, CurDist);
            }
            // 현재 입력데이터가 어떤 클래스로 분류되었는지 출력
            // fprintf(stderr, "pInput[%3d] = (%3d,%3d) ==> class%3d = (%3d,%3d)\n", i, pInput[i].x,
            // pInput[i].y, pInput[i].group, pCenterDot[pInput[i].group].x,
            // pCenterDot[pInput[i].group].y);
        }
        // classify 된 데이터들로 다시 중점을 계산한다.
        memset(pNewCenterDot, 0, sizeof(DOT) * nClass);
        for (j = 0; j < nClass; j++) {
            Cnt = 0;
            for (i = 0; i < MAX_SET; i++) {
                if (j == pInput[i].group) {
                    pNewCenterDot[j].x += pInput[i].x;
                    pNewCenterDot[j].y += pInput[i].y;
                    Cnt++;
                }
            }
            if (Cnt == 0) {
                fprintf(stderr, "error, divied by zero...\n");
                return false;
            }
            pNewCenterDot[j].x /= Cnt;
            pNewCenterDot[j].y /= Cnt;
        }

        // 이전 중점과 새롭게 계산된 중점이 같으면 빠져나간다.
        for (j = 0; j < nClass; j++) {
            if (pNewCenterDot[j].x == pCenterDot[j].x && pNewCenterDot[j].y == pCenterDot[j].y) {
                bFind = true;
            } else {
                bFind = false;
                break;
            }
        }
        if (bFind) {
            break;
        }

        // 새롭게 계산되 중점을 반영한다.
        for (j = 0; j < nClass; j++) {
            pCenterDot[j].x = pNewCenterDot[j].x;
            pCenterDot[j].y = pNewCenterDot[j].y;
        }
    }

    delete[] pCenterDot;
    delete[] pNewCenterDot;

    return true;
}
