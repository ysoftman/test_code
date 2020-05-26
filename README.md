# concal

## 개발 환경

```bash
# flutter 설치(mac 기준)
wget https://storage.googleapis.com/flutter_infra/releases/stable/macos/flutter_macos_1.17.1-stable.zip
unzip flutter_macos_1.17.1-stable.zip
export PATH=$PATH:$(pwd)/flutter/bin

# flutter 동작에 필요한 요소 체크
flutter doctor -v

# ios
# 앱스토어에서 xcode 설치
# xcode 설치 아래 명령 실행
sudo xcode-select --switch /Applications/Xcode.app/Contents/Developer
sudo xcodebuild -runFirstLaunch
# 배포를 위한 cocoapod 툴 설치
sudo gem install cocoapods

# android
# android studio 등 다운로드 받아 설치
https://developer.android.com/studio
# android studio -> cmd+, (preferences) 에서
# 최신 android sdk 설치
# flutter plugin 설치

# app 생성
flutter create concal
# ios simulator 열기(spotlight 에서 simulator 실행해도됨)
open -a Simulator
# simulator 에 앱 실행
flutter run

# pubspec.yaml -> dependencies 에 패키지 명시 후 설치
flutter pub get

# vscode 에서 flutter extension 설치하면
# 자동 yaml 변화를 감지해 자동 설치
# F5 빌드하면 simulator 자동실행
# 변화 자동 감지 반영("hot reload" (press "r"))

# 빌드 및 배포
# android build
# open build/app/outputs/apk/release/app-release.apk 파일 폰으로 복사해 실행
flutter build apk
# ios build
open ios/Runner.xcworkspace
# Project navigator -> Runner -> signing & capabilites -> team -> add accont 또는 development 계정
flutter build ios
```

## 참고

- <https://flutter.dev/docs/get-started/install>
- <https://pub.dev/packages/flutter_calendar_carousel#-installing-tab->
