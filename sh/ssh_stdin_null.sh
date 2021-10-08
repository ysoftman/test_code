#!/bin/bash
# ysoftman

# 테스트를 위한 임시 파일 생성
echo '1
2
3' > temp.txt

while read a
do
    echo ${a}
    # stdin(< temp.txt) 파이프라인을 사용중 ssh 로 원격 명령실행으로
    # stdin("hostname") 을 사용하면 기존 stdin(< temp.txt)이 끝나게 되어 루프가 끝나게 된다.
    # out=`ssh ysoftman@server "hostname"`
    # < /dev/null 로 stdin 을 사용하지 않도록 한다.
    out=`ssh ysoftman@server "hostname" < /dev/null`
    echo ${out}
done < temp.txt

# 테스트를 위한 임시 파일 삭제
rm temp.txt
