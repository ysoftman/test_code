// ysoftman
// prime factorization (소인수 분해)
#include <stdio.h>

#include <iostream>
#include <vector>

using namespace std;

// 소인수 분해하기
void prime_factorization(int num, vector<int> &result) {
    if (num < 2) {
        printf("Wrong Number...\n");
        exit(1);
    }

    int divisor = 2;
    // int remainder = 0;
    int quotient = num;
    while (quotient != 1) {
        if (quotient % divisor == 0) {
            quotient = quotient / divisor;
            result.push_back(divisor);
        } else {
            ++divisor;
        }
    }
}

int main() {
    int num = 0;

    printf("Input Number : ");
    scanf("%d", &num);

    vector<int> result;
    vector<int>::iterator iter;
    prime_factorization(num, result);
    for (iter = result.begin(); iter != result.end(); ++iter) {
        cout << *iter << endl;
    }

    return 0;
}
