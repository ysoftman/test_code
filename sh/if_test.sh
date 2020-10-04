#!/bin/bash

# var="a"
var="b"
echo $var
if [[ $var == 'a' ]]; then
    echo 'first'
# elif 를 써야 한다. else if 는 syntax error: unexpected end of file
elif [[ $var == 'b' ]]; then
    echo 'second'
else
    echo 'last'
fi


var="ysoftman lemon 123"
echo $var
if [[ $var == *"man"* ]]; then
    echo "contain"
fi
if [[ $var == *"lemon 1"* ]]; then
    echo "contain"
fi
