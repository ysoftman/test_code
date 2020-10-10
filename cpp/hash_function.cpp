// ysoftman
// c++11 hash function test
#include <iostream>

using namespace std;

int main()
{
    std::hash<string> hfn;
    cout << "hash function " << hfn("ysoftman") << endl;

    std::size_t hash_value = std::hash<string>{}("ysoftman");
    cout << "hash function " << hash_value << endl;

    hash_value = std::hash<int>{}(123);
    cout << "hash function " << hash_value << endl;

    hash_value = std::hash<char>{}('a');
    cout << "hash function " << hash_value << endl;

    hash_value = std::hash<float>{}(123.123);
    cout << "hash function " << hash_value << endl;

    hash_value = std::hash<double>{}(123.123);
    cout << "hash function " << hash_value << endl;
    return 0;
}
