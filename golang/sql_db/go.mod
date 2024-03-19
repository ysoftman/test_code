module sql_db

go 1.14

// 디버깅을 위해 다운받은 gorm 패키지 사용시
// replace gorm.io/gorm => /Users/ysoftman/workspace/gorm

require (
	github.com/DATA-DOG/go-sqlmock v1.5.2
	github.com/go-sql-driver/mysql v1.5.0
	gorm.io/driver/mysql v1.0.2
	gorm.io/gorm v1.20.2
)
