# firebase test

## firebase 프로젝트 생성 후 최초 설정

```bash
# https://console.firebase.google.com/u/0/project/ysoftman-firebase/settings/general/
# 에서 web api key 참고해 src/web_api_key.js(.gitignore 로 추가했음) 생성
# 키노출시(깃헙에 푸시된 경우) 다음 링크에서 재생성하자
# https://console.cloud.google.com/apis/credentials?project=ysoftman-firebase
cat << zzz >! src/web_api_key.js
export const webApiKey = () => {
  return "여기에 api키 설정";
};
zzz

# firebase -> storage -> rules
# 읽기 허용으로 설정
rules_version = "2";
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
      // read 를 무조건 허용하면 비용 증가로 이어 질 수 있음
      allow read, write: if request.auth.uid != null;
    }
  }
}

# firebase -> 데이터 -> 컬렉션시작
index 컬렉션 생성

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

# 파일 위치 이동
gsutil mv -pv "gs://ysoftman-firebase.appspot.com/*.mp4" "gs://ysoftman-firebase.appspot.com/funny/"
gsutil mv -pv "gs://ysoftman-firebase.appspot.com/*.jpg" "gs://ysoftman-firebase.appspot.com/funny/"
```

## firebase 프로젝트 배포

```bash
# firebase-tools (cli) 설치(bun 설치가 빠르다)
npm install -g firebase-tools
# or
yarn global add firebase-tools
# or
bun add -g firebase-tools

# 프로젝트 초기화(프로젝트 환경구성을 위해 최초 한번만)
firebase init
- hosting 선택(스페이스바) 후 엔터
- 프로젝트 선택 후 엔터
하면 기본 환경파일들이 구성된다.

# firebase 구글 로그인
# (브라우저가 열리고 firebase 승인하면된다.)
firebase login

# 401 OAuth 관련 에러 발생시 재인증
firebase login --reauth

# project list
firebase projects:list

# 최초 한번만 패키지 설치
yarn
# 또는
bun install

# 로컬 테스트를 위해 로컬(dist) 서빙
yarn build && yarn serve
# 또는
bun serve

# 로컬 확인
http://localhost:8080/

# 배포
yarn build && firebase deploy
# 또는
bun run build && firebase deploy

# 배포 확인
https://ysoftman-firebase.firebaseapp.com/
```

## 참고

- <https://firebase.google.com/docs/storage/web/start>
- <https://firebase.google.com/docs/firestore/quickstart>
- <https://github.com/firebase/quickstart-js/blob/master/storage/index.html>
- <https://nostalgic-css.github.io/NES.css/#installation>
