// ysoftman
// integrated test
// 프로젝트/tests/ 내에서 통합테스트(외부 테스트 코드들을 모두 호출해서 사용) 코드를 작성한다.
// src 디렉토리는 유닛테스트코드를 작성하고
// tests 디렉토리는 통합테스트코드를 작성한다.
// tests 디렉토리의 파일들은 #[cfg(test)] 어노테이션 없어도 cargo test 에만 수행된다.
// 여기는 my_testing 와 별개라 extern crate 롤 my_testing 를 가져와야 한다.
// 참고로 통합테스트시 extern crate 를 사용하는데 이는
// 라이브러리만(lib.rs) 사용가능하고 바이너리(main.rs)는 사용할수 없다.
// 따라서 lib.rs 에 코드를 작성하고 main.rs 에는 lib 호출해서 사용하는 최소한의 코드만 작성하도록 한다.
extern crate my_testing;

#[test]
fn integrated_test_add_two() {
    assert_eq!(4, my_testing::pub_add_two(2));
}

mod common;
#[test]
fn integrated_test_common_name() {
    // common 모듈의 함수 사용하기
    assert_eq!("ysoftman", common::common_name());
}
