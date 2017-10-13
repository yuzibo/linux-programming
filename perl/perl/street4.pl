#!/bin/perl
while(<>){
	($name,$phone,$address,$birth,$salary) = split(":",$_);
	print if $phone =~ /408/;
	
}
# 打印电话区号为408的行，这里你该能看出来，"=~"是匹配变量的一个单位
