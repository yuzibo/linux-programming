#!/bin/perl
###############
# chapter 4 NO.1
# intend：	write a fun called print sum of some numbers.
# key:	数字型的列表还是有很多的注意事项；在这个函数中，首先需要state声明持
# 久私有变量然后怎么把列表中的数据保存到当前的sum中。@_是参数的默认列表，
# 用pushI将列表中数据存放在$number中.这个函数有一点bug，就是从键盘输入的
# 结果保存了上次运算的结果。
#
#
###############
use utf8;
use 5.010;
use warnings;
my @yubo = qw/ 1 3 5 7 9/;
my $yubo_total = &total(@yubo);
print "$yubo_total\n";
print "请输入一些数字:";
my $user_total = &total(<STDIN>);
print "Those numbers is $user_total\n";
sub total{
	state $sum;
	state @numbers;
	foreach my $number(@_){
		push @numbers, $number;
		$sum += $number;
#		print "\$number is $number\n";
	}
	
	return $sum;

}
