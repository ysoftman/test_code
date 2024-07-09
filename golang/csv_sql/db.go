package main

import (
	"database/sql"
	"log"
)

type SQLDataBase struct {
	sqlDB *sql.DB
}

var sqldb *SQLDataBase

func NewDB() *SQLDataBase {
	db, err := sql.Open("sqlite3", "./sqlite.db")
	if err != nil {
		log.Fatal("open sqlite err =>", err)
	}
	// log.Println("db:", db)
	return &SQLDataBase{
		sqlDB: db,
	}
}

func (db *SQLDataBase) CreateTable(stmt string) error {
	// log.Printf("stmt => %q\n", stmt)
	_, err := db.sqlDB.Exec(stmt)
	if err != nil {
		log.Printf("stmt => %v, err => %v", stmt, err)
		return err
	}
	return nil
}

func (db *SQLDataBase) SelectData(query string) (map[int]interface{}, error) {
	// log.Printf("query => %q\n", query)
	rows, err := db.sqlDB.Query(query)
	if err != nil {
		log.Printf("query => %v, err => %v", query, err)
		return nil, err
	}
	defer rows.Close()
	columns, err := rows.Columns()
	if err != nil {
		log.Printf("query => %v, err => %v", query, err)
		return nil, err
	}
	// log.Println("columns:", columns)

	out := map[int]interface{}{}
	ptrResults := make([]interface{}, len(columns))
	cnt := 0
	for rows.Next() {
		results := make([]interface{}, len(columns))
		for i := range columns {
			ptrResults[i] = &results[i]
		}
		if err := rows.Scan(ptrResults...); err != nil {
			log.Printf("query => %v, err => %v", query, err)
			return nil, err
		}
		// log.Println("results:", results)
		// log.Println("ptrResults:", ptrResults)
		// out = append(out, results)
		out[cnt] = results
		cnt++
	}
	return out, nil
}

func (db *SQLDataBase) InsertData(prepareStmt string, data [][]string) error {
	// log.Printf("stmt => %q\n", prepareStmt)
	tx, err := db.sqlDB.Begin()
	if err != nil {
		log.Printf("err => %v", err)
		return err
	}
	stmt, err := db.sqlDB.Prepare(prepareStmt)
	if err != nil {
		log.Printf("stmt => %v, err => %v", stmt, err)
		return err
	}
	defer stmt.Close()
	for _, d := range data {
		// log.Println("==>", d)
		temp := make([]interface{}, len(d))
		for i, j := range d {
			temp[i] = j
		}
		if _, err := stmt.Exec(temp...); err != nil {
			log.Printf("stmt => %v, err => %v", stmt, err)
			return err
		}
	}
	tx.Commit()
	return nil
}
