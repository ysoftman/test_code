// ysoftman
// string test
// rust 에서는 스트링 슬라이스(바이너리 어딘가에 저장되는)str 와 컬렉션으로 힙에 데이터를 저장하고는 String 라이브러리가 있다.
fn main() {
    // String 생성방법들
    let s1 = String::new(); // 빈스트링
    let string_data = "ysoftman2"; // str 생성
    let s2 = string_data.to_string();
    let s3 = "ysoftman3".to_string();
    // 중간 str 변수 없이 String 생성시 String::from() 사용
    // rust 의 스트링은 utf8로되어 있다.
    let s4 = String::from("안녕하세요.");

    println!("s1 {}", s1);
    println!("s2 {}", s2);
    println!("s3 {}", s3);
    println!("s4 {}", s4);

    // string -> str 로 참조
    // as_str() 사용
    let str1 = s4.as_str();
    println!("str1 {}", str1);
    // 슬라이싱 사용
    let str2 = &s4[..];
    println!("str2 {}", str2);

    // String 갱신
    let mut s5 = String::from("ysoftman");
    s5.push_str(",");
    s5.push_str(" bill");
    s5.push('!');
    let temp = "temp";
    // push_str 는 스트링슬라이스(&str)을 사용하기 때문에 소유권을 가져오지 않는다.
    s5.push_str(&temp);
    // 그래서 temp 를 출력할 수 있다.
    println!("temp {}", temp);
    println!("s5 {}", s5);

    // 스트링 더하기
    let s6 = String::from("lemon");
    let s7 = "orange0";
    let s8 = String::from("orange1");
    let s9 = String::from("orange2");
    // + 연산은 표준라이브러리의 add() 제너릭 메소드가 사용되며
    // 다음과 같이 스트링 슬라이스 참조를 사용한다.
    // fn add(self, s: &str) -> String {
    // 그리고 &String -> &str 로 강제될 수 있다.
    let s10 = s6 + "," + &s7 + "," + &s8 + "," + &s9;
    println!("s10 {}", s10);
    // s7 ~s9 스트링 슬라이스 참조해 소유권이 이동하지 않는다.
    println!("s7 {}", s7);
    // s6 소유권이 s10 로 이동돼 더이상 유효하지 않다.
    // println!("s6 {}", s6);

    // + 대신 format() 을 사용하는것이 코드를 읽기 쉽다.
    let s11 = format!("{},{},{}", s7, s8, s9);
    println!("s11 {}", s11);

    let s12 = "y안녕하세요!";
    // rust str 은 utf8이라 [0][1] 등으로 인덱싱은
    // 바이트 하나로 유효한 문자가 아닌경우가 있을 수 있어 허용하지 않는다.
    // println!("s12 {}", &s12[0]);
    // 대신 범위를 지정으로 액세스는 가능하다.
    // String, str 모두 슬라이스로 접근해야 한다.
    println!("&s12[0..1] {}", &s12[0..1]); // -> y 출력
    println!("&s9[0..1] {}", &s9[0..3]);

    // 하지만 한글과 같이 2바이트이상으로 문자가 형성되는 경우 잘못 인덱싱하면 panic 이 발생하니 주의가 필요하다.
    // println!("s12 {}", &s12[1..3]);  // panic 발생!

    println!("&s12[1..4] {}", &s12[1..4]); // -> 안 출력

    // 문자단위로 안전하게 인덱싱하려면 chars() 를 이용한다.
    for ch in s12.chars() {
        print!("{} ", ch);
    }
    println!("");
    // 바이트 단위로 구분할 경우
    for by in s12.bytes() {
        print!("{} ", by);
    }
    println!("");
}
