// ysoftman
// istreambuf_iterator 파일내용 스트링으로 담기

#include <iostream>
#include <string>
#include <fstream> // ifstream, istreambuf_iterator

using namespace std;

int main()
{
    cout << "load file (" << __FILE__ << ") into string" << endl;

    // 현재 파일을 스트림으로 연다
    ifstream f(__FILE__);
    // 파일 스트림의 처음부터 끝까지 읽어 str 로 넣는다.
    string str((istreambuf_iterator<char>(f)), (istreambuf_iterator<char>()));

    cout << str << endl;
    return 0;
}
