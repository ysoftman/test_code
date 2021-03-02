// ysoftman
// channel test
// 동시성(concurrency) 보장을 위해 메시지 패싱(message passing)기법을 사용하는데
// 이를 위해 rust 에서는 channel 을 사용한다.(golang 도 채널 chan 을 사용한다.)
use std::sync::mpsc;
use std::thread;
use std::time::Duration;
fn main() {
    // 채널을 생성하면 송신자, 수신자의 튜플(쌍)으로 리턴된다.
    // mpsc(multiple producer, single consumer) 표준 라이브러리는
    // 여러개의 송신자가 있을 수 있지만 이를 소비하는 수신자는 하나라는 개념이다.
    let (tx, rx) = mpsc::channel();

    // tx(송신자) 의 소유권을 가진 쓰레드가
    thread::spawn(move || {
        let val = String::from("orange");
        // 송신자로 데이터를 보낸다.
        tx.send(val).unwrap();
        // send 된 값은 사용하면 안된다.(컴파일 에러)
        // println!("vals : {:?}", vals);
    });

    // rx.recv()는 메시지를 받을때까지 블록된다.(기다린다.)
    let received = rx.recv().unwrap();
    println!("main thread received {}", received);

    channtest1();
}

fn channtest1() {
    let (tx, rx) = mpsc::channel();
    // mpsc 개념으로 송신자를 여러개 만들 수 있다.
    // tx 가 thread 로 move 되기전에 클론해둬야 한다.
    let tx2 = mpsc::Sender::clone(&tx);

    thread::spawn(move || {
        let vals = vec![
            String::from("orange"),
            String::from("lemon"),
            String::from("plum"),
        ];
        for v in vals {
            tx.send(v).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    thread::spawn(move || {
        let vals = vec![
            String::from("cola"),
            String::from("cider"),
            String::from("water"),
            String::from("milk"),
            String::from("juice"),
        ];
        for v in vals {
            // tx2 송신자를 통해 보낸다.
            tx2.send(v).unwrap();
            thread::sleep(Duration::from_secs(1));
        }
    });

    // 위 2개의 송신 쓰레드로 부터 수신
    // 수신자를 반복자를 사용해 받을 수 있다.
    for received in rx {
        println!("received {}", received);
    }
}
