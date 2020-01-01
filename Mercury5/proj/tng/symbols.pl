#!/usr/bin/perl

use strict;

my $nm = shift;
my $sbl = shift;

my %line;

open NM, "< $nm" or die "cannot read file \"$nm\"\n";
open SBL, "> $sbl" or die "cannot write file \"$sbl\"\n";

print SBL "\nSymbol Table\n";

while(<NM>)
{
	my ($addr, $type, $name) = split;

	if (($type ne "a") && ($name =~ m/^[[:alnum:]_]/))
	{
		if (! defined($line{$_}))
		{
			print SBL $name, "\t", $addr, "\n";
			$line{$_} = 1;
		}
	}
}
