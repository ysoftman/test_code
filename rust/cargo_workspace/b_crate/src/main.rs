// a_crate 사용
extern crate a_crate;
fn main() {
    println!("use a_crate...");
    let num = 10;
    println!("a_create::add_ten(10) : {}", a_crate::add_ten(num));
    println!(
        "a_crate::get_random_number(): {}",
        a_crate::get_random_number()
    );
}
