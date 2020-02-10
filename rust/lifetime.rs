// ysoftman
// lifetime test
// lifetime(생애주기)는 특정시간만큼 살아있음을 나타낸다.
// 모든 참조자는 lifetime 이 있고 컴파일러에 의해 암묵적으로 추론될 수 있다.
// 추론될 수 없는 경우 lifetime 을 명시해 파라미터간 서로 연관 짓도록 한다.

fn main() {
    // rust 는 초기화되지 않는 변수를 사용할 수 없다.alloc
    // 아래 스코프가 없으면 에러가 발생하지만
    // 아래 스코프내에서 x 값을 초기화해 컴파일 된다.
    let x;
    {
        let y = 5;
        x = y;

        // y 는 스코프를 벗어나면 drop 되는데
        // x 가 y 주소를 참고 하고 있어 '오래살수없는' 라이프타임 에러가 발생해
        // dangling reference 방지할 수 있다.
        // borrowed value does not live long enough
        // x = &y
    }
    println!("x:{}", x);

    let a = "ysoftman";
    let b = "lemon_apple_orange";
    println!("longest_string : {}", longest_string(a, b));

    // 'static 전체 생애주기(lifetime)를 갖는다.
    let mystr: &'static str = "ysoftman my string";
    println!("{}", mystr)
}

// &str 로 빌림(borrowed)리턴하면 x 또는 y 어디로부터 빌림하는지
// 컴파일 타임에 알수 없고, x,y 가 항상 유효한지 컴파일러가 알 수 없다.
// fn longest_string(x: &str, y: &str) -> &str {
//     if x.len() > y.len() {
//         x
//     } else {
//         y
//     }
// }

// 따라서 다음과 같이 string 값으로 리턴할 수도 있다.
// fn longest_string(x: &str, y: &str) -> String {
//     if x.len() > y.len() {
//         x.to_string()
//     } else {
//         y.to_string()
//     }
// }

// 또는 제너릭으로 lifetime 파라미터로 명시(표기)해 라이프타임을 서로 연관짓는다.
// lifetime 파라미터 명시는 '로 시작하고 짧은소문자로 보통 a를 써서 'a 로 많이 쓴다.('aa, 'b 등등 모두 가능)
// 아래 함수에서 'a 라이프타임 명시로 x, y 의 구제적인 라이프타임과
// 리턴에 사용된다는 관계를 컴파일러에게 알려줘
// 스코프가 벗어나도 유효한 리턴을 줄 수 있다.
// 시그니처에만 'a 를 명시하면 함수 내용은 컴파일러가 추론 할 수 있다.
fn longest_string<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}
