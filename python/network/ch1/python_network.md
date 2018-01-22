---
title: "python网络编程"
category: python
layout: article
---

# 简单介绍
其实python的socket库与c语言的socket库非常相似，现在简单地介绍下其中的几个简单应用。

## 基本信息

```python
import socket

def print_machine_info():
	host_name = socket.gethostname()
	ip_address = socket.gethostbyname(host_name)
	print("Host name: %s" % host_name)
	print("Ip address: %s" %ip_address)

if __name__ == '__main__':
	print_machine_info()
```

这一个代码段就是打印本地的host以及对应的ip地址。简单介绍下我们使用的在*__main__*代码块中使用这个函数，为什么呢？在这里，*__name__*表示程序的进程名，如果在命令行中运行脚本，*__name__*的值就是*__main__*,但是，如果在其他脚本中导入，情况就不一样。如果在命令行中调用这个模块，会自动运行print_machine_info()函数，如果在其他脚本中导入，用户就要手动调用这个函数



```python

def get_remote_machine_info():
	remote_host = 'www.baidu.com'
	try:
		print("Ip address: %s " %socket.gethostbyname(remote_host))
	except socket.error, err_msg:
		print("%s: %s" %(remote_host, err_msg))

if __name__ == '__main__':
	get_remote_machine_info()
```

## ipv4转换不同的格式

```python

from binascii import hexlify

def convert_ip4_address():
	for ip in ['127.0.0.1', '192.168.0.1']:
		pakced_ip_addr = socket.inet_aton(ip)
		unpacked_ip_addr = socket.inet_ntoa(pakced_ip_addr)
		print("Ip address: %s => Packed: %s, unpacked: %s" \
			%(ip, hexlify(pakced_ip_addr), unpacked_ip_addr))

```
分析：这段代码把字符串形式的ip地址转换成打包后的32位二进制格式，然后调用binascii模块中的hexlify()函数，以十六进制形式表示二进制。

## 通过指定的端口和协议找到服务名

注意，没有注明

	import socket

	if __name__ == '__main__':


```python

def find_service_name():
	protocolname = 'tcp'
	for port in [80, 25]:
		print("Port: %s => service name: %s" %(port, socket.getservbyport(port, protocolname)))

	print("Port: %s => service name: %s" % (53, socket.getservbyport(53, 'udp')))
```

程序运行结果如下所示：

	Port: 80 => service name: http
	Port: 25 => service name: smtp
	Port: 53 => service name: domain

使用*getservbyport()*函数解析几个端口。

## 主机字节序和网络字节序之间的转换

使用*ntohl()*或者*htonl()*,其中的"l"可以转换为"s",表示短型。

```python

def convert_integer():
	data = 1234
	# 32 - bits
	print("原始数据: %s => Long host byte order: %s, Network byte order; %s" \
		%(data, socket.ntohl(data), socket.htonl(data)))

	# 16 - bits
	print("原始数据: %s => Short host byte order: %s, Network byte order; %s" \
		%(data, socket.ntohs(data), socket.htons(data)))
```

## 设定并获取默认的socket超时时间

```python
import socket
def test_socket_timeout():
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	print "默认socket timeout: %s" %s.gettimeout()
	s.settimeout(100)
	print("现在的socket timeout: %s" %s.gettimeout())
```

## try-except

```python


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

```

这里的用法是

	python socketerror.py --host=191.101.9.198 --port=80 --file=socketerror.py


要简单地会用parser库，以后自己写软件需要这个用法。

## 修改socket发送和接收的缓冲区

```python


import socket
SEND_BUF_SIZE = 4096
RECV_BUF_SIZE = 4096

def modify_buffer_size():
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	# get the size of teh socket s send buffer
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
```
在套接字对象上可调用方法getsockopt()和设置setsockopt()分别获取和修改套接字对象的属性，setsockopt()方法接受三个参数：level、optname和value，其中，optname是选项名，value是该选项的值，是第一个参数所用的符号常量(SO_*等)可在socket模块中查看。

## 阻塞模式

```python
import socket

def test_socket_modes():
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.setblocking(1)
	s.settimeout(0.5)
	s.bind(("127.0.0.1", 0))

	socket_adress = s.getsockname()
	print("Trivial Server on socket: %s" %str(socket_adress))
	while(1):
		s.listen(1)

if __name__ == '__main__':
	test_socket_modes()

```
 在上面的 *setblocking()*中的1改为0就是非阻塞模式。

## socket重用

 ```python
import socket
import sys

def reuse_socket_addr():
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	# get the old status of the SO_REUSEADDR option
	old_state = sock.getsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR)
	print("The old state: %s" % old_state)

	# enbale the SO_REUSEADDR option
	sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	new_state = sock.getsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR)
	print("THe new sock state: %s" % new_state)

	local_port = 8282

	srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	srv.bind(('', local_port))
	srv.listen(1)
	print("listening on port %s" % local_port)
	while True:
		try:
			connection, addr = srv.accept()
			print("Connected by %s: %s" %(addr[0], addr[1]))
		except KeyboardInterrupt:
			break
		except socket.error, msg:
			print('%s' % meg)

if __name__ == '__main__':
	reuse_socket_addr()
 ```

## 从网络时间(NTP)获取并打印时间
运行这段代码需要ntplib库。

```python

import ntplib
from time import ctime

def print_time():
	ntp_client = ntplib.NTPClient()
	response = ntp_client.request('pool.ntp.org')
	print(ctime(response.tx_time))

if __name__ == '__main__':
	print_time()

```
创建一个NTPClient实例，然后这个实例调用request()方法，把ntp服务器的地址传递给方法。

## 编写一个SNTP客户端
首先，定义两个常量：NTP_SERVER和TIME1970.前者是要连接的服务器地址，TIME1970是1970年1月1日，这个客户端通过UDP协议创建一个UDP套接字(SOCK_DGRAM),用于连接服务器。然后，客户端要在一个数据包中把数据'\x1b' + 47 * '\0'发送给SNTP服务器，UDP客户端分别使用sendto()和recvfrom()方法发送和接收数据。服务器返回的时间信息打包在一个数组中，客户端需要使用struct模块取出数据。我们所需要的数据是数据中的第11个元素，最后，我们要从取出的数据上减掉TIME1970,得到真正的当前时间。

```python

import socket
import struct
import sys
import time

NTP_SERVER = "0.uk.pool.ntp.org"
TIME1970 = "2208988800L"

def sntp_client():
	client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	data = '\x1b' + 47 * '\0'
	client.sendto(data, (NTP_SERVER, 123))
	data, address = client.recvfrom(1024)
	if data:
		print("Response received from:" , address)
	t = struct.unpack('!12I', data)[10]
	t -= TIME1970
	print('\tTime=%s' % time.ctime(t))

if __name__ == '__main__':
	sntp_client()
```

