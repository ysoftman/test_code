#include <stdio.h>
#include <string.h>

void print_binary_digit(int num)
{
    const int max_length = 10;
    int temp = num;
    int d[max_length], idx = 0;
    memset(d, 0, sizeof(int) * max_length);

    while (temp > 0)
    {
        d[idx++] = temp % 2;
        temp /= 2;
    }
    d[idx++] = temp;

    for (int i = (max_length - 1); i >= 0; i--)
    {
        printf("%d", d[i]);
    }
    printf("\n");
}

int main()
{
    int a = 100, b = 128;
    printf("a: %d, b: %d\n", a, b);
    printf("not operator ~a: %d\n", ~a);
    printf("not not operator ~~a: %d\n", ~~a);
    printf("(-) -> (+) using not operator ~a+1: %d\n", ~a+1);
    printf("(+) -> (-) using not operator ~(~a+1)+1: %d\n", ~(~a+1)+1);
    int temp = a & b;
    printf("a&b: %d\n", temp);
    temp = a | b;
    printf("a|b: %d\n", temp);

    printf("a=>: ");
    print_binary_digit(a);
    printf("b=>: ");
    print_binary_digit(b);

    printf("b>>1:");
    print_binary_digit(b >> 1);
    printf("b>>2:");
    print_binary_digit(b >> 2);
    printf("b<<1:");
    print_binary_digit(b << 1);

    // max_length overflow
    // printf("b<<2:");
    // print_binary_digit(b << 2);

    return 0;
}
