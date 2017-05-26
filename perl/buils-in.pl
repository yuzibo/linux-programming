#/usr/bin/perl -w
#明显测试这个某个函数是不是build-in的函数
use strict;

use feature qw/say/;

sub f1{}

say TestFunctions('f1');
say TestFunctions('hex');
say TestFunctions('f2');

sub TestFunctions {
__PACKAGE__->can("CORE::$_[0]") ? 'build in':
__PACKAGE__->can($_[0]) ? 'user':'not exist'
}
