#!/bin/perl
#########
#   chapter 3 no.3
#   use sort in @something
#	key: 将列表的内容转化为数组，需要将"@"转化为"$"然后下标需要你在外面得到
#		和c语言访问数组一模一样了
#
#########
while (chomp(@text=<STDIN>)){
	@text = sort(@text);
foreach $var (0..$#text){
	# 1. use \
	# 2. use \n
	print "$text[$var]\t";
}

}
