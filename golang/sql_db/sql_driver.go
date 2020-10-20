package main

import (
	"database/sql"
	"fmt"
	"log"
	"strconv"

	"github.com/go-sql-driver/mysql"
	_ "github.com/go-sql-driver/mysql" // mysql 드라이버를 소스에서 직접 명시해서 사용하지 않기 때문에 alias 를 _ 로 설정
)

func main() {
	// 현재 사용할 수 있는 sql 드라이버 파악
	drivers := sql.Drivers()
	for i := range drivers {
		fmt.Printf("drivers[%d]=%s\n", i, drivers[i])
	}

	// sql 접속 정보 설정
	hostIP := "127.0.0.1"
	hostPort := 3306
	protocol := "tcp"
	dbname := "mytest"
	id := "root"
	pass := ""

	// DSN(Data Source Name) 설정
	// username:password@protocol(address)/dbname?param=value
	DSN := id + ":" + pass + "@" + protocol + "(" + hostIP + ":" + strconv.Itoa(hostPort) + ")/" + dbname

	fmt.Println("DNS=" + DSN)

	// db 접속
	db, err := sql.Open("mysql", DSN)
	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	// insert, update, delete 경우 Execute() 사용
	// 아래 테스트를 위해 테이블 데이터 모두 삭제
	result, err := db.Exec("delete from test_info")
	if err != nil {
		fmt.Println("insert error!")
		log.Fatal(err)
	}
	fmt.Println(result.LastInsertId())
	fmt.Println(result.RowsAffected())

	// 컬럼명이 order 등과 같은 mysql 에약어인 경우가 있을 수 있어 ``(grave) 로 묶어주는게 좋다.
	result, err = db.Exec("insert into test_info(`age`, `name`, `last_date`, `enable`) values(?,?,now(),?)", 20, "ysoftman", 0)
	if err != nil {
		fmt.Println("insert error!")
		log.Fatal(err)
	}
	fmt.Println(result.LastInsertId())
	fmt.Println(result.RowsAffected())

	// prepare 로 sql 처리 하고 살행하면 좀더 빠르게 처리할 수 있다.
	q := fmt.Sprintf("insert into test_info(`age`, `name`, `last_date`) values('%d','%s',now())", 20, "윤병훈")
	fmt.Println(q)
	stmt, err := db.Prepare(q)
	if err != nil {
		fmt.Println("insert (prepare) error!")
		log.Fatal(err)
	}
	result, err = stmt.Exec()
	if err != nil {
		fmt.Println("insert (prepare-exec) error!")
		log.Fatal(err)
	}

	// read 경우 Query() 사용
	rows, err := db.Query("select id, age, name, last_date, enable from test_info where name = ?", "ysoftman")
	if err != nil {
		fmt.Println("error1")
		log.Fatal(err)
	}
	defer rows.Close()

	// 쿼리 결과 파악
	for rows.Next() {
		var id int64
		var age int
		var name string
		var lastdate mysql.NullTime
		var enable bool
		err := rows.Scan(&id, &age, &name, &lastdate, &enable)
		if err != nil {
			log.Fatal(err)
		}

		log.Println("id:", id)
		log.Println("age:", age)
		log.Println("name:", name)
		log.Println("lastdate:", lastdate)
		log.Println("lastdate:", lastdate.Time)
		log.Println("enable:", enable)
	}
}
