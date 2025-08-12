# golang test

golang test code

## github security > Vulnerability alerts > dependabot 알람사항 수정

- 모든 패키지들 업데이트

```bash
for d in $(ls -d */); do pushd $d; go mod tidy; go get -u ./...; popd; done
```
