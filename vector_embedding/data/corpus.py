"""Small Korean retrieval corpus for Recall@K / MRR benchmarking."""

from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class Query:
    text: str
    relevant_ids: list[int]


CORPUS: list[str] = [
    # 요리 / 음식
    "김치찌개는 돼지고기와 묵은지를 넣고 끓이면 깊은 맛이 난다.",
    "라면을 끓일 때 계란을 넣으면 더 고소해진다.",
    "된장국은 멸치와 다시마로 육수를 낸 뒤 된장을 풀어 끓인다.",
    # 프로그래밍
    "파이썬에서 리스트 컴프리헨션은 for 루프보다 간결하게 컬렉션을 만든다.",
    "Go 언어의 고루틴은 채널을 통해 값을 주고받는다.",
    "러스트의 소유권 시스템은 컴파일 타임에 메모리 안전성을 보장한다.",
    "데이터베이스 인덱스를 잘 설계하면 쿼리 성능이 크게 향상된다.",
    # 금융 / 경제
    "미국 연준이 기준금리를 동결했다.",
    "코스피 지수가 외국인 매도세에 하락 마감했다.",
    "비트코인 가격이 최근 일주일간 크게 변동하고 있다.",
    # 스포츠
    "손흥민이 토트넘 경기에서 한 골을 기록했다.",
    "한국 야구 대표팀이 국제대회에서 우승했다.",
    "LPGA 투어에서 한국 선수가 우승을 차지했다.",
    # 날씨 / 재난
    "내일 수도권에 많은 비가 예보되었다.",
    "태풍이 남해안에 상륙할 것으로 예상된다.",
    "올겨울은 예년보다 추울 것으로 관측된다.",
    # 문화 / 엔터
    "BTS의 신곡이 빌보드 차트 1위에 올랐다.",
    "한국 영화가 칸 영화제에서 상을 받았다.",
    "넷플릭스 한국 드라마가 글로벌 시청 1위를 기록했다.",
    # 과학 / 기술
    "NASA가 화성 탐사선을 성공적으로 착륙시켰다.",
    "양자컴퓨터가 특정 문제에서 기존 컴퓨터를 능가했다.",
    "국내 연구팀이 새로운 배터리 소재를 개발했다.",
]


QUERIES: list[Query] = [
    Query("김치찌개 끓이는 법 알려줘", relevant_ids=[0]),
    Query("라면에 계란 넣으면 어때?", relevant_ids=[1]),
    Query("된장국 육수 내는 방법", relevant_ids=[2]),
    Query("파이썬 리스트 만드는 간결한 방법", relevant_ids=[3]),
    Query("고루틴과 채널 사용법", relevant_ids=[4]),
    Query("러스트 메모리 안전성은 어떻게 보장되나", relevant_ids=[5]),
    Query("DB 쿼리 성능 향상 방법", relevant_ids=[6]),
    Query("연준 금리 결정", relevant_ids=[7]),
    Query("한국 주식 시장 동향", relevant_ids=[8]),
    Query("최근 비트코인 시세 변동", relevant_ids=[9]),
    Query("손흥민 경기 결과", relevant_ids=[10]),
    Query("한국 야구 국제대회 성적", relevant_ids=[11]),
    Query("내일 날씨 어때?", relevant_ids=[13]),
    Query("태풍 상륙 소식", relevant_ids=[14]),
    Query("BTS 차트 성적", relevant_ids=[16]),
    Query("한국 영화 해외 수상", relevant_ids=[17]),
    Query("화성 탐사 뉴스", relevant_ids=[19]),
    Query("양자컴퓨터 성능", relevant_ids=[20]),
]
