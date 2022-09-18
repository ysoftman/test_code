#!/bin/bash
# ysoftman
# '' 에 사용하는 프로그래밍은 c 언어 문법과 비슷함
set -ex
msg="lemon (days 1) 100\napple (days 2) 200"
echo -e $msg

# 결과의 모든열 출력
echo -e $msg | awk '{print $0}'

# 결과에서 1번,3번째 제거한 모든열 출력
echo -e $msg | awk '{$1=$3=""; print $0}'

# 결과에서 1,2,3번째 열 모두 붙여서 출력, 이렇게 되면 이후 필드 구분처리(OFS)이 안된다.
echo -e $msg | awk '{print $1$2$3}'
# " " 로 필드 사이에 공백을 출력할 수는 있지만 이후에 필드 구분처리(OFS)가 안된다.
echo -e $msg | awk '{print $1" "$2" "$3}'
# , 를 주면 공백으로 출력되고 이후에 필드 구분처리(OFS)도 된다.
echo -e $msg | awk '{print $1,$2,$3}'

# 결과의 모든 열 출력후 ysoftman 추가
echo -e $msg | awk '{print $0,"ysoftman"}'

# 하나의 print 가 하나의 레코드
# 아래처럼 print 를 두번쓰면 2개의 레코드(레코드 출력시 엔터구분(ORS 설정)
echo -e $msg | awk '{print $0; print "ysoftman"}'

# 입력 레코드 구분자
# RS(Record Separator, default newline)
echo -e $msg | awk '{print $1}' RS=' '
# 출력 필드 구분자
# OFS(Output Field Separator, default blank)
# 출력 레코드 구분자
# ORS(Output Record Separator, default new line)
echo -e $msg | awk '{print $1,$2,$3}' OFS='___' ORS=' '
echo ""

# 결과에서 NF(Num of Fields) 마지막 컬럼(파일이름)만 출력
echo -e $msg | awk '{print $(NF)}'
# 또는
echo -e $msg | awk '{print $(NF-0)}'

# 결과에서 마지막 -1 번째 컬럼만 출력
echo -e $msg | awk '{print $(NF-1)}'

# NR(Num of Record) 레코드(라인)번호
echo -e $msg | awk '{print NR}'
# 두번째 라인에서 첫번째 컬럼만 출력
echo -e $msg | awk 'NR==2 {print $1}'

# 전체 tolower
echo -e $msg | awk '{print tolower($0)}'
# 첫번째 필드만 tolower
echo -e $msg | awk '{print tolower($1)}'

# 전체 toupper
echo -e $msg | awk '{print toupper($0)}'

# (days xx) 부분 앞으로 옮기기
# -F 필드 구분을 '(' 으로 한다.
echo -e "$msg" | awk -F '(' '{print "("$2,$1}'
# -F 값으로 문자열도 가능
echo -e "orange_abc_lemon_abc_apple" | awk -F "_abc_" '{print $1,$2,$3}'

# 레코드 중 첫번째 필드값이 lemon 이면 aaa 로 레코드 출려, 아니면 레코드 그대로 출력
echo -e $msg | awk '{if ($1 == "lemon") print "aaa"; else print $0; }'

# 레코드 중 첫번째 필드값이 apple 이면 첫번째 필드만 very-apple로 변경해 레코드 출려, 아니면 레코드 그대로 출력 를 5번 반복
echo -e $msg | awk '{
for (i=0;i<5;i++) {
    if ($1 == "apple") {
        $1="very-apple"
        print $0
    }
    else {
        print $0;
    }
}
}'

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
