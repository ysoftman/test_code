#!/bin/bash
# ysoftman
# field1 의 날짜값만 파악하기
# field1: -> field1:\n (mac 에서도 줄바꿈 동작하기 위해  위히 $추가) 로 줄변경
# 2017로 시작하는 라인만 선택 (grep -n 으로 alias 된 경우 -n(line-number) 를 제거해야 한다.)
# 1~23 번째바이트만 출력
sed 's/field1\":\"/field1\":\"\'$'\n/g' ./extract_json.txt | grep "^2017*" | cut -b 1-23
