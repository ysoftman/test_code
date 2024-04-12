module sql_db

go 1.22

// 디버깅을 위해 다운받은 gorm 패키지 사용시
// replace gorm.io/gorm => /Users/ysoftman/workspace/gorm

require (
	github.com/DATA-DOG/go-sqlmock v1.5.2
	github.com/go-sql-driver/mysql v1.5.0
	github.com/mitchellh/mapstructure v1.5.0
	gopkg.in/square/go-jose.v2 v2.6.0
	gorm.io/driver/mysql v1.0.2
	gorm.io/driver/sqlite v1.5.5
	gorm.io/gorm v1.25.8
)

require (
	github.com/jinzhu/inflection v1.0.0 // indirect
	github.com/jinzhu/now v1.1.5 // indirect
	github.com/mattn/go-sqlite3 v1.14.22 // indirect
)
