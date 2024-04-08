import {setRestaurantDoc,readRestaurantAll,onLikeClick,onDisLikeClick} from "./common.js"

let restaurantlist = [{
    name: "다연",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 681 H스퀘어 N동 1층",
    menu: "제육쌈밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "감성타코",
    glyphicons: "glyphicons-13-heart.png",
    location: "경기 성남시 분당구 삼평동 740 판교호반써밋플레이스 2층 231,232호",
    menu: "타코,멕시칸요리",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "신승반점 현대백화점판교점",
    glyphicons: "glyphicons-13-heart.png",
    location: "경기 성남시 분당구 백현동 541 지하1층",
    menu: "유니짜장,짬뽕,탕수육",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "이터스 현대백화점판교점",
    glyphicons: "glyphicons-13-heart.png",
    location: "경기 성남시 분당구 백현동 541 지하1층",
    menu: "칠리치킨타코,치킨퀘사디아",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "춘천명물닭갈비",
    glyphicons: "glyphicons-13-heart.png",
    location: "경기 성남시 분당구 운중동 933-1 1층",
    menu: "닭갈비",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "숙성도",
    glyphicons: "glyphicons-13-heart.png",
    location: "경기 성남시 분당구 판교역로 136 힐스테이트판교역 1층 1042호",
    menu: "숙성 돼지고기구, 동치미국수,  된장술밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "우테이블",
    glyphicons: "glyphicons-13-heart.png",
    location: "경기 성남시 분당구 동판교로177번길 25 아브뉴프랑 1층 우테이블",
    menu: "소고기구이",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "Bientoi(비앙또아)",
    glyphicons: "glyphicons-13-heart.png",
    location: "경기 성남시 분당구 동판교로177번길 25 판교아브뉴프랑 1층 127호",
    menu: "오일파스타,오일샌드위치,스튜,브런치",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "붓처스컷",
    glyphicons: "glyphicons-50-star.png",
    location: "경기 성남시 분당구 삼평동 740 2층",
    menu: "스테이크,아메리칸브런치",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "코이라멘",
    glyphicons: "glyphicons-50-star.png",
    location: "경기 성남시 분당구 삼평동 679 삼환하이펙스 B동 지하층 B113호",
    menu: "라멘,치킨가라아게,차슈덮밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "본설렁탕",
    glyphicons: "glyphicons-50-star.png",
    location: "경기 성남시 분당구 판교역로 231 H스퀘어 S동 1층 131호",
    menu: "홍설면,홍설렁탕,백설면,백설렁탕",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "담솥",
    glyphicons: "glyphicons-50-star.png",
    location: "경기 성남시 분당구 동판교로177번길 25 1층 103호",
    menu: "가지솥밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "일면식",
    glyphicons: "glyphicons-50-star.png",
    location: "경기 성남시 분당구 동판교로177번길 25 판교호반써밋플레이스 2층 221호",
    menu: "칼국수,오징어덮밥,낚지볶음",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "빕스",
    glyphicons: "glyphicons-50-star.png",
    location: "경기 성남시 분당구 삼평동 740 아브뉴프랑 2층",
    menu: "패밀리레스토랑",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "양육점",
    glyphicons: "glyphicons-50-star.png",
    location: "백현동 534 판교테크원타워 2층 양육점 판교점",
    menu: "북해도식 양갈비 화로구이",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "매일식당",
    glyphicons: "glyphicons-13-heart.png",
    location: "경기 성남시 분당구 판교역로192번길 14-2 골드타워 1층",
    menu: "수제돈까스",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "인디테이블",
    glyphicons: "glyphicons-50-star.png",
    location: "경기 성남시 분당구 동판교로177번길 25 판교아브뉴프랑 1층 109호",
    menu: "치킨,커리",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "만복 국수",
    glyphicons: "glyphicons-13-heart.png",
    location: "분당구 삼평동 681번지 H스퀘어 N동 108호",
    menu: "비빔국수, 주먹밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "미정 국수",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 680 판교 H스퀘어S동 지하1층",
    menu: "비빔국수, 닭조림 덮밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "소바니 우동",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 682 유스페이스2 B동 지하 1층",
    menu: "돈까스, 생선까스, 우동, 김치알밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "이태원 천상",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 대왕판교로 660(삼평동) B122호",
    menu: "소바니 우동, 카레 우동",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "미래에셋 구내식당",
    glyphicons: "glyphicons-13-heart.png",
    location: "분당구 삼평동 685 미래에셋 지하 1층",
    menu: "백반(4,500원, A/B코스 둘다 먹을수 있음)",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "스마일쿡",
    glyphicons: "glyphicons-13-heart.png",
    location: "판교 테크노밸리 H스퀘어 S동 지하 1층",
    menu: "백반(6천원, 현금 쿠폰구입시 10장에 5만원)",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "밥먹은 닭",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 대왕판교로 670 유스페이스2 A동 B106",
    menu: "계란덮밥, 치킨덮밥, 제육덮밥, 떡만두국, 냉모밀",
    detailInfo:"",
    likeCntUsers: [],
    dislikeCntUsers: [],
    likeCnt: 0,
    dislikeCnt: 0
},
{
    name: "상록면",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 670 유스페이스 1동 지하1층 B109호",
    menu: "우동, 소바, 닭고기 덮밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "차이나 오라",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 670 유스페이스몰 1동 2층 234",
    menu: "짜장면, 짱뽕",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "락앤웍",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 H스퀘어 S동 지하1층",
    menu: "짜장면, 짱뽕",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "찌개애",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 유스페이스1 204호",
    menu: "된장찌개, 생선구이",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "킹콩 부대 찌개",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 판교역로 240 삼환하이펙스A동 2층",
    menu: "킹콩 부대찌개",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "진진반상",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 670 유스페이스1 A동 지하1층 127호",
    menu: "진진반상(한식)",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "더 집밥",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 삼환 하이펙스 A동 지하 1층",
    menu: "백반",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "서경 백반집",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 삼환 하이펙스 A동 지하 1층",
    menu: "백반",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "맛있다",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 유스페이스 1A동 지하 1층",
    menu: "집밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "소호정",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 유스페이스 2B동 지하 1층",
    menu: "집밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "상황 삼계탕",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 유스페이스 2B동 2층",
    menu: "삼계탕, 닭도리탕",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "정원 오리부추 구이",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 유스페이스 2B동 2층",
    menu: "오리구이,볶음밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "명인 만두",
    glyphicons: "glyphicons-13-heart.png",
    location: "판교 테크노밸리 유스페이스1 1층",
    menu: "비빔밤, 라면, 만두, 돈까스, 오므라이스, 기타 분식",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "강남 교자",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 유스페이스 1A동 311호",
    menu: "만두국, 칼국수",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "군산 오징어",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 유스페이스 1A동 310호",
    menu: "오징어 불고기",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "오징어랑",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 670 삼환아이펙스 B동 지하 1층",
    menu: "오징어 볶음, 고등어 구이",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "마키노 차야",
    glyphicons: "glyphicons-50-star.png",
    location: "판교역로 알파리움 2단지 지하1층",
    menu: "씨푸드 뷔페",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "매드 포 갈릭",
    glyphicons: "glyphicons-50-star.png",
    location: "판교역로 알파리움 1단지 2층",
    menu: "갈릭 피자, 파스타, 스테이크",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "순남 시래기",
    glyphicons: "glyphicons-50-star.png",
    location: "판교역로 235 H스퀘어 N동 1층",
    menu: "시래기국, 반찬 셀프",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "모모 카페",
    glyphicons: "glyphicons-50-star.png",
    location: "판교역로 192번길 12 판교 메리어트 8층",
    menu: "뷔페",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "짱가네 포크포크",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 682 유스페이스 2A동 지하1층",
    menu: "냉면 돈까스",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "됐소",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 682 유스페이스 2A동 지하1층",
    menu: "차돌된장찌개(점심시간만),김치째게(점심시간만)",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "담소사골순대",
    glyphicons: "glyphicons-50-star.png",
    location: "판교역로 235 H스퀘어 S동 1층",
    menu: "순대국밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "차이엔",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 판교역로 235 H스퀘어 N동 126호",
    menu: "짜장면, 짱뽕, 탕수육, 깐풍기, 누룽지탕",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "빽다방",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 대왕판교로 660 유스페이스1 134호",
    menu: "커피, 사라다빵, 딸바쥬스, 초코쥬스",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "더 피크닉",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 670 유스페이스 1A동 130호",
    menu: "오므라이스, 오믈렛, 리코타치즈 샐러드",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "기름 짜는 김밥집",
    glyphicons: "glyphicons-50-star.png",
    location: "판교역로 235 H스퀘어 S동 1층",
    menu: "김밥, 쫄면, 분식",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "반장 떡볶이",
    glyphicons: "glyphicons-50-star.png",
    location: "판교역로 235 H스퀘어 S동 1층",
    menu: "반장떡볶이, 부반장떡볶이, 전학생떡볶이",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "오군 식당",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 678 삼환아이펙스 A동 1층 105호",
    menu: "오군 카레",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "브랜든 돈까스",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 678 삼환아이펙스 A동 1층 105호",
    menu: "돈까스, 치킨까스, 생선까스",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "서호 돈까스",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 H스퀘어 S동 지하 1층",
    menu: "돈까스",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "샤보텐",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 아비뉴프랑 A동 1층 105호",
    menu: "돈까스, 치킨까스, 우동",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "생어거스틴",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 아비뉴프랑 A동 1층 105호",
    menu: "팟타이, 나시고랭, 파인애플 볶음밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: '아세야마',
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 판교역로 240 삼환하이펙스 A동 지하1층 123호",
    menu: "덴푸라 카레, 가아라게 카레",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "채선당 플러스",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 대왕판교로606번길 47",
    menu: "샤브샤브, 뷔페",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "맥도날드",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 H스퀘어 S동 1층",
    menu: "버거, 감자튀김, 아이스크림, 쉐이크",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "버거킹",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 유스페이스 1A동 1층",
    menu: "버거, 감자튀김",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "찬장",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 알파리움 1단지 라스트스트리트 2층",
    menu: "고등어 구이, 순두부찌개",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "더 냄비",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 유스페이스 1A동 1층",
    menu: "닭고기 정식, 쭈꾸미, 제육볶음",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "준영",
    glyphicons: "glyphicons-13-heart.png",
    location: "분당구 판교역로 240 삼환하이펙스 A동 지하1층",
    menu: "파이탄라멘, 매운라멘, 차슈동",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "다루마 라멘",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 판교역로 240 삼환하이펙스 A동 지하1층",
    menu: "돈코츠 라멘, 쯔께멘",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "두부가 보쌈애",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 H스퀘에 N동 지하 1층",
    menu: "두부 김치짹, 해물 된장찌개",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "홍대 돈부리",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 H스퀘에 S동 1층",
    menu: "새우튀김우동, 믹스가츠동, 사케우나기동",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "카레 뜰에",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 H스퀘에 S동 지하 1층",
    menu: "돈까스 카레, 치킨까스 카레",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "김밥 천국",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 H스퀘에 S동 지하 1층",
    menu: "김밥, 떡볶이, 기타 분식",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "미쓰 싸이공",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 H스퀘에 S동 지하 1층",
    menu: "소고기 쌀국수, 사이공 볶음밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "낭 싸이공",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 H스퀘에 S동 지하 1층",
    menu: "쌀국수, 볶음밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "전주 콩나물 국밥",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 H스퀘에 S동 지하 1층",
    menu: "김치찌개, 제육볶음, 김치찜",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "죠샌드위치",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 H스퀘에 S동 지하 1층",
    menu: "샌드위치",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "메콩타이",
    glyphicons: "glyphicons-50-star.png",
    location: "판교 테크노밸리 H스퀘에 N동 1층",
    menu: "소고기 쌀국수, 파인애플 볶음밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "슈퍼타이",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 판교로319번길 13",
    menu: "소고기 쌀국수, 파인애플 볶음밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "포메인",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 삼평동 682 유스페이스1 제3층 313호",
    menu: "쌀국수, 볶음밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "써브웨이",
    glyphicons: "glyphicons-13-heart.png",
    location: "분당구 삼평동 682 유스페이스2 제1층 119호",
    menu: "샌드위치, 샐러드",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "봉편메밀촌 뜨락",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 서판교로 164 훼미리빌딩1층",
    menu: "비빔막국수, 메밀소바, 메밀칼국수",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "광남 포차",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 판교로319번길 13 디테라스 1층",
    menu: "떡복이, 순대, 돈까스, 라면",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "영심이 떡볶이",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 판교역로 240 삼환하이펙스A동 105호",
    menu: "떡복이, 순대",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "나고미",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 판교역로 230 삼환하이펙스B동 지하1층 103호",
    menu: "카레 돈부리, 제육덮밥, 참치덮밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "밥볶다",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 판교역로 240 삼환하이펙스 A동 지하 1층",
    menu: "불고기 밴반 볶음",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "오덮",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 판교역로 240 삼환하이펙스 A동 지하 114-1호",
    menu: "오징어덮밥, 제육덮밥, 참치덮밥",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "스시쿤",
    glyphicons: "glyphicons-50-star.png",
    location: "분당구 대왕판교로 660 유스페이스몰1차 지하1층 115호",
    menu: "스시",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "림꼬또",
    glyphicons: "glyphicons-198-remove-circle.png",
    location: "분당구 판교역로 240 삼환하이펙스 A동 지하 1층",
    menu: "치킨 덮밥, 소고기 덮밥 😠",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "등심촌",
    glyphicons: "glyphicons-198-remove-circle.png",
    location: "분당구 삼평동 681 H스퀘어 N동 1층",
    menu: "밀면 (고무줄) 😠",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
},
{
    name: "챠오바라이트",
    glyphicons: "glyphicons-198-remove-circle.png",
    location: "판교역로192번길 14-2",
    menu: "파스타 (서비스,음식 엉망) 😠",
    detailInfo:"", likeCntUsers: [], dislikeCntUsers: [], likeCnt: 0, dislikeCnt: 0
}
];

const coll = "restaurant";
window.onload = function () {
    readRestaurantAll(coll);
    // firestore 컬렉션(판교식당) 문서있으면 업데이트 없으면 생성
    //restaurantlist.forEach((doc) => {
    //    setRestaurantDoc(coll, doc)
    //});
}
