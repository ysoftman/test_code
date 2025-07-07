// https://github.com/fmtlib/fmt 이 c++ 20 (fmt), c++ 23(print) 정식으로 추가됨
// c++20 std::format https://en.cppreference.com/w/cpp/utility/format.html
// c++23 std::print https://en.cppreference.com/w/cpp/io/print.html
// cout(ostream), 심지어 printf 보다도 빠르다.
//
// g++ -std=c++23 ./fmt_print.cpp && ./a.out
#include <format>
#include <print>

int main() {
    std::string str_fmt =
        std::format("{} is yellow, {} is red", "lemon", "apple");
    std::println("I have fruits, {}", str_fmt);
    std::println("{1} {2} {0}", "first", "second", "third");
    return 0;
}
