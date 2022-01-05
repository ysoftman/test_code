#!/bin/bash
# linux 용
cpu_usage=$(grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage "%"}');

# https://support.site24x7.com/portal/en/kb/articles/how-is-memory-utilization-calculated-for-a-linux-server-monitor
# free -h
#               total        used        free      shared  buff/cache   available
# Mem:            31G        6.1G        399M        1.6G         24G         23G
# Swap:            9G        652K

# free memory  = available
# memory utilized = ((total-free)/total*100)
mem_usage=$(free | grep -i mem | awk '{print (($2-$7)/$2)*100}')%;

# buff/cache 합쳐진 컬럼이 아닌 경우
# free memory  = (total - used + buffer + cache)
# memory utilized = ((total-free)/total*100)
if [[ $(free | grep -i 'buff/cache') == "" ]]; then
    mem_usage=$(free | grep -i mem | awk '{print (($2-($2-$3+$6+$7))/$2)*100}')%;
fi
echo -e "${cpu_usage}\t${mem_usage}"
