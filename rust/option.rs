// ysoftman
// option test
// rust 에서는 null 이 없고 대신 Option 이라는 enum 으로 Some(value,type 의 튜플) 또는 None(실패나 값이 없음을 의미) 을 나타낸다.
// enum Option<T> {
//     Some(T),
//     None,
// }
fn main() {
    let val1 = Some(123);
    let val2 = Some(555);
    let val3 = Some("ysoftman");
    // None 는 타입 추론을 할 수 없어 타입을 지정해야 한다.
    let none_val: Option<i32> = None;

    // Some 은 값이 없을 수도 있기 때문에 match None 에 대한 처리를 해야 한다.
    let temp_val1 = match val1 {
        None => 0,
        Some(v) => v,
    };
    let temp_val2 = match val2 {
        None => 0,
        Some(v) => v,
    };

    // Option 타입은 디폴트포맷터({})를 사용할 수 없고 {:?}를 사용해야 한다.
    println!(
        "val1 {:?} + val2 {:?} = {}",
        val1,
        val2,
        temp_val1 + temp_val2
    );
    println!("val3 {:?} ", val3);
    println!("none_vale {:?} ", none_val);
}
