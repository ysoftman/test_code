// ysoftman
#include <iostream>
#include <list>
#include <string>
#include <unordered_set>

using namespace std;

struct Node {
    string data;
};

void print_linked_list(list<Node> *node) {
    for (auto i : *node) {
        cout << i.data << endl;
    }

    cout << "-----" << endl;
}
void remove_duplicated_node(list<Node> *node) {
    // 방법1 - 현재 노드 값을 기준으로 뒤의 모든 노드에 중복 노드 파악
    list<Node>::iterator iter;
    for (iter = node->begin(); iter != node->end(); iter++) {
        cout << "node(data: " << iter->data << ")";
        list<Node>::iterator iter2 = iter;
        iter2++;
        while (iter2 != node->end()) {
            if (iter->data == iter2->data) {
                cout << "--> erase...";
                // 삭제된 원소의 다음 원소를 리턴받는다.
                iter2 = node->erase(iter2);
            } else {
                iter2++;
            }
        }
        cout << endl;
    }
    cout << "-----" << endl;
}

void remove_duplicated_node2(list<Node> *node) {
    // 방법2 - hashset 에 값을 저장해두고 중복 여부 파악
    unordered_set<string> hashset;
    list<Node>::iterator iter = node->begin();
    while (iter != node->end()) {
        cout << "node(data: " << iter->data << ")";
        if (hashset.find(iter->data) != hashset.end()) {
            cout << "--> erase...";
            hashset.insert(iter->data);
            iter = node->erase(iter);
        } else {
            hashset.insert(iter->data);
            iter++;
        }
        cout << endl;
    }
    cout << "-----" << endl;
}

list<Node> create_linked_list() {
    list<Node> node;
    Node n1{.data = "lemon"};
    node.push_back(n1);
    Node n2{.data = "orange"};
    node.push_back(n2);
    Node n3{.data = "apple"};
    node.push_back(n3);
    Node n4{.data = "lemon"};
    node.push_back(n4);
    Node n5{.data = "banana"};
    node.push_back(n5);
    Node n6{.data = "banana"};
    node.insert(node.begin(), n6);  // 맨처음 노드로 추가
    Node n7{.data = "apple"};
    list<Node>::iterator iter = node.begin();
    iter++;
    node.insert(iter, 5, n7);  // 2번째 노르로 연속해서 5개의 노드 추가
    iter = node.begin();
    iter++;
    iter = node.erase(iter);  // 2번째 노드 삭제

    return node;
}
int main() {
    list<Node> node = create_linked_list();
    print_linked_list(&node);

    // 중복데이터 노드 삭제
    remove_duplicated_node(&node);
    print_linked_list(&node);
    node.empty();
    node = create_linked_list();
    print_linked_list(&node);
    remove_duplicated_node2(&node);
    print_linked_list(&node);

    return 0;
}
