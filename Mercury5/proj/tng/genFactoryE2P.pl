#!/usr/bin/perl

#####
## SYNTAX:
## perl genFactoryE2P.pl v2751_app.e2p z_factory.e2p
#####

use warnings;
use strict;

my $inFileName = shift;
my $outFileName = shift;

my $nextLineFlag = 0;
my $msg = "1 %u8";

open(IN_FILE, "$inFileName") or die "cannot read \"$inFileName\" file\n";
my @content=<IN_FILE>;
close(IN_FILE);
	
open(OUT_FILE, "> $outFileName") or die "cannot read \"$outFileName\" file\n"; 
for my $line (@content)
{
	if ($line =~ /MMIRunMode/) 
	{
		$nextLineFlag = 1;
		print OUT_FILE $line;
	}
	else
	{
		if($nextLineFlag eq 1) 
		{
			print OUT_FILE $msg;
		}
		$nextLineFlag = 0;
	}
}
close(OUT_FILE);
