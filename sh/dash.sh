#!/bin/bash
set -x

# - (dash) 로 끝나면 - 이후에 옵션은 모두 무시되며
# 파일명이나 아큐먼트로 취급한다.
# echo 출력(/dev/stdout) 후 file 에서 - 는 /dev/stdin 으로 받는다.
echo ysoftman | file -

cat > dash_test.sh << EOF
#!/bin/bash
echo test
EOF

# bash 에서는 - 와 -- 는 같다.
bash - ./dash_test.sh
bash -- ./dash_test.sh

rm -f dash_test.sh
