// ysoftman
// drop trait test

struct Dummy {
    data: String,
}

// Drop trait 을 정의해 스코프가 벗어날때 drop 동작을 커스터마이징 할 수 있다.
impl Drop for Dummy {
    fn drop(&mut self) {
        println!("Dropping with data {}", self.data);
    }
}

fn main() {
    let a = Dummy {
        data: String::from("ysoftman1"),
    };
    let b = Dummy {
        data: String::from("ysoftman2"),
    };
    println!("a.data:{}", a.data);
    println!("b.data:{}", b.data);
    // 스코프를 벗어나면 b -> a 순서로 drop 된다.
    // 스코프를 벗어나기 전에 강제 drop 을 호출을 허용하지 않는다.(컴파일 에러)
    // rust 는 스코프를 벗어나면 자동 drop 호출되는것은 변하지 않기 때문에
    // 여기서 drop()을 허용하면 스코프를 벗어날때 또 drop() 호출되어 double free 되는 문제가 있기 때문이다.
    // a.drop();
    // 대신 표준 라이브러리 std::mem::drop() 함수를 사용할 수 있다.
    std::mem::drop(a);
    // println!("a.data:{}", a.data);

    println!("Dummy pointers created.");
}
