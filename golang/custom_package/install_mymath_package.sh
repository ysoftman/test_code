#!/bin/bash
# 패키지 설치 방법
# GOPATH 에 src 복사
rm -rfv $GOPATH/src/mymath
cp -rv ./src/mymath $GOPATH/src/

# 패키지 빌드 및 설치
# 설치가 성공했다으면 (윈도우64 기준으로) $GOPATH/pkg/windows_amd64/mymath.a 가 생성된다.
go build mymath
go install mymath
