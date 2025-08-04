// ysoftman
// const_iterator test
#include <iostream>
#include <map>

using namespace std;

class myinfo {
   public:
    map<string, string> _info_map;

    void                setinfomap(const string& key, const string& value) { _info_map[key] = value; }

    void                getmyinfo(string target) const {
        // 값을 변경할 수 없는 const 형식의 함수에서는 const_iterator 를 사용해야 한다.
        map<string, string>::const_iterator citer;
        citer = _info_map.find(target);
        if (citer != _info_map.end()) {
            cout << citer->first << "=" << citer->second << endl;
        } else {
            cout << target << "=not found" << endl;
        }
    }
};

int main() {
    map<string, string> mymap;
    mymap["aaa"] = "bbb";
    map<string, string>::iterator iter;
    // 일반적인 경우 iterator 로 find 결과를 리턴 받음.
    iter = mymap.find("aaa");
    if (iter != mymap.end()) {
        cout << iter->first << "=" << iter->second << endl;
    }

    myinfo       mi;
    const string k = "111";
    const string v = "222";
    mi.setinfomap(k, v);
    mi.getmyinfo("000");
    mi.getmyinfo("111");

    return 0;
}
