#!/bin/bash
# ysoftman
# 공백 구분자(-d ' ')로 구분했을대 첫번째필드(-f1)와 세번째필드(-f3) 값 파악 
cat ./extract_string.txt  | cut -d ' ' -f1 -f3
