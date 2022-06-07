# csv 업로드 후 sql 조회

## 데이터 출처

- small data size
  - cars.csv: <https://www.kaggle.com/huseyinrakun/carscsv/version/1>
  - 2019_Census_US_Population_Data_By_State_Lat_Long.csv: <https://www.kaggle.com/peretzcohen/2019-census-us-population-data-by-state>
- large data size
  - train.csv: <https://www.kaggle.com/ebertolo/mnist-csv>

## 빌드 및 실행

```bash
go get github.com/dgraph-io/ristretto
go get github.com/stretchr/testify
go get github.com/mattn/go-sqlite3
go get github.com/xwb1989/sqlparser
go get ./...
go build && ./main
```

## 테스트

- 테스트 코드로 테스트

```bash
go test *.go -v
```

- curl 수동 테스트

```bash
curl -X GET "http://localhost:9000/api/getstatus" -v
curl -X POST -F "filename=@./cars.csv" "http://localhost:9000/api/upload" -v
curl -X POST -F "filename=@./2019_Census_US_Population_Data_By_State_Lat_Long.csv" "http://localhost:9000/api/upload" -v
curl -X POST -F "filename=@./train.csv" "http://localhost:9000/api/upload" -v
curl -X POST http://localhost:9000/api/query -d "select * from ds_cars"
curl -X POST http://localhost:9000/api/query -d "select * from ds_cars where income > '11000'"
curl -X POST http://localhost:9000/api/query -d "select * from ds_cars order by age desc" | jq '."0"'
curl -X POST http://localhost:9000/api/query -d "select * from ds_2019_Census_US_Population_Data_By_State_Lat_Long"
curl -X POST http://localhost:9000/api/query -d "select * from ds_2019_Census_US_Population_Data_By_State_Lat_Long where popestimate2019 > '10000000'"
curl -X POST http://localhost:9000/api/query -d "select * from ds_cars as a, ds_2019_Census_US_Population_Data_By_State_Lat_Long as b where a.income > '11000' and b.popestimate2019 > '10000000'"

rm -r z.txt; curl -X POST http://localhost:9000/api/query -d "select * from ds_train where pixel0 = '0'" > z.txt

# timeout
rm -f z.txt; curl -X POST http://localhost:9000/api/query -d "select * from ds_cars as a, ds_train as b where a.income > '11000' and b.pixel0 = '0'" > z.txt
```

## [API 명세](./api.md)

## db 확인시

```bash
sqlite sqlite.db

# 테이블 확인
.tables

# 데이터 확인
select * from ds_cars;

# 종료
.quit
```
