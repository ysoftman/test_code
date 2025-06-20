// friend 모듈의 내용
// friend::list() 가 된다.
pub fn list() {
    println!("bill, yoon, ysoftman...");

    other::list();
}

// friend 모듈에서 other 모듈껍데기만 만든다.
// other.rs  파일명이 모듈명이라 사용할 수 있다.
mod other;
