// g++ -std=c++11 ./emplacement_map.cpp && ./a.out
#include <iostream>
#include <map>

using std::cout;
using std::endl;
using std::string;

class ITEM
{
public:
    ITEM()
    {
        cout << "ITEM() default constructor" << endl;
    }
    ITEM(string n, int v)
    {
        cout << "ITEM(string n, int v) copy constructor" << endl;
        name = n;
        val = v;
    }
    ~ITEM()
    {
        cout << "~ITEM() destructor" << endl;
    }
    string name;
    int val;
};

void printItemMap(std::map<int, ITEM> itemMap)
{
    for (auto v : itemMap)
    {
        cout << v.first << ", " << v.second.name << endl;
    }
}
int main()
{
    cout << "----- using map emplace_back() -----" << endl;
    std::map<int, ITEM> m;
    m.emplace(123, ITEM("lemon", 111));
    printItemMap(m);
    // 참고로 map insert,emplace 는 key 가 존재하지 않을때만 추가된다.
    // m.insert(std::pair<int, ITEM>(123, ITEM("apple", 222)));
    // m.insert(std::make_pair(123, ITEM("orange", 333)));
    // [] = 로 overwirte 할 수 있다.
    // [] = 는 빈객체 생성(때문에 파라메터 없는 기본 ITEM() 생성자가 필요)하고 banana 아이템객체를 복사한다.
    m[123] = ITEM("banana", 555);
    printItemMap(m);
    return 0;
}
