#!/usr/bin/python
# -*- coding: UTF-8 -*-

import socket
SEND_BUF_SIZE = 4096
RECV_BUF_SIZE = 4096

def modify_buffer_size():
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	# get the size of teh socket's send buffer
	bufsize = sock.getsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF)
	print("BUffer size [之前]; %d" % bufsize)

	sock.getsockopt(
		socket.SOL_SOCKET,
		socket.SO_SNDBUF,
		SEND_BUF_SIZE)
	sock.setsockopt(
		socket.SOL_SOCKET,
		socket.SO_SNDBUF,
		RECV_BUF_SIZE)

	bufsize = sock.getsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF)
	print("buffer size [之后]： %d" % bufsize)

if __name__ == '__main__':
	modify_buffer_size()
