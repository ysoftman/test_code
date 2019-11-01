// ysoftman
// couchDB test
/*
# couchdb
# 설치(mac)
wget http://apache.tt.co.kr/couchdb/source/2.1.1/apache-couchdb-2.1.1.tar.gz
tar zxvf apache-couchdb-2.1.1.tar.gz
cd apache-couchdb-2.1.1
./configure
make && make release
# 실행
./rel/couchdb/bin/couchdb
# 설정 파일
vi rel/couchdb/etc/default.ini
# 동작 확인
http://127.0.0.1:5984/
# Fauxton(new Web UI for CouchDB)
# 계정, database, document 등 생성
http://127.0.0.1:5984/_utils/


# couchbase (couchbDB 를 기반으로 기능이 더 확장됨, https://www.couchbase.com/couchbase-vs-couchdb)
# docker couchase community 최신 버전 사용
docker pull couchbase:community
docker run -d --name db -p 8091-8094:8091-8094 -p 11210:11210 couchbase:community
# 접속, 계정, database, bucket, document 등 생성
http://localhost:8091

# 일반서버(centos) 환경에서 설치 할때
wget https://packages.couchbase.com/releases/6.0.0/couchbase-server-community-6.0.0-centos7.x86_64.rpm
sudo rpm -ivh couchbase-server-community-6.0.0-centos7.x86_64.rpm
sudo systemctl start couchbase-server
# dash 보드 접속 후 add-server 로 다른 couchbase ip  추가
http://ysoftman-server:8091/

# golang SDK
https://developer.couchbase.com/documentation/server/5.1/sdk/go/start-using-sdk.html
rm -rf $GOPATH/src/gopkg.in/couchbase*
go get github.com/couchbase/gocb
*/

package main

import (
	"fmt"

	"github.com/couchbase/gocb"
)

type User struct {
	Id        string   `json:"uid"`
	Email     string   `json:"email"`
	Interests []string `json:"interests"`
}

func main() {
	cluster, _ := gocb.Connect("couchbase://localhost")
	cluster.Authenticate(gocb.PasswordAuthenticator{
		Username: "ysoftman",
		Password: "qwer1234",
	})
	bucket, _ := cluster.OpenBucket("bucket1", "")

	bucket.Manager("", "").CreatePrimaryIndex("", true, false)

	bucket.Upsert("u:ysoftman",
		User{
			Id:        "ysoftman",
			Email:     "ysoftman@couchbase.com",
			Interests: []string{"Holy Grail", "African Swallows"},
		}, 0)

	// Get the value back
	var inUser User
	bucket.Get("u:ysoftman", &inUser)
	fmt.Printf("User: %v\n", inUser)

	// Use query
	query := gocb.NewN1qlQuery("SELECT * FROM bucket1 WHERE $1 IN interests")
	rows, _ := bucket.ExecuteN1qlQuery(query, []interface{}{"African Swallows"})
	var row interface{}
	for rows.Next(&row) {
		fmt.Printf("Row: %v", row)
	}
}
