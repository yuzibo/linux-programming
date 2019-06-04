#!/usr/bin/python
# -*- coding: UTF-8 -*-
# File Name: download.py
# Author: Bo Yu
# mail: tsu.yubo@gmail.com
# Created Time: 2019年06月04日 星期二 20时37分13秒


#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jul  6 11:04:53 2017

@author: chih
例子说明，同时记录自己的程序理解
---
<li>

Mohamed Zait, Sunil Chakkappen, Suratna Budalakoti, Satyanarayana Valluri, Ramarajan Krishnamachari, Alan Wood:<br>

<a href="http://www.vldb.org/pvldb/vol10/p1813-zait.pdf">

  Adaptive Statistics in Oracle 12c</a>. 1813 - 1824.

</li><br>
---
网页源代码是这个样子的。
输出是:

---
Adaptive Statistics in Oracle 12c.pdf
---
"""

from bs4 import BeautifulSoup
import requests

BASE_URL = 'http://www.vldb.org/pvldb/vol10.html'

class VldbCrawler:

    def __init__(self, base_url=BASE_URL):
        self.base_url = base_url

    def fetch_download_link(self):
        page = requests.get(BASE_URL)
        a = BeautifulSoup(page.text, "lxml").findAll('a')
        pdf_map = dict(map(lambda i: {i.text.strip(), i.attrs['href']}, a))

        for item in pdf_map:
            if ".pdf" in pdf_map[item] and "www.vldb.org" in pdf_map[item]:
                pdf_r = requests.get(pdf_map[item])
                with open(item + ".pdf", "wb") as pdf_file:
                    pdf_file.write(pdf_r.content)

    def run(self):
        self.fetch_download_link()


if __name__ == '__main__':
    vc = VldbCrawler()
    vc.run()

