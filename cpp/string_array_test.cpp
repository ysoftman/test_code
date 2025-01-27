// ysoftman
// string array test
#include <stdio.h>

#include <string>

void eval_string(const std::string& inputstr) { printf("inputstr = %s\n", inputstr.c_str()); }

int main() {
    std::string str = "ABC";
    printf("str.c_str() = %s\n", str.c_str());
    printf("&str[0] = %s\n", &str[0]);
    eval_string(str);
    // const 타입으로 전달하기 위해
    eval_string(&str[0]);

    return 0;
}
