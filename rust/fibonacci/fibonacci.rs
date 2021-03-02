// ysoftman
// fibonacci test
// 0,1,1,2,3,5,8,13,21,34,55 ...
// rustfmt ./fibonacci.rs && rustc ./fibonacci.rs && ./fibonacci
fn fibonacci(i: i32) -> i32 {
    if i <= 1 {
        return i;
    }
    // let num = fibonacci(i - 1) + fibonacci(i - 2);
    // num
    return fibonacci(i - 1) + fibonacci(i - 2);
}

fn main() {
    for i in 0..11 {
        println!("fibonacci:{} -> {}", i, fibonacci(i));
        // i 는 immutable 변수라 할당 할 수 없다.
        // i += 1;
    }
}
