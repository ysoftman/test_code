#!/bin/bash
# ysoftman

rm a.out

# && 를 사용하는 이유는 실패한 명령 이후로 진행하지 않기 위해서다.
g++ const_test.cpp && ./a.out

