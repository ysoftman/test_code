// ysoftman
// rust grep 구현
// 실행 - poem.txt 텍스트 파일에서 frog,body 가 포함된 라인을 출력한다.
// cargo run frog poem.txt
// cargo run body poem.txt
// 실행 - 대소문자 무시하기 환경변수 사용
// CASE_INSENSITIVE=1 cargo run DAY poem.txt

// rustgrep 모듈(패키지)를 불러오고
extern crate rustgrep;
// rustgrep 모듈의 Config struct 를 사용
use rustgrep::Config;

use std::env; // command line args 읽기위한 args()
use std::process;

fn main() {
    // args() 의 결과는 반복자(iterator)인데 이를 collect() 로 벡터로 변환한다.
    // collect() 사용시 타임 추론을 할수 없어 Vec<String> 타입을 명시해야 한다.
    // let args: Vec<String> = env::args().collect();

    // config new 로 생성시 cli arguments 파싱
    // unwrap_or_else() 는 Err 발생시 Err 값을 err 인자로 전달하고 클로저(익명함수) 수행
    // let config = Config::new(&args).unwrap_or_else(|err| {
    // Config new 에서 반복자로 env::args()의 소유권을 넘겨받도록 한다.
    let config = Config::new(env::args()).unwrap_or_else(|err| {
        // stderr 로 출력
        eprintln!("파싱 에러:{}", err);
        // panic! 의 불필요한 메시지를 출력하지 않기 위해 exit()사용
        process::exit(1);
    });

    // run 이 Err 를 리턴할때 처리, 성공하면 () 를 리턴
    if let Err(e) = rustgrep::run(config) {
        eprintln!("run 에러 {}", e);
        process::exit(1);
    }
}
