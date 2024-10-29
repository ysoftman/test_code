SERVER_NAME := gin_test_server

BUILD_TIME=$(shell date '+%Y-%m-%d_%H:%M:%S_%Z')
BUILD_UNIX_TIME=$(shell date '+%s')
GITHASH=$(shell git rev-parse HEAD)
OS=$(shell go env GOOS)
ARCH=$(shell go env GOARCH)

.PHONY: all
all: clean build

.PHONY: clean
clean:
	rm -rf ${SERVER_NAME} ./docs ./tmp
	go clean -testcache

.PHONY: swagger
swagger:
	#generate swag doc
	swag init

.PHONY: tidy
tidy:
	go mod tidy

.PHONY: build
build: clean swagger
	@echo "BUILD_TIME:${BUILD_TIME}"
	@echo "BUILD_UNIX_TIME:${BUILD_UNIX_TIME}"
	@echo "GITHASH:${GITHASH}"
	@echo "OS:${OS}"
	@echo "ARCH:${ARCH}"
	GOOS=${OS} GOARCH=${ARCH} go build -o ${SERVER_NAME} .

.PHONY: test
test: clean swagger
	go test ./... -v -p 4 -coverprofile cover.out
