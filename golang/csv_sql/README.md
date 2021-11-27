# csv 업로드 후 sql 조회

## 데이터 다운로드

- cars.csv : <https://www.kaggle.com/huseyinrakun/carscsv/version/1>
- train.csv : <https://www.kaggle.com/ebertolo/mnist-csv>

## 빌드 및 실행

```bash
go get ./...
go build && ./main
```

## 테스트

```bash
curl -X GET 'http://localhost:9000/api/getstatus' -v
curl -X POST -F 'filename=@./cars.csv' 'http://localhost:9000/api/upload' -v
curl -X POST -F 'filename=@./train.csv' 'http://localhost:9000/api/upload' -v
curl -X POST http://localhost:9000/api/query -d 'select * from cars_csv'
curl -X POST http://localhost:9000/api/query -d 'select * from cars_csv where income > 11000;'
rm z.txt; curl -X POST http://localhost:9000/api/query -d 'select * from train_csv' > z.txt
```

## db 확인시

```bash
sqlite sqlite.db

# 테이블 확인
.tables

# 데이터 확인
select * from cars_csv;

# 종료
.quit
```
