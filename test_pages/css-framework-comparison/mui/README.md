# MUI (Material UI)

- 분류: React 컴포넌트 라이브러리
- 스타일 엔진: Emotion (runtime CSS-in-JS)
- 공식 문서: <https://mui.com/>

## 실행

워크스페이스 루트(`css-framework-comparison/`)에서 한 번만 설치:

```bash
bun install
```

이 앱만 개발 서버로 실행:

```bash
bun run dev          # 이 폴더에서
# 또는 루트에서: bun run dev:mui
```

프로덕션 빌드:

```bash
bun run build        # dist/ 생성 (base: /test_code/css-framework-comparison/mui/)
```

## 데모 사양 (모든 프레임워크 공통)

각 프레임워크가 동일하게 구현해 1:1 비교하는 항목:

1. 다크모드 토글
2. Buttons — contained / outlined / text / with icon / disabled
3. Card — title + body + actions
4. Form — text input · select · checkbox · submit → 제출 결과(JSON) 표시

## 메모

- 번들(첫 빌드): JS ~375KB / gzip ~117KB
- 완성된 컴포넌트가 많아 구현이 가장 짧음
- 런타임 CSS-in-JS(Emotion) 비용 존재
