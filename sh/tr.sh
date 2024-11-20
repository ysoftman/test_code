#!/bin/sh

# ysoftman
# tr 을 이용한 문자 변경 테스트

# 명령자체도 화면에 출력하기 위해
set -x

# 소문자를 대문자로 변경
echo "ysoftman" | tr '[a-z]' '[A-Z]'
# 또는
#[:class:]  Represents all characters belonging to the defined character class.  Class names are:
#alnum        <alphanumeric characters>
#alpha        <alphabetic characters>
#blank        <whitespace characters>
#cntrl        <control characters>
#digit        <numeric characters>
#graph        <graphic characters>
#ideogram     <ideographic characters>
#lower        <lower-case alphabetic characters>
#phonogram    <phonographic characters>
#print        <printable characters>
#punct        <punctuation characters>
#rune         <valid characters>
#space        <space characters>
#special      <special characters>
#upper        <upper-case characters>
#xdigit       <hexadecimal characters>
echo "ysoftman" | tr '[:lower:]' '[:upper:]'

# 개행을 공백으로 변경
cal | tr "\n" " "

echo ""

# 숫자 제거하여 출력
cal | tr -d "[0-9]"

# m -> x, a -> y, n -> z 문자로 변경
echo "ysoftman123" | tr "man" "xyz"

# -s (Squeeze)옵션으로 중복 문자를 하나로 줄인다.
echo "ysoftmannnnnnn" | tr -s 'n'

# -c(complement)
# -d(delete)
echo "v1.2.3-rc" | tr -cd '[:digit:].'
