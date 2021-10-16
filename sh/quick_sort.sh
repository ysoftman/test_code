#!/bin/bash
# ysoftman
# quick sort test
swap() {
    temp=${arr[$1]}
    arr[$1]=${arr[$2]}
    arr[$2]=$temp
    echo "swapped $1 $2"
}

quick_sort() {
    local start=$1
    local end=$2
    local left=$start
    local right=$end
    
    if (( start >= end )); then
        return
    fi
    local pivot=${arr[$left]}
    while (( left <= right )); do
        while (( ${arr[left]} < pivot )); do
            ((left++))
        done
        while (( arr[right] > pivot )); do
            ((right--))
        done
        if (( left <= right )); then
            swap $left $right;
            ((left++))
            ((right--))
        fi
    done
    if (( left > end)); then
        ((left--))
    fi
    # echo "${arr[@]}  -  $start $left $right $pivot"
    quick_sort $start $((left-1))
    quick_sort $left $end
}


arr=(1 7 2 5 10 3 0 9 8 6) # global variable
echo ${arr[@]}
# swap 1 9
quick_sort 0 9
echo ${arr[@]}

# 0~49 랜덤 숫자 20개의 배열 만들기
arr=()
echo ${arr[@]}
for ((i=0;i<10;i++)); do
    arr+=($(($RANDOM%50)))
done
echo ${arr[@]}
quick_sort 0 9
echo ${arr[@]}