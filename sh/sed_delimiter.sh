#!/bin/bash
# 구분자 / 를 쓰는 경우 https:// 와 겹치기 때문에 escape 가 필요하다.
echo "http://ysoftman.co.kr" | sed "s/http:\/\/ysoftman/https:\/\/lemon/g"

# delimiter 를 / 외의 것을 사용해서 escape 를 하지 않아도 된다.
echo "http://ysoftman.co.kr" | sed "s+http://ysoftman+https://lemon+g"
echo "http://ysoftman.co.kr" | sed "s-http://ysoftman-https://lemon-g"
echo "http://ysoftman.co.kr" | sed "s#http://ysoftman#https://lemon#g"
echo "http://ysoftman.co.kr" | sed "s(http://ysoftman(https://lemon(g"
echo "http://ysoftman.co.kr" | sed "s)http://ysoftman)https://lemon)g"
echo "http://ysoftman.co.kr" | sed "s_http://ysoftman_https://lemon_g"
echo "http://ysoftman.co.kr" | sed "s%http://ysoftman%https://lemon%g"
echo "http://ysoftman.co.kr" | sed "s*http://ysoftman*https://lemon*g"
echo "http://ysoftman.co.kr" | sed "s@http://ysoftman@https://lemon@g"
