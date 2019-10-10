// ysoftman
// stl sort test
#include <iostream>
#include <algorithm>  // sort()

using namespace std;

int main()
{
    int arr[] = {3, 5, 10, 1, 7, 2, 20, 17};
    // 배열 길이 파악
    int length = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < length; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    std::sort(arr, arr + length);
    for (int i = 0; i < length; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    // reverse sort
    std::sort(arr, arr + length, std::greater<int>());
    for (int i = 0; i < length; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}