#!/bin/bash
# strings command test
# 텍스트 파일이 아닌 경우 깬진문자까지 보게 된다.
# cat /bin/ls

echo -e '\n-----\n'

# 파일에서 출력가능한 문자들만 출력해준다.
strings /bin/ls
