fn main() {
    println!("Hello, world!");
    let ret = another_fn(123, "ysoftman");
    println!("another_fn returns:{}", ret);
}

// 함수 파라미터 사용시,  str 는 참조자(&) 사용
// -> 리턴타입
fn another_fn(x: i32, y: &str) -> &str {
    println!("another function!");
    println!("x:{}, y:{}", x, y);

    let mut a = 1;
    let mut b = 2;
    let mut c = 3;
    // 다음과 같은 식은 허용되지 않는다.
    // a = b = c;
    // temp a 값으로 최초 할당한 후에 읽기에만 사용하기 때문에 불변으로 선언해야 한다.
    let temp;
    temp = a;
    a = b;
    b = c;
    c = temp;
    println!("temp:{}, a:{}, b:{}, c:{}", temp, a, b, c);
    let aa = 10;
    // {} 로 새로운 범위를 지정하는 표현식
    let bb = {
        let bbb = 30;
        println!("bbb:{}", bbb);
        // 표현시의 마지막에 ; 를 붙이지 말아야 리턴된다.(암묵적 리턴)
        // 만약 마지막에 ; 을 붙이면 구문으로 취급되면 리턴되지 않는다.
        bbb - 10
    };
    let cc = if bb == 20 { 30 } else { 40 };
    // 분기에서 각각 다른 타입을 리턴할 수 없다.(컴파일 에러)
    // let cc = if bb == 20 { 30 } else { "40" };
    println!("aa:{}, bb:{}, cc:{}", aa, bb, cc);

    // 리턴
    // return "okay";
    // 또는 암묵적 리턴
    // 마지막에 ; 을 붙이지 않으면 리턴
    "okay"
}
