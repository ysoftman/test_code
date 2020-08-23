
// ysoftman
// 자리수 숫자 파싱
#include <stdio.h>
#include <vector>

using namespace std;

void parseDigitNumber(int n)
{
    printf("n = %d\n", n);
    vector<int> vec;
    while (n >= 1)
    {
        vec.push_back(n % 10);
        n /= 10;
    }
    vector<int>::reverse_iterator iter;
    for (iter = vec.rbegin(); iter != vec.rend(); ++iter)
    {
        printf("%d ", *iter);
    }
    printf("  digit cnt(%ld)\n", vec.size());
}

int main()
{
    parseDigitNumber(228);
    parseDigitNumber(1230560);
    parseDigitNumber(78984568);
    return 0;
}
