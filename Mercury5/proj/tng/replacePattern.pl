#!/usr/bin/perl

use warnings;
use strict;

my $filename = shift;
my $pattern = shift;
my $newPattern = shift;
open(H_FILE, "$filename") or die "cannot read \"$filename\" file\n";
my @content=<H_FILE>;
close(H_FILE);
	
open(H_FILE, "> $filename") or die "cannot read \"$filename\" file\n";
for my $line (@content)
{
	if ($line =~ /$pattern/)
	{
		$line =~ s/$pattern/$newPattern/;
	}
	print H_FILE $line;
}
close(H_FILE);
