# firebase test

## firebase 프로젝트 생성 후 최초 설정

```bash
# api키, 프로젝트 정보 참고해 common.js -> var config {} 설정
https://console.firebase.google.com/u/0/project/ysoftman-firebase/settings/general/


# firebase -> storage -> rules
# 읽기 허용으로 설정
service firebase.storage {
  match /b/{bucket}/o {
    match /{allPaths=**} {
      allow read: if true;
    }
  }
}

# firebase -> database(cloud firestore) -> rules
# 앱에서 로그인한 사용자만 데이터 쓰기 허용
service cloud.firestore {
  match /databases/{database}/documents {
    match /{document=**} {
      allow read: if true;
      allow write: if request.auth.uid != null;
    }
  }
}

# firebase -> 데이터 -> 컬렉션시작
컬렉션: test 문서 ysoftman
필드: name , 유형: string, 값: ysoftman
필드: visitCnt , 유형: number, 값: 0

컬렉션: restaurant 문서 "강남 교자" 만 추가
1. setRestaurantDoc() 주석 해제 후 firebase deploy
2. https://ysoftman-firebase.firebaseapp.com/restaurant_pangyo.html 접속
3. 강제 refresh(ctrl+shift+r)
4. 식당리스트가 firestore 에 자동 추가되어 보인다.

# firebase storage 업로드
# gs(googlestorage) url 과 일반 http url 로 파일에 접근할 수 있다.
# gs(googlestorage) url 는 gsutil(google-cloud-sdk)로 접근할 수 있다.
# gcloud gsutil 설치 참고
# https://cloud.google.com/storage/docs/gsutil_install#mac
# gcloud 로 컴포넌트 업데이트
gcloud components update
# gcloud 인증(브라우저 열리고 로그인)
gcloud auth login
# gsutil 명령어 참고
# https://cloud.google.com/storage/docs/gsutil/commands/cp
# gs(googlestorage) url 파일 보기
gsutil ls -ahl gs://ysoftman-firebase.appspot.com
# *.jpg 파일 업로드
gsutil cp -v *.jpg gs://ysoftman-firebase.appspot.com/
# 다운로드 참고
gsutil cp -v gs://ysoftman-firebase.appspot.com/xelloss.jpg .
gsutil cp -v gs://ysoftman-firebase.appspot.com/박카스.jpg .
```

## firebase 프로젝트 배포

```bash
# firebase-tools 설치
npm install -g firebase-tools

# 프로젝트 초기화(프로젝스 환경구성을 위해 최초 한번만)
firebase init
- hosting 선택(스페이스바) 후 엔터
- 프로젝트 선택 후 엔터
하면 기본 환경파일들이 구성된다.

# firebase 구글 로그인
# (브라우저가 열리고 firebase 승인하면된다.)
firebase login

# 테스트를 위해 로컬에서 서빙
firebase serve

# 401 OAuth 관련 에러 발생시 재인증
firebase login --reauth

# 배포
firebase deploy

# 확인
https://ysoftman-firebase.firebaseapp.com/
```

## 참고

- <https://firebase.google.com/docs/storage/web/start>
- <https://firebase.google.com/docs/firestore/quickstart>
- <https://github.com/firebase/quickstart-js/blob/master/storage/index.html>
