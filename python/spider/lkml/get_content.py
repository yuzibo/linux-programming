#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: rmrb.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com


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
    article_title = bf.find('h1')
    author = bf.find_all('li')
    commit = bf.find('pre')
    print '\t'
    print 'Subject: ' + article_title.get_text()
    print '\t'
    text = str(commit.get_text())
    cleaned_text = text.partition("diff --git")[0].strip()
    print 'Commit:' + '\n'
    print (cleaned_text)




