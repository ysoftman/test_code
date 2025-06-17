fn main() {
    // 튜플(여러개 값)파라미터로 넘기로 튜플로리턴 받기
    let (x, y) = (-100, 100);
    let (a, b, c) = ret_n_values((x, y));
    println!("{} {} {}", a, b, c);
    // 리턴값들을 각각 인덱싱할 수도 있다.
    println!("{}", ret_n_values((x, y)).0);
    println!("{}", ret_n_values((x, y)).1);
    println!("{}", ret_n_values((x, y)).2);
    // 리턴값 여러개를 한번에 찍을 수도 있다.
    println!("{:?}", ret_n_values((x, y)));

    let ret = another_fn(123, "ysoftman");
    println!("another_fn returns:{}", ret);

    unit_function();
    // 1번째 리턴값만 출력
    println!("return {}", unit_function2().1);
}

fn ret_n_values((a, b): (i32, i32)) -> (u32, String, f32) {
    println!("tuple parameter({}, {})", a, b);
    // 여러개 값 리턴
    (123, "ysoftman".to_string(), 1.12)
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
    let temp = a;
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

// () 는 유닛(unit) 또는 nil 이라불리는 타입으로 ()라는 값 하나만 가진다.
// 의미있는 값이 리턴될 필요가 없을때 사용하며 리턴이 없는 경우와 같은데,
// fn unit_function() {
// fn unit_function() -> () { // unneeded unit
fn unit_function() {
    println!("unit function");
}
// 다음과 같이 2개 이상 리턴할때 리턴인덱스를 맞추기 위해서 사용할 수 있다.
fn unit_function2() -> ((), String) {
    ((), "aaa".to_string())
}
