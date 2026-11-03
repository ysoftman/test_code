use std::collections::HashMap;
// ysoftman
// iterator(반복자) test
// 반복자는 표준 라이브러리에 다음과 같은 트레잇을 가지고 있다.
// trait Iterator {
//     // Iterator 트레잇은 Item 타입도 정의해야 된다.
//     // next() 의 리턴으로 사용하기 위한 타입
//     type Item;
//     // Iterator 트레잇은 next() 를 구현해야 한다.
//     fn next(&mut self) -> Option<Self::Item>;
// }

fn main() {
    // let v1 = vec![1, 2, 3]; // useless vec!
    let v1 = [1, 2, 3];
    // v1_iter 반복자를 생성, v1.iter() 는 반복자를 리턴하는 메소드일 뿐이다.
    // 생성된 반복자를 사용(소비)하면 더이상 사용할 수 없다.
    // 반복자는 항목들을 소비하기 전까지 반복자는 호출해도 아무 동작을 하지 않는다.
    let v1_iter = v1.iter();
    // v1_iter 의 항목들이 value 로 소비된다.
    // value 를 for {} 스코프가 종료되면 사용할 수 없다.
    for value in v1_iter {
        println!("value {value}");
    }
    // 위에서 v1_iter 반복자를 소비해 여기서는 사용 못한다.
    // for v in v1_iter {
    //     println!("value {}", v);
    // }

    // iter() 메소드를 사용하면 v1을 참조하기 때문에 계속 사용할 수 있다.
    // iter() 는 불변 참조에 대해서만 사용할 수 있다.
    for value in v1.iter() {
        println!("value {value}");
    }
    for value in v1.iter() {
        println!("value {value}");
    }

    // into_iter() 메소드를 사용하면 v1 소유권이 넘어가기 때문에 계속 사용할 수 없다.
    // for value in v1.into_iter() {
    //     println!("value {}", value);
    // }
    // for value in v1.iter() {
    //     println!("value {}", value);
    // }

    let mut mut_v1 = [1, 2, 3];
    // 가변 참조 변수 반복을 위해선 iter_mut() 을 사용해야 한다.
    for value in mut_v1.iter_mut() {
        *value += 1;
        println!("value+1 : {value}");
    }
    for value in mut_v1.iter_mut() {
        *value += 1;
        println!("value+1 : {value}");
    }

    let mut v1_iter = v1.iter();
    // next()을 사용하면 반복자를 소비하고 이때 내부적으로 변경하기 때문에 mut 로 받아야 한다.
    if v1_iter.next() == Some(&1) {
        println!("equal");
    }
    assert_eq!(v1_iter.next(), Some(&2));
    assert_eq!(v1_iter.next(), Some(&3));
    // 마지막 아이템의 next 는 None 값이다.
    assert_eq!(v1_iter.next(), None);

    // v1.iter().next()로는 이동되지 않는다.
    // assert_eq!(v1.iter().next(), Some(&1));
    // assert_eq!(v1.iter().next(), Some(&1));
    // assert_eq!(v1.iter().next(), Some(&1));
    assert_eq!(v1.first(), Some(&1));
    assert_eq!(v1.first(), Some(&1));
    assert_eq!(v1.first(), Some(&1));

    let v1_iter = v1.iter();
    // sum() 은 next() 로 v1_iter 반복자를 소비해서 이후 v1_iter 를 사용할 수 없다.
    let total: i32 = v1_iter.sum();
    assert_eq!(total, 6);

    // map 메소드에 v1 요소에 +1 하는 클로저를 넘겨 반복자를 리턴 받는다.
    // 반복자는 collect() 로 벡터를 리턴한다.
    // collect() 는 iterator 를 관련있는 collection(컬렉션, vector, string, hash map등)으로 변환시켜 준다.
    // map 등 이터레이터 어댑터(Iterator Adaptor)라고 불리는 거의 모든 메서드들은 예외 없이 전부 지연 평가(Lazy Evaluation)로 동작(collect() 가 실행될때 실행)한다.
    let v2: Vec<_> = v1.iter().map(|x| x + 1).collect();
    assert_eq!(vec![2, 3, 4], v2);

    let vec_size = vec![10, 12, 15, 10];
    println!("{:?}", find_my_size(vec_size, 10));
    // find_my_size 내에서 vec_size를 into_iter() 로 소유권을 가져가서  소비했기 때문에 더이상 사용할 수 없다.
    // println!("{:?}", find_my_size(vec_size, 12));

    println!("--- custom_iter_test ---");
    custom_iter_test();
}

fn find_my_size(v_size: Vec<u32>, my_size: u32) -> Vec<u32> {
    // into_iter() 로 v_size 에 대한 소유권으로 가진다.
    // filter() 에 shoes_size 에 맞는 사이즈들을 shoe 벡터에서 찾아
    // collect() 로 벡터로 리턴한다.
    v_size.into_iter().filter(|s| *s == my_size).collect()
}

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

fn custom_iter_test() {
    let mut counter = Counter::new();

    // counter 의 커스텀 반복자 트레잇의 next() 메소드를 사용
    assert_eq!(counter.next(), Some(1));
    assert_eq!(counter.next(), Some(2));
    assert_eq!(counter.next(), Some(3));
    assert_eq!(counter.next(), Some(4));
    assert_eq!(counter.next(), Some(5));
    assert_eq!(counter.next(), None);

    // [1,2,3,4,5]
    let temp: Vec<u32> = Counter::new().collect();
    println!("{temp:?}");
    // 1번째 요소 건너뛰어 [2,3,4,5]
    let temp: Vec<u32> = Counter::new().skip(1).collect();
    println!("{temp:?}");
    // zip()으로 위 2개 벡터를 쌍으로 묶는다.
    // {1: 2, 4: 5, 3: 4, 2: 3} 으로 vec1의 5에 대한 쌍이 없으면(None) 생성되지 않음
    let temp: HashMap<_, _> = Counter::new().zip(Counter::new().skip(1)).collect();
    println!("{temp:?}");
    // key * value 값을 벡터로 [2, 6, 12, 20]
    let temp: Vec<_> = Counter::new()
        .zip(Counter::new().skip(1))
        .map(|(a, b)| a * b)
        .collect();
    println!("{temp:?}");
    // 이 벡터에서 3의 배수만 필터링해서 [6, 12]
    let temp: Vec<_> = Counter::new()
        .zip(Counter::new().skip(1))
        .map(|(a, b)| a * b)
        .filter(|x| x % 3 == 0)
        .collect();
    println!("{temp:?}");
    // 필터링된 벡터의 합을 구한다.
    let sum: u32 = Counter::new()
        .zip(Counter::new().skip(1))
        .map(|(a, b)| a * b)
        .filter(|x| x % 3 == 0)
        .sum();
    println!("sum: {sum}");
    assert_eq!(18, sum);
}
