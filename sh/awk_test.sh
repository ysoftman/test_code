#!/bin/bash
#ysoftman

msg="lemon (days 1) 100\napple (days 2) 200"

echo -e $msg

# 결과에서 3번재열만 출력
echo -e $msg | awk '{print $3}'

# 출력 구분시 공백 사용 default(new line)
# ORS(Output Record Separator)
echo -e $msg | awk '{print $3}' ORS=' '
echo ""

# 결과에서 NF(Num of Fields) 마지막 컬럼(파일이름)만 출력
echo -e $msg | awk '{print $(NF)}'
# 또는
echo -e $msg | awk '{print $(NF-0)}'

# 결과에서 마지막 -1 번째 컬럼만 출력
echo -e $msg | awk '{print $(NF-1)}'

# NR(Num of Record) 레코드(라인)번호
echo -e $msg | awk '{print NR}'

# 전체 tolower
echo -e $msg | awk '{print tolower($0)}'
# 첫번째 필드만 tolower
echo -e $msg | awk '{print tolower($1)}'

# 전체 toupper
echo -e $msg | awk '{print toupper($0)}'

# (days xx) 부분 앞으로 옮기기
# -F 필드 구분을 '(' 으로 한다.
echo -e "$msg" | awk -F '(' '{print "("$2,$1}'


# 각 라인의 스트링을 변수로 저장 -> heredoc 으로 설정 -> echo 출력
msg="lemon
apple
orange"
aa=$(echo "$msg" | tr '\n' ' ' | awk '{print $1}')
bb=$(echo "$msg" | tr '\n' ' ' | awk '{print $2}')
cc=$(echo "$msg" | tr '\n' ' ' | awk '{print $3}')
cat << EOF | xargs echo $*
first:${aa}
second:${bb}
thrid:${cc}
EOF
