# cargo workspace test

```bash
# cargo_workspace 생성
mkdir cargo_workspace
cd cargo_workspace

# a,b crate 를 같은 현재 워크스페이스로 관리할 수 있다.
# 현재 위치에 Cargo.toml 를 생성하고 [workspace] 를 설정한다.
touch Cargo.toml


# a crate 라이브러리로 생성
cargo new a-crate --lib

# b crate 바이너리로 생성
cargo new b_crate --bin

# 테스트
cargo test

# a_crate 만 테스트
cargo test -p a_crate

# b_crate 만 테스트
cargo test -p b_crate

# 실행
cargo run

# 빌드
cargo build

# target 디렉토리와 Cargo.lock 등은 각 crate 마다 있지 않고
# 프로젝트 경로에 하나만 존재하게 된다.
```
