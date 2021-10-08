#!/bin/bash
# bash test

# bash 는 기본적으로 스크립트 파일(.sh)을 새 bash 프로세스에서 실행한다.
# -c 옵션을 주면 뒤에 스트링을 명령으로 취급해 실행할 수 있다.
bash -c "echo ysoftman"
# -i interactive 모드로 .bashrc 를 읽어 새로운 bash 쉘을 만든다.
bash -i
