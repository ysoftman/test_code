// 통합테스트에서 공통으로 사용할 모듈을 정의한다.
// mod.rs 파일로 모듈을 정의하면 외부에서 mod common 으로 사용할 수 있다.
pub fn common_name() -> String {
    println!("ysoftman");
    "ysoftman".to_string()
}
