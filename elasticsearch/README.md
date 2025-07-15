# elasticserach test

elasticsearch(es) 테스트

## local 환경 구성

```bash
# es 설치
# brew install elastic/tap/elasticsearch-full (에러 발생,  brew 설치 관리가 안되고 있는것 같음)
wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-9.0.3-darwin-aarch64.tar.gz
mkdir -p $HOME/workspace
tar zxvf ./elasticsearch-9.0.3-darwin-aarch64.tar.gz -C $HOME/workspace
# 실행
$HOME/workspace/elasticsearch-9.0.3/bin/elasticsearch

# 동작 확인
# 로그인: elastic / 터미널화면에 패스워드 사용
https://localhost:9200
```
