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
}
