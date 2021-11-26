package main

import (
	"encoding/csv"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"strconv"
	"strings"

	_ "github.com/mattn/go-sqlite3"
)

func UploadHandler() http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		switch r.Method {
		case http.MethodGet:
		case http.MethodPost:
			uploadData(w, r)
		case http.MethodPut:
		case http.MethodDelete:
		default:
		}
	}
}
func QueryDataHandler() http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		switch r.Method {
		case http.MethodGet:
		case http.MethodPost:
			queryData(w, r)
		case http.MethodPut:
		case http.MethodDelete:
		default:
		}
	}

}

func uploadData(w http.ResponseWriter, r *http.Request) {
	file, fileHeader, err := r.FormFile("filename")
	if err != nil {
		log.Println("err:", err)
		return
	}
	defer file.Close()

	log.Println("uploaded filename:" + fileHeader.Filename)

	// buf, _ := ioutil.ReadAll(file)
	// backup := ioutil.NopCloser(bytes.NewBuffer(buf))
	// log.Println("-----", string(buf))
	rows, _ := csv.NewReader(file).ReadAll()
	// log.Println("-----", rows)

	tbName := strings.ReplaceAll(fileHeader.Filename, ".", "_")
	if len(rows) < 2 {
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte("error, no data"))
		return
	}
	if err := sqldb.CreateTable(makeSQLTableSchema(tbName, rows[0], rows[1])); err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte("error, failed to create table"))
		return
	}
	if err := sqldb.InsertData(makeSQLInsert(tbName, rows[0]), rows[1:]); err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte("error, failed to insert table"))
		return
	}

	w.Write([]byte("file is inserted"))
	return
}

func queryData(w http.ResponseWriter, r *http.Request) {
	buf, _ := ioutil.ReadAll(r.Body)
	log.Println(string(buf))
	results, err := sqldb.SelectData(string(buf))
	if err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte("error, failed to select data"))
		return
	}
	resp, err := json.MarshalIndent(results, "", "  ")
	if err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte("error, failed to marsahl json"))
		return
	}
	w.Write(resp)
	return
}

func makeSQLTableSchema(tbName string, names []string, values []string) string {
	stmt := fmt.Sprintf("drop table %v; create table %v (", tbName, tbName)
	for i := range names {
		stmt += names[i]
		if _, err := strconv.ParseInt(values[i], 10, 64); err != nil {
			stmt += " text default null,"
		} else {
			stmt += " bigint(20) default null,"
		}
	}
	stmt = strings.TrimSuffix(stmt, ",")
	stmt += ");"
	return stmt
}

func makeSQLInsert(tbName string, colNames []string) string {
	stmt := fmt.Sprintf("insert into %v(", tbName)
	valuesStmt := "values("
	for _, v := range colNames {
		stmt += v + ","
		valuesStmt += "?,"
	}
	stmt = strings.TrimSuffix(stmt, ",")
	valuesStmt = strings.TrimSuffix(valuesStmt, ",") + ");"
	stmt += ") " + valuesStmt
	return stmt
}
