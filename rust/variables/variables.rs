// static 으로 global 변수
static GLOBAL_STRING: &str = "ysoftman";

//  사용하지 않는 코드 warning 발생하지 않게 하는 attribute
#[allow(dead_code)]
static GLOBAL_INT: i32 = 123123;

// static 은 const 와 다르게
// static mutable 로 사용할수 있지만 unsafe 영역내에서만 사용 할 수 있다.
static mut GLOBAL_AAA: i32 = 123123;

// 불변 변수를 통해 쉽게 안정성과 동시성을 취할 수 있다.
fn main() {
    println!("GLOBAL_STRING : {}", GLOBAL_STRING);

    println!("GLOBAL_INT : {}", GLOBAL_INT); // 컴파일시 아래에 GLOBAL_INT 로 고정되어 9999 이 출력된다

    // 같은 이름의 변수라면 global 보다 local 이 우선한다.
    static GLOBAL_INT: i32 = 9999;
    println!("GLOBAL_INT : {}", GLOBAL_INT);

    // static 가변은 쓸 수 없다.
    static GLOBAL_INT2: i32 = 7777;
    unsafe {
        GLOBAL_AAA = 11111;
        println!("GLOBAL_AAA : {}", GLOBAL_AAA);
    }
    println!("GLOBAL_INT2 : {}", GLOBAL_INT2);

    // 데이터 타입을 명시할 수도 있다.
    let a: u8;
    // 최초 초기화(u8로 선언되어 있어 0~255값만 가능한다.)
    a = 255;
    println!("a : {}", a);
    // immutable 이라 변경할 수 없다.
    // a = 456;

    // 같은 이름의 변수를 재정의해 사용할 수 있다.
    // : f64 와 같이 명시하지 않아도 f64 타입으로 된다.
    let a = 12.3;
    println!("a : {}", a);

    println!("min i32:{}", std::i32::MIN);
    println!("max i32:{}", std::i32::MAX);
    println!("min i64:{}", std::i64::MIN);
    println!("max i64:{}", std::i64::MAX);

    // _로시작하는 변수는 unused 해도 워닝이 발생하지 않는다.
    let _asdf = 123;
    // 가변 변수
    let mut x = 5;
    println!("x : {}", x);
    x = 6;
    println!("x : {}", x);

    // multiple variables 할당
    let (aaa, bbb) = ("lemon", 123);
    println!("aaa:{}, bbb:{}", aaa, bbb);
    // () 로 묶어 하나의 placeholder 에 출력
    println!("aaa,bbb = {:?}", (aaa, bbb));

    // 상수 선언, 대문자여야 한다.(소문자면 빌드 warning 발생)
    // #[allow(non_upper_case_globals)] attribute 를 사용하면 warning 을 발생하지 않는다.
    // 상수 자체가 불변성이라 mut 을 쓰지 않고
    // 상수의 유형을 명시해야 한다.
    // 가독성을 위해 _ 로 시각적으로 자릿수를 구분을 위해 사용할 수 있다.
    #[allow(non_upper_case_globals)]
    const abc: i32 = 123;
    println!("abc:{}", abc);

    const MAX_PORINTS: u32 = 100_000;
    println!("MAX_PORINTS : {}", MAX_PORINTS);
    // string 타입은 참조자로 명시
    const MY_NAME: &str = "ysoftman";
    println!("MY_NAME : {}", MY_NAME);

    // shadowing : 같은 변수의 이름을 사용하는 경우, 원래의 변수는잠깐 사라지고 나중에 필요할대
    // 나타난다
    let y = 1;
    {
        let y = y + 1;
        println!("y:{}", y);
    }
    println!("y:{}", y);

    // 문자형식의 불변 변수
    let spaces1 = "   ";
    // 숫자형으로 새롭게 불변 변수 선언
    let spaces1 = spaces1.len();
    println!("spaces1:{}", spaces1);

    let mut spaces2 = "   ";
    // 변수 유형을 변경할 수 없어 컴파일시 에러
    // spaces2 = spaces2.len();

    // 가변(mut)으로 선언하고
    // 사용하고 변경하지 않으면 컴파일시 경고가 발생한다.
    println!("spaces2:{}", spaces2);
    spaces2 = "ysoftman";
    println!("spaces2:{}", spaces2);

    // 실수형, 데이터 타입을 명시하지 디폴트로 f64
    let float32: f32 = 2.0;
    let float64: f64 = 2.0;
    println!("float32:{}", float32);
    println!("float64:{}", float64);

    // bool 타입
    let tf1: bool = true;
    let tf2 = false;
    println!("tf1:{}", tf1);
    println!("tf2:{}", tf2);

    // 문자 타입
    let ch1 = 'a';
    let ch2: char = 'z';
    println!("ch1:{}", ch1);
    println!("ch2:{}", ch2);
}
