// ysoftman
// stringsubstr test

#include <iostream>
#include <string>

using namespace std;

int main()
{
    std::string str = "lemon,orange,banana";
    cout << str << endl;

    string::size_type pos = str.find("lemon");
    if (pos == string::npos)
        return -1;
    cout << "find lemon pos : " << pos << endl;
    cout << str.substr(pos, sizeof("lemon") - 1) << endl;

    pos = str.find("orange");
    if (pos == string::npos)
        return -1;
    cout << "find orange pos : " << pos << endl;
    cout << str.substr(pos, sizeof("orange") - 1) << endl;

    pos = str.find("banana");
    if (pos == string::npos)
        return -1;
    cout << "find banana pos : " << pos << endl;
    cout << str.substr(pos, sizeof("banana") - 1) << endl;
    // 마지막까지 substr 할 경우 시작 위치만 정해주면 된다.
    cout << str.substr(pos) << endl;

    // string::size_type 는 unsignet int 로 음수면 오버플로우가 발생해 양수 큰값으로 설정된다.
    string::size_type p = -1;
    cout << p << endl;
    // static const size_type npos = -1; 로 설정되어 있다.
    cout << string::npos << endl;

    return 0;
}