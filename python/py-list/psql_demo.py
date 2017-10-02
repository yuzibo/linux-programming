#!/usr/bin/python
# -*- coding: UTF-8 -*-

import MySQLdb
import psycopg2

db = psycopg2.connect(database = "test", user = "root")

def show():
	cursor.execute("select username, email from users:")
	for row in cursor.fetchall():
		print(*row, sep=", ")

users = [
	'yubo', 'hechun', 'liubo'
]

emailaddresses = [
	'tsu.yubo@gmail.com',
	'yuzibode@126.com',
	'hehe@gmail.com'
]

cursor = db.cursor()

print("Brfore update")
show()

cursor.executemany(
	"update users set email = %s where usersname=%s;",
	zip(emailaddresses, users)
)

db.commit()

print("After update")
show()


