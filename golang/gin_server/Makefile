SERVER_NAME := gin_server
VERSION:= 0.0.1
BUILD_TIME=$(shell date '+%Y-%m-%d_%H:%M:%S_%Z')
BUILD_UNIX_TIME=$(shell date '+%s')
GITHASH=$(shell git rev-parse HEAD)
OS=$(shell go env GOOS)
ARCH=$(shell go env GOARCH)

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

.PHONY: swagger
swagger:
	@#generate swag doc
	swag init

.PHONY: tidy
tidy:
	go mod tidy

.PHONY: lint
lint:
	golangci-lint run

.PHONY: build
build: clean swagger
	@echo "BUILD_TIME:${BUILD_TIME}"
	@echo "BUILD_UNIX_TIME:${BUILD_UNIX_TIME}"
	@echo "GITHASH:${GITHASH}"
	@echo "OS:${OS}"
	@echo "ARCH:${ARCH}"
	@# -ldflags : golinker 인자 전달
	GOOS=${OS} GOARCH=${ARCH} go build -o ${SERVER_NAME} -ldflags '${LDFLAGS}'

.PHONY: test
test: clean swagger
	go test ./... -v -p 4 -coverprofile cover.out
