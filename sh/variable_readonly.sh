#!/bin/bash

# set -e
a=123
echo $a
a=lemon
echo $a

readonly a=apple
echo $a

# readonly 된 변수는 수정하지 못한다.
a=lemon
echo $a
