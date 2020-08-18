// ysoftman
// 원형큐(circular queue) 구현
// 일반 선형큐는 dequeue 후 front 지시자가 뒤로 이동하면
// 앞의 메모리는 사용하지 못하기 때문에
// dequeue 후 남은 모든 원소를 앞으로 shift 하는 비용이 발생해 느리다.
// 원형큐는 rear -> front 로 이어 큐공간을 재사용할 수 있다.
#include <stdio.h>

struct cir_queue
{
    int front;
    int rear;
    int size;
    int *arr;
    cir_queue()
    {
        front = -1; // -1 는 데이터가 값이 없음을 의미
        rear = -1;
        size = 0;
        arr = NULL;
    }
};

void printQueue(cir_queue *q, const char *msg, int val)
{
    printf("(size:%d front:%d, rear:%d) %s %d -> ", q->size, q->front, q->rear, msg, val);
    if (q->front < 0 || q->rear < 0)
    {
        printf("\n");
        return;
    }
    int i = q->front;
    while (i != q->rear)
    {
        if (i < 0 || i == q->size)
        {
            i = 0;
            printf("%d ", q->arr[i]);
            continue;
        }
        printf("%d ", q->arr[i]);
        ++i;
    }
    if (q->front <= q->rear)
    {
        printf("%d ", q->arr[i]);
    }

    printf("\n");
}

void enqueue(cir_queue *q, int val)
{
    // 최초 값을 넣는 경우
    if (q->front == -1)
    {
        q->front = q->rear = 0;
        q->arr[q->front] = val;
    }
    // 꽉찬 경우1
    else if (q->front == 0 && q->rear == q->size - 1)
    {
        printf("full!\n");
        return;
    }
    // 꽉찬 경우2
    else if (q->rear == q->front - 1)
    {
        printf("full!\n");
        return;
    }
    // 배열의 마지막인 경우 다시 0번째 부터
    else if (q->rear == q->size - 1)
    {
        q->rear = 0;
        q->arr[q->rear] = val;
    }
    else
    {
        ++q->rear;
        q->arr[q->rear] = val;
    }
    printQueue(q, "enqueue", val);
}

int dequeue(cir_queue *q)
{
    int val = 0;
    if (q->front == q->rear)
    {
        if (q->front == -1)
        {
            printf("empty!\n");
            return 0;
        }
        val = q->arr[q->front];
        q->front = q->rear = -1;
    }
    else if (q->front == q->size - 1)
    {
        val = q->arr[q->front];
        q->front = 0;
    }
    else
    {
        val = q->arr[q->front];
        ++q->front;
    }
    printQueue(q, "dequeue", val);
    return val;
}

int main()
{
    int arr[3] = {
        0,
    };
    cir_queue q;
    q.size = 3;
    q.arr = arr;
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    enqueue(&q, 3);
    enqueue(&q, 3);
    dequeue(&q);
    enqueue(&q, 3);
    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    return 0;
}
