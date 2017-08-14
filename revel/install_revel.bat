@rem ysoftman
@rem Revel 설치하기(윈도우를 기준으로 했지만, 리눅스도 GOPATH 설정는것 빼면 같음)
@rem golang, git, hg 가 이미 설치되어 있다고 가정

@rem 현재 경로를 GOPATH 로 설정
set GOPATH=%cd%

@rem go get 커맨드로 revel framework 설치
go get github.com/revel/revel

@rem go get 커맨드로 revel command line tool 설치
go get github.com/revel/cmd/revel
