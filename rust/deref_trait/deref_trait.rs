// ysoftman
// deref trait test
// 역참조 트레잇 사용

fn main() {
    let x = 5;
    // y 는 x의 주소값을 참조하는 포인터
    let y = &x;
    // 역참조 강제로 y를 역참조해 값을 출력해준다.
    println!("{}", y);
    // 정석적인 방법은 y 포인터를 역참조해서 값을 파악한다.
    println!("{}", *y);
    // 포인터라 정수와 비교할 수 없다.
    // assert_eq!(5, y);
    assert_eq!(5, *y);

    println!("-----");

    let x = 5;
    // y 는 x 를 가르키는 box 의 인스턴스다.
    let y = Box::new(x);
    // Box<T> 는 역참조 연산을 할 수 있다.
    assert_eq!(5, *y);

    println!("-----");

    let x = 10;
    let y = MyBox::new(x);
    // MyBox는 역참조 강제 기능이 없어 *y 로 사용해야 한다.
    // println!("{}", y);
    println!("{}", *y);
    // rust 는 기본적으로 &(참조) 에 대해서만 역참조(*) 할 수 있다.
    // *y 는 사실 *(y.deref()) 를 수행한다.
    // y.derf() 가 & 로 리턴하고 이에 &를 수행한다.
    assert_eq!(10, *y);

    println!("-----");

    let mybox2 = MyBox2 { value: "lemon" };
    println!(
        "mybox2.len:{}",
        // .len()으로 mybox2 가 자동참조되고 이때 역참조(deref)가 자동으로 발생한다
        mybox2.len()
    );

    println!("-----");

    let msg = MyBox::new(String::from("ysoftman"));
    // deref 를 사용해 역참조 강제(&String -> &str 로 변환)된다.
    print_string(&msg);
    // 역참조 강제가 없으면 다음과 같이 사용해야 한다.
    // *msg 로 msg를 역참조하고 슬라이스[..]하고 & 로 print_string() 함수 시그니처와 맞쳐줘야 한다.
    // 역참조 강제로 아래와 같이 가독성이 힘든 코드를 사용하지 않을 수 있다.
    print_string(&(*msg)[..]);
}

fn print_string(s: &str) {
    println!("{}", s);
}

// Box와 비슷한역할을 하는 스마트 포인터를 작성
struct MyBox<T>(T);
impl<T> MyBox<T> {
    fn new(x: T) -> MyBox<T> {
        MyBox(x)
    }
}
struct MyBox2<T> {
    value: T,
}

use std::ops::Deref;

// rust 는 기본적으로 &(참조) 에 대해서만 역참조(*) 할 수 있다.
// & 이외는 Deref(역참조) trait 구현해야 역참조 연산을 사용할 수 있다.
// Deref traic 정의를 참조
// 참고로 가변참조자 -> 가변참조자로 역참조 강제하기 위애서는 DerefMut 트레잇 사용
impl<T> Deref for MyBox<T> {
    // 연관타입(associated type) 정의
    type Target = T;
    // deref(역참조)일때 수행될 메소드
    fn deref(&self) -> &T {
        println!("MyBox 역참조(deref) 발생");
        // 현재 스마트포인터 자체의 0번째 값을 리턴하도록 한다.
        &self.0
    }
}

impl<T> Deref for MyBox2<T> {
    type Target = T;
    fn deref(&self) -> &T {
        println!("MyBox2 역참조(deref) 발생");
        println!("{} was used!", std::any::type_name::<T>());
        &self.value
    }
}
