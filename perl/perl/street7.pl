#!/bin/perl
while(<>){
	($name,$phone,$address,$birth,$salary) = split(":",$_);
	print "$. -- $_" unless ($. == 4);
}
#
#打印不含4的行，说实在的，我感觉有些问题，$.打印出来是当前的行数，unless不太
#明白什么意思

