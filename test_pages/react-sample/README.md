# react app test

React 19 + Vite 샘플. 탭으로 3가지 예제를 전환할 수 있다.

## 예제 구성

- `src/crud/` — CRUD 예제 (useState, useMemo, 컴포넌트 분리, controlled form)
  - `CrudApp.jsx`: 목록/상세/생성/수정/삭제 상태 관리
  - `CrudHeader.jsx`: 제목 + 아이템 개수 배지
  - `CrudList.jsx`: 아이템 목록
  - `ItemDetail.jsx`: 선택 아이템 상세 및 update/delete
  - `ItemForm.jsx`: 생성/수정 공용 폼
- `src/hooks/` — hooks 예시
  - `UseRefExample.jsx`: 리렌더 없이 값 보관, DOM 포커스
  - `UseMemoExample.jsx`: 피보나치 연산 캐시
  - `UseCallbackExample.jsx`: memo 자식의 불필요한 리렌더 방지
  - `UseReducerExample.jsx`: action 기반 상태 관리
  - `UseLocalStorageExample.jsx`: custom hook (`useLocalStorage`)
- `src/react19/` — React 19 신기능 예시
  - `UseActionStateExample.jsx`: form action + isPending
  - `UseOptimisticExample.jsx`: 낙관적 UI 업데이트
  - `UseExample.jsx`: `use()` + Suspense 로 promise 읽기

## 앱 생성시

```bash
# React + Vite (CRA 는 deprecated 라 vite 사용)
bun create vite@latest react-sample --template react
```

## 앱 실행

```bash
bun run dev
```

## build

```bash
bun run build
```

## update package dependency

```bash
# (bun.lock)
bun update

# npm update (package-lock.json) 는 너무 느려서 사용하지 말자.
```

## 일괄 포맷팅

```bash
# biome.json 설정 참고
biome format --write
```
