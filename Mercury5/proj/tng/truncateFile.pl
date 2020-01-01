#!/usr/bin/perl

#####
## SYNTAX:
## perl tng/truncateFile.pl sc pattern
#####

use warnings;
use strict;

my %used;

my $search_folder = shift(@ARGV);
my $searchPattern = shift(@ARGV);

sub truncateFile
{
	my @makFiles = <*>;
	for my $path (@makFiles)
	{
		if (-d $path)
		{
			chdir $path;
			truncateFile();
			chdir "../";
		}
		else
		{
			if ($path =~ /\.mak$/)
			{
				open(MAK_FILE, "$path") or die "cannot read \"$path\" file\n";
				my @content=<MAK_FILE>;
				close(MAK_FILE);
				open(MAK_FILE, "> $path") or die "cannot read \"$path\" file\n";
				my $found = 0;
				for my $line (@content)
				{
					if ($found == 0)
					{
						print MAK_FILE $line;
					}
					if ($line =~ /$searchPattern/)
					{
						$found = 1;
					}
				}
				close(MAK_FILE);
			}
		}
	}
}

chdir $search_folder;
truncateFile();
