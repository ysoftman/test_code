#!/bin/bash
# ysoftman
# 디렉토리 내의 모든 파일들을 대상으로 문자열 찾기
# -r : 재귀수행(하위 디렉토리)
# -n : 라인번호# --include=*.cpp : cpp 확장자 파일만 대상
# ysoftman : 찾을 문자열
# . : 시작할 디렉토리
grep -rn --include=*.txt ysoftman .

