#/bin/sh
# unexport 
unset ysoftmanvar1
unset ysoftmanvar2

# export
# sh export_test.sh 로 실행하면 export_test.sh 쉘과 그 자식쉘에만 export 가 반영된다.
# source export_test.sh 로 실행해야 현재 쉘에 export 내용이 반영된다.
export ysoftmanvar1='ysoftmanvar1'
export ysoftmanvar2='ysoftmanvar2'

