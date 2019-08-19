// ysoftman
// breadth first search test
// depth first search test
// g++ -std=c++11 search_bfs_dfs.cpp && ./a.out
#include "iostream"
#include "string"
#include "map"
#include "vector"
#include "queue"
#include "stack"
using namespace std;

struct Node
{
    string name;
    unsigned int nodescnt;
    map<unsigned int, Node *> nodes;
};

void add_node(Node *n, Node *new_node)
{
    n->nodes[n->nodescnt] = new_node;
    ++n->nodescnt;
}

void bfs(Node *n)
{
    cout << "bfs" << endl;
    // queue for bfs
    queue<Node *> q;
    q.push(n);
    while (not q.empty())
    {
        cout << "Node : " << q.front()->name << endl;
        vector<Node *> childnodes;
        for (auto i : q.front()->nodes)
        {
            childnodes.push_back(i.second);
        }
        q.pop();
        for (auto i : childnodes)
        {
            q.push(i);
        }
    }
}

void dfs(Node *n)
{
    cout << "dfs" << endl;
    // stack for dfs
    stack<Node *> st;
    st.push(n);

    map<unsigned int, Node *>::reverse_iterator iter;
    while (not st.empty())
    {
        cout << "Node : " << st.top()->name << endl;
        vector<Node *> childnodes;
        // for (auto i : st.top()->nodes)
        for (iter = st.top()->nodes.rbegin(); iter != st.top()->nodes.rend(); ++iter)
        {
            childnodes.push_back(iter->second);
        }
        st.pop();
        for (auto i : childnodes)
        {
            st.push(i);
        }
    }
}

void dfs_recursive(Node *n)
{
    if (n->nodes.empty())
    {
        return;
    }
    for (auto i : n->nodes)
    {
        cout << "Node : " << i.second->name << endl;
        dfs_recursive(i.second);
    }
}

int main()
{
    cout << "make graph(tree)" << endl;
    Node root{"A"};
    Node bnode = {"B"};
    Node cnode = {"C"};
    add_node(&root, &bnode);
    add_node(&root, &cnode);

    Node dnode = {"D"};
    Node enode = {"E"};
    add_node(&bnode, &dnode);
    add_node(&bnode, &enode);

    Node fnode = {"F"};
    Node gnode = {"G"};
    add_node(&cnode, &fnode);
    add_node(&cnode, &gnode);

    bfs(&root);
    dfs(&root);
    cout << "dfs_recursive" << endl;
    cout << "Node : " << root.name << endl;
    dfs_recursive(&root);

    return 0;
}
