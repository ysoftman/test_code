# go-appengine-test
google appengine test using golang


# go-appengine 환경 구성
```bash
##########
# 작업환경1 - google clould 접속해서 작업하기
# google cloud console -> shell 접속

##########
# 작업환경2 - 로컬에서 작업하기
# go appengine sdk 다운로드 및 설치
https://cloud.google.com/appengine/downloads?hl=en
tar zxvf go_appengine_sdk_darwin_amd64-1.9.48.zip
cd go_appengine
export PATH=$PATH:~/workspace/go_appengine/

# google cloud 다운로드 및 설치
https://cloud.google.com/sdk/
tar zxvf google-cloud-sdk-136.0.0-darwin-x86_64.tar.gz
./google-cloud-sdk/install.sh
export PATH=$PATH:~/workspace/google-cloud-sdk/bin
# google cloud 초기화
gcloud init
```
