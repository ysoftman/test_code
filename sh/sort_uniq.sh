#!/bin/bash
out="b=c=a 1\n\
c=a=b 3\n\
a=b=c 2
"

echo '[before sort]'
echo -e $out

echo '[after sort]'
echo -e $out | sort

# reverse
echo '[after sort -r]'
echo -e $out | sort -r

# key(field) 두번째 필드값으로 정렬
echo '[after sort -k 2]'
echo -e $out | sort -k 2

# field-separator 필드구분을 = 로해서 2번째 필드로 정렬
echo '[after sort -t "=" -k 2]'
echo -e $out | sort -t '=' -k 2

# uniq 는 인접한 라인과 비교해 반복되는것은 필터링 시키기 때문에 sort 이후에 사용해야 한다.
# 빈라인도 하나의 uniq 로 구분된다.
echo "lemon
apple


lemon
orange" | sort | uniq
