#include <stdio.h>

#include <algorithm>  // lower_bound, upper_bound
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int target = 3;
    // vector<int> v(3);
    // v = {1,2,3};
    vector<int> v{8, 2, 5, 6, 3, 4, 1, 0, 4, 1, 10};
    sort(v.begin(), v.end());
    for (auto i : v) {
        printf("%d  ", i);
    }
    printf("\ntarget --> %d\n", target);

    // target 보다 작은 마지막 위치
    // vector<int>::iterator iter_lower = lower_bound(v.begin(), v.end(), target);
    auto iter_lower = lower_bound(v.begin(), v.end(), target);
    // target 보다 커지는 첫번째 위치
    // vector<int>::iterator iter_upper = upper_bound(v.begin(), v.end(), target);
    auto iter_upper = upper_bound(v.begin(), v.end(), target);
    printf("lower bound position: %ld\n", (iter_lower - v.begin()));
    printf("upper bound position: %ld\n", (iter_upper - v.begin()));
    printf("lower bound value: %d\n", *iter_lower);
    printf("upper bound value: %d\n", *iter_upper);

    return 0;
}