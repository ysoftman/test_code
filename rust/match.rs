// ysoftman
// match test

#[derive(Debug)]
enum UsState {
    Alabama,
    Alaska,
}

enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter(UsState),
}

fn main() {
    println!("Penny! {}", value_in_cents(Coin::Penny));
    println!("Nickel! {}", value_in_cents(Coin::Nickel));
    value_in_cents(Coin::Dime);
    // Quarter에 UsState enum 값 패턴도 같이 있을 수 있다.
    value_in_cents(Coin::Quarter(UsState::Alaska));
    value_in_cents(Coin::Quarter(UsState::Alabama));

    // Option 파라미터 사용, 리턴 값도 Option 이라 {:?} 또는 {:#?} 로 출력
    println!("5 plus_one : {:?}", plus_one(Some(5)));
    println!("1 plus_one : {:?}", plus_one(Some(1)));
    println!("None plus_one : {:?}", plus_one(None));

    println!("some u8 value 1 : {}", some_u8_value(1));
    println!("some u8 value 2 : {}", some_u8_value(2));
    println!("some u8 value 3 : {}", some_u8_value(3));
    println!("some u8 value 4 : {}", some_u8_value(4));
    println!("some u8 value 5 : {}", some_u8_value(5));

    multi_match();
    some_ref_match();
    match_guard();
    at_binding_match();
}

fn value_in_cents(coin: Coin) -> u32 {
    // if 처럼 bool 조건대신 다양한 패턴을 취할 수 있다.
    match coin {
        // 패턴 => 갈래(처리할내용)
        // 패턴이 매칭될때까지 다음 패턴을 체크한다.
        // 코드가 1줄이면 {} 사용안한다.(rustfmt 에서 제거함)
        Coin::Penny => 1,
        Coin::Nickel => 5,
        Coin::Dime => {
            println!("Dime!");
            10
        }
        // 패턴 과 매치되는 부분을 받을 수 있다.
        // state 는 UsState::Alaska 또는 UsState::Alabama 에 바인딩 된다.
        Coin::Quarter(state) => {
            println!("Quarter! state {:?}", state);
            25
        }
    }
}

// x 는 Option 타입을 사용하면 x 는 i32 값이 있거나 없을(None) 수 있다.
fn plus_one(x: Option<i32>) -> Option<i32> {
    // Option 타입은 Some, None 모두 match 패턴으로 명시해야 한다.
    // Some, None 둘 중에 하나라도 빠지면 컴파일 에러 발생한다.
    match x {
        None => None,
        // x는 Some(5), Some(1) 인 경우
        // i 는 5 또는 1 에 바인딩된다.
        Some(i) => Some(i + 1),
    }
}

fn some_u8_value(u: u8) -> String {
    // u8 8bit(1byte) 0~255 값을 가지는 경우
    // 모든 0~255에 대한 모든 패턴을 명시하지 않고
    // _ (placeholder)를 사용하면 그밖의 모든 경우가 매칭된다.
    match u {
        1 => String::from("one"),
        2 => String::from("two"),
        3 => String::from("three"),
        _ => String::from("greater than 3"),
        // 리턴이 없는 경우라면 다음과 같이 () 로 단위값만 명시하면 아무것도 처리하지 않을 수 있다.
        // _ => (),
    }
}

fn multi_match() {
    let x = 2;
    match x {
        // 1 또는 99 일때
        1 | 99 => println!("1 or 99"),
        // 1 ~ 10 범위 일때(deprecated 되었다.)
        // 2...10 => println!("1 or 99"),
        // 대신 ..= 를 사용한다.
        2..=10 => println!("2 ~ 10"),
        _ => println!("i don't know!"),
    }

    let c = 'd';
    match c {
        // a 또는 z 일때
        'a' | 'z' => println!("'a' or 'z'"),
        // b ~ f 사이 일때
        'b'..='f' => println!("'b' ~ 'f'"),
        _ => println!("i don't know!"),
    }

    struct Point {
        x: u32,
        y: u32,
        z: u32,
    }

    let point = Point { x: 0, y: 1, z: 2 };
    println!("x:{}, y:{}, z:{}", point.x, point.y, point.z);
    match point {
        // x 외 다른 필드는 .. 무시하기
        Point { x, .. } => println!("x:{}", x),
    }
}

fn some_ref_match() {
    let fruit = Some(String::from("lemon"));
    match fruit {
        // s 소유권이 이동되어 이후에는 사용하지 못한다.
        // Some(s) => println!("s:{}", s),
        // ref 로 s 를 소유권 이동 없이 빌림으로 사용할 수도 있다.
        Some(ref s) => println!("s:{}", s),
        None => (),
    }
    println!("fruit:{:?}", fruit);

    let mut mut_fruit = Some(String::from("lemon"));
    match mut_fruit {
        // ref mut 으로 소유권이동없이(빌림) mut_fruit 를 변경할 수 있다.
        Some(ref mut s) => {
            println!("s:{}", s);
            *s = String::from("orange")
        }
        None => (),
    }
    println!("mut_fruit:{:?}", mut_fruit);
}

fn match_guard() {
    let x = Some(5);
    match x {
        // match 뒤에 if 조건을 추가 할 수 있다.(match guard)
        Some(s) if s == 5 => println!("{} is 5", s),
        Some(s) if s > 3 => println!("greater than 3 :{}", s),
        Some(s) => println!("s:{}", s),
        None => (),
    }

    let num = 10;
    let tf = true;
    match num {
        // match 뒤에 if 조건을 추가 할 수 있다.(match guard)
        10 | 9 | 8 if tf => println!("10 or 9 or 8 s:{}", num),
        _ => (),
    }
}

fn at_binding_match() {
    enum Message {
        Hello { id: i32 },
    }
    let msg = Message::Hello { id: 5 };
    match msg {
        Message::Hello {
            // @ 는 패턴 매칭을 확인 하는 동시에 해당 값을 갖는 변수를 생성한다.
            id: id_variable @ 3..=7,
        } => println!("3~7 {}", id_variable),
        Message::Hello { id: 8..=10 } => println!("8~10"),
        Message::Hello { id } => println!("other"),
    }
}
