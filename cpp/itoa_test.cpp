// ysoftman
// itoa() 만들기
#include <stdio.h>

int main() {
    int  Value      = 1037626467;

    char Result[20] = {
        0,
    };
    char Temp[20] = {
        0,
    };

    int i = 0;
    int j = 0;
    while (Value / (int)10 > 0) {
        // 10 으로 나눈 나머지를 기록
        // 기록할때 ASCII 코드 값으로 표현한기 위해서 0(48) 값을 더해서 저장한다.
        Temp[i] = (Value % (int)10) + '0';
        i++;
        // 10으로 나눠 자리 수를 줄여나간다.
        Value = Value / (int)10;
    }

    // 한자리 수는 그래도 기록한다.
    Temp[i] = Value + '0';

    // 기록된 내용을 거꾸로 저장한다.
    for (; i >= 0; i--) {
        Result[j] = Temp[i];
        j++;
    }

    Result[j] = '\0';

    fprintf(stdout, "result = %s\n", Result);

    return 0;
}
