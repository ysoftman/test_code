// ysoftman
// Calculate Factorial
// Factorial Number Range : 0 ~ 16
#include <stdio.h>

// Using Recursive Function To Get Factorial.
int fact_recursive(int input) {
    // 0! = 1 and 1! = 1
    if (input < 1) {
        return 1;
    }
    return input * fact_recursive(input - 1);
}

// Using Iteration Function To Get Factorial.
int fact_iteration(int input) {
    int output = 1;
    while (input > 1) {
        output *= input;
        input--;
    }
    return output;
}

int main() {
    unsigned int result = 0;
    unsigned int in_number = 0;
    printf("[Factorial]Input Number : ");
    scanf("%d", &in_number);
    result = fact_recursive(in_number);
    printf("recursive method %d! = %d\n", in_number, result);
    result = fact_iteration(in_number);
    printf("iteration method %d! = %d\n", in_number, result);

    return 0;
}
