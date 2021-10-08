#/bin/sh
# ysoftman

# set(builtin command) 현재 쉘에만 국한된 환경변수 조회
set

echo '-----'

# ysoftmanvar1=1234 로 저장된 상태
export ysoftmanvar1="1234"
echo $ysoftmanvar1


# env 만 사용하면 zzz 값으로 되지 않는다.
env ysoftmanvar1="zzz" echo $ysoftmanvar1
# ysoftmanvar1=zzz 로 명령 수행하기
# -c 옵션은 뒤에 스트링을 쉘 명령으로 수행한다.
ysoftmanvar1="zzz" bash -c 'echo $ysoftmanvar1'


# unexport 
unset ysoftmanvar1
unset ysoftmanvar2

# export 는 현재 쉘과 현재 쉘에서 파생된 쉘에 환경변수를 적용한다.
# sh ysoftman.sh 로 실행하면 ysoftman.sh 쉘과 그 자식쉘에만 export 가 반영된다.
# . ysoftman.sh 또는 source ysoftman.sh 로 실행해야 현재 쉘에 export 내용이 반영된다.
export ysoftmanvar1='ysoftmanvar1'
export ysoftmanvar2='ysoftmanvar2'

echo '-----'

# export 또는 env 로 export 된 환경변수 조회
env
