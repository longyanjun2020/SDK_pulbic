#!/usr/bin/perl
use strict;
use warnings;
use Getopt::Std;

my $Version="v 1.0";
my $Date="May 2012";

##--------------------------------------------------------------------------------------------------
## Author  | Rev | Date     | Comment
##--------------------------------------------------------------------------------------------------
##  Janet  | 1.0 | 18/05/12 | Creation, first version
##--------------------------------------------------------------------------------------------------



my %opts;
my $target_file;

getopts("b:",\%opts);
if( exists $opts{b} ) { 
	$target_file = $opts{b};
}else{
	print "no bin file";
	exit 1;
}


my $size_of_target_file = -s $target_file;
open(TMP, ">>".$target_file) or die "Can't open Output file: $!";
while ( ($size_of_target_file%4) ne 0 )
{
	print TMP pack("c", 1);
	$size_of_target_file++;
}
close TMP;
