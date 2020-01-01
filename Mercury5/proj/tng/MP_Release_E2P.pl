#!/usr/bin/perl

#####
## SYNTAX:
## perl MP_Release_E2P.pl filename pattern
## Note: next line of the pattern will be replaced to 1
#####

use warnings;
use strict;

my $fileName = shift;
my $pattern = shift;
my $nextLineFlag = 0;

open(IN_FILE, "$fileName") or die "cannot read \"$fileName\" file\n";
my @content=<IN_FILE>;
close(IN_FILE);

open(IN_FILE, "> $fileName") or die "cannot read \"$fileName\" file\n";
for my $line (@content)
{
	if ($line =~ /$pattern/) 
	{
	    # match the pattern
		$nextLineFlag = 1;
	}
	else
	{
		if($nextLineFlag eq 1) 
		{
		    # next line of the pattern, replace 0 t0 1
			$line =~ s/0/1/;
		}
		$nextLineFlag = 0;
	}
	print IN_FILE $line;
}
close(IN_FILE);
