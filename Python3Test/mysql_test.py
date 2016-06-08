# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 3.x
# desc : mysql db test

# mysql-python 설치 (2.x 버전)
# pip install mysql-python

# mysql-python 설치 (3.x 버전)
# pip install pymysql

# mysql-python 설치 확인 
# pip list

import pymysql
import sys

db_host = "127.0.0.1"
db_port = 13306
db_user = "root"
db_passwd = "ysoftman"
db_dbname = "test"
db_charset = "utf8"

def db_test():
	# db 연결
	conn = pymysql.connect(host=db_host, port=db_port, user=db_user, passwd=db_passwd, database=db_dbname, charset=db_charset)

	# 커서 준비
	cursor = conn.cursor()

	# 쿼리 설정
	query = "select curdate();"

	# 쿼리 실행하기
	cursor.execute(query)

	# 쿼리 결과 가져오기
	result = cursor.fetchone()

	# 결과 출력
	print("query = %s , result = %s" % (query, result))



	# 테이블 상태 파악 해보기
	query = "show table status;"
	cursor.execute(query)
	print("query = %s" % query)
	for out in cursor:
		print("result = %s" % out[0])


	# 연결 종료
	conn.close()

# mysql db test
db_test()

