# github_webhook_action

github webhook 을 받아 필요한 액션(api 호출)을 수행합니다.

- build

```
go get ./...

# run for local test
go build -ldflags "-X main.buildtime=$(date '+%Y-%m-%d_%H:%M:%S_%Z')"

# build
go build -ldflags "-X main.buildtime=$(date '+%Y-%m-%d_%H:%M:%S_%Z')"
```

