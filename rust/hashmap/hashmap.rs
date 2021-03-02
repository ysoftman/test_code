// ysoftman
// hashmap test

// HashMap 은 String, Vec 와 달리 use 로 사용을 명시해야 한다.
use std::collections::HashMap;

fn main() {
    let mut hm = HashMap::new();
    let aa = String::from("mango");
    hm.insert(aa, 170);
    // aa 는 hashmap 으로 소유권이 이전돼 유효하지 않다.
    // println!("aa{}", aa);
    // 같은 타입의 <key, value> 추가
    hm.insert(String::from("apple"), 150);
    hm.insert(String::from("lemon"), 100);
    // lemon 값 덮어쓰기
    hm.insert(String::from("lemon"), 101);
    // lemon 값 덮어쓰기
    hm.insert(String::from("lemon"), 102);

    // entry 를 통해 lemon 키 존재하지 않으면20을 추가(덮어쓰기)
    hm.entry("lemon".to_string()).or_insert(103);
    hm.entry("lemon2".to_string()).or_insert(103);
    println!("hm {:#?}", hm);

    // hashmap 순회
    // &mut hm(가변참조)로 순회하면서 값을 변경할 수 있도록 한다.
    for (k, v) in &mut hm {
        println!("key:{}, value:{}", k, v);
        // *역참조로 값을 변경
        *v += 1000;
    }

    // 값 가져오기, Option 타입으로 리턴한다.
    println!("hm.get(\"lemon\") -> {:#?}", hm.get("lemon"));
    let k = "apple";
    println!("hm.get(\"apple\") -> {:#?}", hm.get(k));
    let k = String::from("mango");
    println!("hm.get(\"mango\") -> {:#?}", hm.get(&k));
    println!(
        "hm.get_key_value(\"mango\") -> {:#?}",
        hm.get_key_value("mango")
    );
    // 값 제거하면 None 으로 된다.
    hm.remove("mango");
    println!(
        "remove() mango, hm.get_key_value(\"mango\") -> {:#?}",
        hm.get_key_value("mango")
    );
    // 값 변경
    // 원래 값의 타입으로만 변경할 수 있다.
    // 제거된 값(None)은 변경할 수 없다.
    *hm.get_mut("apple").unwrap() = 9999;
    println!(
        "get_mut() apple, nmango, hm.get_key_value(\"apple\") -> {:#?}",
        hm.get_key_value("apple")
    );
    // and_modify(클로저함수명시)로 변경
    hm.entry("apple".to_string()).and_modify(|v| *v = 2222);
    println!(
        "entry().and_modify(), hm.get_key_value(\"apple\") -> {:#?}",
        hm.get_key_value("apple")
    );
    // 벡터들의 값을 추가
    let fruit = vec![String::from("orange"), String::from("grape")];
    let cost = vec![200, 220];
    // zip() 으로 fruit, cost 쌍의 튜플을 만들 수 있다.
    // collect() 로 튜플 벡터를 hashmap 으로 바꿀 수 있다.
    // HashMap<_,_> 키와 값에 대해선 입력에 따라 추론되도록 한다.
    let hm2: HashMap<_, _> = fruit.iter().zip(cost.iter()).collect();
    println!("hm2 {:#?}", hm2);

    let strdata = "lemon orange lemon apple lemon fineapple";
    println!("count word \"{}\"\n{:#?}", strdata, count_word(strdata));
}

// 단어 카운트
fn count_word(s: &str) -> HashMap<String, u32> {
    let mut map = HashMap::new();
    // 스트링 공백 구분
    for w in s.split_whitespace() {
        // entry 로 중복 단어(key) 제외후 해당 단어의 값(value,카운트)을 가변 변수로 리턴한다.
        let cnt = map.entry(String::from(w)).or_insert(0);
        // 역참조로 현재 단어 개수 증가
        // ++ 는 rust 없는 표현이다.
        *cnt += 1;
    }
    map
}
