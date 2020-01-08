// 테스트수행 및 모듈화를 위해 lib.rs(라이브러리) 에 로직을 구현하고 main.rs(바이너리) 에서는 최소한의 코드만 유지한다. rust 라이브러리만 테스트한다.
// cargo test 로 테스트해보자
use std::env;
use std::error::Error; // Error trait
use std::fs::File;
use std::io::prelude::*; // read_to_string()

pub struct Config {
    query: String,
    filename: String,
    case_insensitive: bool, // 대소문자 구별 여부
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

        // 대소문자 옵션은 환경변수로 부터 받는다.
        // var 는 Result 타입을 리턴하고 Result의 is_err() 메소드로 에러 판단
        // CASE_INSENSITIVE 환경변수가 설정되어 있으면 is_err() 는 false 리턴,
        // let case_insensitive = env::var("CASE_INSENSITIVE").is_err();
        // CASE_INSENSITIVE 환경변수가 설정되어 있으면 is_ok() 는 true 리턴,
        let case_insensitive = env::var("CASE_INSENSITIVE").is_ok();
        print!("case_insensitive:{}\n", case_insensitive);
        Ok(Config {
            query,
            filename,
            case_insensitive,
        })
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

    // 대소문자 구별 옵션에 따라 분기
    let results = if config.case_insensitive {
        // search()로 contents 에서 query 가 포함된 라인들(Vector)을 출력, 대소문자 구별 안함
        // results 불변 변수에 할당 라인이 끝이 아니기 때문에 ; 쓰면 안된다.(3항연사자와 비슷)
        search_case_insensitive(&config.query, &contents)
    } else {
        // search()로 contents 에서 query 가 포함된 라인들(Vector)을 출력, 대소문자 구별
        // results 불변 변수에 할당 라인이 끝이 아니기 때문에 ; 쓰면 안된다.(3항연사자와 비슷)
        search(&config.query, &contents)
    };
    for line in results {
        println!("[query:{} 가 있는 라인]\n{}", config.query, line);
    }
    // 이상 없으면 OK unit(nil, ()) 리턴
    Ok(())
}

// contents 을 리턴과 lifetime 문법으로 연결시킨다.
pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    let mut results = Vec::new();

    // query 가 포함된 라인을 벡터로 저장
    for line in contents.lines() {
        if line.contains(query) {
            results.push(line);
        }
    }
    results
}

pub fn search_case_insensitive<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    // 소문자로 변경
    let query = query.to_lowercase();
    let mut results = Vec::new();
    for line in contents.lines() {
        // 라인들 소문자로 변경해서 비교
        // 위에서 query 슬라이스가 아닌 to_lowercase() 는 스트링을 리턴해
        // contain()의 &str 슬라이스 인자를 &query(&String타입) 로 써야 한다.
        // &String -> &str 로 쓸 수 있다.
        if line.to_lowercase().contains(&query) {
            results.push(line)
        }
    }
    return results;
}

#[cfg(test)]
mod rustgreptest {
    // 같은 파일에 있지만 rustgreptest 테스트 모듈 밖에 있는 search() 등의 함수들을 사용하기 위해
    // rustgreptest 모듈내에서 사용해야 한다.
    use super::*;

    #[test]
    fn test1() {
        let query = "duct";
        let contents = "\
Rust:
safe, fast, productive.
Pick  three.";
        assert_eq!(vec!["safe, fast, productive."], search(query, contents))
    }

    #[test]
    fn test2_case_insensitive() {
        let query = "FAsT";
        let contents = "\
Rust:
safe, fast, productive.
Pick  three.";
        assert_eq!(
            vec!["safe, fast, productive."],
            search_case_insensitive(query, contents)
        )
    }
}
