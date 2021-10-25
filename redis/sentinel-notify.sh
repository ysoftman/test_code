#!/bin/bash
echo "sentinel notify..."

# sentinel 이벤트 발생시 인벤트와 내용을 인자로 전달한다.
event_type=${1}
event_desc=${2}

# 주요 event_type 종류
# +monitor : sentinel monitor 명령 실행으로 monitor 시작
# -monitor : sentinel remove 명령으로 monitor 해제
# +set : sentinel set 명령 실행으로 센티널 설정이 변경될 때
# +reset-master : settinel reset 명령 실행으로 마스터 정보를 리셋
# +sdown : sdown 인지, 대상 서버: 마스터, 슬레이브, 센티널
# -sdown : sdown 해제, 대상 서버: 마스터, 슬레이브, 센티널
# +odown : odown 확정, 대상 서버: 마스터
# -odown : odown 해제, 대상 서버: 마스터
# +promoted-slave : 선정된 슬레이브가 새 마스터로 승격
# +switch-master : 세 마스터로 변경이 완료

if [[ $event_type == "+sdown" ]]; then
    custom_desc="master 노드들 모니터링 시작합니다."
elif [[ $event_type == "-sdown" ]]; then
    custom_desc="master 노드들 모니터링 해제되었습니다."
elif [[ $event_type == "+odown" ]]; then
    custom_desc="master 노드가 다운됐습니다."
elif [[ $event_type == "-odown" ]]; then
    custom_desc="master 노드 다운 해제되었습니다."
elif [[ $event_type == "+switch-master" ]]; then
    custom_desc="새 마스터로 master 변경됐습니다."
else
    echo "event_type:${event_type}"
    exit 0
fi

echo $message