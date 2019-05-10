# flatbuffer test

## flatbuffer 설치

```bash
# mac
brew install flatbuffers
flatc

# linux
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
make
./flattests
./flatc

# flatbuffer schema 컴파일(.go 생성)
flatc --go  monsters.fbs

# GOPATH 설정
mkdir -p ./go_gen/src/
mv -v MyGame ./go_gen/src/

mkdir -p ./go_gen/src/github.com/google/flatbuffers/go
cp -v flatbuffers/go/*.go ./go_gen/src/github.com/google/flatbuffers/go
export GOPATH=$GOPATH:$PWD/go_gen

# run
GO111MODULE=off go run main.go
```
