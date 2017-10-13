#!/bin/perl
while(<>) {
	($name,$phone,$address,$birth,$salary) = split(":",$_);
	print if /Ker/;
}
# print matched "Ker"

