#!/usr/bin/perl

use warnings;
use strict;

my %used;

my $searchFolder=shift;

sub doClean
{
	my $path = shift;
	my @findFiles = <*>;

	for my $file (@findFiles)
	{
		if (-d $file)
		{
			my $count;
			chdir $file;
			$count = doClean("$path\/$file");
			chdir "../";
			if ($count == -1)
			{
				#print "delete folder $file\n";
				rmdir $file;
			}
		}
	}
	my @dir = <*>;
	return $#dir;
}

chdir $searchFolder;
my $count;
$count = doClean($searchFolder);
if ($count == -1)
{
	rmdir $searchFolder;
	#print "delete folder $searchFolder\n";
}
