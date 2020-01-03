// my_mod(library crate)사용을 위한 binary crate
// 이 파일은 my_mod crate 와는 별개의 binary crate 이다.
// 외부의 my_mod 사용
extern crate my_mod;

fn main() {
    // my_mod unsed function 경고를 없애기 위해 사용
    my_mod::fruit::list();
    my_mod::friend::list();
}
