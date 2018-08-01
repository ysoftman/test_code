# github api 사용하기

```bash
# 사용자의 모든 저장소 정보
curl -s --user "ysoftman:password123" https://api.github.com/user/repos

# 해당 저장소에서 사용되는 언어별 사용 bytes
 curl -s --user "ysoftman:password123" https://api.github.com/repos/ysoftman/test_code/languages

# github api 를 이용해 이슈 정보 파악하기
# https://developer.github.com/v3/issues/
# 이슈번호 : 10
curl -s --user "ysoftman:password123" https://api.github.com/repos/ysoftman/test_code/issues/10

# git release 정보 파악하기
# https://developer.github.com/v3/repos/releases/
curl -s --user "ysoftman:password123" https://api.github.com/repos/ysoftman/test_code/releases
```

## git-br

브랜치명이 xxx-이슈번호 인 경우, github 의 이슈타이틀을 파악해서 현재 로컬 브랜치에 정보에 같이 표시한다.

- 예시

```bash
# test_code 에 테스트를 위한 이슈(10번)를 만들어두었음
# ysoftman-10 를 만들어 본다.
git co -b ysoftman-10
# git-br 에 password 명시하고 실행
git br
```
