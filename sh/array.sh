#/bin/bash
# () 로 배열 만들기

# 이건 배열 원소 1개가 된다.
# arr=(1,23,4,"a")
# echo $arr 

# 원소 구분은 공백으로 한다.
arr=(1 23 4 "a")
# bash 는 0, zsh 는 1이 시작 인덱스다.
echo ${arr[0]}
echo ${arr[1]}
echo ${arr[2]}
echo ${arr[3]}
echo ${arr[4]}
# 모든 원소 값 조회
echo ${arr[@]}
# 모든 원소 index 조회
echo ${!arr[@]}
# 원소 개수(사이즈)
echo ${#arr[@]}

# 원소 값 변경
arr[2]="ysoftman"
echo ${arr[@]}
# 원소 추가
arr+=("lemon")
arr+=(777)
echo ${arr[@]}

# 2번 인덱스부터 시작해서 3개원소 조회
echo ${arr[@]:2:3}

echo "loop array test1"
for i in ${arr[@]}
do
    echo $i;
done

echo "loop array test2"
for ((i=0;i<${#arr[@]};i++))
do
    echo "[${i}] ${arr[$i]}";
done
