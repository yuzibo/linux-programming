#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: rmrb.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com
# Created Time: 2017年11月15日 星期三 17时30分56秒

""" This is source code in page that i want to get

"""
import sys
reload(sys)
sys.setdefaultencoding('utf8')
# 这一个对于编码的工作也是至关重要

import urllib2
from bs4 import BeautifulSoup
import requests

import chardet
import re

# import myself print function

from get_content import print_content

if __name__ == '__main__':
    comment_url = []
    target = 'https://www.spinics.net/lists/kernel/threads.html'
    req = requests.get(url=target)
    req.encoding = 'utf-8'
    content = req.text
    bf = BeautifulSoup(content ,'lxml') # There is no problem

    context = bf.find_all('strong')
    #area = context.find('li')
    for ret in context[2:3]:
    #    print ret['href']
    #    url = target.replace("threads.html",str(ret['href']))
    #    comment_url.append(url)

    #    print ret.contents
    #    print '\t'
    #    print type(ret)
        for test in ret:
            print '\t'
            x = re.split(' ', str(test))
            y = re.search('"(.+?)"', str(x)).group(1)
            comment_url.append(target.replace("threads.html", str(y)))

    for tmp_target in comment_url:
        print "===This is a new file ==="
        print_content(tmp_target, 'utf-8', 'title')

    #ret = context
    #url = target.replace("threads.html",str(ret['href']))
    #print_content(url, 'utf-8', 'title')
    #print url
    #print context[1]
