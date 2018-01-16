#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: rmrb.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com
# Created Time: 2017年11月15日 星期三 17时30分56秒
# 成功实现抓取网页汉字内容
# 给一个网址，可以根据标签抓取文本内容


# 这一个对于编码的工作也是至关重要

import urllib2
from bs4 import BeautifulSoup
import requests

import chardet
import re

def print_content(url, charset, find_id):
    req = requests.get(url=url)
    req.encoding = charset
    content = req.text
    bf = BeautifulSoup(content ,'lxml')
    context = bf.find(id=find_id)
    print context.get_text(separator = u'\n')

#print_content(target, 'utf-8', 'articleContent')

