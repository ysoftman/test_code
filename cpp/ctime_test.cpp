// ysoftman
// ctime test
#include <unistd.h>  // for sleep()

#include <ctime>
#include <iostream>
#include <string>

using namespace std;

int main() {
    // clock() 은 microseconds CLOCKS_PER_SEC(1000000)를 리턴한다.
    clock_t start_clock = clock();
    cout << "CLOCKS_PER_SEC : " << CLOCKS_PER_SEC << endl;
    cout << "start_clock " << start_clock << endl;
    for (int i = 0; i < 1000000000; i++) {
    }
    // sleep systemcall 로
    // sleep 한 시간동안은 clock count 가 되지 않는다.
    // sleep(1);
    clock_t end_clock = clock();
    cout << "end_clock " << clock() << endl;
    cout << "elapsed (sec) " << double(end_clock - start_clock) / CLOCKS_PER_SEC << endl;

    return 0;
}
