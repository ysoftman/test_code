#!/bin/bash
#ysoftman

# ls -ahl 결과에서 3번재열(사용자id)만 출력
ls -ahl | awk '{print $3}'

# 출력 구분시 공백 사용 default(new line)
# ORS(Ouput Record Separator)
ls -ahl | awk '{print $3}' ORS=' '

# ls -ahl 결과에서 NF(Num of Fields) 마지막 컬럼(파일이름)만 출력
ls -ahl | awk '{print $(NF)}'
# 또는
ls -ahl | awk '{print $(NF-0)}'

# ls -ahl 결과에서 마지막 -1 번째 컬럼(수정시간)만 출력
ls -ahl | awk '{print $(NF-1)}'

# 라인별(레코드별) 순서 번호
ls -ahl | awk '{print NR}'

# (days xx) 부분 앞으로 옮기기
# -F 필드 구분을 '(' 으로 한다.
msg="lemon (days 1)
apple (days 2)"
echo "$msg" | awk -F '(' '{print "("$2,$1}'
