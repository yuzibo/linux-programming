#!/bin/perl
while(<>){
	($name, $phone,$address,$birth,$salary) = split(":",$_);
	($birth_month, $birth_day,$birth_year) = split("/", $birth);
	print $name if $birth_month =~ /6/;
}
# 打印在6月份出生的人，这个例子的较新，利用两次函数，有新意
