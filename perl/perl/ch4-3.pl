#!/bin/perl
#################
#  sum of 1..1000
# chapter 4 No.3
#
#
################
use 5.010;
use warnings;
use utf8;

@yubo = (1..1000);

my $yubo_total = &total(@yubo);
print "$yubo_total";
sub total{
	state $sum;
	state @numbers;
	foreach my $number(@_){
		push @numbers, $number;
		$sum += $number;
	
	}
	return $sum;

}
