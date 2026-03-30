# supabase test

## supabase 프로젝트 생성 후 최초 설정

```bash
# https://supabase.com/dashboard 에서 새 프로젝트 생성
# Settings > General > Project ID 확인 후 Project URL 조합 (.com 이 아니라 .co 임에 주의)
# Settings > API Keys > Publishable and secret API keys 탭에서 확인
# src/supabase_config.js(.gitignore 로 추가했음) 생성
cat << zzz >! src/supabase_config.js
export const supabaseUrl = () => {
  return "https://<project-id>.supabase.co";
};

export const supabasePublishableKey = () => {
  return "sb_publishable_...";
};
zzz
```

## supabase 대시보드 설정

### Authentication 설정

- Authentication > Sign In / Providers > Third-Party Auth 탭 > Google 활성화
  - Google Cloud Console 에서 OAuth 클라이언트 ID/Secret 생성 필요
  - Client IDs: Google OAuth Client ID 입력 (공백 없이, 쉼표로 구분)
  - Client Secret (for OAuth): Google OAuth Client Secret 입력
  - Callback URL (for OAuth): `https://<project-id>.supabase.co/auth/v1/callback` (자동 생성됨, Google Cloud Console 의 승인된 리디렉션 URI 에 등록)
- Authentication > Sign In / Providers > Supabase Auth 탭 > Allow anonymous sign-ins 활성화

### Storage 설정

```bash
# Storage > New bucket > "images" 버킷 생성 (Public bucket 체크)
# 이미지 파일 업로드는 대시보드에서 드래그앤드롭으로 가능
```

### Storage Policy 설정

Storage > Policies > images 버킷 > New policy:

- Policy name: `read image`
- Allowed operation: SELECT 체크 (download, list, createSignedUrl, createSignedUrls, getPublicUrl 허용됨)
- Target roles: 기본값 (all public roles)
- Policy definition: `bucket_id = 'images'`

### Database 설정

```sql
-- SQL Editor 에서 실행

-- index 테이블 생성 (firebase 의 index 컬렉션 대체)
CREATE TABLE IF NOT EXISTS index (
  name TEXT PRIMARY KEY,
  visit_cnt INTEGER DEFAULT 1
);

-- RLS(Row Level Security) 활성화
ALTER TABLE index ENABLE ROW LEVEL SECURITY;

-- 읽기 허용 정책
CREATE POLICY "Allow read" ON index FOR SELECT USING (true);

-- 인증된 사용자만 쓰기 허용
CREATE POLICY "Allow write for authenticated" ON index
  FOR ALL USING (auth.uid() IS NOT NULL);

-- 방문 카운트 원자적 증가를 위한 RPC 함수
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

## supabase storage 파일 업로드

```bash
# 방법 1: 웹 대시보드에서 드래그앤드롭 업로드
# Storage > images 버킷 > Upload files

# 방법 2: supabase CLI 사용
bun install -g supabase
supabase login
# supabase CLI 로 스토리지 관리는 대시보드 권장

# 방법 3: curl 로 업로드 (anon key 필요)
# curl -X POST "https://<project-ref>.supabase.co/storage/v1/object/images/photo.jpg" \
#   -H "Authorization: Bearer <anon-key>" \
#   -H "Content-Type: image/jpeg" \
#   --data-binary @photo.jpg
```

## 프로젝트 배포

```bash
# mise 툴로 이프로젝트에서 사용할 node 버전 고정 및 설치
mise use node@24

# 최초 한번만 패키지 설치
bun install

# 로컬 테스트 (vite dev server 가 빌드 + 서빙을 자동으로 해준다)
bun serve

# 로컬 확인
# http://localhost:5173/
```

## GitHub Pages 배포

### GitHub Actions 자동 배포

`supabase/` 하위 파일이 변경되어 `master`에 push 되면 GitHub Actions 가 자동으로 빌드/배포한다.

- workflow 파일: `.github/workflows/deploy-supabase.yml`
- 배포 URL: `https://ysoftman.github.io/test_code/`

### GitHub 레포 설정 (최초 1회)

1. GitHub 레포 > Settings > Pages > Source 를 `GitHub Actions` 로 변경

### GitHub Secrets 설정 (최초 1회)

`src/supabase_config.js` 는 `.gitignore` 에 포함되어 있어 GitHub Actions 빌드 시 존재하지 않는다.
GitHub Secrets 로 주입해야 한다.

1. GitHub 레포 > Settings > Secrets and variables > Actions
2. **Repository secrets** 에 다음 추가:
   - `SUPABASE_URL`: Supabase Project URL
   - `SUPABASE_PUBLISHABLE_KEY`: Supabase Publishable Key (`sb_publishable_...`)

## 참고

- <https://supabase.com/docs>
- <https://supabase.com/docs/guides/auth>
- <https://supabase.com/docs/guides/storage>
- <https://supabase.com/docs/guides/database>
- <https://nostalgic-css.github.io/NES.css/#installation>
