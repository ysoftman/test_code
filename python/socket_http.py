# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x
# desc : socket 으로 http 요청
import sys
import socket

if len(sys.argv) != 3:
    print 'ex) python', sys.argv[0], "'httpbin.org/get' 80"
    sys.exit(0)

method = "GET"
url = sys.argv[1]
urlindex = url.index("/")
host = url[:urlindex]
uri = url[urlindex:]
port = int(sys.argv[2])
headers = '''User-Agent: python-socket-http\r\n\
Accept-Language: ko,en-US;q=0.9,en;q=0.8\r\n'''

req = '''{} {} HTTP/1.0\r\nHost: {}:{}\r\n{}\r\n\r\n'''.format(
    method, uri, host, port, headers)
print '[http request]'
print req

print '----------\n'

recv_buffer_size = 1024*1024
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))
s.sendall(req)
resp = s.recv(recv_buffer_size)
print '[http response]'
print resp
