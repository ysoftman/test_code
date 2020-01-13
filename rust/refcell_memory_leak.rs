// ysoftman
// memory leak test

use std::cell::RefCell;
use std::rc::Rc;
use std::rc::Weak;
use List::{Nil, Node};
use NewList::{NewNil, NewNode};

#[derive(Debug)]
enum List {
    Node(i32, RefCell<Rc<List>>),
    Nil,
}
impl List {
    fn next(&self) -> Option<&RefCell<Rc<List>>> {
        match *self {
            Node(_, ref item) => Some(item),
            Nil => None,
        }
    }
}

#[derive(Debug)]
enum NewList {
    // 순환 참조를 막기위한 Weak 참조 사용
    // weak 참조는
    NewNode(i32, RefCell<Weak<NewList>>),
    NewNil,
}
impl NewList {
    fn next(&self) -> Option<&RefCell<Weak<NewList>>> {
        match *self {
            NewNode(_, ref new_item) => Some(new_item),
            NewNil => None,
        }
    }
}

fn rc_strong() {
    let a = Rc::new(Node(5, RefCell::new(Rc::new(Nil))));
    // a,b 가 서로 순환 참조하기
    // b next -> a
    let b = Rc::new(Node(10, RefCell::new(Rc::clone(&a))));
    println!("a = {:?}", a);
    println!("b = {:?}", b);
    // a next -> b
    if let Some(link) = a.next() {
        *link.borrow_mut() = Rc::clone(&b);
    }
    // a,b 각각 rc 2가 되지만
    println!("a rc strong_count = {}", Rc::strong_count(&a));
    println!("b rc strong_count = {}", Rc::strong_count(&b));
    println!("a rc weak_count = {}", Rc::weak_count(&a));
    println!("b rc weak_count = {}", Rc::weak_count(&b));

    // 실제 값을 출력하면 a,b 서로 순환 참조로 무한 루프로 stack overflow 발생
    // println!("a next  = {:?}", a.next());
    // println!("b next  = {:?}", b.next());
}

fn rc_weak() {
    let new_a = Rc::new(NewNode(5, RefCell::new(Weak::new())));
    let new_b = Rc::new(NewNode(10, RefCell::new(Weak::new())));
    println!("new_a = {:?}", new_a);
    println!("new_b = {:?}", new_b);
    // a,b 가 서로 순환 참조하기
    // a next -> b
    if let Some(next) = new_a.next() {
        // downgrade()는 Weak<T>에 대한 참조자(스마트 포인터)를 리턴한다.
        // downgrade() 는 weak_count 를 1증가 시킨다.
        *next.borrow_mut() = Rc::downgrade(&new_b);
        // Weak 참조자는 값이 이미 없을 수도 있기때문에 존재여부체크가 필요한데
        // 이때 upgrade() 로 Option<Rc<T>> 리턴받는데 Some 타입이면 존재여부를 판단할 수 있다.
        println!("new_a next = {:?}", next.borrow().upgrade());
    }
    // b next -> a
    let next = new_b.next();
    match next {
        Some(next) => {
            // downgrade()는 Weak<T>에 대한 참조자(스마트 포인터)를 리턴한다.
            // downgrade() 는 weak_count 를 1증가 시킨다.
            *next.borrow_mut() = Rc::downgrade(&new_a);
            // Weak 참조자는 값이 이미 없을 수도 있기때문에 존재여부체크가 필요한데
            // 이때 upgrade() 로 Option<Rc<T>> 리턴받는데 Some 타입이면 존재여부를 판단할 수 있다.
            println!("new_b next = {:?}", next.borrow().upgrade());
        }
        // None => println!("값이 없습니다."),
        None => {}
    }

    println!("new_a rc strong_count = {}", Rc::strong_count(&new_a));
    println!("new_b rc strong_count = {}", Rc::strong_count(&new_b));
    println!("new_a rc weak_count = {}", Rc::weak_count(&new_a));
    println!("new_b rc weak_count = {}", Rc::weak_count(&new_b));

    // a,b 서로 weak 연결하면 순환 참조가 발생하지 않는다.
    println!("new_a next = {:?}", new_a.next());
    println!("new_a next = {:?}", new_a.next());
    println!("new_b next = {:?}", new_b.next());
}

fn main() {
    rc_strong();
    rc_weak();
}
