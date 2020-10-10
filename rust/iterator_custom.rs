// ysoftman
// 커스텀 iterator(반복자) test

use std::collections::HashMap;

#[derive(Debug)]
struct Counter {
    count: u32,
}

impl Counter {
    fn new() -> Counter {
        Counter { count: 0 }
    }
}

// Counter 를 위한 커스텀 반복자 trait(트레잇) 생성
// 반복자 트레잇은 Item 과 next() 메소드를 정의해야 한다.
// rust 에서 Iterator trait 을 어떻게 정의하고 있는지 참고하면 좋다.
impl Iterator for Counter {
    type Item = u32;
    fn next(&mut self) -> Option<Self::Item> {
        self.count += 1;
        if self.count < 6 {
            Some(self.count)
        } else {
            None
        }
    }
}

fn main() {
    let mut counter = Counter::new();

    // counter 의 커스텀 반복자 트레잇의 next() 메소드를 사용
    assert_eq!(counter.next(), Some(1));
    assert_eq!(counter.next(), Some(2));
    assert_eq!(counter.next(), Some(3));
    assert_eq!(counter.next(), Some(4));
    assert_eq!(counter.next(), Some(5));
    assert_eq!(counter.next(), None);

    // collect() 는 iterator 를 관련있는 collection(컬렉션, vector, string, hash map등)으로 변환시켜 준다.
    // [1,2,3,4,5]
    let temp: Vec<u32> = Counter::new().collect();
    println!("{:?}", temp);
    // 1번째 요소 건너뛰어 [2,3,4,5]
    let temp: Vec<u32> = Counter::new().skip(1).collect();
    println!("{:?}", temp);
    // zip()으로 위 2개 벡터를 쌍으로 묶는다.
    // {1: 2, 4: 5, 3: 4, 2: 3} 으로 vec1의 5에 대한 쌍이 없으면(None) 생성되지 않음
    let temp: HashMap<_, _> = Counter::new().zip(Counter::new().skip(1)).collect();
    println!("{:?}", temp);
    // key * value 값을 벡터로 [2, 6, 12, 20]
    let temp: Vec<_> = Counter::new()
        .zip(Counter::new().skip(1))
        .map(|(a, b)| a * b)
        .collect();
    println!("{:?}", temp);
    // 이 벡터에서 3의 배수만 필터링해서 [6, 12]
    let temp: Vec<_> = Counter::new()
        .zip(Counter::new().skip(1))
        .map(|(a, b)| a * b)
        .filter(|x| x % 3 == 0)
        .collect();
    println!("{:?}", temp);
    // 필터링된 벡터의 합을 구한다.
    let sum: u32 = Counter::new()
        .zip(Counter::new().skip(1))
        .map(|(a, b)| a * b)
        .filter(|x| x % 3 == 0)
        .sum();
    println!("sum: {}", sum);
    assert_eq!(18, sum);
}
