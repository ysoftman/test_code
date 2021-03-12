use std::thread;
use std::time;

// 그냥 3초간 기다리고 파라미터 값을 돌려주는 함수
// fn calc_something(val: u32) -> u32 {
//     println!("calculating something slowly...");
//     thread::sleep(time::Duration::from_secs(1));
//     val
// }

// 클로저는 클로저를 호출하는 스코프의 변수값을 캡쳐할때 3가지 트레잇(특징)있다.
// FnOne : 캡쳐할때 한번만 소유권을 얻을 수 있다. 따라서 한번만 호출할 수 있다.
// Fn : 캡쳐할때 불변으로 빌려 온다. 변수값을 읽기만 할 수 있다.
// FnMut : 캡쳐할때 가변으로 빌려 온다. 변수값을 변경 할 수 있다.
// 클로저 함수를 받을 제너릭 T 와 T에 대한 트레잇 바운드(where)로 Fn 을 클로저를 갖는 구조체 정의
// Fn(u32) 로 클로저는 u32 타입의 파라미터를 받는다.
// 최초 클로저 함수 결과 저장(캐싱)하고 있다.
struct Cacher<T>
where
    T: Fn(u32) -> u32,
{
    calculation: T,
    value: Option<u32>,
}
impl<T> Cacher<T>
where
    T: Fn(u32) -> u32,
{
    fn new(calculation: T) -> Cacher<T> {
        Cacher {
            calculation, // calculation 변수에 클로저 T를 할당
            value: None, // 클로저 실행 결과가 저장될 변수
        }
    }
    fn value(&mut self, arg: u32) -> u32 {
        match self.value {
            // self.value 에 None 이 아닌 값이 있다그 그 값을 리턴
            Some(v) => v,
            // 값이 없다면 self.calculation(클로저)를 호출하고
            // 그 값을 Some(v) self.value 에 저장한다.
            None => {
                let v = (self.calculation)(arg);
                self.value = Some(v);
                v
            }
        }
    }
}

pub fn run(val: u32) {
    let x = vec![1, 2, 3];
    // 일반 내부 함수에서는 함수 밖의 변수에 접근하지 못한다.
    // fn inner_func() {
    //     println!("{:?}", x);
    // }
    // inner_func();
    // 클로저와 클로저 수행 후 값을 저장하고 있는 struct 사용을 위해 new 로 생성
    // move 를 사용하면 클로저가 정의 될때 외부 변수 x 의 소유권이 이동된다.
    // let mut cs_closure = Cacher::new(move |num| {
    let mut cs_closure = Cacher::new(|num| {
        // 클로저에서는 외부 변수에 접근 가능하다.
        println!("calculating something slowly...{:?}", x);
        thread::sleep(time::Duration::from_secs(1));
        num
    });
    // 위 클로저가 move 를 사용했다면 소유권이 클로저 안으로 이동되어 여기서 x 를 사용할 수 없다.
    println!("x {:?}", x);
    if val < 25 {
        // 최초 한번만 클로저 실행
        println!("val < 25 {}", cs_closure.value(val));
        // 이후부터는 cs_closure.value 값을 사용
        println!("val < 25 {}", cs_closure.value(val));
        println!("val < 25 {}", cs_closure.value(val));
        println!("val < 25 {}", cs_closure.value(val));
        println!("val < 25 {}", cs_closure.value(val));
    } else {
        println!("val >= 25 {}", cs_closure.value(val));
    }
}
