#-*- coding: utf-8 -*-
# 20160422 ysoftman
# zmq 설치(python3.x 기준)
# sudo pip3 install zmq
import zmq
import sys
import time

def start_server(port):
	print("start server... port %s" % port)

	context = zmq.Context()
	socket = context.socket(zmq.REP)
	socket.bind("tcp://*:%s" % port)
	while True :
		message = socket.recv()

		print("recv mesg:", message)

		time.sleep(1)

		socket.send(b"reply")


if __name__ == "__main__":
	port = sys.argv[1]
	start_server(port)


