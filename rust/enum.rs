// ysoftman
// enum test
#[derive(Debug)]
struct Fruit {
    name: String,
    value: u32,
}

#[derive(Debug)]
// enum(열거형) 이름과 값들(variants)들 모두 carmel case 를 쓰도록 한다. 아니면 경고 발생
enum YsoftmanEnum {
    // variant 의 데이터 타입은()로 지정
    V4(String),
    V6(String),
    V4Digit(u32, u32, u32, u32),
    Cnt(u32),
    // struct 타입 지정 가능
    Fruit(Fruit),

    // 데이터 타입을 지정하지 않을 수 있다.
    Quit,
    // struct 데이터 타입
    Move { x: i32, y: i32 },
    // tuple 데이터 타입
    Write(String),
    ChangeColor(i32, i32, i32),
}

// enum 메소드
impl YsoftmanEnum {
    fn call(&self) {
        println!("self {:#?}", self);
    }
}

fn main() {
    let ipv4 = YsoftmanEnum::V4(String::from("127.0.0.1"));
    let ipv4_digit = YsoftmanEnum::V4Digit(127, 0, 0, 1);
    let ipv6 = YsoftmanEnum::V6(String::from("::1"));
    let cnt = YsoftmanEnum::Cnt(123);
    let fruit = YsoftmanEnum::Fruit(Fruit {
        name: String::from("lemon"),
        value: 123,
    });

    println!("ipv4 {:#?}", ipv4);
    println!("ipv4_digit {:#?}", ipv4_digit);
    println!("ipv6 {:#?}", ipv6);
    println!("cnt {:#?}", cnt);
    println!("fruit {:#?}", fruit);

    let mesg0 = YsoftmanEnum::Quit;
    mesg0.call();
    let mesg1 = YsoftmanEnum::Write(String::from("write ysoftman!"));
    mesg1.call();
    let mesg2 = YsoftmanEnum::Move { x: 1, y: -2 };
    mesg2.call();
    let mesg3 = YsoftmanEnum::ChangeColor(123, 123, 123);
    mesg3.call();

    /* rust 에는 null 없지만, 값의 부재를 나타내는 Option 열거형이 있다.
    // Option 표준 라이브러리에 다음과 같이 정의되어 있고
    // <> 제너릭으로 모든 데이터 타입을 받을 수 있다.
    enum Option<T> {
        Some(T),
        None, //  null 같은 의미
    }
    */
    // Option 열거형은 Options:: 을 명시하지 않는다.
    // Option 은 {} 디폴트 포맷터인 std::fmt::Display trait 이 impl 되어 있지 않다.
    // OPtion 은 {:?} 또는 {:#?} 을 사용한다.
    let some_num = Some(5);
    println!("some_num {:?}", some_num);
    let some_string = Some("String");
    println!("some_string {:?}", some_string);
    // None 은 데이터 타입을 알 수 없기때문에
    // 사용하려면 Option 데이터 타입을 명시해야 한다.
    let absent_num: Option<i32> = None;
    println!("absent_num {:?}", absent_num);
}
