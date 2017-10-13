#!/bin/perl
while(<>){
	($name,$phone, $address,$birth, $salary) = split(":",$_);
	print if $name =~ /[Bb]/;
}
