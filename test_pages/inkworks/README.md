# Inkworks

[Moh4696/inkworks-skill](https://github.com/Moh4696/inkworks-skill) 에 들어 있는 kit 예제(엔진 · 자전거 펌프 · 슬라이더 크랭크)를 그대로 옮긴 데모다. 기계의 작동 원리를 엔지니어링 도면처럼 그린 인터랙티브 3D 페이지로, 일시정지 · 단계 이동 · 슬로 모션 · 사이클 차트 스크럽 · 카메라 회전을 할 수 있다. 스킬은 설치하지 않았고, 스킬이 새로 만든 페이지도 아니다.

빌드 없는 정적 페이지 묶음이다. GitHub Pages 배포 시 디렉토리를 그대로 복사한다. 목록 페이지(`index.html`)는 test_pages 공용 `../common/doc.css` 를 불러쓰므로 `common/` 이 이 디렉토리와 같은 깊이에 함께 있어야 한다.

## 구성

| 경로                | 내용                                                                                                      |
| ------------------- | --------------------------------------------------------------------------------------------------------- |
| `index.html`        | 목록 페이지. 예제 3개를 `sheet` 레이아웃으로 여는 링크. `figure` 는 그림이 이미 `sheet` 에 들어 있어 뺐다 |
| `kit/`              | 원본 `skills/inkworks/kit/` 사본(1.1.0, `8769b7d`). 수정하지 않는다                                       |
| `kit/index.html`    | kit 진입점. `?m=engine\|pump\|starter` 로 예제를, `?layout=sheet\|figure` 로 레이아웃을 고른다            |
| `kit/js/`           | `kit.js` 그리기 스타일, `sheet.js` 레이아웃 · 컨트롤 · 차트, `mechanisms/*.js` 기계별 형상 · 운동 · 설명  |
| `kit/vendor/three/` | three.js r169 와 OrbitControls (MIT, 자체 LICENSE 포함)                                                   |
| `kit/LICENSE`       | inkworks-skill MIT License                                                                                |

원본 kit 의 `serve.py` 와 `tools/`(Playwright 녹화 · smoke 테스트용 Python 스크립트)는 정적 데모에 필요 없어 옮기지 않았다. `kit/` 은 three.js 클래스 이름 등이 오탐되어 저장소 `typos.toml` 에서 검사 제외한다.

## 확인 (로컬)

kit 은 ES module 과 import map 을 써서 파일로 직접 열면 동작하지 않는다. `../common/doc.css` 도 불러쓰므로 상위 `test_pages` 를 루트로 정적 서버를 띄운다.

```bash
cd test_pages
bunx serve .    # http://localhost:3000/inkworks/
```

## kit 갱신

원본을 받아 kit 의 페이지 파일과 LICENSE 만 다시 복사한다.

```bash
git clone --depth 1 https://github.com/Moh4696/inkworks-skill /tmp/inkworks-skill
rm -rf test_pages/inkworks/kit && mkdir -p test_pages/inkworks/kit
cp -r /tmp/inkworks-skill/skills/inkworks/kit/{index.html,css,js,vendor} test_pages/inkworks/kit/
cp /tmp/inkworks-skill/LICENSE test_pages/inkworks/kit/
```

갱신 후 `index.html` 과 이 README 의 버전 · 커밋 표기를 맞춘다.
