#include <limits.h>
#include <stdio.h>

// https://www.in-ulm.de/~mascheck/various/argmax/
// getconf 명령으로 확인할 수 있다.
// getconf ARG_MAX
int main() {
    printf("argsmax: %d\n", ARG_MAX);
    return 0;
}
