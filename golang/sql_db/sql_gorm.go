package main

import (
	"fmt"
	"log"
	"strconv"
	"time"

	"gorm.io/driver/mysql"
	"gorm.io/gorm"
	"gorm.io/gorm/logger"
	"gorm.io/gorm/schema"
)

// TestInfo => test_info
// gorm 은 PascalCase 인 struct와 필드 이름을 snake_case 로 변경해 테이블/컬럼명으로 사용한다.
type TestInfo struct {
	ID       int64
	Age      int
	Name     string
	LastDate time.Time
	// Enable   bool `gorm:"not null;default:1"`
	Enable bool `gorm:"not null"`
}

func DoGorm() {
	// sql 접속 정보 설정
	hostIP := "127.0.0.1"
	hostPort := 3306
	protocol := "tcp"
	dbname := "mytest"
	id := "root"
	pass := ""

	// DSN(Data Source Name) 설정
	// username:password@protocol(address)/dbname?param=value
	// parseTime=True 를 사용해야 datetime uint8 대신 time.Time 으로 가져올 수 있다.
	DSN := id + ":" + pass + "@" + protocol + "(" + hostIP + ":" + strconv.Itoa(hostPort) + ")/" + dbname + "?charset=utf8&parseTime=True"

	// gorm v1.9.16 이전 방식
	// db, err := gorm.Open("mysql", DSN)
	// 테이블명이 a_b_xxs 처럼 복수형 이름을 사용하지 않게 설정
	// db.SingularTable(true)
	// 수행한 쿼리 stdout 출력
	// db.LogMode(true)

	// gorm 으로 mysql 접속
	db, err := gorm.Open(mysql.Open(DSN), &gorm.Config{NamingStrategy: schema.NamingStrategy{SingularTable: true},
		Logger: logger.Default.LogMode(logger.Error)})
	if err != nil {
		log.Fatal(err)
	}

	// 테이블 내용 전체 삭제
	db.Exec("DELETE FROM test_info")

	user := TestInfo{
		Age:      21,
		Name:     "bill",
		LastDate: time.Now(),
		Enable:   true,
	}
	// 레코드 추가
	// user 는 TestInfo struct 으로 test_info 테이블을 사용한다.
	db.Create(&user)

	// 레코드 수정
	user.Age = 22
	user.Enable = true
	db.Save(&user)
	// 레코드 조회
	user = TestInfo{}
	// db.Table("test_info").Where("name = ?", "bill").First(&user2)
	// db.Where("name = ?", "bill").First(&user2)
	db.Find(&user, "name = ?", "bill")
	fmt.Println(user.ID)
	fmt.Println(user.Age)
	fmt.Println(user.Name)
	fmt.Println(user.LastDate)
	fmt.Println(user.Enable)

	user.Age = 23
	user.Enable = false
	db.Delete(TestInfo{}, "id = ?", user.ID)
	// 현재 user.Enable 의 값은 false 인데 db 에는 default:1 로 저장된다.
	fmt.Println("user.Enable:", user.Enable)
	// Enable   bool `gorm:"not null;default:1"`
	db.Save(&user)

	// 레코드 삭제 및 저장(update)를 트랜잭션으로 처리
	// db.Transaction(func(tx *gorm.DB) error {
	// 	// tx.Delete(TestInfo{}, "id = ?", user.ID)
	// 	if err := tx.Save(&user).Error; err != nil {
	// 		return err
	// 	}
	// 	return nil
	// })

}
