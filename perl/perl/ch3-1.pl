#!/bin/perl
use warnings;
# use 5.012;
###########
# chapter 3
# No.1 : 读一些字符串，每行一个，利用键盘的输入结束表示，然后以相反的顺序的
#		写出。
# 20160303
##########

while(@lines = <STDIN>){
	@lines = reverse(@lines);
	foreach $var (@lines){
		print "$var\n";
	}
}


