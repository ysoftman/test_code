// ysoftman
// smart pointer test
// 스마트 포인터는 대상 자원이 더이상 사용되지 않으면 자동으로 메모리 해제(delete)한다.
// 스마트 포인터를 생성하면 rc(reference counter), wrc(weak reference counter)등을 관리하는 control
// block 이 생긴다.
#include <iostream>
#include <memory>  // unique_ptr, shared_ptr, weak_ptr (since c++ 11)
#include <string>
using namespace std;

void unique_pointer_test() {
    cout << "[unique_ptr test]" << endl;
    std::unique_ptr<string> up1 = std::make_unique<string>("ysoftman");
    cout << "up1:" << *up1 << endl;

    // unique_ptr 는 포인팅 되는 대상에 대한 소유권은 공유할 수 없다.
    // std::unique_ptr<string> up2 = up1;
    // move 를 통해 up1 -> up2 로 소유권을 이전할 수 있다.
    std::unique_ptr<string> up2 = std::move(up1);
    cout << "up2:" << *up2 << endl;
}

void shared_pointer_test() {
    cout << "[shared_ptr test]" << endl;
    std::shared_ptr<string> sp1 = std::make_shared<string>("ysoftman");
    // shared_ptr 는 소유권을 공유 할 수 있다.
    // 소유권이 공유되면 rc(reference counter) 가 증가되며, rc 가 0 되면 포인팅 되는 대상 메모리
    // 해제
    std::shared_ptr<string> sp2 = sp1;
    cout << "sp1:" << *sp1 << " rc:" << sp1.use_count() << endl;
    cout << "sp2:" << *sp2 << " rc:" << sp2.use_count() << endl;
    // sp1 소유권 해제
    sp1.reset();
    cout << "sp2:" << *sp2 << " rc:" << sp2.use_count() << endl;
}

void weak_pointer_test() {
    cout << "[weak_ptr test]" << endl;
    std::shared_ptr<string> sp1 = std::make_shared<string>("ysoftman");
    // weak_ptr 는 shared_ptr 를 참조 하는데, 메모리 해제를 관여하는 rc 는 증가시키지는 않고
    // wrc(weak reference counter)만 증가시킨다. 2개의 shared_ptr 가 서로를 참조하는 순환 참조를
    // 해야 될때, rc 는 0이 될 수 없어 메모리가 해제되지 않기 때문에, 이 경우 weak_ptr 를 사용한다.
    std::weak_ptr<string> wp1 = sp1;
    cout << "sp1:" << *sp1 << " rc:" << sp1.use_count() << endl;
    // weak_ptr 는 lock() 으로 shared_ptr 생성을 통해서만 대상의 값을 알 수 있다.
    auto sp2 = wp1.lock();
    cout << "sp1:" << *sp1 << " rc:" << sp1.use_count() << endl;
    cout << "sp2:" << *sp2 << " rc:" << sp2.use_count() << endl;
    sp2.reset();
    cout << "sp1:" << *sp1 << " rc:" << sp1.use_count() << endl;
    sp1.reset();
    // rc 가 0 이 되면 weak ptr 는 만료되어 더이상 사용할 수 없다.
    if (wp1.expired()) {
        cout << "wp1 has expired" << endl;
    }
    // use_count() 는 shared_ptr 의 현재 rc 값만 리턴한다. (wrc 아님)
    cout << "wp1 rc: " << wp1.use_count() << endl;
}

int main() {
    unique_pointer_test();
    shared_pointer_test();
    weak_pointer_test();
    return 0;
}
