// ysoftman
// https://rinthel.github.io/rust-lang-book-ko/ch00-00-introduction.html
 
// hello_world 처럼 단어 사이는 _ 사용
// 들여쓰기는 space 사용
// rustfmt(${HOME}/.cargo/bin/rustfmt) 으로 코드 포맷팅할 수 있다.
// 코드 포맷팅
// rustfmt ./hello_world.rs
// 빌드 및 실행
// rustc ./hello_world.rs && ./hello_world
fn main() {
    // ! 는 매크로 의미
    println!("hello, world!");
}
