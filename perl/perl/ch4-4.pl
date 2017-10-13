#!/bin/perl
#################
# chapter 4 NO.3
# print above_average and return list
#  **** psuh: put $element into @list
#
################
use 5.010;
use warnings;
use utf8;

#my @yubo = (1..10);

my @average= &above_average(100,1..10);

foreach my $var(@average){
	print "$var\n";
}
#print "@average\n";

#print "$total\n";
sub above_average{
	state $sum = 0;
	state @numbers;
	state @return_list;
	state $num = 0;
	foreach my $var_1(@_){
		$sum += $var_1;
		$num ++;
	
	}
	# average 
	my $average = $sum / $num;
	foreach my $var_2(@_){
		if($var_2 > $average){
			push @numbers, $var_2;			

		}
	
	}

		return @numbers;
}
