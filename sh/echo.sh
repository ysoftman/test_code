#!/bin/bash

set -x

# bash 에서는 -E 가 디폴트
# zsh 에셔는 -e 가 디폴트
echo "\"apple\n   lemon\""

# bash 에서는 declare -x z="\"apple\\n   lemon\""
# zsh 에서는 z='"apple\n   lemon"'
# bash 에서 연속적인 공백문자를 출력하려면 변수를 "" 로 감싸야 한다
export z="\"apple\n   lemon\"";  export | grep z=; echo -e "$z"

# disable interpretation escape
echo -E "\"apple\n   lemon\""

# interpretation escape
# https://www.gnu.org/software/coreutils/manual/html_node/echo-invocation.html
# \a alert (bell)
# \b backspace
# \c produce no further output
# \e escape
# \f form feed
# \n newline
# \r carriage return
# \t horizontal tab
# \v vertical tab
# \\ backslash
echo -e "\"apple\n   lemon\""

# without trailing newline
echo -n "\"apple\n   lemon\""

