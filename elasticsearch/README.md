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
# 또는
# config/elasticsearch.yml 에서 https 비활성화
# xpack.security.enabled: false
http://localhost:9200

# 사용 가능한 cat api
http://localhost:9200/_cat/
# 모든 인덱스 정보
http://localhost:9200/_cat/indices?v
# my_documents_index 이름의 인덱스 상세 정보
http://localhost:9200/my_documents_index?pretty

# elastic gui 사용하면 편하다.
# 앱
https://github.com/cars10/elasticvue
# chrome extension
https://chromewebstore.google.com/detail/elasticvue/hkedbapjpblbodpgbajblpnlpenaebaa
```

## test

```bash
# elasticsearch 패키지 설치
pip install elasticsearch

# 예제 코드 실행
python es_example1.py
```
