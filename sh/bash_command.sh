#!/bin/bash
# bash test

# -- 이후로는 bash arguments 로 취급하지 않는다.(bash option 끝을 나타낸다.)
bash -c -- "echo ysoftman"

# bash 는 기본적으로 스크립트 파일(.sh)을 새 bash 프로세스에서 실행한다.
# -c 옵션을 주면 뒤에 스트링을 명령으로 취급해 실행할 수 있다.
# alias 설정된게 없다.
bash -c "echo ysoftman; alias"
# -i interactive 모드로 .bashrc 를 읽어 새로운 bash 쉘을 만든다.
# interactive 쉘이 새로 시작됐기 때문에 이전 쉘로 돌아가려면 exit 해야 한다.
# bash -i
# interactive(.bashrc 실행하고)로 ysoftman 을 출력하고 쉘은 종료된다.
# .bashrc 실행해서 alias 설정된게 있다.
bash -ic "echo ysoftman; alias"

# -s 옵션을 주면 stdin 으로 입력 받을 수 있다.
# bash < bash_args.sh lemon 123
bash -s lemon 123 <bash_args.sh
