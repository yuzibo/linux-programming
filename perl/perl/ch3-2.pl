#!/bin/perl
#########
#  chapter 3 No.2
#    input a num and output responed value (--> array,)
# key:  num inputed is's' origin num (actually should aub 1),
#########
@text = qw/ fred betty barney dino wilma pebbles bamm-bamm /;
$num = 0;
while(chomp($num = <STDIN>)){
	print "$text[$num - 1]\n";

}
