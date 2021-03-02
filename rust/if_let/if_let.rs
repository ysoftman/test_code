// ysoftman
// if let test

fn main() {
    // u8 타입의값 3
    let some_u8_value = Some(3u8);
    match some_u8_value {
        Some(1) => println!("one"),
        Some(2) => println!("two"),
        Some(3) => println!("three"),
        // u8 0~255까지만 된다.
        // Some(256) => println!("256"),
        _ => (),
    }

    // match 로 구현시 너무 verbose 한 경우
    // 대신 if let 으로 사용할 수 있다.
    if let Some(3) = some_u8_value {
        println!("three")
    } else if let Some(4) = some_u8_value {
        println!("four")
    } else {
        println!("else")
    }
}
