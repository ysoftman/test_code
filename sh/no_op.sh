#!/bin/bash

# 에러가 발생해 0이 아닌 상태값이 리턴
# command_does_not_exist 2>/dev/null

# 에러가 발생해도 echo 사용으로 0 을 리턴
# command_does_not_exist 2>/dev/null || echo "command not found"

# : (no-op)로 별도 처리 없이 exit 0 리턴
command_does_not_exist 2>/dev/null || :
