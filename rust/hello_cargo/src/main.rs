// ysoftman
// cargo.toml 에 명시된 외부의 rand crate(크레이트) 는 패키지를 가져온다
extern crate rand;

// prelude 로 std 내의 타입 가져오기
// 표준 입출력
use std::cmp::Ordering;
use std::io;
// 이제 rand 라이브러리를 사용할 수 있다.
use rand::Rng;

fn main() {
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

    // String 표준 라이브러리에서 제공하는 UTF-8 인코딩 문자열
    // ::new() String 내의 new() 함수
    // String 인스턴스와 연결되 가변 변수 생성
    let mut guess = String::new();

    println!("Please input your guess.");

    // 1~100 중 랜덤값
    // thread_rng() os 가 seed 정하고 현재 쓰레드에서만 사용
    let rand_num = rand::thread_rng().gen_range(1, 101);
    println!("rand_num:{}", rand_num);

    // 무한 루프
    loop {
        // use 가 없다면 std::io::stdin() 처러 전체 명시
        // & 는 값복사를 하진 않기 위한 참조자
        // Ok 또는 Err 를 갖는 io::Result 인스턴스의 expect 함수로
        // 이부분을 빼면 컴파일시 경고가 나온다.
        // read_line 에 Err 발생하면 expect 는 "Failed to read line" 출력하고 프로그램을 중단한다.(일종의 에러 처리)
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");
        println!("You guessed: {}", guess);

        println!("generate random...");

        // guess 를 usinged int 32 로 받는다.
        let guess_u32: u32 = guess.trim().parse().expect("Please type a number!");

        // 입력 숫자와 랜덤 값과 크기 비교
        match guess_u32.cmp(&rand_num) {
            Ordering::Less => println!("Too small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                // 값이 같으면 무한 루프 종료
                println!("You win!");
                break;
            }
        }

        // guess 클리어
        guess = "".to_string();
    }
}
