// friend 모듈의 내용
// friend::list() 가 된다.
pub fn list() {
    println!("bill, yoon, ysoftman...");

    other::list();
}

// friend 모듈에서 other 모듈껍데기만 만든다.
// 모듈 안에 모듈에 반복되는 경우 friend 디렉토리를 만들어야 한다.
mod other;
