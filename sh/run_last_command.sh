#!/bin/bash
# 이전 명령어 실행 테스트
# 다음 예시를 터미널상에서 직접 타이핑해서 테스트한다.
# 참고로 zsh 에서는 이전 명령이 바로 실행되지 않고 이전 명령을 프롬프트에 표시한다.

# 명령1
clear
# 명령2
echo "ysoftman"
# 명령3
uname -a
# 명령4
pwd
# 명령5 명령기록 보기
history

# 바로 이전 명령 실행
!!
# 또는
!-1

# 2번째 전 명령 실행
!-2

# 가장 최근의 e 로 시작하는 명령 실행
!e

# sudo 등 붙여서 이전 명령 실행
sudo !!

# 바로 이전 명령의 0번째 항목(명령)
!!:0

# 바로 이전 명령의 1번째 항목(아규먼트)
!!:1

# 이외 ctrl+r 로 이전 명령을 fuzzy search 할 수 있다.
