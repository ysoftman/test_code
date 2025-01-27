// ysoftman
// stl sort test
// g++ -std=c++11 std_sort.cpp && ./a.out
#include <algorithm>  // sort()
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int arr[] = {3, 5, 10, 1, 7, 2, 20, 17};
    // 배열 길이 파악
    int length = sizeof(arr) / sizeof(arr[0]);
    cout << "array = ";
    for (int i = 0; i < length; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "sort array = ";
    std::sort(arr, arr + length);
    for (int i = 0; i < length; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "reverse sort array = ";
    std::sort(arr, arr + length, std::greater<int>());
    for (int i = 0; i < length; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "----------" << endl;

    cout << "vector = ";
    vector<int> v{3, 6, 1, 54, 7, 2, 56, 284};
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;

    cout << "sort (0 ~ 5 element) in vector = ";
    std::sort(v.begin(), v.begin() + 5);
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;

    cout << "sort vector = ";
    std::sort(v.begin(), v.end());
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;

    cout << "reverse sort vector = ";
    std::sort(v.begin(), v.end(), std::greater<int>());
    for (auto i : v) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
