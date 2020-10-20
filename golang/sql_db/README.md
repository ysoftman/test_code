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

```bash
go build && ./sql_db
```

## 참고

- <https://golang.org/pkg/database/sql/>
- <https://github.com/golang/go/wiki/SQLDrivers>
- <https://gorm.io/docs/>
