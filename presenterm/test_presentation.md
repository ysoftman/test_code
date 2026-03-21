---
title: Presenterm Test
sub_title: Feature Demo
author: ysoftman
---

Intro
-----

- presenterm 주요 기능을 테스트하는 슬라이드입니다
- 터미널에서 `presenterm test_presentation.md` 로 실행하세요

<!-- end_slide -->

Text Formatting
---------------

**굵은 텍스트** / *이탤릭* / ~~취소선~~

`인라인 코드` 도 지원합니다

> 인용문(blockquote)도 사용할 수 있습니다
> 여러 줄도 가능합니다

<span style="color: #ff6347">빨간색 텍스트</span> / <span style="color: #00bfff">파란색 텍스트</span>

<!-- end_slide -->

Lists
-----

순서 없는 리스트:

- 항목 1
  - 하위 항목 1-1
  - 하위 항목 1-2
- 항목 2
- 항목 3

순서 있는 리스트:

1. 첫 번째
2. 두 번째
3. 세 번째

<!-- end_slide -->

Code Highlighting
-----------------

```rust +line_numbers
fn main() {
    let greeting = "Hello, presenterm!";
    println!("{}", greeting);

    for i in 0..5 {
        println!("count: {}", i);
    }
}
```

<!-- end_slide -->

Dynamic Code Highlighting
-------------------------

```python {1-2|4-6|8-10}
import os
import sys

def greet(name):
    """Say hello"""
    print(f"Hello, {name}!")

if __name__ == "__main__":
    greet("world")
    sys.exit(0)
```

<!-- end_slide -->

Table
-----

| Language   | Type     | Speed  |
|------------|----------|--------|
| Rust       | Compiled | Fast   |
| Go         | Compiled | Fast   |
| Python     | Script   | Slow   |
| JavaScript | Script   | Medium |

<!-- end_slide -->

Image
-----

마크다운 이미지 문법으로 이미지를 삽입할 수 있습니다:

![image:width:50%](sample.png)

<!-- end_slide -->

Pause Demo
----------

첫 번째 내용이 먼저 보입니다

<!-- pause -->

그 다음 이 내용이 나타납니다

<!-- pause -->

마지막으로 이 내용이 나타납니다!

<!-- end_slide -->

Thank You
----------

- presenterm 공식 문서: mfontanini.github.io/presenterm
- 키보드: 화살표 / hjkl 로 이동
- `?` 키로 단축키 확인
