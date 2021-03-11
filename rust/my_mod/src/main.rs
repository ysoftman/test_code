// 이 파일은 my_mod(library crate, lib.rs)사용을 위한 binary crate(main.rs)
// 이 파일은 my_mod crate 와는 별개의 binary crate 이다.

// 외부의 my_mod 사용
extern crate my_mod;

// binary 내에서 모듈 정의
mod lemon {
    pub mod apple {
        pub mod orange {
            pub fn juice() {
                println!("orange juice!");
            }
        }
    }
}

// use 로 스코프를 명시를 줄일 수 있다.
use lemon::apple::orange;
use lemon::apple::orange::juice;

// 별도 파일로 된 모듈 사용, 모듈명과 파일명이 같아야 한다.
mod banana;

fn main() {
    // my_mod unsed function 경고를 없애기 위해 사용
    my_mod::fruit::list();
    my_mod::friend::list();

    lemon::apple::orange::juice();

    // use lemon::apple::orange; 를 사용한 경우
    orange::juice();

    // use lemon::apple::orange::juice; 를  사용한 경우
    juice();

    // banana.rs 모듈 함수 실행
    banana::print_banana();
}
