// ysoftman
// raw string literal test

fn main() {
    // 일반적인 스트링 사용시 double quotation 을 escape 해줘야 한다.
    let s = "I'm ysoftman, ## __ \"hello\"".to_string();
    println!("{s}");

    // r#""# 형식의 raw 스트링으로 사용할 수 있다.
    let raw_s = r#"I'm ysoftman, ## __ "hello""#;
    println!("{raw_s}");

    // json 등의 데이터를 raw 스트링을 처리하기에 좋다.
    let json_s = r#"{
        "name": "ysoftman",
        "age": 30,
        "fruits": [
            "lemon",
            "orange",
            "apple"
        ]
    }"#;
    println!("{json_s}");

    //파일 같은 큰 문자열을 읽을때 include_str! 매크로 사용
    let big_text = include_str!("big_text.txt");
    println!("{big_text}")
}
