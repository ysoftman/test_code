// ysoftman
// function pointer test

fn main() {
    // computer 의 첫번째 인자는 함수명이다.

    let result = compute(add_one, 10);
    println!("result : {}", result);
}
fn add_one(x: i32) -> i32 {
    x + 1
}

// f 는 함수 포인터로 fn 타입으로 함수 스그니처로 표현한다.
fn compute(f: fn(i32) -> i32, arg: i32) -> i32 {
    // 함수 포인터를 사용
    f(arg) + f(arg)
}
