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

# 릴리즈용으로 빌드(최적화된다.)
cargo build --release

# 문서(html) 생성 하고 열기
# ./target/doc 에 생성된다.
cargo doc --open

# 실행 파일
./hello_cargo/target/debug/hello_cargo

# 패키지 업데이트
cargo update

# cargo 에 github 계정 연동하고, email 확인 받고
# https://crates.io/me 에서 토큰 생성(한번 생성하고 없어지기 때문에 따로 저장해둬야 한다.)
# cargo 로그인
cargo login 토큰값

# crates.io 에 배포하기
# 한번 배포된 크레이트는 수정, 삭제할 수 없어 주의해야 한다.
# 대신 버전을 계속 변경해서 올릴 수 있다.
# Cargo.toml 체크
# - [package] name,version,authors,description,license 필수 필드가 채워져 있어야 배포 된다.
# - [dependencies] 패키지 버전을 정확한 값을 명시해야 한다. "*" 사용하면 안됨.
cargo publish
# 또는
# --allow-dirty 로컬 변경 사항이 있는채로 배포 허용
cargo publish --allow-dirty

# crates.io 올라간 버전을 제거할 수 없지만 yank(홱 잡아 당기다.)로
# 특정 버전을 종속성으로 사용할 수 없도록 막아준다.
cargo yank --vers 0.1.0

# yank 취소
cargo yank --vers 0.1.0 --undo

# 문서화
cargo doc --open
```
