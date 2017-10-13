#!/bin/perl
while(<>) {
	($name,$phone,$address,$brth,$salary) = split(":",$_);
	print "$name ----$address" if $name =~ /Gortz/;
}
# 这里的perl逐渐显示出了很强的应用性。首先可以分段，利用":",还可以分别打印各
# 自的内容
