# rust test

rust test code

## github security > Vulnerability alerts > dependabot 알람사항 수정

- 모든 패키지들 업데이트

```bash
for d in $(ls -d */); do pushd $d; cargo update; popd; done
```
