#!/bin/bash
# ysoftman
# predefined variable
# http://www.tldp.org/LDP/abs/html/internalvariables.html

# 머신 타입
echo "\${MACHTYPE}:" ${MACHTYPE}
# 기본 에디터 프로그램
echo "\${EDITOR}:" ${EDITOR}
# 설정된 경로
echo "\${PATH}:" ${PATH}
# 디폴트로 지정된 쉘
echo "\${SHELL}:" ${SHELL}
# 현재 사용중인 쉘(커맨드라인에서는 echo $0 만 실행해도 된다.)
echo "current shell:" $(ps $(echo $$) | awk '{print $5}' | sed -n "2p")
# 쉘 시작 후 경과 시간(초)
# sleep 1
echo "\${SECONDS}:" ${SECONDS}
# 디폴트 프롬프트
echo "\${PS1}:" ${PS1}
# continue 프롬프트, 커맨드라인에더 다음줄에 계속 입력할때 표시되는 프롬프트
echo "\${PS2}:" ${PS2}
# select 명령 수행시 선택입력을 위해 표시되는 프롬프트
echo "\${PS3}:" ${PS3}
# 이전 디랙토리 전체 경로 출력
echo "\${OLDPWD}:" ${OLDPWD}
# 현재 디랙토리 전체 경로 출력(Print Working Directory)
echo "\${PWD}:" ${PWD}
# ${var#Pattern} 변수 앞에서부터 패턴과 매치되는 가장 짧은 부분 제거
# ${var##Pattern} 변수 앞에서부터 패턴과 매치되는 가장 긴 부분 제거
# ${var%Pattern} 변수 뒤에서부터 패턴과 매치되는 가장 짧은 부분 제거
# ${var%%Pattern} 변수 뒤에서부터 패턴과 매치되는 가장 긴 부분 제거
echo "\${PWD#*/}" ${PWD#*/}
echo "\${PWD##*/}:" ${PWD##*/}  # 현재 디렉토리만 출력
echo "\${PWD%/*}" ${PWD%/*} # 현재 디렉토리 상위 디렉토리까지의 full path
echo "\${PWD%%/*}" ${PWD%%/*}
# bash 버전
echo "\${BASH_VERSION}:" ${BASH_VERSION}
# 하드웨어 타입
echo "\${HOSTTYPE}:" ${HOSTTYPE}
