# rust test

rust test code

- 컴파일 에러 체크(cargo build 보다 체크만 하는것은 빠르다)

```bash
for d in $(ls -d */); do pushd $d; cargo check; popd; done
```

- 모든 패키지들 업데이트(github security > Vulnerability alerts > dependabot 알람발생시)

```bash
for d in $(ls -d */); do pushd $d; cargo update; popd; done
```

- 정적분석(코드스타일,버그위험,성능개선점,다양한 경고)

```bash
# rust-analyzer 설치해서 진단 -> 오래 걸리니 clippy 만 하자.
rustup component add rust-analyzer
for d in $(ls -d */); do pushd $d; rust-analyzer diagnostics .; popd; done

# clippy(lint) 설치해서 진단
rustup component add clippy
for d in $(ls -d */); do pushd $d; cargo clippy; popd; done
```
