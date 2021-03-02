// ysoftman
// box test
// box 로 heap(힙)에 데이터를 저장할 수 있는 스마트포인터다.

// 매번 List:: 를 명시하지 않기 위해 사용
use List::{Cons, Nil};

fn main() {
    // 5 값을 힙 데이터로 저장, 힙도 스코프를 벗어나면 메모리 해제한다.
    let b = Box::new(5);
    println!("{}", b);
    // let list = Cons(1, Cons(2, Cons(3, Nil)));
    let list = Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil))))));
    println!("{:?}", list);
}

#[derive(Debug)]
enum List {
    // Cons i32, List 에서 List 는 자신을 포함해 재귀적으로 구성된다.
    // rust List 열거형이 얼마큼의 공간이 필요한지 컴파일시 파악하게 되는데
    // List -> List -> ... 무한 반복 돼서 에러가 발생한다.
    // Cons(i32, List),
    // Box , Rc , & 등의 사용해 포인터크기만 필요하다는것 알게 할 수 있게 한다.
    Cons(i32, Box<List>),
    // null, nil 의미가 이닌 재귀의 기본 케이스로
    // 재귀의 끝, 아이템이 없음을 나타낸다.
    Nil,
}
