# my mod test

```bash
# --lib 옵션이 없으면 기본 애플리케이션(--bin)로 생성하게 된다.
cargo new --lib my_mod

cd my_mod

# 코드 포맷팅
cargo fmt

# 코드 체크
cargo check

# 테스트 코드 수행
cargo test

# 빌드
cargo build

# library 라서 실행은 할 수 없다.
# 하지만 my_mod 에는 main() 도 같이 만둘오 둬 빌드 할 수 있다.
cargo run

# my_mod/target/ 이 생성된다.
# library
./my_mod/target/debug/libmy_mod.rlib
# binary
./my_mod/target/debug/my_mod
```
