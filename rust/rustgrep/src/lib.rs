// 테스트 및 모듈화를 위해 lib.rs(라이브러리) 에 로직을 구현하고 main.rs(바이너리) 에서는 최소한의 코드만 유지한다.

use std::error::Error; // Error trait
use std::fs::File;
use std::io::prelude::*; // read_to_string()

pub struct Config {
    query: String,
    filename: String,
}
impl Config {
    // 에러 처리에 친화적인 Resuslt<성공일때, 에럴일때> 타입으로 리런
    pub fn new(args: &[String]) -> Result<Config, &'static str> {
        println!("{:?}", args);

        if args.len() < 3 {
            return Err("인자가 개수가 3개 보다 적습니다.");
        }

        // 비용은 들지만 직관적인 클론으로 데이터를 복사한다.
        let query = args[1].clone();
        let filename = args[2].clone();
        Ok(Config { query, filename })
    }
}

// Box<Error>는 Error trait(특성,인터페이스) 타입
// trait objects without an explicit `dyn` are deprecated
pub fn run(config: Config) -> Result<(), Box<dyn Error>> {
    // 파일이 없으면 expect 로 패닉 발생
    // let mut f = File::open(config.filename).expect("file not found");
    // ? 로 패닉없이 Result Err 이면 리턴, Ok이면 계속 진행
    let mut f = File::open(config.filename)?;
    let mut contents = String::new();
    // 파일 내용을 contents 로 읽어 들인다.
    // f.read_to_string(&mut contents).expect("파일을 읽기에 문제가 발생했습니다.");
    // ? 로 패닉없이 Result Err 이면 리턴, Ok이면 계속 진행
    f.read_to_string(&mut contents)?;
    println!("[파일내용]\n{}", contents);
    // 이상 없으면 OK unit(nil, ()) 리턴
    Ok(())
}
