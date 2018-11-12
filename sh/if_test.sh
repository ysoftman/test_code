#!/bin/bash

# var="a"
var="b"
# var="c"
if [[ $var == 'a' ]]; then
    echo 'first'
# elif 를 써야 한다. else if 는 syntax error: unexpected end of file
elif [[ $var == 'b' ]]; then
    echo 'second'
else
    echo 'last'
fi
