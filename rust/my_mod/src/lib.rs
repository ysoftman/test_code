// 테스트를 위한 테스트 모듈
#[cfg(test)]
mod tests {

    // 테스트 함수
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);

        // 모듈 경로는 상대적이다.
        // test 모듈입장에선 fruit, friend 모두 상위 모듈에서 명시되야(찾아야)하고
        // 이때 super 로 상위 모듈 부터 명시할 수 있다.
        // 즉 형제 모듈을 가져올때 super 사용
        super::fruit::list();
        super::friend::list();

        // 또는 use 로 미리 스코르를 선언해 둘 수도 있다.
        use super::friend;
        use super::fruit;
        fruit::list();
        friend::list();
    }
}

// fruit 모듈 정의
// main.rs 등의 binary 내에서도 mod 를 이용한 모듈은 만들 수 있다.
// mod 기는 기본 private 라 외부에서 쓸려면 pub 으로 공개해야 한다.
pub mod fruit {
    // fruit 모듈의 list 함수 정의
    // 함수도 pub 로 공개해야 외부에서 사용할 수 있다.
    pub fn list() {
        println!("this is fruit list function()!");

        // lemon_fodd 는 같은 루트 모듈인 fruit 를 사용하고 있어 pub 없이도 사용할 수있다.
        // 대신 lemon_foods::list 는 pub 로 해야 사용할 수 있다.
        lemon_foods::list();
    }

    // 모듈안에 또 모듈을 정의할 수 있다.
    mod lemon_foods {
        pub fn list() {
            println!("lemon foods list()\nlemon cake, lemon ade, lemon juice, lemon pie");
        }
    }
}
// friend 라는 모듈 정의만 하고 내용은 friend.rs 또는 ./friend/mod.rs 에 구현할 수 있다.
// friend 안에 모듈을 또 정의하면 ./friend/mod.rs 로만 써야 한다.
pub mod friend;
