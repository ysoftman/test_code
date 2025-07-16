from elasticsearch import Elasticsearch

# 1. Elasticsearch 클라이언트 연결
# 로컬에서 기본 설정으로 실행 중이라면 이 주소를 사용합니다.
# 만약 Docker 등으로 실행 중이고 포트가 다르거나, 사용자 인증이 필요하다면
# 주소를 변경하거나 basic_auth=('username', 'password') 등을 추가해야 합니다.
es = Elasticsearch("http://localhost:9200")

# 연결 확인 (핑 테스트)
if es.ping():
    print("Elasticsearch에 성공적으로 연결되었습니다!")
else:
    print(
        "Elasticsearch 연결에 실패했습니다. Elasticsearch가 실행 중인지 확인해주세요."
    )
    exit()  # 연결 실패 시 프로그램 종료

# 인덱스 이름 정의
index_name = "my_documents_index"

# 2. 기존 인덱스 삭제 (선택 사항: 테스트를 위해 매번 깨끗하게 시작)
# 이 코드를 사용하면 스크립트 실행 시마다 이전 데이터를 지우고 새로 시작합니다.
if es.indices.exists(index=index_name):
    es.indices.delete(index=index_name)
    print(f"기존 인덱스 '{index_name}'를 삭제했습니다.")

# 3. 새로운 인덱스 생성
# 인덱스 생성 시 특별한 매핑(데이터 구조 정의)이 없으면 기본 매핑으로 생성됩니다.
es.indices.create(index=index_name)
print(f"인덱스 '{index_name}'가 성공적으로 생성되었습니다.")

# 4. 문서(데이터) 인덱싱 (추가)
# 여러 개의 문서를 리스트로 정의합니다. 각 문서는 딕셔너리 형태입니다.
documents_to_add = [
    {
        "id": 1,
        "title": "Elasticsearch 시작 가이드",
        "author": "김철수",
        "content": "Elasticsearch는 분산 검색 및 분석 엔진입니다.",
    },
    {
        "id": 2,
        "title": "빅데이터 분석을 위한 파이썬",
        "author": "이영희",
        "content": "파이썬은 데이터 과학 및 머신러닝에 널리 사용됩니다.",
    },
    {
        "id": 3,
        "title": "NoSQL 데이터베이스 비교",
        "author": "박민준",
        "content": "MongoDB, Cassandra, Elasticsearch는 인기 있는 NoSQL 데이터베이스입니다.",
    },
    {
        "id": 4,
        "title": "검색 엔진 최적화 (SEO) 전략",
        "author": "최지영",
        "content": "효과적인 SEO는 웹사이트 트래픽 증가에 필수적입니다.",
    },
    {
        "id": 5,
        "title": "클라우드 컴퓨팅의 이해",
        "author": "김철수",
        "content": "AWS, Azure, GCP 등 클라우드 서비스는 현대 IT의 핵심입니다.",
    },
]

print("\n--- 문서 인덱싱 중 ---")
for doc in documents_to_add:
    # es.index()를 사용하여 인덱스에 문서를 추가합니다.
    # 'id'를 명시적으로 지정하여 문서의 고유 ID를 설정합니다.
    es.index(index=index_name, id=doc["id"], document=doc)
    print(f"  - 문서 ID: {doc['id']}, 제목: '{doc['title']}' 인덱싱 완료.")

# 인덱싱된 문서가 즉시 검색 가능하도록 새로 고침 (테스트 환경에서 유용)
es.indices.refresh(index=index_name)
print(f"인덱스 '{index_name}'가 새로 고쳐졌습니다. 모든 문서가 검색 가능합니다.")

# 5. 기본적인 검색 수행 (Match Query)
print("\n--- '검색 엔진' 키워드로 문서 검색 ---")
search_query_1 = {
    "query": {
        "match": {
            "content": "검색 엔진"  # 'content' 필드에서 "검색 엔진" 키워드와 일치하는 문서 검색
        }
    }
}
response_1 = es.search(index=index_name, body=search_query_1)

print(f"총 {response_1['hits']['total']['value']}개의 결과가 발견되었습니다.")
for hit in response_1["hits"]["hits"]:
    # '_score'는 검색 결과의 관련성 점수입니다. 높을수록 더 관련성이 높습니다.
    # '_source'는 인덱싱된 원본 문서 데이터를 포함합니다.
    print(
        f"  - ID: {hit['_id']}, 점수: {hit['_score']:.2f}, 제목: '{hit['_source']['title']}'"
    )

# 6. 다른 키워드로 검색 (Match Query)
print("\n--- '파이썬' 키워드로 문서 검색 ---")
search_query_2 = {
    "query": {"match": {"content": "파이썬"}}  # 'content' 필드에서 "파이썬" 키워드 검색
}
response_2 = es.search(index=index_name, body=search_query_2)

print(f"총 {response_2['hits']['total']['value']}개의 결과가 발견되었습니다.")
for hit in response_2["hits"]["hits"]:
    print(
        f"  - ID: {hit['_id']}, 점수: {hit['_score']:.2f}, 제목: '{hit['_source']['title']}'"
    )

# 7. 특정 필드에서 정확히 일치하는 검색 (Term Query)
print("\n--- '김철수' 저자가 작성한 문서 검색 (정확히 일치) ---")
# 'term' 쿼리는 텍스트 필드의 경우 정확히 일치하는 단어를 찾을 때 사용됩니다.
# 분석(tokenization)을 거치지 않은 'keyword' 타입 필드에 더 적합합니다.
# 현재 'author' 필드는 텍스트 타입이라 '김철수'와 '김철수'가 정확히 일치하여 찾아집니다.
search_query_3 = {
    "query": {
        "term": {"author.keyword": "김철수"}  # .keyword를 붙여 정확한 문자열 매칭 시도
    }
}
response_3 = es.search(index=index_name, body=search_query_3)

print(f"총 {response_3['hits']['total']['value']}개의 결과가 발견되었습니다.")
for hit in response_3["hits"]["hits"]:
    print(
        f"  - ID: {hit['_id']}, 제목: '{hit['_source']['title']}', 저자: '{hit['_source']['author']}'"
    )

# 8. 모든 문서 검색 (Match All Query)
print("\n--- 인덱스 내의 모든 문서 검색 ---")
search_query_all = {
    "query": {"match_all": {}},  # 인덱스의 모든 문서를 반환
    "size": 10,  # 한 번에 가져올 문서의 최대 개수 (기본값 10)
}
response_all = es.search(index=index_name, body=search_query_all)

print(f"총 {response_all['hits']['total']['value']}개의 모든 문서가 발견되었습니다.")
for hit in response_all["hits"]["hits"]:
    print(
        f"  - ID: {hit['_id']}, 제목: '{hit['_source']['title']}', 내용: '{hit['_source']['content'][:50]}...'"
    )  # 내용 일부만 출력

# 9. 인덱스 삭제 (선택 사항: 테스트 후 정리)
# 모든 테스트가 끝나면 인덱스를 삭제하여 깔끔하게 정리할 수 있습니다.
# es.indices.delete(index=index_name)
# print(f"\n인덱스 '{index_name}'를 삭제했습니다.")
