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
