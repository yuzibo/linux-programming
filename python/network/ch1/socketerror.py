#!/usr/bin/python
# -*- coding: UTF-8 -*-

import sys
import socket
import argparse

def main():
	#setup argparse parsing
	parser = argparse.ArgumentParser(description = 'Socket Error Example')
	parser.add_argument('--host', action="store", dest="host", required=False)
	parser.add_argument('--port', action="store", dest="port", type=int, required=False)
	parser.add_argument('--file', action="store", dest="file",required=False)
	given_args = parser.parse_args()
	host = given_args.host
	port = given_args.port
	filename = given_args.file
	# First try-except block --create socket
	try:
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	except socket.error, e:
		print("Error 创造socket: %s" % e)
		sys.exit(1)

	# second --connect to given host/port
	try:
		s.connect((host, port))
	except socket.gaierror, e:
		print("地址相关的错误连接到服务器: %s" % e)
		sys.exit(1)
	except socket.error, e:
		print("连接错误 %s" % e)
		sys.exit(1)

	# third --sending data
	try:
		s.sendall("Get %s HTTP/1.0\r\n\r\n" % filename)
	except socket.error, e:
		print("发送数据错误 %s" % e)
		sys.exit(1)

	# forth --waiting to receive data from remote host
	while 1:
		try:
			buf = s.recv(2048)
		except socket.error, e:
			print("接收数据错误 %s" % e)
			sys.exit(1)
		if not len(buf):
			break
		sys.stdout.write(buf)

if __name__ == '__main__':
	main()

