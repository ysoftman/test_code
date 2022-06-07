# api 명세

## csv 파일 업로드

- Desc: .csv 파일을 서버로 업로드하여, sql db 로 저장한다. (같은 csv 파일의 db,cache 가 있다면 삭제된다.)
- Method: POST
- Path: /api/upload
- Timeout: 5Min
- 사용 예시

  ```bash
  curl -X POST -F "filename=@./cars.csv" "http://localhost:9000/api/upload" -v
  curl -X POST -F "filename=@./2019_Census_US_Population_Data_By_State_Lat_Long.csv" "http://localhost:9000/api/upload" -v
  curl -X POST -F "filename=@./train.csv" "http://localhost:9000/api/upload" -v
  ```

## csv 조회

- Desc: 업로드된 csv 의 데이터를 조회한다.
- Method: POST
- Path: /api/query
- Timeout: 5Min
- 사용 예시

  ```bash
  curl -X POST -F "filename=@./cars.csv" "http://localhost:9000/api/upload" -v
  curl -X POST -F "filename=@./2019_Census_US_Population_Data_By_State_Lat_Long.csv" "http://localhost:9000/api/upload" -v
  curl -X POST -F "filename=@./train.csv" "http://localhost:9000/api/upload" -v
  curl -X POST http://localhost:9000/api/query -d "select * from ds_cars"
  curl -X POST http://localhost:9000/api/query -d "select * from ds_cars where income > '11000'"
  curl -X POST http://localhost:9000/api/query -d "select * from ds_cars order by age desc" | jq '."0"'
  curl -X POST http://localhost:9000/api/query -d "select * from ds_2019_Census_US_Population_Data_By_State_Lat_Long"
  curl -X POST http://localhost:9000/api/query -d "select * from ds_2019_Census_US_Population_Data_By_State_Lat_Long where popestimate2019 > '10000000'"
  curl -X POST http://localhost:9000/api/query -d "select * from ds_cars as a, ds_2019_Census_US_Population_Data_By_State_Lat_Long as b where a.income > '11000' and b.popestimate2019 > '10000000'"
  
  # 조회 결과 파일로 저장하는 경우
  rm -r z.txt; curl -X POST http://localhost:9000/api/query -d "select * from ds_train where pixel0 = '0'" > z.txt

  # timeout 이 발생하는 경우
  rm -f z.txt; curl -X POST http://localhost:9000/api/query -d "select * from ds_cars as a, ds_train as b where a.income > '11000' and b.pixel0 = '0'" > z.txt
  ```

## 캐싱 상태 조회

- csv 조회로 캐싱된 쿼리들이 어떤것이 있는지 조회한다. 캐싱은 csv 파일명으로 구분된다.
- Method: GET
- Path: /api/getstatus
- Timeout: 5Min
- 사용 예시

  ```bash
  curl -X GET "http://localhost:9000/api/getstatus" -v
  ```
