# presenterm test

터미널에서 마크다운 기반 프레젠테이션을 실행하는 [presenterm](https://github.com/mfontanini/presenterm) 테스트 파일입니다.

## 설치

```bash
# macOS
brew install presenterm

# cargo
cargo install presenterm
```

## 실행

```bash
presenterm test_presentation.md
```

## 키보드 조작

| 키 | 동작 |
|---|---|
| `→` / `l` / `PageDown` | 다음 슬라이드 |
| `←` / `h` / `PageUp` | 이전 슬라이드 |
| `gg` | 첫 슬라이드 |
| `G` | 마지막 슬라이드 |
| `<번호>G` | 특정 슬라이드로 이동 |
| `Ctrl+P` | 슬라이드 인덱스 |
| `?` | 단축키 도움말 |
| `q` / `Esc` | 종료 |

## 슬라이드 구성

| 슬라이드 | 내용 |
|---|---|
| Intro | 소개 |
| Text Formatting | 굵게, 이탤릭, 취소선, 인용문, 컬러 텍스트 |
| Lists | 순서 있는/없는 리스트 |
| Code Highlighting | Rust 코드 + 라인 번호 |
| Dynamic Code Highlighting | Python 코드 단계별 강조 |
| Table | 테이블 |
| Image | 이미지 삽입 |
| Pause Demo | pause로 순차 표시 |
| Thank You | 마무리 |
