// ysoftman
// casting test

fn main() {
    // literal 참고 https://doc.rust-lang.org/reference/expressions/literal-expr.html
    // 32bit floating liternal 표현들
    let real_number = 65.345_f32;
    println!("real_number:{real_number}");
    let real_number = 65.345f32;
    println!("real_number:{real_number}");

    // imiplicit(암묵적) conversion 은 에러
    // let int_number: u32 = real_number;
    // explicit(명시적) conversion 가능 as 키워드를 사용한다.
    let int_number = real_number as u32;
    println!("int_number:{int_number}");
    let int_number = real_number as u8;
    println!("int_number:{int_number}");
    // u8 -> char 로 캐스팅 가능
    let character = int_number as char;
    println!("character:{character}");

    // u32 -> f32 로 캐스팅
    let real_number = int_number as f32;
    println!("real_number:{real_number}");
}
