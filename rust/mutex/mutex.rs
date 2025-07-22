// ysoftman
// mutex test
// use std::rc::Rc;
use std::sync::Arc;
use std::sync::Mutex;
use std::thread;

fn main() {
    // mutex 객체 생성, 초기값으로 i32 10 을 설정한다.
    let mtx = Mutex::new(10);
    {
        // mutex 객체에 접근하기 위해 락을 얻어야 한다.
        // 락을 얻을때까지는 블럭된다.
        // lock() 은 MutexGuard 스마트 포인터를 리턴하고
        let mut num = mtx.lock().unwrap();
        // 스마트 포인터 내부 값을 6으로 변경한다.
        *num = 17;
    }
    println!("mtx = {mtx:?}");

    mutex_test1();
}

fn mutex_test1() {
    // let counter = Mutex::new(0);
    // 쓰레드간 뮤텍스 공유를 하려면 Arc(Atomic Reference Counting)를 사용해야 한다.
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];
    // 쓰레드 10개를 생성하고 각 쓰레드는 mutex 값을 1씩 증가시킨다.
    for th_num in 0..10 {
        // 싱글 쓰레드내에서는 Rc 로 클론해 복수의 소유권을 갖을 수 있지만
        // let counter = Rc::clone(&counter);
        // 멀티 쓰레드 환경에서는 Rc 대신 Arc 을 사용해야 한다.
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            // 이전 루프의 쓰레드로 counter 뮤텍스의 소유권이 이동되었고
            // 다음 루프의 쓰레드로 counter 뮤텍스의 소유권이 이동될 수 없다.(컴파일 에러)
            // 하지만 위에서 Arc 를 사용하면 된다.
            let mut num = counter.lock().unwrap();
            *num += 1;
            println!("thread {}  - num : {}", th_num, *num);
        });
        handles.push(handle)
    }

    // 모든 쓰레드들이 작업 종료까지 기다린다.
    for handle in handles {
        handle.join().unwrap();
    }
    println!("counter {}", *counter.lock().unwrap());
}
