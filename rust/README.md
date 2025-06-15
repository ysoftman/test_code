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
