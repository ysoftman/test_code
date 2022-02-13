// g++ -std=c++11 ./emplacement.cpp && ./a.out
#include <iostream>
#include <vector>
#include <list>
#include <map>

using std::cout;
using std::endl;
using std::string;

class ITEM
{
public:
    ITEM()
    {
    }
    ITEM(string n, int v)
    {
        name = n;
        val = v;
    }
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
void printItemMap(std::map<int, ITEM> itemMap)
{
    for (auto v : itemMap)
    {
        cout << v.first << ", " << v.second.name << endl;
    }
}
int main()
{
    std::vector<ITEM> vec1;
    // item 객체 생성 -> vector 에 복사 -> item 객체 삭제
    vec1.push_back(ITEM("lemon", 100));
    printItemVector(vec1);

    std::vector<ITEM> vec2;
    // emplace 를 사용하면 vector 에 바로 추가된다. 별도 객체 생성,삭제 비용을 피할 수 있다.
    vec2.emplace_back("lemon", 100);
    printItemVector(vec2);

    std::list<ITEM> list;
    list.emplace_back("lemon", 100);
    list.emplace_front("apple", 200);
    printItemList(list);

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
