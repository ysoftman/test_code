#-*- coding: utf-8 -*-
# 20160422 ysoftman
# pyzmq (python3.x) client
import zmq
import sys


def send_req(ip, port):
    context = zmq.Context()
    socket = context.socket(zmq.REQ)
    # socket.setsockopt(zmq.REQ, b'')
    socket.connect("tcp://%s:%s" % (ip, port))

    # python 3 에서 기본 인코딩이 유니코드
    # send 함스는 유니코드를 사용할 수 없어, byte 형태로 만든다.
    data = b'hello'
    for i in range(10):
        socket.send(data)
        print("send %s to server. [%d]" % (data, i))
        reply = socket.recv()
        print("reply %s from server.[%d]" % (reply, i))


if __name__ == "__main__":

    print("start testing...")
    send_req("127.0.0.1", "55555")
