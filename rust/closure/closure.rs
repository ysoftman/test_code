// ysoftman
// closure test
// closure(클로저)란 변수에 저장하거나 다른 함수에 인자로 넘길 수 있는 익명 함수를 말한다.
// 클로저는 외부함수가 종료되도 유지되는 내부함수라고도 한다.
use std::thread;
use std::time;

mod clouser_test1;

fn main() {
    // 함수 호출을 변수에 담아 사용할 수 있다.
    // let cs = calc_something(val);

    // 클로저는 fn , 타입명시등의 어노테이션이 없이 간략하다.
    // 클로저를 정의하고 변수에 저장, 클로저 정의형식은 다음과 같다.
    // |클로저파라미터1, 클로저파라미터2 ... | { 클로저 내용 }
    // 타입추론이 가능하면 파라티머 타입을 명시하지 않아도 된다.
    // 클로저 내용이 하나의 표현식이면 {}가 없어도 된다.
    let cs_closure = |num| num;
    println!("{}", cs_closure(123));

    // 또는 명확성을 높이기 위해 클로저 파라미터외 리턴 타입을 명시할 수도 있다.
    let cs_closure = |num: u32| -> u32 { num };
    println!("{}", cs_closure(123));

    // 1초있다가 받은 파라미터 리턴하는  클로저
    let cs_closure = |num| {
        println!("calculating something slowly...");
        thread::sleep(time::Duration::from_secs(1));
        num
    }; // let 문을 완성하기 위해 ; 필요

    let val = 10;
    if val < 25 {
        // 클로저를 사용
        println!("val < 25 {}", cs_closure(val));
        println!("val < 25 {}", cs_closure(val));
        println!("val < 25 {}", cs_closure(val));
        println!("val < 25 {}", cs_closure(val));
        println!("val < 25 {}", cs_closure(val));
    // 최초 클로저 사용시점에 파라미터, 리턴 타입이 추론되서
    // 이후부터는 같은 타입의 파라미터로만 클로저를 사용해야 한다.
    // 이미 위에서 u32 값으로 클로저를 사용해야 아래 코드는 컴파일시 에러가 난다.
    // println!("{}", cs_closure(String::from("ysoftman")));
    } else {
        println!("val >= 25 {}", cs_closure(val));
    }

    clouser_test1::run(12);
}
