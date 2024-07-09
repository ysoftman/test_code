// cargo lib 생성하면 자동으로 테스트 모듈 코드 샘플이 생긴다.
// cfg 로 특정한 환경에서만 수행할 수 있다.
// 테스트 모듈 어노테이션(cargo test 에만 수행하라는 의미,컴파일시 빌드에 포함되지 않음을 의미)
#[cfg(test)]
mod tests {
    // 함수를 테스트 어노테이션 한다.
    #[test]
    fn it_works() {
        // 테스트 성공하는 경우
        assert_eq!(2 + 2, 4);
        assert_ne!(2 + 2, 5);
        // 테스트 실패하는 경우
        // assert_eq!(2 + 2, 5);
    }

    #[test]
    fn maybe_it_works2() {
        let mystr = "lemon orange mango";

        // assert! 에는 사용자 커스텀 메시지를 작성할 수 있다.
        assert!(
            mystr.contains("apple"),
            "{} 에 apple 포함되어 있지 있습니다.",
            mystr
        );
    }

    // ignore 하면 'ignored'로 표시되고 실제 수행되지는 않는다.
    #[test]
    #[ignore]
    fn ignore_test() {
        assert_eq!(1 + 1, 2);
    }
    #[test]
    fn another() {
        panic!("일부터 패닉 발생!");
    }
    // 같은 파일의 Rectangle 을 사용하려면 super(루트 스코프)를 명시해야 한다.
    use super::*;
    #[test]
    fn larger_can_hold_smaller() {
        let larger = Rectangle {
            length: 8,
            width: 7,
        };
        let smaller = Rectangle {
            length: 5,
            width: 1,
        };

        assert!(larger.can_hold(&smaller));
    }

    #[test]
    fn add1() {
        assert_eq!(4, pub_add_two(2));
    }
    #[test]
    fn add2() {
        assert_eq!(4, internal_add_two(2));
    }

    // test 다음에 should_panid 어노테이션을 하면 테스트시 실패등으로 패닉이 발생해도 통과시킨다.
    // should_panic 에 expected 로 특정한 패닉메시지만 통과되도록 조건을 둘 수도 있다.
    #[test]
    #[should_panic]
    // #[should_panic(expected = "12 10보다 큰값이라 패닉발생시켰습니다.")]
    fn check_number() {
        check_number_range(12);
    }
}

// tests 와 같은 외부 모듈에서 사용하려면 public
pub struct Rectangle {
    width: u32,
    length: u32,
}

impl Rectangle {
    // other 이 현재 rectangle 에 포함되는지 여부
    pub fn can_hold(&self, other: &Rectangle) -> bool {
        println!("can_hold 함수 실행");
        self.width > other.width && self.length > other.length
    }
}

pub fn pub_add_two(v: u32) -> u32 {
    internal_add_two(v)
}

// 같은 파일내라면 rust 는 pub 없는 (비공개) 함수도 테스트는 허용(수행)한다.
fn internal_add_two(v: u32) -> u32 {
    2 + v
}

pub fn check_number_range(v: u32) {
    if v > 10 {
        panic!("{} 10보다 큰값이라 패닉발생시켰습니다.", v)
    }
    println!("{} 는 10보다 작은 값입니다.", v);
}
