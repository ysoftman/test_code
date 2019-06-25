#!/bin/bash
touch ./-aa.txt
touch ./-bb.txt

# - (dash, hyper) 으로 시작하는 파일은
# -- (stop parsing) 옵션을 사용해서 지우거나
rm -- -aa.txt

# 상대경로를 지정해서 지워야 한다.
rm ./-bb.txt
