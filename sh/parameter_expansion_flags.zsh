#!/bin/bash
#!/bin/zsh

# 다음과 같은 스크립트가 있을때
a="a
b
c
d"

cnt=0
for i in $a; do
    ((cnt++))
    echo "[cnt:$cnt] $i"
done

# bash 로 실행하면 원하는 결과를 얻을 수 있다.
# [cnt:1] a
# [cnt:2] b
# [cnt:3] c
# [cnt:4] d

# zsh newline 으로 구분하지 않아 loop 가 한번만 실행되고 다음과 같이 하나로 출력 된다.
# [cnt:1] a
# b
# c
# d

# bash 로 실행시 에러 발생
# 다음과 같이 Parameter Expansion Flags 중 f 를 명시해야 된다.
# https://zsh.sourceforge.io/Doc/Release/Expansion.html#Parameter-Expansion-Flags
# f : Split the result of the expansion at newlines. This is a shorthand for ‘ps:\n:’.
cnt=0
for i in ${(f)a}; do
    ((cnt++))
    echo "[cnt:$cnt] $i"
done

echo "-----"

# 다음과 같이 for 에서 사용하면 bash, zsh 모두 사용할 수 있다.
for i in $(echo $a); do
    ((cnt++))
    echo "[cnt:$cnt] $i"
done
