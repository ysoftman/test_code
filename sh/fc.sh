#!/bin/bash
# https://www.unix.com/man-page/linux/1/fc/
# fc - process the command history list
# -e editor
# -l (The letter ell.) List the commands rather than invoking an editor on them. The commands shall be written in the sequence  indicated by the first and last operands, as affected by -r, with each command preceded by the command number.
# -n Suppress command numbers when listing with -l.
# -r Reverse the order of the commands listed (with -l) or edited (with neither -l nor -s).
# -s Re-execute the command without invoking an editor.
# 명령 history 중 1~10까지 역순으로 리스트 출력
fc -rl 1 10
