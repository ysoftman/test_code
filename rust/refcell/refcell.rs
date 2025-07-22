// ysoftman
// refcell test

// Refcell<T> 는 가변 빌림을 허용해 불변이라도 내부값을 변경할 수 있다.(내부 가변성 패턴)
// 컴파일러의 빌림검사기는 메소등의 내부에서는 내부 가변성을 허용하고, 런타임시에 검사한다.
// rc, refcell 모두 단일 쓰레드내에서만 가능하다.
// rc 는 여러개의 소유자가 있을 수 있지만 box, refcell 은 단일 소유자만 갖는다.

use std::cell::RefCell;

fn main() {
    // let x = 5;
    // 불변 x 를 가변 참조할 수 없다.
    // let y = &mut x;

    let mock_messenger = MockMessenger::new();
    let mut limit_tracker = LimitTracker::new(&mock_messenger, 100);
    limit_tracker.set_value(80);
    // Messenger 의 send(&self) 불변 참조를 사용하라면
    // assert_eq!(mock_messenger.sent_message.len(), 2);
    // RefCell 의 borrow()를 사용해야 한다.
    assert_eq!(mock_messenger.sent_message.borrow().len(), 2);
    println!("{mock_messenger:?}");
}

trait Messenger {
    fn send(&self, msg: &str);
}
struct LimitTracker<'a, T: 'a + Messenger> {
    messenger: &'a T,
    value: usize,
    max: usize,
}
//예전에는 'a 같은 라이프타임 annotation 은 명시적으로 자주 썼지만 지금은 Rust가 대부분 자동으로 추론하기 때문에 생략해도 됨.
// '_ 익명 라이프타임 사용으로 추론 가능하도록 한다.
// impl<'a, T> LimitTracker<'a, T>
impl<T> LimitTracker<'_, T>
where
    T: Messenger,
{
    pub fn new(messenger: &T, max: usize) -> LimitTracker<T> {
        LimitTracker {
            messenger,
            value: 0,
            max,
        }
    }
    pub fn set_value(&mut self, value: usize) {
        self.value = value;
        let percentage_of_max = self.value as f64 / self.max as f64;

        // if percentage_of_max >= 0.75 && percentage_of_max < 0.9 {
        if (0.75..0.9).contains(&percentage_of_max) {
            self.messenger.send("할당의 75% 이상 사용되었습니다.");
        // } else if percentage_of_max >= 0.9 && percentage_of_max < 1.0 {
        } else if (0.9..1.0).contains(&percentage_of_max) {
            self.messenger.send("할당의 90% 이상 사용되었습니다.");
        } else if percentage_of_max >= 1.0 {
            self.messenger.send("할당량을 모두 사용했습니다.");
        }
    }
}

#[derive(Debug)]
struct MockMessenger {
    // sent_message: Vec<String>,
    // 벡터의 가변참조자를 얻기 위해 RefCell 을 사용한다.
    // RefCell<T> 는
    // borrow()를 호출할때 불변 참조자 Ref<T> 개수를 증가한다.
    // borrow_mut() 를 호출할때 가변 참조자 RefMut<T> 를 증가한다.
    sent_message: RefCell<Vec<String>>,
}
impl MockMessenger {
    fn new() -> MockMessenger {
        MockMessenger {
            // sent_message: vec![],
            // 벡터의 가변참조자를 얻기 위해 RefCell 을 사용한다.
            sent_message: RefCell::new(vec![]),
        }
    }
}
impl Messenger for MockMessenger {
    fn send(&self, message: &str) {
        // 원래는 Messenger 의 send() 시그니처가 &self 불변 참조(빌림)형태라
        // sent_message.push로 값을 변경하는 가변참조(&mut)으로 써야 한다.
        // self.sent_message.push(String::from(message));
        // 그런데 RefCell 사용해 가변 참조자를 얻을 수 있다.
        // 불변 참조(&)는 borrow() 를 사용, Ref<T> 리턴
        // 가변 참조자(&mut) 는 borrow_mut() 를 사용, RefMut<T> 리턴
        self.sent_message.borrow_mut().push(String::from(message));

        // 같은 스코프에서 2개이상의 가변 참조자 생성은 허용하지 않는다.
        // 컴파일되지만 실행하면 panic 발생
        //  panicked at 'already borrowed: BorrowMutError
        let mut borrow1 = self.sent_message.borrow_mut();
        // let mut borrow2 = self.sent_message.borrow_mut();
        borrow1.push(String::from(message));
        // borrow2.push(String::from(message));
    }
}
