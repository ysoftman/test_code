// ysoftman
// thread test

use std::thread;
use std::time::Duration;

fn main() {
    // spawn 으로 새로운 쓰레드만들어 클로저 로직을 수행한다.
    let th1 = thread::spawn(|| {
        for i in 1..10 {
            println!("th1 - spawned thread! {}", i);
            thread::sleep(Duration::from_millis(1));
        }
    });

    // th1 쓰레드가 종료될때까지 기다린다.(현재 쓰레드는 이곳에서 block 된다.)
    th1.join().unwrap();

    // 프로그램 메인 쓰레드
    // 메인 쓰레드가 종료(프로그램 종료)되면 spawned 쓰레드들은 종료된다.
    for i in 1..5 {
        println!("main thread! {}", i);
        thread::sleep(Duration::from_millis(1));
    }

    // th1 쓰레드가 종료될때까지 기다린다.(현재 쓰레드는 이곳에서 block 된다.)
    // th1.join().unwrap();

    let v1 = vec![1, 2, 3];
    // v1 의 참조자 유효할것인지 모르기 때문에 move 로 v1 의 소유권을 th2 로 강제로 이동시킨다.
    let th2 = thread::spawn(move || {
        println!("th2 - spawned thread! v1 {:?}", v1);
    });
    // v1 소유권이 th2로 이동되어 메인쓰레드에선 v를 drop 할 수 없다.
    // drop(v);
    th2.join().unwrap();
}
