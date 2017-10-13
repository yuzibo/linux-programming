#!/bin/perl
########################
#	requirement is same as previous
#	but i stuck in store value in @names (列表又叫环境变量?)
#	keys: keep in mind,we will store value into @_ via $var, use method "push"
#	format:			push @dest,$src
####################3


use warnings;
use 5.010;

greet("Fred");
greet("Bar");
greet("Wila");
greet("Betty");

sub greet{
	
	state @names;
	
	my $current = shift;
	if(@names){
		print "Hi $current!\t,I'v seen @names\n";
#		&print_all(@names);
	}else{
		print "Hi $current!\t, you are the first one here\n";
	}
#	@names = $current;    hrer is my first editors
	push @names, $current;
}

