// g++ -std=c++11 ./emplacement_vector.cpp && ./a.out
#include <iostream>
#include <vector>
#include <list>
#include <map>

using std::cout;
using std::endl;
using std::string;

bool enableMsg = true;
class ITEM
{
public:
    ITEM()
    {
        cout << "ITEM() default constructor" << endl;
    }
    ITEM(string n, int v)
    {
        name = n;
        val = v;
        if (!enableMsg)
        {
            return;
        }
        char msg[512];
        sprintf(msg, "ITEM(string n, int v) general constructor(%s %d)", name.c_str(), val);
        cout << msg << endl;
    }
    ITEM(const ITEM &lhs) : name(std::move(lhs.name)), val(std::move(lhs.val))
    {
        if (!enableMsg)
        {
            return;
        }
        char msg[512];
        sprintf(msg, "ITEM(const ITEM &lhs) Lvalue constructor(%s %d)", name.c_str(), val);
        cout << msg << endl;
    }
    ITEM(ITEM &lhs) : name(std::move(lhs.name)), val(std::move(lhs.val))
    {
        if (!enableMsg)
        {
            return;
        }
        char msg[512];
        sprintf(msg, "ITEM(ITEM &lhs) Lvalue constructor(%s %d)", name.c_str(), val);
        cout << msg << endl;
    }
    ITEM(ITEM &&rhs) : name(std::move(rhs.name)), val(std::move(rhs.val))
    {
        if (!enableMsg)
        {
            return;
        }
        char msg[512];
        sprintf(msg, "ITEM(ITEM &&rhs) Rvalue constructor(%s %d)", name.c_str(), val);
        cout << msg << endl;
    }
    ~ITEM()
    {
        if (!enableMsg)
        {
            return;
        }
        char msg[512];
        sprintf(msg, "~ITEM() destructor (%s %d)", name.c_str(), val);
        cout << msg << endl;
    }
    // ITEM &operator=(const ITEM &other) = default;
    string name;
    int val;
};

void printItemVector(std::vector<ITEM> itemVector)
{
    for (auto v : itemVector)
    {
        cout << v.name << ", " << v.val << endl;
    }
}
void printItemList(std::list<ITEM> itemList)
{
    for (auto v : itemList)
    {
        cout << v.name << ", " << v.val << endl;
    }
}

// push_back(), emplace_back() 은 인자가
// lvalue reference 인 경우 copy 된다.
// rvalue reference 인 경우 move 된다.
// 하지만 emplace_back 는 임시 생성없이 벡터내에 바로에 바로 생성할 수 있다.
int main()
{
    cout << "---using vector push_back()---" << endl;
    std::vector<ITEM> vec1;
    ITEM item1{"apple", 100};
    vec1.push_back(item1); // Lvalue 인자
    ITEM item2{"banana", 200};
    vec1.push_back(std::move(item2)); // Rvalue 인자

    vec1.clear();
    cout << endl;
    cout << "---vec1 was cleared---" << endl;
    // 임시 item 객체 생성 -> Rvalue 복사 생성자로 vector 에 추가(복사) -> 임시 item 객체 삭제
    vec1.push_back({"lemon", 300});
    vec1.push_back({"orange", 400});

    cout << endl
         << endl;
    cout << "---using vector emplace_back()---" << endl;
    std::vector<ITEM> vec2;
    ITEM item3{"apple", 100};
    vec2.emplace_back(item3); // Lvalue 인자
    ITEM item4{"banana", 200};
    vec2.emplace_back(std::move(item4)); // Rvalue 인자

    vec2.clear();
    cout << endl;
    cout << "---vec2 was cleared---" << endl;
    // vector 내에 item 이 생성되고 생성된 item 에 값을 설정하기 때문에 임시 item 객체를 생성하지 않아도 된다.
    vec2.emplace_back("lemon", 300);
    vec2.emplace_back("orange", 400);

    cout << endl
         << endl;

    enableMsg = false;
    cout << "---print vec1---" << endl;
    printItemVector(vec1);
    cout << "---print vec2---" << endl;
    printItemVector(vec2);

    return 0;
}
