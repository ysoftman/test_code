# Godot Dodge

떨어지는 운석을 피하는 Godot 4.7 게임. 버틴 시간이 점수이고, 시간이 지날수록 운석이 더 자주·빠르게 떨어진다.
에셋 없이 `main.gd` 의 `_draw()` 로만 그린다.

## 조작

| 입력 | 동작 |
|---|---|
| ← → / A D | 이동 |
| 마우스·터치 누른 채 드래그 | 그 위치로 이동 |
| Space / 클릭 | 게임 오버 후 재시작 |

## 로컬 실행

웹 export 나 템플릿 없이 데스크톱 창으로 바로 실행할 수 있다.

```sh
godot                                # project.godot 이 있는 이 폴더에서 실행하면 게임이 창으로 뜬다
godot --path test_pages/godot-game   # 다른 폴더에서 실행할 때
godot -e                             # 에디터로 열기 (F5 또는 ⌘B 로 실행, 스크립트 에러는 하단 Debugger 패널)
godot --headless --quit-after 1200   # 창 없이 1200 프레임 실행 후 종료, 에러가 있으면 콘솔에 출력
```

데스크톱과 웹은 같은 코드라 게임 동작은 같다. 다만 웹에서만 생기는 문제(로딩, 캔버스 크기, 폰트)는
데스크톱 실행으로는 잡히지 않으므로 배포 전에는 웹 빌드도 한 번 열어 본다.

## 웹 빌드 · 서빙

`brew install godot` 은 에디터만 설치한다. Web export 템플릿은 따로 설치해야 하며, 없으면 export 가
`No export template found` 로 실패한다. 에디터의 Editor → Manage Export Templates 를 쓰면 전체(1.2GB)를 받으므로,
아래처럼 웹 템플릿만 설치해도 된다.
스레드 지원을 끈 export 라 COOP/COEP 헤더 없이 아무 정적 서버로 서빙된다.

```sh
brew install godot

# Web export 템플릿만 설치 (tpz 에서 web_nothreads_release.zip 만 추출)
V=4.7.2-stable
T="$HOME/Library/Application Support/Godot/export_templates/${V/-/.}"
mkdir -p "$T"
curl -L -o /tmp/tpl.tpz "https://github.com/godotengine/godot/releases/download/$V/Godot_v${V}_export_templates.tpz"
unzip -j /tmp/tpl.tpz templates/web_nothreads_release.zip -d "$T" && rm /tmp/tpl.tpz

# build/ 가 프로젝트 안에 있으므로 .gdignore 로 에셋 스캔에서 빼야 이전 빌드 산출물이 pck 에 섞이지 않는다
mkdir -p build && touch build/.gdignore
godot --headless --import
godot --headless --export-release Web build/index.html
python3 -m http.server -d build 8000
```

GitHub Pages 배포 시에는 `.github/workflows/pages.yml` 에서 같은 방식으로 export 해 `/godot-game/` 에 올린다.
