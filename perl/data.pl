#!/usr/bin/perl -w
use strict;

use POSIX qw(mktime);

my $date_start = '2016-05-09';
my $date_until = '2017-05-09';

sub d2ts
{
	my ($y, $m, $d) = $_[0] =~ /\d+/g;

	$y -= 1900;

	--$m;

	return mktime(0, 0, 0, $d, $m, $y);
}

print((d2ts($date_until) - d2ts($date_start)) /86400, "\n");
