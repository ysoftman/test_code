package main

import (
	"context"
	"encoding/csv"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"log"
	"net/http"
	"strconv"
	"strings"
	"time"

	"github.com/xwb1989/sqlparser"

	_ "github.com/mattn/go-sqlite3"
)

// const DefaultTimeOut = time.Millisecond * 100
const DefaultTimeOut = time.Minute * 5

type wrHandlerFunc func(w http.ResponseWriter, r *http.Request) error

type methodHandler struct {
	Get    wrHandlerFunc
	Post   wrHandlerFunc
	Put    wrHandlerFunc
	Delete wrHandlerFunc
}

func UploadHandler() http.HandlerFunc {
	return HandlerContext(
		methodHandler{
			Post: uploadData,
		})
}

func QueryDataHandler() http.HandlerFunc {
	return HandlerContext(
		methodHandler{
			Post: queryData,
		})
}

func GetStatusHandler() http.HandlerFunc {
	return HandlerContext(methodHandler{
		Get: getStatusHandler,
	})
}

func HandlerContext(mh methodHandler) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		ctx, cancel := context.WithTimeout(r.Context(), DefaultTimeOut)
		defer cancel()
		r.WithContext(ctx)
		ch := make(chan error)

		go func() {
			switch r.Method {
			case http.MethodGet:
				ch <- mh.Get(w, r)
			case http.MethodPost:
				ch <- mh.Post(w, r)
			case http.MethodPut:
				ch <- mh.Put(w, r)
			case http.MethodDelete:
				ch <- mh.Delete(w, r)
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

func getStatusHandler(w http.ResponseWriter, r *http.Request) error {
	status := struct {
		CacheKeys map[string][]string `json:"cacheKeys"`
	}{
		CacheKeys: cache.cacheKeys,
	}
	log.Printf("status:%#v", status)
	resp, err := json.MarshalIndent(status, "", "  ")
	if err != nil {
		err := errors.New("failed to get status")
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte(err.Error()))
		return err
	}
	w.Write([]byte(resp))

	return nil
}

func uploadData(w http.ResponseWriter, r *http.Request) error {
	file, fileHeader, err := r.FormFile("filename")
	if err != nil {
		log.Println("err:", err)
		return errors.New("error")
	}
	defer file.Close()
	log.Println("uploaded filename:" + fileHeader.Filename)
	tbName := strings.TrimSuffix(fileHeader.Filename, ".csv")
	tbName = "ds_" + strings.ReplaceAll(tbName, ".", "_")
	log.Println("tbName:", tbName)

	// buf, _ := io.ReadAll(file)
	// backup := io.NopCloser(bytes.NewBuffer(buf))
	// log.Println("-----", string(buf))
	rows, _ := csv.NewReader(file).ReadAll()
	// log.Println("-----", rows)
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

	evictCache(tbName)

	w.Write([]byte("file is inserted"))
	return nil
}

func queryData(w http.ResponseWriter, r *http.Request) error {
	buf, _ := io.ReadAll(r.Body)
	query := string(buf)
	log.Println(query)

	if cacheVal, err := cache.Get(query); err == nil {
		// log.Println("using cache data", cacheVal.(string))
		if resp, ok := cacheVal.(string); ok {
			log.Println("using cache data")
			w.Write([]byte(resp))
			return nil
		}
		log.Println("failed to get cache data")
	}
	results, err := sqldb.SelectData(query)
	if err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte("error, failed to select data"))
		return errors.New("error")
	}

	resp, err := json.Marshal(results)
	if err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		w.Write([]byte("error, failed to marshal json"))
		return errors.New("error")
	}

	parsedStmt, err := sqlparser.Parse(query)
	if err != nil {
		log.Println(err)
		w.WriteHeader(http.StatusBadRequest)
		w.Write([]byte(err.Error()))
		return err
	}

	tableNames := []string{}
	_ = sqlparser.Walk(func(node sqlparser.SQLNode) (kontinue bool, err error) {
		switch node := node.(type) {
		case sqlparser.TableName:
			if len(node.Name.CompliantName()) > 0 {
				tableNames = append(tableNames, node.Name.CompliantName())
			}
		}
		return true, nil
	}, parsedStmt)
	cache.Set(query, string(resp), strings.Join(tableNames, ","))

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

func evictCache(tbName string) {
	for tableName := range cache.cacheKeys {
		if strings.Contains(tableName, tbName) {
			log.Println("[evictCache] contains:", tableName)
			if cache.cacheKeys[tableName] != nil {
				for _, v := range cache.cacheKeys[tableName] {
					cache.Del(v)
				}
				cache.cacheKeys[tableName] = cache.cacheKeys[tableName][:0]
			}
		}
	}
}
