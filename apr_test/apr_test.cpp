// ysoftman
// apr(Apache Portable Runtime) library test
/*
# 설치 방법1 - apche httpd 설치하면 생성되는 apr 사용
wget http://mirror.apache-kr.org//httpd/httpd-2.2.34.tar.gz
tar zxvf httpd-2.2.34.tar.gz
cd httpd-2.2.34
./configure --prefix="${HOME}/httpd" --with-mpm-prefork
make && make install
# 빌드
g++ -O2 -g -fPIC -I${HOME}/httpd/include -L${HOME}/httpd/lib -lapr-1 apr_test.cpp -o aprtest


# 설치 방법2 - apr 만 설치
apr 설치
wget http://apache.mirror.cdnetworks.com//apr/apr-1.6.3.tar.gz
cd apr-1.6.3
./configure --prefix="${HOME}/apr"
make && make install
# apr-util 설치
wget http://apache.mirror.cdnetworks.com//apr/apr-util-1.6.1.tar.gz
tar zxvf apr-util-1.6.1.tar.gz
cd apr-util-1.6.1
./configure --prefix="${HOME}/apr"  --with-apr="${HOME}/apr/bin/apr-1-config"
make && make install
# 빌드
g++ -O2 -g -fPIC -I${HOME}/apr/include/apr-1 -L${HOME}/apr/lib -lapr-1 apr_test.cpp -o aprtest
*/

#include "apr.h"
#include "apr_file_io.h"
#include "apr_strings.h"
#include "apr_network_io.h"
#include "apr_pools.h"
#include "apr_poll.h"
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
    // string ip = "www.json.org";
    // int port = 80;
    // string uri = "/json-ko.html";
    if (argc == 4)
    {
        ip = argv[1];
        port = atoi(argv[2]);
        uri = argv[3];
    }
    else
    {
        cout << argv[0] << " \"www.json.org\" " << 80 << " \"/json-ko.hml\"" << endl;
        exit(0);
    }
    stringstream portstr;
    portstr << port;

    cout << "ip: " << ip << endl;
    cout << "port: " << port << endl;
    cout << "uri: " << uri << endl;

    unsigned int waitms = 1000 * 500;
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

    char recvbuff[1024];
    apr_size_t recvlen = sizeof(recvbuff);
    memset(recvbuff, 0, sizeof(recvbuff));
    apr_socket_recv(sock, recvbuff, &recvlen);
    if (rc != APR_SUCCESS)
    {
        cout << "[ERROR] " << __FILE__ << ":" << __LINE__ << " " << errmsg(rc) << endl;
        apr_socket_close(sock);
        return -1;
    }
    cout << "[received http response]" << endl
         << recvbuff << endl;
    cout << "[received len]" << endl
         << recvlen << endl;

    apr_socket_close(sock);
    apr_pool_destroy(pool);
    return 0;
}
