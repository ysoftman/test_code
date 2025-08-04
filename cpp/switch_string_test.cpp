// ysoftman
#include <stdio.h>

#include <iostream>
#include <string>  // string, hash<>

int main() {
    // 문자 하는 integer 로 표현되서 switch 사용할 수 있다.
    // a == 97
    char c = 'a';
    switch (c) {
        case 'a':
            printf("case a\n");
            break;
        case 'b':
            printf("case b\n");
            break;
        default:
            printf("case default\n");
            break;
    }

    // switch 는 문자열을 허용하지 않는다.
    // 그래서 쓰고 싶다면 hash 값을 정수로 변경해서 써야 한다.
    std::string            str = "a";
    std::hash<std::string> hash_fn;
    size_t                 sz = hash_fn(str);
    std::cout << sz << std::endl;
    switch (sz) {
        case 2603192927274642682:
            printf("case a(2603192927274642682)\n");
            break;
        case 999:
            printf("case 999\n");
            break;
        default:
            printf("case default\n");
            break;
    }
    return 0;
}
