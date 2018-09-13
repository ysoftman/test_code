#!/bin/bash
#ysoftman

# ls -ahl 결과에서 3번재열(사용자id)만 출력
ls -ahl | awk '{print $3}'

# ls -ahl 결과에서 NF(Num of Fields) 마지막 컬럼(파일이름)만 출력
ls -ahl | awk '{print $(NF)}'
# 또는
ls -ahl | awk '{print $(NF-0)}'

# ls -ahl 결과에서 마지막 -1 번째 컬럼(수정시간)만 출력
ls -ahl | awk '{print $(NF-1)}'
