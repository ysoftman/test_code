// ysoftman
// while let test

fn main() {
    let mut stack = Vec::new();
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    /*
    for _ in 0..stack.len() {
        // pop() 한 내용을 출력
        let some_value = stack.pop();
        match some_value {
            Some(1) => println!("1"),
            Some(2) => println!("2"),
            Some(3) => println!("3"),
            Some(4) => println!("4"),
            Some(5) => println!("5"),
            // match Options 이 가질 수 있는 모든 값을 다 명시해야 한다.
            // 그밖에...
            _ => (),
        }
    }
    */

    // 위 문장을 while let 로 짧게 표현할 수 있다.
    while let Some(s) = stack.pop() {
        println!("{}", s);
    }
}
