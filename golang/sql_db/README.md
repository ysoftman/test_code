# sql 관련 테스트

## local mysql 준비

```bash
# db 및 테이블 생성
mysql -u root < mytest.sql

# mysql 접속해서 확인
mysql -u root
mysql> describe mytest.test_info; select * from mytest.test_info;
```

## 실행

- go-sql-driver 사용 테스트

```bash
# golang 은 database/sql 로 인터페이스만 제공한다.
# 각 db 별 driver 는 직접 설치해야 한다.
go get github.com/go-sql-driver/mysql
GO111MODULE=off go run sql_driver.go
```

- gorm(go-sql-driver 을 쉽게 사용하기 위한) 사용 테스트

```bash
go get github.com/jinzhu/gorm
GO111MODULE=off go run sql_gorm.go
```

## 참고

- <https://golang.org/pkg/database/sql/>
- <https://github.com/golang/go/wiki/SQLDrivers>
- <https://gorm.io/docs/>
