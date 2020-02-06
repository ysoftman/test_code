# firebase test

## firebase 프로젝트 설정

```bash
# 앱키, 프로젝트 정보
https://console.firebase.google.com/u/0/project/ysoftman-test/settings/general/

# firebase -> storage -> 규칙
# 읽기 허용으로 설정
service firebase.storage {
  match /b/{bucket}/o {
    match /{allPaths=**} {
      allow read: if true;
    }
  }
}

# firebase -> database(cloud firestore) -> 규칙
# 앱에서 로그인한 사용자만 데이터 쓰기 허용
service cloud.firestore {
  match /databases/{database}/documents {
    match /{document=**} {
      allow read: if true;
      allow write: if request.auth.uid != null;
    }
  }
}


# 참고
https://firebase.google.com/docs/storage/web/start
https://firebase.google.com/docs/firestore/quickstart
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

## firebase 업로드된 파일 사용

```bash
# firebae storage
# gs(googlestorage) url 과 일반 http url 로 파일에 접근할 수 있다.
https://console.firebase.google.com/project/ysoftman-test/storage/ysoftman-test.appspot.com/files

# gs(googlestorage) url 는 gsutil(google-cloud-sdk)로 접근할 수 있다.
# gsutil 명령어 참고
# https://cloud.google.com/storage/docs/gsutil/commands/cp
# gs(googlestorage) url 파일 보기
gsutil ls -ahl gs://ysoftman-test.appspot.com
# gs(googlestorage) url 파일로 로컬로 복사(다운로드)
gsutil cp -v gs://ysoftman-test.appspot.com/xelloss.jpg .
```
