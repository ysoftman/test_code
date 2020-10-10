// ysoftman
// memmove test
#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "memmove() test" << endl;
    char str1[] = "abcdefg";
    cout << "str1 = " << str1 << "  length " << sizeof(str1) << endl;
    // str1+1위치(b)에, str1+3위치에(d)서 2크기글자를(de) 이동(덮어쓴다)한다.
    memmove(str1 + 1, str1 + 3, 2);
    cout << "str1 = " << str1 << "  length " << sizeof(str1) << endl;

    char str2[] = "abcdefg";
    cout << "str2 = " << str2 << "  length " << sizeof(str2) << endl;
    // str2+1위치(b)에, str2+3위치에(d)서 5크기글자를(defgs널) 이동(덮어쓴다)한다.
    // str2 크기를 넘어가지 않도록 조심해야 한다.
    // 5크기를 하면 널이 포함되어 adefg 로 표시된다.
    memmove(str2 + 1, str2 + 3, 5);
    cout << "str2 = " << str2 << "  length " << sizeof(str2) << endl;

    return 0;
}