// ysoftman
// vector test

#[derive(Debug)]
enum VecData {
    Value1(i32),
    Value2(f32),
    Value3(String),
}

use VecData::*;

// vector, string, hash map 등은 표준 라이브러리에 포함된 컬렉션이고 가변적인 데이터를 힙에 저장한다.
fn main() {
    // 벡터 생성
    // let mut v: Vec<i32> = Vec::new();
    // mutable 이면 push 되는 값으로 타입추론으 가능해 타입을 명시하지 않아도 된다.
    let mut v = Vec::new();
    v.push(-3);
    v.push(-2);
    v.push(-1);
    v.push(0);
    v.push(1);
    v.push(2);
    v.push(3);
    v.pop();
    v.pop();
    v.pop();
    println!("v {:?}", v);
    // 또는 벡터 매크로를 사용할 수도 있다.
    let v2 = vec![-3, -2, -1, 0, 1, 2, 3];
    println!("v2 {:?}", v2);
    // 0~99까지 벡터 컬렉션으로 리턴
    let v2: Vec<u32> = (0..100).collect();
    println!("v2 {:?}", v2);

    // 원소에 접근
    // let value: &i32 = &v[1];
    // println!("value {}", value);
    println!("value {}", &v[1]);
    // 존재하지않는 100번째 원소에 접근하려고 해서 panic 발생한다.
    // println!("value {}", &v[100]);
    // 또는 get() 로 접근 할 수 있고 이때는 Option 값이 리턴된다.
    // 존재하지않는 100번째 원소에 접근하면 Option 의 None 값이 리턴돼 더 안전하다.
    // let value: Option<&i32> = v.get(1);
    // println!("value {:?}", value);
    println!("value {:?}", v.get(100));

    let ref_v = &mut v[0];
    // 스코프내에서 불변 참조는 한번밖에 못한다.
    // let ref_vv = &v[0];
    println!("ref_v {}", ref_v);
    // println!("ref_vv {}", ref_vv);
    v.push(5);

    let ref_v2 = &v2[0];
    println!("ref_v2 {}", ref_v2);
    // immutable v2 를 ref_v2 참조해(빌림 상태)인데 v2 를 수정할 수 없다.
    // v2.push(5);

    for i in &v {
        println!("for {}", i);
    }
    println!("-----");

    // index(정확히는 원소 카운트), value 둘다 파악할때
    for (cnt, value) in v.iter().enumerate() {
        println!("for {} : {}", cnt, value);
    }
    println!("-----");

    // 가변 참조로 값을 변경할 수 있다.
    for i in &mut v {
        // *역참조로 값을 변경
        *i += 10;
        println!("for {}", i);
    }

    // enum 으로 다른 데이터 타입을 갖는 벡터를 생성할 수도 있다.
    let v3 = vec![Value1(123), Value2(1.23), Value3(String::from("ysoftman"))];
    println!("{:?}", v3);
}
