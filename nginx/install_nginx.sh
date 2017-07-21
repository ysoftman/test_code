# 다운로드
wget http://nginx.org/download/nginx-1.12.0.tar.gz
# 압축 해제
tar zxvf nginx-1.12.0.tar.gz
cd nginx-1.12.0
# nginx 에 필요한 모듈 설치
sudo yum install pcre-devel
sudo yum install openssl-devel
# configure 수행 및 빌드 및 설치
./configure --prefix=../nginx --with-http_ssl_module --with-http_v2_module --with-http_stub_status_module
make
make install
# nginx 설정
#vi nginx/conf/nginx.conf
# nginx 시작
#sudo nginx/sbin/nginx
# nginx 재시작
#sudo nginx/sbin/nginx -s reload
# nginx 정지
#sudo nginx/sbin/nginx -s stop
# nginx 설명
#sudo nginx/sbin/nginx -h
