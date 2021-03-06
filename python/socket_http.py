# -*- coding: utf-8 -*-
# author: ysoftman
# python version : 2.x 3.x
# desc : socket 으로 http 요청
import sys
import socket


def deletePrefixHttp(url):
    prefixes = ['http://', 'https://']
    for p in prefixes:
        if url[:len(p)] == p:
            url = url[len(p):]
            break
    return url


if len(sys.argv) != 2:
    print('ex) python', sys.argv[0], "'httpbin.org/get'")
    sys.exit(0)

method = "GET"
url = deletePrefixHttp(sys.argv[1])
uri = '/'
try:
    urlindex = url.index("/")
    host = url[:urlindex]
    uri = url[urlindex:]
except ValueError as err:
    host = url
    pass
port = 80
try:
    portindex = url.index(':')
    portstr = url[portindex+1:].split('/')[0]
    temp = url[:portindex]
    url = temp
    url += url[portindex+1+len(portstr):]
    port = int(portstr)
    host = url[:portindex]
except ValueError as err:
    pass

headers = '''User-Agent: python-socket-http\r\n\
Accept-Language: ko,en-US;q=0.9,en;q=0.8\r\n'''

req = '''{} {} HTTP/1.0\r\nHost: {}:{}\r\n{}\r\n\r\n'''.format(
    method, uri, host, port, headers)
print('[http request]')
print(req)

print('----------\n')

recv_buffer_size = 1024*1024
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))
# python 2.x
# s.sendall(req)
# python 3.x
s.sendall(bytes(req, 'utf-8'))

resp = ''
while True:
    temp = s.recv(recv_buffer_size)
    if len(temp) <= 0:
        break
    resp += str(temp)
print('[http response]')
print(resp)
