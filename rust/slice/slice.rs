// ysoftman
// slice test

fn main() {
    // 0으로 초기화된 512 바이트 크기의 버퍼
    let buffer = [0; 512];
    println!("buffer: {}", buffer.len());
    println!("buffer: {}", buffer[0]);

    let num = [1, 2, 3, 4, 5];
    println!("num:{}", num[1]);
    // 슬라이스는 &로 참조해서 사용해야 한다.
    println!("num:{}", &num[1]);
    // 슬라이스 1~2까지
    println!("num:{:?}", &num[1..3]);

    // 2~3 슬라이스 값을 참조
    let num2: &[i32] = &num[2..4];
    println!("num2:{:?}", &num2);

    let mut s = String::from("lemon apple orange");
    println!("s:{}", s);
    // 슬라이스 전체
    println!("{}", &s[..]);
    // 슬라이스 0~4까지
    println!("{}", &s[..5]);
    // 슬라이스 6~10까지
    println!("{}", &s[6..11]);
    // 슬라이스 12~끝까지
    println!("{}", &s[12..]);
    // 슬라이스 12~끝까지
    println!("{}", &s[12..s.len()]);

    let fw = first_word(&s);
    println!("first_word:{}", fw);

    s.clear();
    println!("s:{}", s);
}

// &str 는 스트링 슬라이스를 나타낸다.
// s: &String 과 s: &str 모두 가능
// fn first_word(s: &String) -> &str {
fn first_word(s: &str) -> &str {
    let bytes = s.as_bytes();
    for (i, &value) in bytes.iter().enumerate() {
        // b''는 아스키 byte 문자 하나를 나타내는 literal 이다.
        if value == b' ' {
            // slice 를 이용해서 첫번째 단어의 참조값을 리턴한다.
            return &s[..i];
        }
    }

    // 공백 구분이 없으면 s 전체
    &s[..]
}
