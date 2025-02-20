SERVER_NAME := gin_server
VERSION:= 0.0.1
BUILD_TIME=$(shell date '+%Y-%m-%d_%H:%M:%S_%Z')
BUILD_UNIX_TIME=$(shell date '+%s')
GITHASH=$(shell git rev-parse HEAD)
OS=$(shell go env GOOS)
ARCH=$(shell go env GOARCH)

# go install github.com/rakyll/gotest@latest
GOTEST:=$(shell command -v gotest 2> /dev/null)
ifneq ($(GOTEST),)
$(info $(GOTEST) command found in PATH)
	GOTEST:=gotest
else
$(info gotest command not found in PATH)
	GOTEST:=go test
endif

#https://pkg.go.dev/cmd/link
#-X importpath.name=value
#    Set the value of the string variable in importpath named name to value.
LDFLAGS += -X "main.name=${SERVER_NAME}"
LDFLAGS += -X "main.version=${VERSION}"
LDFLAGS += -X "main.build_time=${BUILD_TIME}"
LDFLAGS += -X "main.build_unix_time=${BUILD_UNIX_TIME}"
LDFLAGS += -X "main.git_hash=${GITHASH}"
LDFLAGS += -X "main.os=${OS}"
LDFLAGS += -X "main.arch=${ARCH}"

.PHONY: all
all: clean build

.PHONY: clean
clean:
	rm -rf ${SERVER_NAME} ./docs ./tmp
	go clean -testcache

.PHONY: swag
swag:
	@#generate swag doc
	swag fmt
	swag init --parseDependency --parseInternal > /dev/null

.PHONY: tidy
tidy:
	go mod tidy

.PHONY: lint
lint:
	golangci-lint run

.PHONY: build
build: clean swag
	@echo "BUILD_TIME:${BUILD_TIME}"
	@echo "BUILD_UNIX_TIME:${BUILD_UNIX_TIME}"
	@echo "GITHASH:${GITHASH}"
	@echo "OS:${OS}"
	@echo "ARCH:${ARCH}"
	@# -ldflags : golinker 인자 전달
	GOOS=${OS} GOARCH=${ARCH} go build -o ${SERVER_NAME} -ldflags '${LDFLAGS}'

.PHONY: test
test: clean swag
	${GOTEST} ./... -v

.PHONY: diagnostic
diagnostic:
	@gopls check $(shell find . -name "*.go")

.PHONY: fmt
fmt:
	@gofumpt -w -l $(shell find . -name "*.go")

.PHONY: staticcheck
staticcheck:
	@#QF(QuickFix) 항목들은 IDE(vscode,nvim) 환경에서 gopls 로 staticcheck 를 사용할때만 가능
	@staticcheck -checks inherit,-ST1005 ./...

.PHONY: doc
doc:
	# http://localhost:6060
	godoc -http=:6060

.PHONY: coverage
coverage:
	${GOTEST} -coverprofile cover.out ./...
	go tool cover -html cover.out -o cover.html
	open cover.html
	# 또는 function 별로 coverage 확인
	# go tool cover -func=cover.out

.PHONY: run
run:
	go run ./...

.PHONY: profile
profile:
	# make run 으로 별도 프로세스로 서버 실행 후
	curl 'http://localhost:8080/debug/pprof/profile?seconds=10' -o profile.out
	go tool pprof -http=:9090 profile.out

.PHONY: profile_heap
profile_heap:
	# make run 으로 별도 프로세스로 서버 실행 후
	curl 'http://localhost:8080/debug/pprof/heap?seconds=10' -o heap.out
	go tool pprof -http=:9090 heap.out

