#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::string;

int main()
{
    std::queue<int> q;
    cout << "q.size():" << q.size() << endl;
    q.push(100);
    q.push(110);
    cout << "q.size():" << q.size() << endl;

    cout << "q.front():" << q.front() << endl;
    cout << "q.front():" << q.front() << endl;
    cout << "q.back():" << q.back() << endl;
    cout << "q.back():" << q.back() << endl;
    cout << "q.size():" << q.size() << endl;

    q.pop();
    cout << "q.pop()...q.size():" << q.size() << endl;
    q.pop();
    cout << "q.pop()...q.size():" << q.size() << endl;

    // size 가 0일때 pop() 하면 프로그램이 종료되지 않으니 size >0 일때만 pop 하자
    if (q.size() > 0)
    {
        q.pop();
        cout << "q.pop()...q.size():" << q.size() << endl;
    }

    return 0;
}
