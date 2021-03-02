// ysoftman
// generic test
// 제너릭(generic, 타입이나 속성에 대한 추상화한 대리인) 보통 중복 코드 제거를 위해 사용
// 제너릭 타입의 파라미터는 관례상 camelcase 이고
// 짧게 쓰기 때문에 type 의미인 T 를 사용하며 다음과 같이 사용한다.
// 참고로 rust 는 단형성화(monomorphization)로
// 런타임에 성능저하가 발생하지 않도록 한다.
// 예)  enum aa<T> { aa(T) } 가 있다면
// let a = aa_i32::aa(123);
// let b = aa_char:aa('a');
// 로 실제 타입에 맞는 것로 컴파일시 교체된다.

// 필드가 모두 같은 값을 가지는 제너릭
#[derive(Debug)]
struct Point1<T> {
    x: T,
    y: T,
}

#[derive(Debug)]
// 제너릭 파라미터를 여러개 사용하는 경우
// 필드가 같을 수 도 있고 다를 수도 있다.
struct Point2<T, T2> {
    x: T,
    y: T2,
}

// 메소스에서 제너릭 사용
impl<T, T2> Point2<T, T2> {
    fn get_reference_x(&self) -> &T {
        &self.x
    }
    fn get_reference_y(&self) -> &T2 {
        &self.y
    }
}

// enum 에서도 제너릭 적용할 수 있다.
#[derive(Debug)]
enum Fruit<T, A> {
    Apple(T),
    Lemon(A),
}

fn main() {
    // 구조체 제너릭 사용
    let pt = Point1 { x: 1, y: 2 };
    println!("pt {:#?}", pt);
    let pt = Point2 { x: 1.10, y: 2.0 };
    println!("pt {:#?}", pt);
    let pt = Point2 { x: 1, y: 2.0 };
    println!("pt {:#?}", pt);
    println!("pt.get_reference_x {:}", pt.get_reference_x());
    // .3 소소점 3자리까지 표시
    println!("pt.get_reference_y {:.3}", pt.get_reference_y());

    // 열거형 제너릭 사용
    let fru: Fruit<i32, char> = Fruit::Apple(123);
    println!("fru {:?}", fru);
    let fru: Fruit<i32, char> = Fruit::Lemon('l');
    println!("fru {:?}", fru);

    // 함수 파라미터 제너릭 사용
    let numbers = vec![34, 88, 6, 25, 99, 5, 23];
    println!("largest number : {}", find_largest_number(&numbers));
    let numbers = vec!['y', 's', 'o', 'f', 't', 'm', 'a', 'n'];
    println!("largest number : {}", find_largest_number(&numbers));
}

// i32 vector 타입을 처리하는 경우
// fn find_largest_number(list: &[i32]) -> i32 {

// char char 타입을 처리하는 경우
// fn find_largest_number(list: &[i32]) -> i32 {

// 제너릭으로 처리하는 경우
// 비교 연산을 위해 std::cmp::PartialOrd 메소드 트레잇과
// 소유권이동 방지를 위한 copy 메소드 트레잇이 구현된 타입으로 제한(bound)하지 않으면 컴파일 에러
// i32, char 는 PartialOrd() Copy() 트레잇을 구현하고 있음
fn find_largest_number<T: PartialOrd + Copy>(list: &[T]) -> T {
    let mut largest = list[0];
    for &item in list.iter() {
        if item > largest {
            largest = item;
        }
    }
    largest
}
