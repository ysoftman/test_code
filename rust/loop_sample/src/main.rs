// ysoftman
// 반복문 테스트
fn main() {
    let mut i = 0;
    let arr = [1, 2, 3, 4, 5, 6, 7];
    loop {
        if i >= 7 {
            break;
        }
        println!("arr[{}] : {}", i, arr[i]);
        // i++는 사용 못함
        // i++;
        i += 1;
    }
    i = 0;
    let l = loop {
        if i >= 7 {
            break "브레이크로 루프를 빠져 나가고 이 문장을 리턴";
        }
        println!("--> arr[{}] : {}", i, arr[i]);
        // i++는 사용 못함
        // i++;
        i += 1;
    };
    println!("break return: {l}");

    i = 0;
    // loop 레이블 명시해서 중첩 반복 탈출(c,golang 에서 goto 효과)
    'outer_loop: loop {
        println!("outer_loop {i}");
        loop {
            i += 1;
            println!("inner loop {i}");
            if i >= 10 {
                break 'outer_loop; // outer_loop 를 탈출
            }
            // outer_loop 가 loop (2번 이상 반복)되지 않으면 #[deny(clippy::never_loop)] 조건으로 경고 발생
            if i == 7 {
                break;
            }
        }
    }

    i = 0;
    while i < 7 {
        println!("arr[{}] : {}", i, arr[i]);
        i += 1;
    }
    i = 0;
    for ele in arr.iter() {
        println!("arr[{i}] : {ele}");
        i += 1;
    }

    // a(포함)..b(미포함) 으로 1-10 반복
    for n in 1..11 {
        println!("n:{n}");
    }

    // a(포함)..=b(포함) 으로 1-10 반복
    for n in 1..=10 {
        println!("n:{n}");
    }

    // 10-1 역순으로 반복
    for n in (1..11).rev() {
        println!("n:{n}");
    }

    // vec! 를 사용할 필요가 없다.
    // let vec = vec!["lemon", "orange", "banana"];
    let vec = ["lemon", "orange", "banana"];
    // enumerate()로 반복자값에 대한 index 를 추가해 튜플을 만들어 준다.
    for (index, value) in vec.iter().enumerate() {
        println!("index:{index} value:{value}");
    }
}
