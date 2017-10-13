#!/bin/perl
# 打印超过$40000的人
while(<>) {
	($name,$address,$birth,$salary) = split(":",$_);
#	print "$. -- $name\n" if ($salary > 40000); 
	print "$. -- $name\n" if ($name == "Lori Gortz"); 
	
}
