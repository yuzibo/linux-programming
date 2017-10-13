#!/bin/perl
#######################
# chapter 4 No.4
# give you two names and you output information responed
#	keys:	这里怎么样把参数保存下来，以及怎么识别先前有没有记录下来
#	这里首先定义$last_person,用shift传递给$name,在使用defined 函数分开
#	判断
#
######################
use warnings;
use 5.010;

sub greet{

	state $last_person;
	my $name = shift;
	print "Hi,$name\t";
	if(defined $last_person){
		print "$last_person is here also!\n";
	}
	else{
		print "You are the first one here\n";
	}
	$last_person = $name;

}

greet("Fred");
greet("yubo");
