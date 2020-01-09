// ysoftman
fn main() {
    println!("{}", hello_cargo::add(1));

    // 불변(immutable) 변수 생성시
    let aaa = "aaaa";
    // 가변(mutable) 변수 생성시 mut 을 사용
    let mut bbb = "bbbb";
    // aaa 값을 변경할 수 없다.
    // aaa = "bbb";
    // {} 변경자(placholder)로 변수별 출력 위치 지정
    println!("{} {}", aaa, bbb);

    // 가변 변수라 값을 바꿀 수 있다.
    // to_string() 으로 스트링으로 변환해야 한다.
    bbb = "lemon";
    println!("{} {}", aaa, bbb);

    hello_cargo::guess_game();
}
