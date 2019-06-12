#!/bin/bash
. echo_color.sh

colorpath() {
    n=$(( ${1}%6 ))
    case $n in
        0) echo ${red};;
        1) echo ${green};;
        2) echo ${yellow};;
        3) echo ${blue};;
        4) echo ${purple};;
        5) echo ${cyan};;
    esac
    return 0
}

cnt=0
output="${red}/"
for i in $(pwd | sed 's/\// /g'); do
    color=$(colorpath ${cnt})
    output="${output}${color}$i/"
    ((cnt++))
done
output="${output}${reset_color}"
echo -e ${output}
