#!/bin/bash
# ysoftman
# brace expansion

# https://www.gnu.org/software/bash/manual/html_node/Shell-Parameter-Expansion.html
# aaa 가 값이 있으면 확장된 bbb 도 aaa 값이 된다.
# aaa 가 빈값(unset/null) 이면 aaa 자체가 변경되지는 않고, 확장된 bbb 는 디폴트값으로 변경된다.
aaa=""
bbb=${aaa:-default_lemon}
echo 'bbb=${aaa:-default_lemon}'
echo '$aaa' $aaa
echo '$bbb' $bbb

# aaa 가 값이 있으면 확장된 bbb 도 aaa 값이 된다.
# aaa 가 null 이면 확장된 bbb 는 디폴트값으로 변경된다.
aaa=""
bbb=${aaa-default_lemon}
echo 'bbb=${aaa-default_lemon}'
echo '$aaa' $aaa
echo '$bbb' $bbb
unset aaa
echo "unset aaa"
bbb=${aaa-default_lemon}
echo 'bbb=${aaa-default_lemon}'
echo '$aaa' $aaa
echo '$bbb' $bbb

# aaa 빈값(unset/null) 이면 디폴트 값 사용, aaa 자체도 디폴트값으로 변경되고 확장된 bbb 도 디폴트값으로 변경된다.
aaa=""
bbb=${aaa:=default_apple}
echo 'bbb=${aaa:=default_apple}'
echo '$aaa' $aaa
echo '$bbb' $bbb

# aaa 빈값(unset/null) 이면 stderr 에 에러가 발생한다.
# unset aaa
# aaa=""
bbb=${aaa:?default_orange}
echo 'bbb=${aaa:?default_orange}'
echo '$aaa' $aaa
echo '$bbb' $bbb

# aaa 빈값(unset/null) 이면 aaa 자체가 변경되지 않고 확장된 bbb 는 빈값이 된다.
aaa=""
bbb=${aaa:+default_banana}
echo 'bbb=${aaa:+default_banana}'
echo '$aaa' $aaa
echo '$bbb' $bbb



aaa="01234567890abcdefg"
# 0번째 부터 3개
echo '${aaa:0:3}' ${aaa:0:3}
# 3번째 부터 끝까지
echo '${aaa:3}' ${aaa:3}

# 9번째 부터 끝에 -1 위치까지
echo '${aaa:9:-1}' ${aaa:9:-1}
# 9번째 부터 끝에 -1 위치까지
echo '${aaa:9:-2}' ${aaa:9:-2}

# 끝에 -3 위치 부터 끝까지 (:- 가되지 않도록 : - 로 공백이 있어야 한다.)
echo '${aaa: -3}' ${aaa: -3}
# 끝에 -3 위치 부터 2개
echo '${aaa: -3:2}' ${aaa: -3:2}


#####


# {} 내에 , 로 구분하면 구분된 개수 만큰 확장(치환)된다.
# mkdir {a,b}zzz ==> azzz 와 bzzz 생성 으로 많이 사용한다.
echo LEMON_{aaa,bbb,ccc}_ORANGE

# ,외 공백이 들어가면 확장되지 않는다.
echo LEMON_{aaa, bbb, ccc}_ORANGE

# 요소에 공백을 포함하는 경우 quote, double-quote 로 감싸준다.
echo LEMON_{aaa,"b b b",ccc}_ORANGE
echo LEMON_{aaa,'b b b',ccc}_ORANGE


# 2개의 내용{} 조합 3x3=9 가지 생성: ab1z ab2z ab3z ac1z ac2z ac3z ad1z ad2z ad3z
echo a{b,c,d}{1,2,3}z
# 배열로 담기
arr=(a{b,c,d}{1,2,3}z)
echo ${arr[0]}
echo ${arr[1]}
# all element
echo ${arr[@]}

# 0~10 까지 : 0 1 2 3 4 5 6 7 8 9 10
echo {0..10}
# 10~0 까지: 10 9 8 7 6 5 4 3 2 1 0
echo {10..0}
# a~z 까지: a b c d e f g h i j k l m n o p q r s t u v w x y z
echo {a..z}

# 0~10까지 2씩 건너뛰기: 0 2 4 6 8 10
echo {0..10..2}
# a~z 까지 3씩 건너뛰기: a d g j m p s v y
echo {a..z..3}
