# nginx
if [ ! -e nginx-1.14.0.tar.gz ]; then
    wget https://nginx.org/download/nginx-1.14.0.tar.gz
fi
if [ ! -d nginx-1.14.0 ]; then
    tar zxvf nginx-1.14.0.tar.gz
fi


# nginx 모듈은 다음 2개의 파일로 구성된다.
# ngx_http_모듈이름_module.c -> 모듈 소스 파일과
# config -> 모듈 설정 파일
# 예제 https://github.com/perusio/nginx-hello-world-module


# 정적라이브러리 사용시 모듈 디텍토리를 알려주고 nginx 를 새로 빌드해야 한다.
# 동적라이브러리르 사용한다면 --add-dynamic-module 옵션 사용
cd nginx-1.14.0
./configure --add-module=$(cd ..; pwd)
make -j8
sudo make install


# nginx 설치 후 ysoftman 모듈 설정
# sudo vi /usr/local/nginx/conf/nginx.conf
# location /ysoftman {
#     ysoftman_test_module
# }
# nginx 시작
# sudo /usr/local/nginx/sbin/nginx
# sudo /usr/local/nginx/sbin/nginx -s stop
# 테스트
# http://localhost/ysoftman
# ysoftman 모듈에서 처리시 stderr 로 내보낸 값은
# /usr/local/nginx/logs/error.log 에서 확인할 수 있다.
