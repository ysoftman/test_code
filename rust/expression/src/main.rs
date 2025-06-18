// if, match, 함수, 또는 범위 블록의 마지막 구문에 ';'가 없다면 Rust는 그 값을 블록의 리턴 값으로 간주
fn func1(a: i32) -> i32 {
    // 표현식(expression)은 리턴을 한다. ; 으로 끝나지 않는다.
    a + 1
}
fn main() {
    // 구문(statement)는 리턴이 없다. ;  으로 끝난다
    // 다음과 같은 구문(리턴이 없으니) 사용할 수 없다.
    // expected expression, found `let` statement
    // let b = let a = 1;
    // println!("b = {b}");
    // 참고로 c언어에서는 int a = 1, b = a;가 된다.
    let x = 1;
    println!("x = {x}");
    println!("func1 = {}", func1(1));

    // 블럭 expression 리턴값 사용
    let x = {
        let a = 1;
        let b = 2;
        a + b
    };
    println!("x = {x}");

    // if expression 리턴값 사용
    let x = if x == 1 { 3 } else { 4 };
    println!("x = {x}");

    // match expression 리턴값 사용
    let x = match x {
        1 => "10",
        _ => "100",
    };
    println!("x = {x}");
}
