package main

import (
	"fmt"
	"log"
	"strconv"
	"time"

	"github.com/mitchellh/mapstructure"
	"gopkg.in/square/go-jose.v2/json"
	"gorm.io/driver/mysql"
	"gorm.io/driver/sqlite"
	"gorm.io/gorm"
	"gorm.io/gorm/logger"
	"gorm.io/gorm/schema"
)

type InnerData struct {
	Enable bool `gorm:"not null"`
}

// TestInfo => test_info
// gorm 은 PascalCase 인 struct와 필드 이름을 snake_case 로 변경해 테이블/컬럼명으로 사용한다.
type TestInfo struct {
	gorm.Model
	//ID uint64
	// Age      int    `gorm:"default:99"`
	// Name     string `gorm:"default:lemon"`
	// Enable   bool   `gorm:"not null;default:1"`
	Age      int
	Name     string
	LastDate time.Time
	// embed struct 이름 없이 바로 필드로 사용하려면 squash 태그를 명시해야 한다.
	// https://pkg.go.dev/github.com/mitchellh/mapstructure#hdr-Embedded_Structs_and_Squashing
	InnerData `mapstructure:",squash"`
}

func OpenSqlite() gorm.Dialector {
	return sqlite.Open("sqlite.db")
}
func OpenMysql() gorm.Dialector {
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
	// loc=Asia/Seoul (loc=Asia%2FSeoul) 로 설정해야 로컬 시간값으로 설정된다.
	DSN := id + ":" + pass + "@" + protocol + "(" + hostIP + ":" + strconv.Itoa(hostPort) + ")/" + dbname + "?charset=utf8&parseTime=True&loc=Asia%2FSeoul"

	// gorm v1.9.16 이전 방식
	// db, err := gorm.Open("mysql", DSN)
	// 테이블명이 a_b_xxs 처럼 복수형 이름을 사용하지 않게 설정
	// db.SingularTable(true)
	// 수행한 쿼리 stdout 출력
	// db.LogMode(true)
	return mysql.Open(DSN)
}

func printTestInfo(info TestInfo) {
	fmt.Printf("info:%#v\n", info)
	fmt.Println("Id:", info.ID)
	fmt.Println("Age:", info.Age)
	fmt.Println("Name:", info.Name)
	fmt.Println("CreatedAt:", info.CreatedAt)
	fmt.Println("UpdatedAt:", info.UpdatedAt)
	fmt.Println("DeletedAt:", info.DeletedAt)
	fmt.Println("Lastdate:", info.LastDate)
	// embed struct 를 명시하거나 명시하지 않아도 액세스 가능
	fmt.Println("Enable:", info.Enable)
	fmt.Println("InnerDataen.Enable:", info.InnerData.Enable)
}

func DoGorm() {
	//targetDB := OpenSqlite()
	targetDB := OpenMysql()
	db, err := gorm.Open(targetDB, &gorm.Config{
		NamingStrategy: schema.NamingStrategy{
			SingularTable: true, // User -> users 로 복수형 테이블 이름 방지
		},
		Logger: logger.Default.LogMode(logger.Info),
	})
	if err != nil {
		log.Fatal(err)
	}
	sdb, _ := db.DB()

	// SetMaxIdleConns sets the maximum number of connections in the idle connection pool.
	sdb.SetMaxIdleConns(10)

	// SetMaxOpenConns sets the maximum number of open connections to the database.
	sdb.SetMaxOpenConns(100)

	// SetConnMaxLifetime sets the maximum amount of time a connection may be reused.
	sdb.SetConnMaxLifetime(time.Hour)

	// 테이블 내용 전체 삭제
	db.Exec("DELETE FROM test_info")

	user := TestInfo{
		Age:       21,
		Name:      "bill",
		LastDate:  time.Now(),
		InnerData: InnerData{Enable: true},
	}
	// 레코드 추가
	// user 는 TestInfo struct 으로 test_info 테이블을 사용한다.
	db.Create(&user)

	////////// embed struct 이름 없이 바로 필드 사용 테스트 /////////
	printTestInfo(user)
	testdata := struct {
		Age    int
		Name   string
		Enable bool
	}{}
	// 방법1
	if err := mapstructure.Decode(user, &testdata); err == nil {
		fmt.Printf("[mapstructure] %+v\n", testdata)
		//{Age:21 Name:bill Enable:false} //  InnerData  인경우 embed struct 로 같이 맞춰야 한다.
		//{Age:21 Name:bill Enable:true} // InnerData `mapstructure:",squash"`
	}
	// 방법2
	// json string 으로 만든 후 unmarshal 로 struct 에 담기
	if outJson, err := json.Marshal(user); err == nil {
		fmt.Println("[outJson] ", string(outJson))
		//{"ID":78,"CreatedAt":"2024-04-12T16:19:47.775332+09:00","UpdatedAt":"2024-04-12T16:19:47.775332+09:00","DeletedAt":null,"Age":21,"Name":"bill","LastDate":"2024-04-12T16:19:47.775055+09:00","Enable":true}
		testdata2 := struct {
			Age    int
			Name   string
			Enable bool
		}{}
		if err := json.Unmarshal(outJson, &testdata2); err == nil {
			fmt.Printf("[UnMarshal] %+v\n", testdata2)
			// {Age:21 Name:bill Enable:true}
		}
	}
	////////////////////

	// 레코드 수정
	user.Age = 22
	user.Enable = true
	user.CreatedAt = time.Now()
	db.Save(&user)

	// 레코드 조회
	//user = TestInfo{}
	// db.Table("test_info").Where("name = ?", "bill").First(&user2)
	// db.Where("name = ?", "bill").First(&user2)
	db.Find(&user, "name = ?", "bill")
	printTestInfo(user)

	db.Delete(TestInfo{}, "id = ?", user.ID)

	// Save() 는 update 후 select 로 레코드를 확인하는데
	// Delete() 로 해당 레코드가 없으면 insert(gorm create함수)를 수행한다.
	// 이때 만약 구조체 필드 중 `gorm:"default:xxx"` 값이 설정되어 있고
	// 그 필드가 초기값 bool = false, int = 0, string = "" 등인 경우
	// Save() -> Create() -> Execute() -> f() ->
	// callbacks/create.go Create() ->
	// ConvertToCreateValues() -> case reflect.Struct ->
	// isZero() 로 해당 필드가 값이 설정되지 않은 것으로 판단해
	// 다음과 같이 default 값으로 insert 구문을 생성해 실행한다.
	//  INSERT INTO `test_info` (`age`,`name`,`last_date`,`enable`,`id`) VALUES (99,'lemon','2020-10-20 23:37:54',true,89)
	// 만약  bool = false, int = 0, string = "" 인 상태로 저장하고 싶다면
	// default:xxx 태그를 명시하면 안된다.
	user.Name = ""
	user.Age = 0
	user.Enable = false
	// loc=Asia%2F/Seoul 로컬 파라미터로 연결됐을때
	user.CreatedAt = time.Now()
	// loc=Asia%2F/Seoul 로컬 파라미터로 연결되지 않았을때 그냥 string 포맷으로 저장
	// 기존 저장된 데이터 포맷에 의존적이라 비추
	// user.CreatedAt = time.Now().Format("2006-01-02 15:04:05")
	// 현재 user.Enable 의 값은 false 인데 db 에는 default:1 로 저장된다.
	fmt.Println("user.Enable:", user.Enable)
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
