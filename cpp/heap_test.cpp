// ysoftman
// heap(이진트리를 이용) 자료구조 사용하기
// min-heap : 부모노드의 값이 자식노드 값보다 작다.
// max-heap : 부모노드의 값이 자식노드 값보다 크다
// 삽입, 삭제할때 추가적인 sort 가 필요없어 유용한다.
#include <iostream>
#include <queue>

// g++ -std=c++11 heap_test.cpp && ./a.out
using namespace std;

int main()
{
    // priority_queue 로 힙을 구성한다.
    // max-heap
    priority_queue<int, vector<int>, less<int>> pq_max;
    // 부모노드 값이 크도록 유지하면 삽입한다.
    // 삽입할때 트리의 높이만큼 비교한다. O(logN)
    pq_max.push(1);
    pq_max.push(3);
    pq_max.push(2);
    pq_max.push(4);
    pq_max.push(5);
    // 삭제할때도 자신의 자식들과 비교해 자리를 찾아 빠르다. O(logN)
    while (not pq_max.empty())
    {
        cout << pq_max.top() << endl;
        pq_max.pop();
    }

    cout << "-----" << endl;

    // min-heap
    priority_queue<int, vector<int>, greater<int>> pq_min;
    pq_min.push(1);
    pq_min.push(3);
    pq_min.push(2);
    pq_min.push(4);
    pq_min.push(5);
    while (not pq_min.empty())
    {
        cout << pq_min.top() << endl;
        pq_min.pop();
    }

    return 0;
}