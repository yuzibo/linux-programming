#!/bin/perl
while(<>) {
	($name,$phone,$address,$birth,$salary) = split(":",$_);
	print "\U$name\E" if $name =~ /Ephram/;
}
#
#打印匹配Ephram的姓名，并以大写的方式打印出来,\U是大写的修饰符，\E是结束修饰
#符的意思，在这里，可有可无
