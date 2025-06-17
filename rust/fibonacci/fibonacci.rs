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
    fibonacci(i - 1) + fibonacci(i - 2)
}

fn main() {
    for i in 0..11 {
        println!("fibonacci:{} -> {}", i, fibonacci(i));
        // i 는 immutable 변수라 할당 할 수 없다.
        // i += 1;
    }

    println!("fibonacci2:10 ----> {} ", fibonacci2(10));
}

fn fibonacci2(n: i32) -> i32 {
    let mut ppre = 0;
    let mut pre = 1;
    let mut result = 0;
    for i in 0..=n {
        if i <= 1 {
            result = i;
        } else {
            result = ppre + pre;
        }
        println!("{}:{}", i, result);
        ppre = pre;
        pre = result;
    }
    result
}
