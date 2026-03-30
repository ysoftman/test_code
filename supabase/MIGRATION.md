# Firebase to Supabase Migration Guide

## Overview

Firebase 프로젝트를 Supabase로 마이그레이션한 내용을 정리한다.

## 사용 중인 Firebase 기능 및 Supabase 대체

| Firebase 기능 | Supabase 대체 | 비고 |
|---|---|---|
| Authentication (Google, Anonymous) | Supabase Auth | OAuth, Anonymous 모두 지원 |
| Cloud Firestore (문서 읽기/쓰기, 트랜잭션) | Supabase Database (PostgreSQL) + RPC | SQL 기반, RPC로 원자적 처리 |
| Firebase Storage (이미지/동영상 저장, 목록, URL) | Supabase Storage (S3 호환) | Public bucket으로 URL 직접 접근 |
| Firebase Hosting (정적 사이트) | GitHub Pages / Cloudflare Pages | 별도 호스팅 필요 |

## API 매핑

### 초기화

```js
// Firebase
import { initializeApp } from "firebase/app";
const firebase = initializeApp(firebaseConfig);

// Supabase
import { createClient } from "@supabase/supabase-js";
const supabase = createClient(supabaseUrl, supabasePublishableKey);
```

### Authentication

```js
// Firebase - 인증 상태 감지
import { getAuth, onAuthStateChanged } from "firebase/auth";
onAuthStateChanged(auth, (user) => { ... });

// Supabase
supabase.auth.onAuthStateChange((_event, session) => {
  const user = session?.user;
});
```

```js
// Firebase - 익명 로그인
import { signInAnonymously } from "firebase/auth";
signInAnonymously(auth);

// Supabase
supabase.auth.signInAnonymously();
```

```js
// Firebase - Google 로그인 (팝업)
import { GoogleAuthProvider, signInWithPopup } from "firebase/auth";
signInWithPopup(auth, new GoogleAuthProvider());

// Supabase - Google 로그인 (리다이렉트 방식)
supabase.auth.signInWithOAuth({
  provider: "google",
  options: { redirectTo: window.location.origin },
});
```

```js
// Firebase - 로그아웃
import { signOut } from "firebase/auth";
signOut(auth);

// Supabase
supabase.auth.signOut();
```

### Storage

```js
// Firebase - 파일 목록 조회
import { getStorage, ref, listAll } from "firebase/storage";
const listRef = ref(storage, path);
const res = await listAll(listRef);
res.items.forEach((itemRef) => { ... });

// Supabase
const { data } = await supabase.storage.from("images").list(path);
const files = data.filter((item) => item.id !== null);
```

```js
// Firebase - 다운로드 URL
import { getDownloadURL, ref } from "firebase/storage";
const url = await getDownloadURL(ref(storage, name));

// Supabase - Public URL (bucket이 public인 경우)
const { data: { publicUrl } } = supabase.storage.from("images").getPublicUrl(name);
```

### Database

```js
// Firebase - Firestore 트랜잭션 (방문 카운트 증가)
import { doc, getFirestore, runTransaction } from "firebase/firestore";
runTransaction(db, async (transaction) => {
  const doc1 = await transaction.get(docRef);
  const newCnt = doc1.data().visitCnt + 1;
  transaction.update(docRef, { visitCnt: newCnt });
});

// Supabase - RPC 함수 호출 (PostgreSQL stored procedure)
const { data } = await supabase.rpc("increment_visit_cnt", { doc_name: docName });
```

## 파일 변경 내역

| Firebase 파일 | Supabase 파일 | 변경 내용 |
|---|---|---|
| `src/web_api_key.js` | `src/supabase_config.js` | API key → Project URL + Publishable Key |
| `src/common.js` | `src/common.js` | firebase/auth → @supabase/supabase-js Auth |
| `src/index.js` | `src/index.js` | firebase/storage, firebase/firestore → supabase storage, database |
| `firebase.json` | 삭제 | Hosting 설정 불필요 (GitHub Pages 사용) |
| `package.json` | `package.json` | `firebase` → `@supabase/supabase-js` |
| `.gitignore` | `.gitignore` | `web_api_key.js` → `supabase_config.js` |

## Supabase 프로젝트 초기 설정

### 1. 프로젝트 생성

- <https://supabase.com/dashboard> 에서 새 프로젝트 생성
- Project Settings > API 에서 Project URL 과 publishable key 확인

### 2. Authentication 설정

- Providers > Google 활성화 (Google Cloud Console에서 OAuth 클라이언트 ID 필요)
- Settings > Enable anonymous sign-ins 활성화

### 3. Database 설정 (SQL Editor에서 실행)

```sql
-- index 테이블 생성
CREATE TABLE IF NOT EXISTS index (
  name TEXT PRIMARY KEY,
  visit_cnt INTEGER DEFAULT 1
);

-- RLS 활성화
ALTER TABLE index ENABLE ROW LEVEL SECURITY;

-- 정책 설정
CREATE POLICY "Allow read" ON index FOR SELECT USING (true);
CREATE POLICY "Allow write for authenticated" ON index
  FOR ALL USING (auth.uid() IS NOT NULL);

-- 방문 카운트 원자적 증가 RPC 함수
CREATE OR REPLACE FUNCTION increment_visit_cnt(doc_name TEXT)
RETURNS INTEGER AS $$
DECLARE
  new_cnt INTEGER;
BEGIN
  INSERT INTO index (name, visit_cnt)
  VALUES (doc_name, 1)
  ON CONFLICT (name) DO UPDATE SET visit_cnt = index.visit_cnt + 1
  RETURNING visit_cnt INTO new_cnt;
  RETURN new_cnt;
END;
$$ LANGUAGE plpgsql SECURITY DEFINER;
```

### 4. Storage 설정

- Storage > New bucket > `images` (Public bucket 체크)
- 기존 Firebase Storage 파일을 Supabase 대시보드에서 드래그앤드롭으로 업로드

### 5. Storage Policy 설정

```sql
CREATE POLICY "Public read access" ON storage.objects
  FOR SELECT USING (bucket_id = 'images');
```

## Firebase Storage 파일 이전

```bash
# 1. Firebase Storage에서 파일 다운로드
gsutil -m cp -r gs://ysoftman-firebase.appspot.com/ ./backup/

# 2. Supabase 대시보드에서 드래그앤드롭 업로드
#    또는 curl 로 업로드
curl -X POST "https://<project-ref>.supabase.co/storage/v1/object/images/<filename>" \
  -H "Authorization: Bearer <anon-key>" \
  -H "Content-Type: image/jpeg" \
  --data-binary @<filename>
```

## 주요 차이점

| 항목 | Firebase | Supabase |
|---|---|---|
| DB 모델 | NoSQL (Document) | SQL (PostgreSQL) |
| 트랜잭션 | `runTransaction()` | RPC (stored procedure) |
| 로그인 방식 | 팝업 (`signInWithPopup`) | 리다이렉트 (`signInWithOAuth`) |
| Storage URL | `getDownloadURL()` (토큰 포함) | `getPublicUrl()` (Public bucket) |
| 호스팅 | Firebase Hosting 내장 | 별도 서비스 필요 |
| 과금 | 사용량 기반 | 무료 티어 넉넉, 프로젝트 단위 과금 |
| 오픈소스 | X | O (self-host 가능) |
