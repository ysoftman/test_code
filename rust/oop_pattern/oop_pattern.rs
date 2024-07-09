// ysoftman
// oop(object oriented programming) test
// 객체지향은 데이터와 데이터를 활용하는 프로시져(메소드)의 묶음이다.
// rust 는 struct, enum 으로 데이터를 의미할 수 있고,
// impl 블럭으로 struct, enum 에 대한 메소드를 제공한다.
// pub 키워드 유무 외부 공개를 제한할 수 있어 oop 캡슐화를 구현한다.
// rust 는 직접적인 상속을 제공 하진 않지만 trait 을 통한 오버라이딩이 상속과 유사하다.

pub struct AveragedCollection {
    list: Vec<i32>,
    average: f64,
}
impl AveragedCollection {
    // 벡터에 값 추가 후 평균 구하기
    pub fn add(&mut self, value: i32) {
        self.list.push(value);
        self.update_average();
    }

    // 벡터에 갑제거(pop) 후 평균 구하기
    pub fn remove(&mut self) -> Option<i32> {
        let result = self.list.pop();
        match result {
            Some(value) => {
                self.update_average();
                Some(value)
            }
            None => None,
        }
    }

    pub fn average(&self) -> f64 {
        self.average
    }

    // 벡터 요소들의 평균 구하기
    // 비공개로 AveragedCollection 내부에서만 사용한다.
    fn update_average(&mut self) {
        let total: i32 = self.list.iter().sum();
        self.average = total as f64 / self.list.len() as f64;
    }
}

fn main() {
    let mut avg_collection = AveragedCollection {
        list: vec![],
        average: 0.0_f64,
    };
    avg_collection.add(1);
    avg_collection.add(2);
    avg_collection.add(3);
    println!(
        "vec {:?} avg {}",
        avg_collection.list, avg_collection.average
    );
}
