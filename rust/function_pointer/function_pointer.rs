// ysoftman
// function pointer test

fn main() {
    // 함수포인터 리턴 받아 사용하기
    let fp = get_add_ten_function();
    println!("result: {}", fp(10));

    // compute 의 첫번째 인자는 함수명이다.
    let result = compute(add_one, 10);
    println!("result: {result}");

    // 클로저(내부함수)를 리턴받아서 사용하기
    let closure_fn = return_closure();
    println!("result: {}", closure_fn(100));
}

fn add_ten(x: i32) -> i32 {
    x + 10
}

// add_ten 시그니처로 리턴을 명시해 함수 포인터를 리턴할 수 있다.
fn get_add_ten_function() -> fn(x: i32) -> i32 {
    add_ten
}

fn add_one(x: i32) -> i32 {
    x + 1
}

// f 는 함수 포인터로 fn 타입으로 함수 스그니처로 표현한다.
fn compute(f: fn(i32) -> i32, arg: i32) -> i32 {
    // 함수 포인터를 사용
    f(arg) + f(arg)
}

// 클로저 리턴
// 클로저는 구체적인 타입이 없어 클로저를 저장하기 위한 사이즈을 알 수 없어
// 아래와 같이 함수 포인터를 std::ops::Fn trait 으로  반환을 허용하지 않는다.
// fn return_closure() -> (dyn Fn(i32) -> i32) {
//     |x| x + 1
// }
// 대신 Box 에 담아 이용하면 된다.
fn return_closure() -> Box<dyn Fn(i32) -> i32> {
    Box::new(|x| x + 1)
}
