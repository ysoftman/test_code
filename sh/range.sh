#/bin/bash

# {}내용 구분해서 조합 : abz acz adz
echo a{b,c,d}z

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
