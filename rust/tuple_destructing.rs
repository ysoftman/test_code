fn main() {
    // tuple 타입(형식이 다른 데이터 묶음)
    let tup1: (i32, f64, u8) = (500, 12.34, 10);
    let tup2 = (550, 34.56, 9);
    println!("tup1.0:{}", tup1.0);
    println!("tup1.1:{}", tup1.1);
    println!("tup1.2:{}", tup1.2);

    // 구조해체(destructing)
    let (aa, bb, cc) = tup2;
    println!("tup2:{}", aa);
    println!("tup2:{}", bb);
    println!("tup2:{}", cc);
}
