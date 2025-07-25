// ysoftman
// ownership(소유권)
// - 모든 값들은 owner(오너) 라는 변수를 가지고 있다.
// - 한번에 하나의 오너만 존재한다.
// - scope 를 벗어나면 값은 drop(메모리 해제)된다.

fn main() {
    // 스트링은 힙에 저장된다.
    let s1 = String::from("ysoftman");

    // c, c++ 등과 같이 포인터값만 복사되는 얉은 복사지만
    // 값은 하나의 오너만이 가지고 있어야 하기 때문에
    // move(s2 로 소유권 이전)가 발생한다.
    let s2 = s1;
    // 소유권을 잃은 s1 는 더이상 유효하지 않아 사용할 수 없다.
    // println!("s1:{}", s1);
    println!("s2:{s2}");

    // clone 으로 깊은 복사가 되고 각각 별도의 값이기 때문에 s2도 유효하다.
    let s3 = s2.clone();
    println!("s2:{s2} s3:{s3}");

    let x = 1;
    // 스트링이 아닌 정수형 값은 스택을 사용함으로 clone 없이도 기본 값복사가 된다.
    // 참조값 이나 그냥 값이나 같은 크기로 차이가 없기 때문이다.
    let y = x;
    println!("x:{x} y:{y}");

    let s4 = String::from("ysoftman");
    let (n, s5) = takes_ownership(s4);
    // s4 힙 변수라 takes_ownership()로 소유권이 넘어가 유효하지 않다.
    // println!("s4:{}", s4);
    println!("n:{n} s5:{s5}");

    let s4 = String::from("ysoftman");
    let (n, s5) = borrows_ownership(&s4);
    // 참조로 넘기면 소유권이 넘어가지 않아(빌려주어) s4 가 유효하다.
    println!("s4:{s4}");
    println!("n:{n} s5:{s5}");

    let s4 = String::from("ysoftman");
    let (n, s5) = borrows_ownership2(&s4);
    // 참조로 넘기면 소유권이 넘어가지 않아(빌려주어) s4 가 유효하다.
    println!("s4:{s4}");
    println!("n:{n} s5:{s5}");

    // x,y 는 스택 변수라 값복사가 돼서 copy_values 호출 이후에도 유효하다.
    copy_values(x, y);
    println!("x:{x} y:{y}");
}

// 스코프를 벗어나면 s는 drop 되지만 리턴에서 소유권을 넘길 수 있다.
// 참고로 () 묶어 여러개의 값들을 리턴할 수 있다.
fn takes_ownership(s: String) -> (u32, String) {
    println!("takes_ownership:{s}");
    (123, s)
}

fn borrows_ownership(s: &String) -> (u32, String) {
    println!("borrows_ownership:{s}");
    (123, String::from("apple"))
}

fn borrows_ownership2(s: &String) -> (u32, &str) {
    println!("borrows_ownership2:{s}");
    (123, "apple")
}

fn copy_values(x: u32, y: u32) {
    println!("copy_values:{x} {y}");
}
