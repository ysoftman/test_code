// ysoftman
// map find test
#include <iostream>
#include <map>
#include <string>

using namespace std;

void FindInMap(std::map<string, int> &mapTemp, string key) {
    cout << "map size : " << mapTemp.size() << endl;
    if (mapTemp.find(key) == mapTemp.end()) {
        cout << "can't find the " << key << endl;
    } else {
        cout << "found the " << key << endl;
    }
}

int main() {
    std::map<string, int> mapTemp;

    FindInMap(mapTemp, "lemon");
    mapTemp["lemon"] = 999;
    FindInMap(mapTemp, "lemon");
    FindInMap(mapTemp, "");

    return 0;
}
