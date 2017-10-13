#!/bin/perl
while(<>){
	($name,$phone,$address,$birth,$salary) = split(":",$_);
	($num, $govern,$post) = split(",",$address);

	($pro,$post_num) = split(" ",$post);
	print  " ----$post_num\n" if $pro =~ /MA/;
}
