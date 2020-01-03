# cargo 사용방법

```bash
# --bin 은 library 가 아닌 binary(실행파일)을 만들기 위한 것
cargo new --bin hello_cargo

cd hello_cargo

# 코드 포맷팅
cargo fmt

# 코드 체크
cargo check

# 빌드
cargo build

# 빌드 및 실행
cargo run

# hello_cargo/target/ 이 생성된다.
# 실행 파일
./hello_cargo/target/debug/hello_cargo

# 패키지 업데이트
cargo update

# 문서화
cargo doc --open
```
