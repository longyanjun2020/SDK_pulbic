#!/usr/bin/perl

#####
## SYNTAX:
## perl tng/release_process/rmSimuFiles.pl
#####

use warnings;
use strict;

open(SIMU_LIST, "tng/release_process/processSimulator.txt") or die "cannot read \"processSimulator.txt\" file\n";
my @simuLists=<SIMU_LIST>;
close(SIMU_LIST);

sub parseFile
{
	my $pType = shift;
	my $fileName = shift;
	my $filterType = shift;
	my $filterName = shift;
	
	open(SIMU_FILE, "$fileName") or die "cannot read \"$fileName\" file\n";
	my @simuFile=<SIMU_FILE>;
	close(SIMU_FILE);
	
	my $storeLine = "";
	my $printLine = 1;
	open(SIMU_FILE, ">$fileName") or die "cannot read \"$fileName\" file\n";
	for my $fileLine (@simuFile)
	{
		my $tmp_line = $fileLine;
		$tmp_line =~ s/\x0d\x0a//ig;
				
		if ($filterType eq "Filter")
		{
			if ($tmp_line =~ /\<Filter/)
			{
				$printLine = 0;
				$storeLine = $fileLine;
			}
			elsif ($tmp_line =~ /Name\=\"/)
			{
				if ($tmp_line =~ /\"$filterName\"/)
				{
					$storeLine = "";
				}
				else
				{
					$fileLine = $storeLine.$fileLine;
					$printLine = 1;
				}
			}
			
			if ($printLine)
			{
				print SIMU_FILE $fileLine;
			}
			else
			{
				if ($tmp_line =~ /\<\/Filter\>/)
				{
					$printLine = 1;
				}
			}
		}
	}
	close(SIMU_FILE);
}

for my $line (@simuLists)
{
	$line =~ s/\x0d\x0a//ig;
	my @simuList = split (/ /, $line);
	parseFile ($simuList[0], $simuList[1], $simuList[2], $simuList[3]);
}
	