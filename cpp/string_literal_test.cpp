// ysoftman
// string literal test
// gcc 빌드 참고
// gcc .c 파일은 c 로, .cpp 파일은 c++ 으로 빌드한다.
// -x <language> 옵션으로 강제로 언어를 설정할 수 있다.
// gcc -x c string_literal_test.cpp && ./a.out
// gcc -x c++ string_literal_test.c && ./a.out

#include <stdio.h>

int main() {
    // char *str = "ysoftman";
    // c++ 로 빌드시 스트링 리터럴을 시 char* 타입으로 선언하면 다음과 같은 경고가 발생한다.
    // warning: conversion from string literal to 'char *' is deprecated
    // [-Wc++11-compat-deprecated-writable-strings] c 에서는 문자열(string literal)은 char*
    // 타입이지만 c++  에서는 const char* 타입이다.
    // https://en.cppreference.com/w/cpp/language/string_literal 그래서 const char* 타입을
    // 사용해야한다.
    const char *str = "ysoftman";
    printf("%s\n", str);
    return 0;
}
