// ysoftman
// std thread test
// g++ -std=c++11 std_thread.cpp && ./a.out
#include <chrono>
#include <iostream>
#include <thread>

using std::cout;
using std::endl;

void func_thread1() {
    for (int i = 0; i < 5; i++) {
        // std::this_thread::sleep_for(500ms); // since c++14
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "thread1) std::this_thread::get_id()" << std::this_thread::get_id() << "  " << i
             << endl;
    }
}

void func_thread2() {
    for (int i = 0; i < 5; i++) {
        // using namespace std::chrono_literals; // s, ms // since c++14
        // std::this_thread::sleep_for(500ms); // since c++14
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        cout << "thread2) std::this_thread::get_id()" << std::this_thread::get_id() << "  " << i
             << endl;
    }
}

int main() {
    std::thread th1(func_thread1);
    std::thread th2(func_thread2);

    cout << "th1.get_id():" << th1.get_id() << endl;
    cout << "th2.get_id():" << th2.get_id() << endl;
    cout << "main thread) std::this_thread::get_id() " << std::this_thread::get_id() << endl;

    // th1 이 완료될때까지 대기
    th1.join();
    // th2 이 완료될때까지 대기
    th2.join();

    cout << "main thread) std::this_thread::get_id() " << std::this_thread::get_id()
         << "  all threads done" << endl;
    return 0;
}
