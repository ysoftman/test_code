// ysoftman
// error test

use std::fs::File;
use std::io;
use std::io::ErrorKind;
use std::io::Read;

// RUST_BACKTRACE=full 환경변수로 백트레이스를 볼 수 있다.
// rm -f error.tmp.txt error2.txt; rustfmt error.rs && rustc error.rs && RUST_BACKTRACE=full ./error
fn main() {
    // panic!("일부러 패닉 발생!");

    // let v = vec![1, 2, 3];
    // vec library 에서 패닉 발생
    // v[100];

    // open 리턴은 다음과 같은 Result 다.
    // enum Result<T,E> {
    //     OK(T),
    //     Err(E),
    // }

    let f = File::open("error.tmp.txt");
    // Result 타입결과에 따라 match 로 분기
    let _f = match f {
        // prelude 되어 있어 Result:: 를 명시하지 않는다.
        // 파일 열기가 성공했을 경우
        Ok(file) => {
            println!("파일 열기 성공~");
            file
        }
        // 파일이 없기 때문에 에러가 발생한 경우
        // File::open 는 Reulst Err variant 는 io::error 타입이다.
        // io::ErrorKind 로 에러 종류를 체크할 수 있다.

        // if error.kind() == ErrorKind::NotFound 이부분을 match guard 라 하는데,
        // error 가 match guard 로 소유권이 넘어가지 않도록 참조라를 사용해야 하는데
        // Err() 패턴에서 참조자를 얻기 위해선 ref 를 사용한다.
        // & 는 참조자를 매치하고 값을 제공
        // ref 는 값을 매치하고 그 참조자를 제공
        Err(ref error) if error.kind() == ErrorKind::NotFound => {
            // 파일이 없으면 생성
            match File::create("error.tmp.txt") {
                Ok(file) => {
                    println!("파일을 새로 생성했습니다!");
                    file
                }
                Err(error) => panic!("파일 생성에 있어 패닉이 발생했습니다. {:?}", error),
            }
        }
        // 그 밖의 파일 열기가 실패한 경우
        Err(error) => panic!("파일 열때 문제가 있어 패닉이 발생했습니다. {:?}", error),
    };

    // Result Err 가 리턴되면 unwrap 은 자동으로 패닉을 발생합니다.
    // let _f = File::open("error2.txt").unwrap();
    // Result Err 가 리턴되면 expect 은 자동으로 지정된 메시지와 함께 패닉을 발생합니다.
    // let _f = File::open("error2.txt").expect("파일을 열 수 없습니다.");

    let ret = read_from_file();
    match ret {
        Ok(_) => println!("파일 내용 읽기 성공!"),
        Err(e) => println!("파일 내용 읽기 실패\nerr => {:?}", e),
    }
}

fn read_from_file() -> Result<String, io::Error> {
    let mut s = String::new();
    // ? 연산자는 Result 리턴인 경우에만 사용할 수 있다.
    // ? 로 File::open의 Result 리턴이 Ok 라면 계속 진행, Err 라면 리턴
    // let mut f = File::open("error3.txt")?;
    // ? 로 read_to_string의 Result 리턴이 Ok 라면 계속 진행, Err 라면 리턴
    // f.read_to_string(&mut s)?;
    // 다음과 같이 chaining 방식으로도 사용할 수 있다.
    File::open("error3.txt")?.read_to_string(&mut s)?;
    Ok(s)
}
