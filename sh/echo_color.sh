#!/bin/bash

# ysoftman
# 터미널 컬러 텍스트 출력하기
# Black        0;30
# Red          0;31
# Green        0;32
# Brown/Orange 0;33
# Blue         0;34
# Purple       0;35
# Cyan         0;36
# Light Gray   0;37
# Dark Gray     1;30
# Light Red     1;31
# Light Green   1;32
# Yellow        1;33
# Light Blue    1;34
# Light Purple  1;35
# Light Cyan    1;36
# White         1;37

# 리셋
reset_color='\033[0m'
# 일반
black='\033[0;30m'
red='\033[0;31m'
green='\033[0;32m'
yellow='\033[0;33m'
blue='\033[0;34m'
purple='\033[0;35m'
cyan='\033[0;36m'
white='\033[0;37m'

echo -e "${black} sample_text ${reset_color}"
echo -e "${red} sample_text ${reset_color}"
echo -e "${green} sample_text ${reset_color}"
echo -e "${yellow} sample_text ${reset_color}"
echo -e "${blue} sample_text ${reset_color}"
echo -e "${purple} sample_text ${reset_color}"
echo -e "${cyan} sample_text ${reset_color}"
echo -e "${white} sample_text ${reset_color}"
