#!/usr/bin/perl

#####
## SYNTAX:
## perl GPRS_E2P.pl filename pattern LineCnt
## Note: next line of the pattern will be replaced to 1
#####

use warnings;
use strict;

my $fileName = shift;
my $pattern = shift;
my $numLine = shift;
my $nextLineFlag = 0;
my $nextLineCnt = 0;
#my $old_val = shift;
#my $new_val = shift;

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
			$nextLineCnt ++;
			if ($nextLineCnt == $numLine)
			{
				$nextLineFlag = 0;
				$line =~ s/0x2/0/;
			}
		  # next 6 lines of the pattern, replace 0x2 to 0
			#$line =~ s/$old_val/$new_val/;
			#$line =~ s/0x2/0/;
		}
		#$nextLineFlag = 0;
	}
	print IN_FILE $line;
}
close(IN_FILE);
