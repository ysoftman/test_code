# csv 업로드 후 sql 조회

## 데이터 다운로드

- cars.csv : <https://www.kaggle.com/huseyinrakun/carscsv/version/1>

## 빌드 및 실행

```bash
go get ./...
go build && ./main
```

## 테스트

```bash
curl -X POST -F 'filename=@./cars.csv' 'http://localhost:9000/api/upload' -v
curl -X POST http://localhost:9000/api/query -d 'select * from cars_csv'
curl -X POST http://localhost:9000/api/query -d 'select * from cars_csv where income > 11000;'
```
