#!/bin/bash
# decode urlencoding

# URL 인코딩된 '아이유' 디코딩하기
urlenc='%EC%95%84%EC%9D%B4%EC%9C%A0'
echo "urlenc=${urlenc}"

# https://ss64.com/bash/printf.html
# %b escape(\) 문자들 처리
echo "urldec=$(printf '%b' "${urlenc//%/\\x}")"
