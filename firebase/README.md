# firebase test

## firebase 프로젝트 설정

```bash
# 앱키, 프로젝트 정보
https://console.firebase.google.com/u/0/project/ysoftman-test/settings/general/

# firebase -> storage -> 규칙
# 읽기 공개 허용으로 설정
service firebase.storage {
  match /b/{bucket}/o {
    match /{allPaths=**} {
      allow read: if true;
    }
  }
}

# 참고
https://github.com/firebase/quickstart-js/blob/master/storage/index.html

```

## firebase 프로젝트 배포

```bash
# firebase-tools 설치
npm install -g firebase-tools

# 테스트를 위해 로컬에서 서빙
firebase serve

# firebase 구글 로그인
# (브라우저가 열리고 firebase 승인하면된다.)
firebase login

# 프로젝트 초기화(프로젝스 환경구성을 위해 최초 한번만)
firebase init
- hosting 선택(스페이스바) 후 엔터
- ysoftman-test 프로젝트 선택 후 엔터
하면 기본 환경파일들이 구성된다.

# 배포
firebase deploy

# 확인
https://ysoftman-test.firebaseapp.com/
```
