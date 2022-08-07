#!/bin/bash
# ysoftman

temp="aaa.cpp
bbb.txt
ccc.text
dd.sh
e.sql
fff.c
gg.
h
"

echo -e "$temp"
echo -e "delete extension from filename"
echo -e "$temp" | sed -e "s/\.[^.]*$//"
