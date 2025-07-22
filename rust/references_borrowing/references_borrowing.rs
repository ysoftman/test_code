// ysoftman
// references and borrowing
// 참조자 규칙 - 하나의 가변 참조자를 갖는다. or 여러개의 불변 참조자를 갖는다.
fn main() {
    let mut s1 = String::from("ysoftman");
    // references(참조자로) s1 을 주면 소유권이 넘어가지 않는다.
    let len = calc_length(&mut s1);
    println!("s1:{s1}\ns1 len:{len}");

    // 한 스코프안에선 2번 이상 참조될 수 는 없다.
    // let s2 = &mut s1;
    // 별도의 스코프를 만들면 된다.(어차피 스코프를 벗어나면 drop 되니까)
    {
        let s2 = &mut s1;
        println!("s2:{s2}");
    }
    let s3 = &mut s1;
    println!("s3:{s3}");

    // 불변 참조차는 여러번 참 할 수 있다.
    // 하지만 가변,불변을 같은 스코프내에서 같이 사용하면 안된다.
    // 참고로 사용하지 않는 변수라면 _를 앞에 붙여주면 경고가 발생하지 않는다.
    // let _s4 = &s1;
    // let _s5 = &s1;
    let s4 = &s1;
    let s5 = &s1;
    // 하지만 불변 참조후 가변 참조를 같은 스코프내에서 같이 사용하면 안된다.
    // 불변은 읽기만 해서 괜찮은데 가변 참조 s6 으로 s4, s5 값이 바뀔 수 있는 경우를 방지하기 위해 같이 에러가 발생한다.
    // let s6 = &mut s1;
    println!("s4:{s4}");
    println!("s5:{s5}");

    // let d = dangling();
    let nod = no_dangling();
    println!("nod:{nod}");
}

// calc_length 에서는 s 를 borrowing(빌린다. 소유권은 없다.)
fn calc_length(s: &mut String) -> usize {
    println!("calc_length() s:{s}");
    s.push_str(", lemon");
    s.len()
}

// s 참조자값  dangling() 스코프를 벗어나면 drop 되서 무효화 된다.
// 결국 dangling pointer 값을 리턴하는 꼴이 된다.
// fn dangling() -> &String {
//     let s = String::from("apple");
//     &s
// }

// string 값을 리턴하면 값이 전달되기 때문에 괜찮다.
fn no_dangling() -> String {
    String::from("apple")
}
