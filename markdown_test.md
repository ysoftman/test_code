# 가장 큰 제목

## 두번째로 큰 제목

### 가장 작은 제목

- **볼드**
- _이탤릭_
- ~~취소선~~
- **볼드안에 _이탤릭_ 문자**

> 인용문구

```text
코드영역
```

```cpp
// 코드영역 시작시 cpp 명시하면 syntax highlight
#include <stdio.h>
void main() {
  printf("hello ysoftman~\n");
}
```

- 리스트1
- 리스트2

1. 순서리스트1
2. 순서리스트2

- [x] 해야할일1
- [ ] 해야할일2

| Tables | col1   | col2 |
| ------ | ------ | ---- |
| line1  | lemon  | 100  |
| line2  | apple  | 50   |
| line3  | banana | 30   |

\*\*백슬레시로 마크다운 문법 무시하기\*\*

<!--
url 은 angle brackets <> 로 감싸지 않으면 다음과 같은 경고가 난다.
MD034/no-bare-urls: Bare URL usedmarkdownlint(MD034)
-->

<https://www.google.com>

[구글링크](http://www.google.com)

```text
![센티멘탈 프로그래머](images/sentimental_programmer.png)
```

![센티멘탈 프로그래머](images/sentimental_programmer.png)

## 이모지(emoji) 사용

:+1: :smile:

## mermaid

```mermaid
sequenceDiagram
lemon->>proxy: hello~
loop Check user
    proxy->>proxy: 자체 체크
end
Note right of proxy: 주석부분
proxy->>apple: hello~
apple-->>proxy: nice to meet you!
proxy-->>lemon: nice to meet you!
```
