#!/bin/bash

# shuf : random permutation
#ls -1 | shuf

shuf --head-count=10 --input-range=1-100

# randomize the order of lines in a file
shuf shuf.sh

