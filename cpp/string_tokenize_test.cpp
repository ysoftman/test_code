// ysoftman
// 문자열 토큰나이즈
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// str				파싱할 문자열
// tokens			토큰을 담을 벡터
// delimiter			구분자
void StringTokenize(string str, vector<string> &tokens, string delimiter) {
    // 처음 구분자가 있을경우을 대비해서
    // find_first_not_of 는 offset 부터 구분자가 아닌 문자가 처음 나온 곳을 찾는다.
    string::size_type frompos = str.find_first_not_of(delimiter, 0);
    string::size_type topos   = str.find_first_of(delimiter, frompos);
    while (topos != string::npos) {
        // substr(offset, count)
        tokens.push_back(str.substr(frompos, topos - frompos));
        frompos = str.find_first_not_of(delimiter, topos);
        topos   = str.find_first_of(delimiter, frompos);
    }
    // 마지막에 구분자가 없을때는 현재까지의 frompos 부터 끝까지를 하나의 토큰을 본다.
    if (frompos != string::npos) {
        tokens.push_back(str.substr(frompos, topos - frompos));
    }
}

int main() {
    string strTest = "가나,다라마바,사아자,차카타파,하";
    cout << strTest << endl;
    vector<string>           vecTokens;
    vector<string>::iterator iter;
    StringTokenize(strTest, vecTokens, ",");
    for (iter = vecTokens.begin(); iter != vecTokens.end(); ++iter) {
        cout << (*iter).c_str() << endl;
    }

    // string find 테스트
    string aa = "yoon\nbyoung\nhoon\n";
    cout << "aa = " << aa << endl;
    if (aa.find("\n") == string::npos) {
        cout << "not found" << endl;
    } else {
        cout << "found  " << endl;
    }
    return 0;
}
