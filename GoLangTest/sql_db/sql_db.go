// author : ysoftman
// encoding : utf-8
// title : sql 관련 테스트
// 참고
// http://golang.org/pkg/database/sql/
//
// golang 은 database/sql 로 인터페이스만 제공한다.
// 각 db 별 driver 는 직접 설치해야 한다.
// sql drivers
// https://github.com/golang/go/wiki/SQLDrivers
//
// github sql driver 다운로드
// go get github.com/go-sql-driver/mysql
package main

import (
	"database/sql"
	"fmt"
	"log"
	"strconv"

	_ "github.com/go-sql-driver/mysql" // mysql 드라이버를 소스에서 직접 명시해서 사용하지 않기 때문에 alias 를 _ 로 설정
)

func main() {

	fmt.Println("sql db test...")

	// 현재 사용할 수 있는 sql 드라이버 파악
	drivers := sql.Drivers()
	for i := range drivers {
		fmt.Printf("drivers[%d]=%s\n", i, drivers[i])
	}

	// sql 접속 정보 설정
	host_ip := "127.0.0.1"
	host_port := 13306
	protocol := "tcp"
	dbname := "test"
	id := "root"
	pass := "ysoftman"

	// DSN(Data Source Name) 설정
	// username:password@protocol(address)/dbname?param=value
	DSN := id + ":" + pass + "@" + protocol + "(" + host_ip + ":" + strconv.Itoa(host_port) + ")/" + dbname

	fmt.Println("DNS=" + DSN)

	// db 접속
	db, err := sql.Open("mysql", DSN)
	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	// write 경우 Execute() 사용
	result, err := db.Exec("insert into test_info(id, age, name, last_date) values(?,?,?,now())", "ysoftman", 20, "윤병훈")
	if err != nil {
		fmt.Println("insert error!")
		log.Fatal(err)
	}
	fmt.Println(result.LastInsertId())
	fmt.Println(result.RowsAffected())

	// read 경우 Query() 사용
	rows, err := db.Query("select id, age, name from test_info where id = ?", "ysoftman")
	if err != nil {
		fmt.Println("error1")
		log.Fatal(err)
	}
	defer rows.Close()

	// 쿼리 결과 파악
	for rows.Next() {
		var id string
		var age int
		var name string
		err := rows.Scan(&id, &age, &name)
		if err != nil {
			log.Fatal(err)
		}

		log.Println("id:", id)
		log.Println("age:", age)
		log.Println("name:", name)
	}

}
