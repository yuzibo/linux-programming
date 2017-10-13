#!/bin/perl
#打印Tommy Savage的生日

while(<>) {
	($name,$phone,$address,$birth,$salary) = split (":",$_);
	print "$birth" if $name =~  /Tommy Savage/;
}
