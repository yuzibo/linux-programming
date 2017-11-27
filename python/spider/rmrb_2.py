#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: rmrb.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com
# Created Time: 2017年11月15日 星期三 17时30分56秒

""" This is source code in page that i want to get
<map name=PagePicMap>
<Area coords="2,29,283,29,283,183,2,183" shape="polygon" href="nw.D110000renmrb_20171117_1-05.htm">
<Area coords="292,29,397,29,397,318,292,318" shape="polygon" href="nw.D110000renmrb_20171117_2-05.htm">
<Area coords="2,193,142,193,142,399,2,399" shape="polygon" href="nw.D110000renmrb_20171117_3-05.htm"><Area coords="147,193,283,193,283,399,147,399" shape="polygon" href="nw.D110000renmrb_20171117_4-05.htm"><Area coords="292,327,397,327,397,563,292,563" shape="polygon" href="nw.D110000renmrb_20171117_5-05.htm">

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
    target = 'http://paper.people.com.cn/rmrb/html/2017-11/17/nbs.D110000renmrb_05.htm'
    req = requests.get(url=target)
    req.encoding = 'utf-8'
    content = req.text
    bf = BeautifulSoup(content ,'lxml')
    context = bf.find("map", {'name' : 'PagePicMap'})
    area = context.find_all('area')
    for ret in area:
        url = target.replace("nbs.D110000renmrb_05.htm",str(ret['href']))
        comment_url.append(url)

    for target in comment_url:
        print "===This is a new file ==="
        print_content(target, 'utf-8', 'articleContent')
