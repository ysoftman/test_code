// ysoftman
// unsafe test

// global 변수는 변경은 unsafe{} 블럭 내에서만 가능하다.
static mut COUNTER: u32 = 0;

fn main() {
    let mut num = 7;
    let r1 = &num as *const i32;
    let r2 = &mut num as *const i32;

    // unsafe 블럭은 가변참조 불변 참조를 동시하는(소유권 규칙에 어긋나는) 등의 안전하지 않는 메모리 참조를 허용하다.
    // unsafe 는 C 코드와 상호작용을 위해 주로 사용된다.
    unsafe {
        println!("r1 : {}", *r1);
        println!("r2 : {}", *r2);
        dangerous();
        println!("{}", abs(-10));
        COUNTER += 1;
        println!("COUNTER:{}", COUNTER);
        COUNTER += 1;
        println!("COUNTER:{}", COUNTER);
    }
}

// 안전하지 않는 함수로 명시하면 unsafe{} 에서만 호출 할 수 있다.
unsafe fn dangerous() {
    println!("dangerous() in unsafe scope")
}

// extern "C" 로 실제 존재하는 C 표준 라이브러이의 abs()함수를 사용할 수 있다.
// unsafe{} 에서만 호출 할 수 있다.
extern "C" {
    fn abs(intput: i32) -> i32;
}

// unsafe trait 도 만들 수 있다.
unsafe trait Fruit {}
unsafe impl Fruit for i32 {}
