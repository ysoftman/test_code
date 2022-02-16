#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using std::stack;
using std::string;

int main()
{
    stack<int> s;
    s.push(100);
    s.push(110);
    s.push(120);

    while (not s.empty())
    {
        cout << "stack size: " << s.size() << ", stack top: " << s.top() << endl;
        s.pop();
    }

    return 0;
}
