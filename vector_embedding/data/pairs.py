"""Korean sentence pairs with similarity labels.

label scale (KorSTS style, normalized 0..1):
  1.0 = 의미 동일 / 거의 동일 패러프레이즈
  0.7 = 주제/의미 강하게 관련
  0.4 = 느슨하게 관련
  0.0 = 무관
"""

from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class Pair:
    a: str
    b: str
    label: float
    tag: str  # "paraphrase_ko", "crosslingual", "related", "unrelated"


PAIRS: list[Pair] = [
    # --- 한국어 패러프레이즈 (label ~1.0) ---
    Pair(
        "고양이가 소파 위에서 잠을 잔다", "냥이가 소파 위에 누워서 자고 있다", 1.0, "paraphrase_ko"
    ),
    Pair("오늘 회의는 오후 3시에 시작합니다", "회의가 오늘 15시에 열린다", 1.0, "paraphrase_ko"),
    Pair("서울의 집값이 크게 올랐다", "서울 부동산 가격이 급등했다", 1.0, "paraphrase_ko"),
    Pair("이 책은 정말 재미있다", "이 책 너무 재밌어", 1.0, "paraphrase_ko"),
    Pair("그는 어제 병원에 다녀왔다", "어제 걔 병원 갔다 왔어", 1.0, "paraphrase_ko"),
    Pair("환율이 다시 상승하고 있다", "달러값이 또 오르는 중이다", 0.9, "paraphrase_ko"),
    Pair("김치찌개 끓이는 법 알려줘", "김치찌개 레시피 좀", 1.0, "paraphrase_ko"),
    # --- 교차언어 (한 / 영) ---
    Pair("나는 피자를 좋아해", "I love pizza", 1.0, "crosslingual"),
    Pair("내일 비가 올 것 같다", "It looks like it will rain tomorrow", 1.0, "crosslingual"),
    Pair("이 영화 정말 감동적이었다", "This movie was truly moving", 1.0, "crosslingual"),
    Pair("지하철이 많이 붐빈다", "The subway is very crowded", 0.9, "crosslingual"),
    Pair(
        "그 회사는 최근 흑자를 기록했다",
        "The company recently turned a profit",
        0.9,
        "crosslingual",
    ),
    # --- 관련 있지만 동일하진 않음 (label ~0.5) ---
    Pair("주식이 올랐다", "채권 금리가 하락했다", 0.5, "related"),
    Pair("오늘 점심으로 라면을 먹었다", "저녁에는 김밥을 먹을 것이다", 0.5, "related"),
    Pair("아이폰 신모델이 출시됐다", "삼성 갤럭시가 새로 나왔다", 0.6, "related"),
    Pair("축구 경기를 봤다", "야구 중계를 시청했다", 0.5, "related"),
    Pair("파이썬으로 웹 서버를 만들었다", "Go 언어로 API를 개발했다", 0.6, "related"),
    # --- 무관 (label ~0.0) ---
    Pair("오늘 날씨가 참 맑다", "데이터베이스 인덱스를 재구성했다", 0.0, "unrelated"),
    Pair("아침에 커피를 마셨다", "화성 탐사선이 착륙에 성공했다", 0.0, "unrelated"),
    Pair("강아지가 공을 물고 왔다", "비트코인 가격이 폭락했다", 0.0, "unrelated"),
    Pair("책상 위에 책이 있다", "교향곡 9번은 베토벤의 작품이다", 0.0, "unrelated"),
    Pair("버스를 놓쳤다", "양자역학은 확률론적이다", 0.0, "unrelated"),
    # --- 미묘한 차이 (negation / 숫자 / 주체) ---
    Pair("나는 그를 좋아한다", "나는 그를 좋아하지 않는다", 0.2, "related"),
    Pair("팀이 3대 1로 이겼다", "팀이 1대 3으로 졌다", 0.4, "related"),
    Pair("엄마가 아빠에게 선물을 줬다", "아빠가 엄마에게 선물을 줬다", 0.6, "related"),
]
