#!/bin/bash
# () 로 배열 만들기

# 이건 배열 원소 1개가 된다.
# arr=(1,23,4,"a")
# echo $arr

# 원소 구분은 공백으로 한다.
arr=(1 23 4 "a")
echo "${arr}" # arr 로 접근하면 첫번째 원소값만 보인다.
echo "----- arr[0] ~ arr[4]"
echo ${arr[0]}
echo ${arr[1]}
echo ${arr[2]}
echo ${arr[3]}
echo ${arr[4]}
echo "----- all elements in array"
echo "${arr[@]}"
echo "----- all elements in array with newline"
printf "%s\n" "${arr[@]}"
echo "----- all elements in array index"
echo "${!arr[@]}"
echo "----- num of elements in array"
echo "${#arr[@]}"
echo "----- first element size(length)"
echo "${#arr[1]}"

echo "----- update array[2] to ysoftman"
arr[2]="ysoftman"
echo "${arr[@]}"
echo "----- add element to array"
arr+=("lemon and apple")
arr+=(777)
echo "${arr[@]}"
echo "----- remove last element in array"
unset "arr[${#arr[@]}-1]"
# or
unset "arr[-1]"
echo "${arr[@]}"
echo "----- 2번 인덱스부터 시작해서 3개원소 조회"
echo "${arr[@]:2:3}"
echo "----- 0번 인덱스부터 시작해서 3개원소 조회"
echo "${arr[@]::3}"
echo "----- 0번 인덱스부터 시작해서 999개원소 조회(원소가 있는것까지만 출력된다.)"
echo "${arr[@]::9999}"

echo "----- loop array test1"
for i in "${arr[@]}"; do
    echo $i
done

echo "----- loop array test2"
for ((i = 0; i < ${#arr[@]}; i++)); do
    echo "[${i}] ${arr[$i]}"
done
