# sql 관련 테스트

## local mysql 준비

```bash
# percona-server (mysql 대체) 설치
brew install percona-server

# local mysqld 실행(mac)
mysqld &

# db 및 테이블 생성
mysql -u root < mytest.sql

# mysql 접속해서 확인
mysql -u root
describe mytest.test_info; select * from mytest.test_info;

# 테스트 완료 후 종료
killall mysqld
```

## 실행

```bash
go build && ./sql_db
```

## test

```bash
go test ./... -v
```

## 참고

- <https://golang.org/pkg/database/sql/>
- <https://github.com/golang/go/wiki/SQLDrivers>
- <https://gorm.io/docs/>
