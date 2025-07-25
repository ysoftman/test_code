// ysoftman
// https://rinthel.github.io/rust-lang-book-ko/ch00-00-introduction.html

// rust naming conventions
// https://doc.rust-lang.org/1.0.0/style/style/naming/README.html
// value 레벨에서는 snake_case (단어 사이 _ 사용) : crates, mod, fn, method, local_variable
// type 레벨에서는 CamelCase : type, traits, enum

// 들여쓰기는 space 사용

// rustfmt(${HOME}/.cargo/bin/rustfmt) 으로 코드 포맷팅할 수 있다.
// rustfmt 가 없다면 cargo 로 설치 할 수 있다.
// cargo install rustfmt
// 코드 포맷팅
// rustfmt ./hello_world.rs

// 빌드 및 실행
// rustc ./hello_world.rs && ./hello_world
fn main() {
    // ! 는 매크로 의미
    println!("hello, world!");

    // println 포맷팅
    // 참고 https://doc.rust-lang.org/std/fmt/index.html#formatting-parameters
    println!("{}", 1);
    // binary 출력
    println!("{:b}", 255);
    // argument 위치별 출력
    println!("{0} {1} {0}", 123, 999);
    // argument 이름별 출력
    println!("{val1:} ysoftman", val1 = 1);
    // 문자열을 포맷팅 하지 않고 문자그대로(literal) 사용하라고 clippy 경고가 뜬다.
    // println!("{val1:} {val2:}", val1 = 1, val2 = "ysoftman");
    // 오른쪽 맞춤(왼쪽에 10 공백을 두고 출력)
    println!("{val1:>10}", val1 = 1);
    // 오른쪽 맞춤(왼쪽에 10 공백을 두고 출력, 변수 뒤에 $를 붙여 usize(unsigned integer)로 취급할 수 있다.)
    println!("{val1:>a$}", val1 = 1, a = 10);
    // 오른쪽 맞춤(왼쪽에 10 공백을 두고 출력, 공백 0 으로 채우기(padding))
    println!("{val1:>010}", val1 = 1);
    // 가운데 맞춤(10 공백 중간에 두고 출력)
    println!("{val1:^10}", val1 = 1);
    // 왼쪽 맞춤(오른쪽에 10 공백을 두고 출력)
    println!("{val1:<10}", val1 = 1);
    let vec1 = [1, 2, 3];
    // debug formatting
    // println!("{:?}", vec1);  // https://rust-lang.github.io/rust-clippy/master/index.html#uninlined_format_args
    println!("{vec1:?}");
    // pretty formatting(indent)
    // println!("{:#?}", vec1); // https://rust-lang.github.io/rust-clippy/master/index.html#uninlined_format_args
    println!("{vec1:#?}");
}
