#!/usr/bin/perl -w
# sample erase and reuse an array
use strict;

my @a = ('foo', 'bar', 'buz');
print "@a\n";

@a = ('some', 'new', 'value' );
print "@a\n";
