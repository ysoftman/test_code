// ysoftman
// referenc counting(rc) test

enum List {
    Node(i32, Box<List>),
    Nil,
}

enum RcList {
    RcNode(i32, Rc<RcList>),
    RcNil,
}

use std::rc::Rc;
use List::{Nil, Node};
use RcList::{RcNil, RcNode};

fn main() {
    // a 리스트를 만들고 b와 c가 a 참조하도록 한다.
    let a = Node(5, Box::new(Node(10, Box::new(Nil))));
    // a 는 b로 이동해서 b가 소유한다.
    let b = Node(3, Box::new(a));
    // 위에서 a 는 이미 소유권이 이동된 상태에서 또 a 를 소유할 수는 없다.
    // let c = Node(4, Box::new(a));

    // Box 대신 Rc 로 참조 카운팅을 하면 여러곳에서 참조 할 수 있다.
    let rc_a = Rc::new(RcNode(5, Rc::new(RcNode(10, Rc::new(RcNil)))));
    // strong_count 로 rc_a 에 대한 참조가 몇개인지 파악할 수 있다.
    println!("reference count:{}", Rc::strong_count(&rc_a));

    {
        // Rc::clone() 은 깊은 복사가 아닌 참조 카운트만 증가시킨다.
        // rc_b 는 a 리스트를 가리키는 Rc<List> 를 clone하고 이때 참조카운트가 증가된다.
        let rc_b = RcNode(3, Rc::clone(&rc_a));
        println!("reference count:{}", Rc::strong_count(&rc_a));
        // 스코프가 벗어나면 참조 카운트는 1 감소한다.
    }
    // rc_c 는 a 리스트를 가리키는 Rc<List> 를 clone하고 이때 참조카운트가 증가된다.
    let rc_c = RcNode(4, Rc::clone(&rc_a));
    println!("reference count:{}", Rc::strong_count(&rc_a));
}
