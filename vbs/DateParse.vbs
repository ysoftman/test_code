'=================================================================
'ysoftman
'date, dateadd, now 등의 함수는 계정의 날짜 포맷에 따라 월/일/년 또는 년-월-일 등 다르게 출력되기 때문에
'일관성 있는 날짜 스트링을 얻기 위해선 year,month,day 함수로 구분지어 사용한다.
'=================================================================
result = date
wscript.echo result
result = year(date) & "-" & month(date) & "-" & day(date)
wscript.echo result

