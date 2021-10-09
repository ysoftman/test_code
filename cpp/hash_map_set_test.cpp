// ysoftman
// hash map test
// map 은 보통 binary tree(red-black tree) 값을 정렬해 저장해 접근(insert,delete)시간복잡도는 O(logN)이 된다.
// hashmap 은 hashtable 로 값을 O(1) 로 접근하지만 정렬은 하지 않는다.
// c++11 부터 unordered_map 이름으로 hashmap 사용할 수 있다.
// unordered_set, unordered_multiset 도 있다.
// g++ -std=c++11 hash_map_test.cpp && ./a.out
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main()
{
    // 정렬되지만 O(logN) hashmap 에 비해 느리다.
    map<int, int> map;
    map[3] = 3;
    map[2] = 2;
    map[5] = 5;
    map[4] = 4;
    map[0] = 0;
    for (auto i : map)
    {
        cout << i.first << endl;
    }

    cout << "-----" << endl;

    // unordered_map 정렬되지 않지만 O(1) 로 빠르다.
    unordered_map<int, int> hashmap;
    hashmap[3] = 3;
    hashmap[2] = 2;
    hashmap[5] = 5;
    hashmap[4] = 4;
    hashmap[0] = 0;
    cout << "hashmap" << endl;
    // 정렬되지 않기 때문에 무작위로 순서로 출력된다.
    for (auto i : hashmap)
    {
        cout << i.first << endl;
    }
    if (hashmap.find(3) != hashmap.end())
    {
        cout << "hashmap found: 3->" << hashmap[3] << endl;
    }

    cout << "-----" << endl;

    // unordered_set
    unordered_set<string> hashset;
    hashset.insert("1.lemon");
    hashset.insert("2.apple");
    hashset.insert("3.orange");
    hashset.insert("3.orange"); // 중복값은 하나로 취급한다.
    cout << "hashset" << endl;
    // 정렬되지 않기 때문에 무작위로 순서로 출력된다.
    for (auto i : hashset)
    {
        cout << i << endl;
    }
    if (hashset.find("2.apple") != hashset.end())
    {
        cout << "hashset found: "
             << "2.apple" << endl;
    }

    // unordered_multiset
    cout << "-----" << endl;
    unordered_multiset<string> hashmset;
    hashmset.insert("lemon");
    hashmset.insert("orange");
    hashmset.insert("apple");
    hashmset.insert("lemon"); // 중복값된 값을 추가할 수 있다.
    hashmset.insert("apple");
    hashmset.insert("lemon");
    for (auto i : hashmset)
    {
        cout << i << endl;
    }
    if (hashmset.find("lemon") != hashmset.end())
    {
        cout << "hashmset found: lemon" << endl;
    }
    return 0;
}
