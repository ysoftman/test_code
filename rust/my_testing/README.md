# my_testing

```bash
# --lib 옵션이 없으면 기본 애플리케이션(--bin)로 생성하게 된다.
cargo new --lib my_testing
# src 디렉토리는 유닛테스트코드를 작성하고
# tests 디렉토리는 통합테스트코드를 작성한다.
cd my_testing

# 코드 포맷팅
cargo fmt

# 코드 체크
cargo check

# 테스트 코드 수행
cargo test

# -- 구분자 뒤에 명시하는 값은 테스트바이너리에 입력할 아규먼트를 명시한다.
# cargo test --help 는 cargo test 의 help 옵션
# cargo test -- --help 는 cargo test 가 테스트 코드(바이너리)에 의 help 옵션
# rust는 테스트를 빠르게 수행하기 위해 기본적으로 쓰레드를 이용해 병렬처리한다.
# 테스트를 하나의 쓰레드에서만 수행
cargo test -- --test-threads=1

# 기본적으로 테스트 라이브러리는 stdout 를 캡쳐하기 때문에,
# cargo test 수행히 println!은 화면에 보이지 않는다.
# 이를 보이기 위해선 --nocapture 옵션을 사용해야 한다.
cargo test -- --nocapture
# 하나의 쓰레드에서 테스트코드결과와 코드의stdout를 같이 츨력하려면
cargo test -- --nocapture --test-threads=1

# 테스트할 함수 별도 지정할 수 있다.
# it_works 를 포함하는 테스트들 수행
# it_works() 와 maybe_it_works2() 가 수행된다.
cargo test it_works

# 무시된(ignore) 테스트들만 강제 수행
cargo test -- --ignored

# 빌드
cargo build

# library 라서 실행은 할 수 없다.
# 하지만 my_testing 에는 main() 도 같이 만둘오 둬 빌드 할 수 있다.
cargo run

# my_testing/target/ 이 생성된다.
# library
./my_testing/target/debug/libmy_testing.rlib
# binary
./my_testing/target/debug/my_testing
```
