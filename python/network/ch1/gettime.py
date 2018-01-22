#!/usr/bin/python
# -*- coding: UTF-8 -*-

import socket
def test_socket_timeout():
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	print "默认socket timeout: %s" %s.gettimeout()
	s.settimeout(100)
	print("现在的socket timeout: %s" %s.gettimeout())

if __name__ == '__main__':
	test_socket_timeout()

