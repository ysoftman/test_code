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
        // 리턴이 없는 경우라면 다음과 같이 () 로 단위값만 명사하면 아무것도 처리하지 않을 수 있다.
        // _ => (),
    }
}
