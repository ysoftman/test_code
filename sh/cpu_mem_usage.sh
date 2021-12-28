#!/bin/bash
# linux 용
cpu_usage=$(grep 'cpu ' /proc/stat | awk '{usage=($2+$4)*100/($2+$4+$5)} END {print usage "%"}');
mem_usage=$(free | grep -i mem | awk '{print ($6/$2)*100}')%;
echo -e "${cpu_usage}\t${mem_usage}"
