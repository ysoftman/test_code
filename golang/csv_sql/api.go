package main

import (
	"context"
	"encoding/csv"
	"encoding/json"
	"errors"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"strconv"
	"strings"
	"time"

	_ "github.com/mattn/go-sqlite3"
)

const DefaultTimeOut = time.Minute * 5

func UploadHandler() http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		ctx, cancel := context.WithTimeout(r.Context(), DefaultTimeOut)
		defer cancel()
		r.WithContext(ctx)
		ch := make(chan error)
		go func() {
			switch r.Method {
			case http.MethodGet:
			case http.MethodPost:
				ch <- uploadData(w, r)
			case http.MethodPut:
			case http.MethodDelete:
			default:
			}
		}()
		select {
		case <-ch:
			return
		case <-ctx.Done():
			w.WriteHeader(http.StatusInternalServerError)
			w.Write([]byte("error, timeout"))
			return
		}
	}
}
func QueryDataHandler() http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		ctx, cancel := context.WithTimeout(r.Context(), DefaultTimeOut)
		defer cancel()
		r.WithContext(ctx)
		ch := make(chan error)
		go func() {
			switch r.Method {
			case http.MethodGet:
			case http.MethodPost:
				ch <- queryData(w, r)
			case http.MethodPut:
			case http.MethodDelete:
			default:
			}
		}()
		select {
		case <-ch:
			return
		case <-ctx.Done():
			w.WriteHeader(http.StatusInternalServerError)
			w.Write([]byte("error, timeout"))
			return
		}
	}
}

func uploadData(w http.ResponseWriter, r *http.Request) error {
	file, fileHeader, err := r.FormFile("filename")
	if err != nil {
		log.Println("err:", err)
		return errors.New("error")
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
		return errors.New("error")
	}
	if err := sqldb.CreateTable(makeSQLTableSchema(tbName, rows[0], rows[1])); err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte("error, failed to create table"))
		return errors.New("error")
	}
	if err := sqldb.InsertData(makeSQLInsert(tbName, rows[0]), rows[1:]); err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte("error, failed to insert table"))
		return errors.New("error")
	}

	w.Write([]byte("file is inserted"))
	return nil
}

func queryData(w http.ResponseWriter, r *http.Request) error {
	buf, _ := ioutil.ReadAll(r.Body)
	log.Println(string(buf))
	results, err := sqldb.SelectData(string(buf))
	if err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte("error, failed to select data"))
		return errors.New("error")
	}
	resp, err := json.MarshalIndent(results, "", "  ")
	if err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte("error, failed to marsahl json"))
		return errors.New("error")
	}

	w.Write(resp)
	return nil
}

func makeSQLTableSchema(tbName string, names []string, values []string) string {
	stmt := fmt.Sprintf("drop table if exists %q; create table %q (", tbName, tbName)
	for i := range names {
		stmt += fmt.Sprintf("%q", names[i])
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
	stmt := fmt.Sprintf("insert into %q(", tbName)
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
