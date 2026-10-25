// {:?} 또는 {:#?} 로 디버깅 출력할 수 있도록 해주는 어노테이션
#[derive(Debug)]
struct User {
    name: String,
    age: u16,
}

fn main() {
    println!("normal print");
    print!("one");
    // println! 쓰라고 경고 뜬다.
    // print!("two\n");
    println!("two");
    println!("three\n");

    let a = 123;
    // pointer
    let b = &a;

    //``, which uses the `Display` trait
    //`?`, which uses the `Debug` trait
    //`e`, which uses the `LowerExp` trait
    //`E`, which uses the `UpperExp` trait
    //`o`, which uses the `Octal` trait
    //`p`, which uses the `Pointer` trait
    //`b`, which uses the `Binary` trait
    //`x`, which uses the `LowerHex` trait
    //`X`, which uses the `UpperHex` trait
    println!("{a} {a} {a:x} {a:X}"); // a 는 포인터 변수가 아니라 {:p} 를 사용하지 못한다
    println!("{b} {b} {b:p} {b:b} {b:e} {b:E} {b:x} {b:X}");

    let title = "lemon apple";
    // 자리수 지정해서 출력하기
    // 숫자 기본 우측 정렬
    println!("{:20}", a);

    // 숫자 기본 우측 정렬(빈공간 0으로 패딩)
    println!("{:09}", a);
    // [정렬방향(>)][0 패딩 플래그(0)][너비(9)]
    // 0 패딩 플래그가 있으면 정렬방향은 무시된다({:09} 와 같음)
    // 부호 뒤에 0 패딩, -123 => -00000123
    println!("{:>09}", a);
    // [채움 문자(0)][정렬방향(>)][너비(9)]
    // 0 을 단순 채움 문자로 사용해 부호 앞에 0 패딩, -123 => 00000-123
    println!("{:0>9}", a);

    // 숫자 기본 좌측 정렬(빈공간 0으로 패딩)
    println!("{:0<20}", a);

    // 문자 기본 좌측 정렬
    println!("{:20}", title);

    // 우측 정렬(빈공간_ 패딩)
    println!("{:_>20}", title);

    // ^ 가운데 정렬
    println!("{title:-^20}"); // ----lemon apple----
    let bar = "|";
    println!("{bar:_<10}{bar: >10}"); // |_________         |

    let user = User {
        name: String::from("ysoftman"),
        age: 10,
    };
    println!("{}", user.name);
    println!("{}", user.age);
    //println!("{user}"); // error,{:?} debug print 를 사용해야 한다.
    println!("{user:?}");
}
