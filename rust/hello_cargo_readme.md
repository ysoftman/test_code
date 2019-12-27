# cargo 로 프로젝트 구조 생성

```bash
# --bin 은 library 가 아닌 binary(실행파일)을 만들기 위한 것
cargo new hello_cargo --bin  

cd hello_cargo

# 코드 포맷팅
cargo fmt

# 빌드
cargo build

# hello_cargo/target/ 이 생성된다.
# 실행 파일
./hello_cargo/target/debug/hello_cargo

# 패키지 업데이트
cargo update

# 문서화
cargo doc --open

```
