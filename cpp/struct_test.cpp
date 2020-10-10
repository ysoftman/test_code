// ysoftman
// struct test
#include <iostream>

using namespace std;

struct Node
{
    char data;
    // Node 가 정의 되지 않은 상태에서 필드로 사용면 에러발생
    // field has incomplete type 'Node'
    // Node n;
    // Node n[26];
    // 포인터로 선언해야 한다.
    Node *n[26];
    // 생성시 호출, 초기화
    Node()
    {
        data = 'A';
        for (int i = 0; i < 26; ++i)
        {
            n[i] = NULL;
        }
    }
};

int main()
{
    Node mynode;
    cout << "mynode.data: " << mynode.data << endl;
    char a = 'a';
    for (int i = 0; i < 26; ++i)
    {
        Node nn;
        nn.data = a++;
        mynode.n[i] = &nn;
        printf("mynode.n[%d]: %c\n", i, mynode.n[i]->data);
    }

    return 0;
}
