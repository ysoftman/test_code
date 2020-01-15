// ysoftman
// web server test

extern crate web_server;
use web_server::ThreadPool;

use std::fs::File;
use std::io::prelude::*;
use std::net::TcpListener;
use std::net::TcpStream;
// use std::thread;
// use std::time::Duration;

fn main() {
    let listener = TcpListener::bind("127.0.0.1:9090").unwrap();
    // 많은 요청 처리를 위해 5개의 쓰레드를 가진 쓰레드풀 생성
    // ThreadPool 은 lib.rs 모듈에 crate 및 구현해놨다.
    let thread_pool = ThreadPool::new(5);
    // let listener = TcpListener::bind("localhost:9090").unwrap();
    // incoming()으로 리스터로 들어오는 스트림들의 반복자들 받을 수 있다.
    // 서버 종료시 drop 되는 과정을 테스트하기 위해 2개의 요청받고 끝내도록 한다.
    // for stream in listener.incoming().take(2) {
    for stream in listener.incoming() {
        let stream = stream.unwrap();
        // println!("connection established!");

        // 요청 처리마다 매번 쓰레드 생성
        // 쓰레드 생성 비용도 있고, 무한정 쓰레드 생성은 시스템 과부하로 이어진다.
        // thread::spawn(move || {
        //     handler1(stream);
        // });

        // 요청을 쓰레드풀로 처리
        thread_pool.execute(|| handler1(stream))
    }

    println!("shutting down.");
}

// 수신된 tcp 스트림 핸들링
fn handler1(mut stream: TcpStream) {
    // 0으로 초기화된 512바이트 버퍼 생성
    let mut buffer = [0; 512];
    // 스트림을 버퍼로 읽기
    stream.read(&mut buffer).unwrap();
    // from_utf8_lossy() 는 u8 -> String 으로 변경하는데 유효하지 않는 문자들에 대해서는 U+FFFD REPLACEMENT CHARACTER 로 치환된다.
    // 바이트로 데이터로 채워진 buffer 를  String 으로 변환해 출력
    println!("[Request]\n{}", String::from_utf8_lossy(&buffer[..]));

    // / 요청이 온 경우(바이트문자열)
    // let get_root_path = b"GET / HTTP/1.1\r\n";
    let get_root_path = "GET / HTTP/1.1\r\n".as_bytes();
    let head_root_path = "HEAD / HTTP/1.1\r\n".as_bytes();
    let (status_line, file_name) =
        if buffer.starts_with(get_root_path) || buffer.starts_with(head_root_path) {
            ("HTTP/1.1 200 OK", "hello.html")
        } else {
            ("HTTP/1.1 404 NOT FOUND", "404.html")
        };
    let headers = "Content-Type: text/html\r\nConnection: Closed";

    // html 으로 응답주기
    // let mut file = File::open("hello.html").unwrap();
    // let mut f = File::open("hello.html");
    let mut file = match File::open(file_name) {
        Ok(o) => o,
        Err(e) => {
            println!("read {} - Error: {:?}", file_name, e);
            return;
        }
    };
    let mut contents = String::new();
    let err = file.read_to_string(&mut contents);
    match err {
        Ok(_) => (),
        Err(e) => println!("error! read to string {:?}", e),
    }

    let response = format!("{}\r\n{}\r\n\r\n{}", status_line, headers, contents);
    // 스트림을 통해 응답 주기
    stream.write(response.as_bytes()).unwrap();
    stream.flush().unwrap();
    println!("[response]\n{}", response);
}
