// ysoftman
// apr(Apache Portable Runtime) library test
/*
# openssl 설치
wget https://www.openssl.org/source/openssl-1.0.2k.tar.gz
tar zxvf openssl-1.0.2k.tar.gz
cd openssl-1.0.2k
./config
make clean
make -j4
sudo make install
cd ..


# apr 설치 방법1
# apche httpd 설치하면 생성되는 apr 사용
wget http://mirror.apache-kr.org//httpd/httpd-2.2.34.tar.gz
tar zxvf httpd-2.2.34.tar.gz
cd httpd-2.2.34
./configure --prefix="${HOME}/workspace/httpd" --with-mpm-prefork
make && make install
# 빌드
g++ -O2 -g -fPIC apr_test.cpp -o aprtest -I${HOME}/workspace/httpd/include -I/usr/local/ssl/include -L${HOME}/workspace/httpd/lib -L/usr/local/ssl/lib -lapr-1 -lssl -lcrypto -ldl


# apr 설치 방법2
wget http://apache.mirror.cdnetworks.com//apr/apr-1.6.3.tar.gz
tar zxvf apr-1.6.3.tar.gz
cd apr-1.6.3
./configure --prefix="${HOME}/workspace/apr"
make && make install
# apr-util 설치
wget http://apache.mirror.cdnetworks.com//apr/apr-util-1.6.1.tar.gz
tar zxvf apr-util-1.6.1.tar.gz
cd apr-util-1.6.1
./configure --prefix="${HOME}/workspace/apr" --with-apr="${HOME}/workspace/apr/bin/apr-1-config"
# make 시 expat.h 가 없어 에러가 난다면 
# centos : yum install expat-devel
# ubuntu : apt-get install libexpat1-dev
make && make install
cd ..
# 빌드
g++ -O2 -g -fPIC apr_test.cpp -o aprtest -I${HOME}/workspace/apr/include/apr-1 -I/usr/local/ssl/include -L${HOME}/workspace/apr/lib -L/usr/local/ssl/lib -lapr-1 -lssl -lcrypto -ldl
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${HOME}/workspace/apr/lib:
*/

#include "apr.h"
#include "apr_file_io.h"
#include "apr_strings.h"
#include "apr_network_io.h"
#include "apr_pools.h"
#include "apr_poll.h"
#include "openssl/ssl.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

char *errmsg(apr_status_t rc)
{
    static char errbuff[1024];
    memset(errbuff, 0, sizeof(errbuff));
    apr_strerror(rc, errbuff, sizeof(errbuff));
    return errbuff;
}

int main(int argc, char **argv)
{
    string ip = "www.json.org";
    int port = 80;
    string uri = "/json-ko.html";
    if (argc == 4)
    {
        ip = argv[1];
        port = atoi(argv[2]);
        uri = argv[3];
    }
    else
    {
        cout << argv[0] << " \"www.json.org\" " << 80 << " \"/json-ko.html\"" << endl;
        exit(0);
    }
    stringstream portstr;
    portstr << port;

    cout << "ip: " << ip << endl;
    cout << "port: " << port << endl;
    cout << "uri: " << uri << endl;

    // unsigned int waitms = 1000 * 500;
    apr_interval_time_t waitms = 1000 * 500;
    apr_socket_t *sock = NULL;
    apr_pool_t *pool;
    apr_sockaddr_t *sa;
    apr_status_t rc;
    apr_pollset_t *pollset_conn = NULL;
    apr_file_t *out;

    apr_initialize();
    atexit(apr_terminate);

    apr_pool_create(&pool, NULL);

    rc = apr_socket_create(&sock, APR_INET, SOCK_STREAM, APR_PROTO_TCP, pool);
    if (rc != APR_SUCCESS)
    {
        cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << " " << errmsg(rc) << endl;
        return -1;
    }

    // rc = apr_socket_opt_set(sock, APR_SO_NONBLOCK, 1);
    // if (rc != APR_SUCCESS)
    // {
    //     cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << " " << errmsg(rc) << endl;
    //     apr_socket_close(sock);
    //     return -1;
    // }

    rc = apr_sockaddr_info_get(&sa, ip.c_str(), APR_INET, port, 0, pool);
    if (rc != APR_SUCCESS)
    {
        cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << " " << errmsg(rc) << endl;
        apr_socket_close(sock);
        return -1;
    }

    apr_socket_timeout_set(sock, waitms);

    // SSL 초기화
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();

    // SSL context 생성
    SSL_CTX *ssl_ctx = SSL_CTX_new(SSLv23_client_method());

    // SSL context 로 SSL 연결생성
    SSL *ssl = SSL_new(ssl_ctx);

    // apr socket 을 SSL 에 연결할 수 없다???
    // SSL_set_fd(ssl, sock->socketdes);
    // int ssl_err = SSL_connect(ssl);
    // if (ssl_err != 1)
    // {
    //     cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << " fail ssl connection err(" << ssl_err << ")" << endl;
    //     apr_socket_close(sock);
    //     return -1;
    // }

    // rc = APR_EINPROGRESS;
    // while (rc == APR_EINPROGRESS)
    {
        rc = apr_socket_connect(sock, sa);
        // usleep(waitms);
    }
    if (rc != APR_SUCCESS)
    {
        cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << " " << errmsg(rc) << endl;
        apr_socket_close(sock);
        return -1;
    }
    cout << "[connected]" << endl
         << ip << endl;

    string httpreq = "GET " + uri + " HTTP/1.0\r\n" + "Host: " + ip + ":" + portstr.str() + "\r\n" + "Accept: */*\r\n\r\n";
    apr_size_t sendlen = httpreq.size();
    rc = apr_socket_send(sock, httpreq.c_str(), &sendlen);
    if (rc != APR_SUCCESS)
    {
        cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << " " << errmsg(rc) << endl;
        apr_socket_close(sock);
        return -1;
    }
    cout << "[sent http request]" << endl
         << httpreq << endl;
    cout << "[sent len]" << endl
         << sendlen << endl;

    apr_size_t max_buffer_size = 1024 * 1024 * 1024;
    // can't create over 1MB local(stack) memeory
    // char recvbuff[max_buffer_size];
    char *recvbuff = (char *)malloc(max_buffer_size);
    memset(recvbuff, 0, sizeof(max_buffer_size));

    char *pos = recvbuff;
    apr_size_t read = 1024;
    while (read > 0)
    {
        read = 1024;
        rc = apr_socket_recv(sock, pos, &read);
        if (rc == APR_EOF)
        {
            break;
        }
        if (rc != APR_SUCCESS)
        {
            cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << " " << errmsg(rc) << endl;
            apr_socket_close(sock);
            apr_pool_destroy(pool);
            free(recvbuff);
            return -1;
        }
        pos += read;
        // cout << "[read from socket len]" << endl
        //      << read << endl;
        // usleep(100);
    }

    cout << "[response]" << endl
         << recvbuff << endl;

    free(recvbuff);

    apr_socket_close(sock);
    apr_pool_destroy(pool);

    // SSL 자원 해제
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ssl_ctx);

    return 0;
}
