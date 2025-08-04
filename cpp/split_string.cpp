// ysoftman
// split string test

#include <iostream>
#include <sstream>  // istringstream
#include <string>
#include <vector>

using namespace std;

void printVecStr(vector<string> &vs) {
    vector<string>::iterator iter;
    for (iter = vs.begin(); iter != vs.end(); ++iter) {
        cout << iter->c_str() << endl;
    }
}

int main() {
    string str = "lemon apple orange";

    // 방법1
    // 공백 구분해서 벡터로 담기
    cout << "[method1]" << endl;
    istringstream  iss(str);
    vector<string> vecStr((istream_iterator<string>(iss)), (istream_iterator<string>()));
    printVecStr(vecStr);

    // 방법2
    // iss 스트림이 모두 소비되서 새로 만들어야 한다.
    // getline 세번째 파라미터로 구분자 , 를 사용할 수 있다.(기본은 값은 \n)
    cout << "[method2]" << endl;
    istringstream iss2(str);
    string        out;
    while (getline(iss2, out, ' ')) {
        cout << out << endl;
    }

    // 방법3
    // 구분자를 찾을때마다 substr 로 자르고 원본 스트링을 지워나간다.
    cout << "[method3]" << endl;
    string sep = " ";
    size_t pos = 0;
    while ((pos = str.find(sep)) != string::npos) {
        out = str.substr(0, pos);
        cout << out << endl;
        str.erase(0, pos + sep.length());
    }
    cout << str << endl;

    return 0;
}
