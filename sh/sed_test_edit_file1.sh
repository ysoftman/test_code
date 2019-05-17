#!/bin/bash
# ysoftman

TEMP_FILE="${0}.tmp"

# 테스트를 위한 임시 파일 생성
cat > ${TEMP_FILE} << zzz
lemon apple orange lemon
banana mango lemon
zzz
# -e 은 editing command 를 추가할때 사용한다.
sed -e 's/lemon/aaa/g' -e 's/aaa/bbb/g' ${TEMP_FILE}
# 또는 다음과 같이 라인으로 구분해서 여러개의 editing command 명시할 수 있다.
sed 's/lemon/aaa/g
s/aaa/bbb/g
s/bbb/ccc/g
s/ccc/ddd/g
s/ddd/eee/g
' ${TEMP_FILE}

# ${TEMP_FILE} 내용을 수정한다.
# -i 확장자명시하면 수정전의 원본파일.확장자 파일로 저장한다.
# -i 는 stdin 과 사용할 수 없어 파이프를 사용하지 못한다.
# /g global 을 사용해야 라인에서 모든 매치되는 경우를 변경한다.
sed -i '.bak' 's/lemon/aaa/g' ${TEMP_FILE}
# 임시 파일 삭제
rm -f ${TEMP_FILE}
rm -f ${TEMP_FILE}.bak
