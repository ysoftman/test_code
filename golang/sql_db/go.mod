module sql_db

go 1.23.3

// 디버깅을 위해 다운받은 gorm 패키지 사용시
// replace gorm.io/gorm => /Users/ysoftman/workspace/gorm

require (
	github.com/DATA-DOG/go-sqlmock v1.5.2
	github.com/go-sql-driver/mysql v1.9.2
	github.com/mitchellh/mapstructure v1.5.0
	github.com/stretchr/testify v1.9.0
	gopkg.in/square/go-jose.v2 v2.6.0
	gorm.io/driver/mysql v1.5.7
	gorm.io/driver/sqlite v1.5.7
	gorm.io/gorm v1.25.12
)

require (
	filippo.io/edwards25519 v1.1.0 // indirect
	github.com/davecgh/go-spew v1.1.1 // indirect
	github.com/jinzhu/inflection v1.0.0 // indirect
	github.com/jinzhu/now v1.1.5 // indirect
	github.com/mattn/go-sqlite3 v1.14.27 // indirect
	github.com/pmezard/go-difflib v1.0.0 // indirect
	golang.org/x/text v0.24.0 // indirect
	gopkg.in/yaml.v3 v3.0.1 // indirect
)
