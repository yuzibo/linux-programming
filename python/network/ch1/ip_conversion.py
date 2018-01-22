#!/usr/bin/python
# -*- coding: UTF-8 -*-

import socket
from binascii import hexlify

def convert_ip4_address():
	for ip in ['127.0.0.1', '192.168.0.1']:
		pakced_ip_addr = socket.inet_aton(ip)
		unpacked_ip_addr = socket.inet_ntoa(pakced_ip_addr)
		print("Ip address: %s => Packed: %s, unpacked: %s" \
			%(ip, hexlify(pakced_ip_addr), unpacked_ip_addr))

if __name__ == '__main__':
	convert_ip4_address()

