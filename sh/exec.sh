#!/bin/bash
# exec command test

# https://ss64.com/bash/exec.html
# exec 현재 쉘 프로세스를 대체(새로운 프레스를 만들지 않고)해서 뒤 명령을 실행한다.
# exec 는 현재 프로세스(보통 쉘)를 뒤에 오는 명령(echo "ysoftman") 프로세스로 대체한다.
# 결국 echo 출력후 종료되어 터미널이 닫힌다.
# 하지만 bash exec_test.sh 처럼 쉘 스크립트 파일내에서 실행하면
# exec_test.sh 가 새로 시작된 후에 exec 가 실행되기 때문에 쉘종료는 되지 않는다.
# exec 가 에러없이 실행되면 exec 의 명령(echo "ysoftman")로 대체되기 때문에
# 그 뒤의 것들은(ls, echo "testing" ... 등) 모두 무시된다.
exec echo "ysoftman"
ls
echo "testing..."

# 참고로 쉘 명령 프롬프트에서 다음을 실행 후 에는
# 모든 stdout 이 화면에 출력되지 않고 exec_out.txt 추가된다.
# exit 로 쉘 자체를 종료후 exec_out.txt 파일 내용을 확인해 보자.
# exec > exec_out.txt
