// {:?} 또는 {:#?} 로 디버깅 출력할 수 있도록 해주는 어노테이션
#[derive(Debug)]
struct User {
    name: String,
    age: u16,
}

fn main() {
    println!("normal print");
    print!("one");
    print!("two\n");
    print!("three\n");

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
    println!("{} {} {:x} {:X}", a, a, a, a); // a 는 포인터 변수가 아니라 {:p} 를 사용하지 못한다
    println!(
        "{} {} {:p} {:b} {:e} {:E} {:x} {:X}",
        b, b, b, b, b, b, b, b
    );

    let user = User {
        name: String::from("ysoftman"),
        age: 10,
    };
    println!("{}", user.name);
    println!("{}", user.age);
    //println!("{}", user); // error,{:?} debug print 를 사용해야 한다.
    println!("{:?}", user);
}
