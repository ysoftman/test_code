# go-appengine

- google appengine test using golang
- google cloud sdk https://cloud.google.com/sdk/docs/
- 애플리케이션  https://cloud.google.com/appengine/docs/standard/go/building-app/creating-your-application
- app.yaml 설명 https://cloud.google.com/appengine/docs/standard/go/config/appref

## go-appengine 환경 구성

```bash
##########
# 작업환경1 - google clould 접속해서 작업하기
# google cloud console -> shell 접속

##########
# 작업환경2 - 로컬에서 작업하기
# go appengine sdk 다운로드 및 설치
# https://cloud.google.com/appengine/downloads
# mac
wget https://dl.google.com/dl/cloudsdk/channels/rapid/downloads/google-cloud-sdk-228.0.0-darwin-x86_64.tar.gz
tar zxvf google-cloud-sdk-228.0.0-darwin-x86_64.tar.gz
# ./google-cloud-sdk/install.sh # 선택사항으로 특정 경로에 sdk 를 추가할때
export PATH=$PATH:~/workspace/google-cloud-sdk/bin
gcloud components install app-engine-go
GO111MODULE=on go get -u google.golang.org/appengine/...

# ubuntu
export CLOUD_SDK_REPO="cloud-sdk-$(lsb_release -c -s)"
echo "deb http://packages.cloud.google.com/apt $CLOUD_SDK_REPO main" | sudo tee -a /etc/apt/sources.list.d/google-cloud-sdk.list
curl https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
sudo apt-get update && sudo apt-get install google-cloud-sdk
sudo apt-get install google-cloud-sdk-app-engine-java
sudo apt-get install google-cloud-sdk-app-engine-go
```

## appengine 관리

```bash
# google cloud 초기화
# url 링크 후 verification code 확인하여 입력
# 기존 프로젝트 또는 신규 프로젝트 생성 선택
# Compute Region and Zone 선택
gcloud init

# glcoud  구글 app engine 에 배포하기
# 배포 종료시 접속 가능한 url 이 표시된다.
gcloud app deploy ./app.yaml --promote

# 배포가 완료되면 확인
https://strategic-ivy-120508.appspot

# 배포 후 접속 URL 확인 하기
gcloud app browse

# 앱 로그 확인
gcloud app logs tail -s default
```
