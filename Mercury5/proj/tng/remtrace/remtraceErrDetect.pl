#!/usr/bin/perl

use warnings;
use strict;

my $filename = shift;
my $target_lib = shift;

#open(H_FILE, "< $filename") or die "cannot read \"$filename\" file\n";
open(H_FILE, "< $filename") or exit 0;
my @content=<H_FILE>;
close(H_FILE);
	
open(TRC_ID, "< tng/remtrace/remtraceID") or die "cannot read \"remtraceID\" file\n";
my $libID_range = 0;
my $libID_end = 0;
my $libID_begin = 0;
my $foundLib = 0;
while (<TRC_ID>)
{
	if (/^$target_lib\=/)
	{
		$libID_range = $';
		$libID_range =~ s/\x0d\x0a//ig;
		$libID_range =~ s/\s//ig;
		chomp $libID_range;
		if ($libID_range =~ /,/)
		{
			$libID_begin = $`;
			$libID_end = $';
		}
		$foundLib = 1;
	}
}
close(TRC_ID);

open(TRC_ID, "< tng/remtrace/remtraceID") or die "cannot read \"remtraceID\" file\n";
while (<TRC_ID>)
{
	if (/^\w/ && !/^$target_lib/)
	{
		if (/\=/)
		{
			my $compareTarget = $`;
			$libID_range = $';
			$libID_range =~ s/\x0d\x0a//ig;
			$libID_range =~ s/\s//ig;
			chomp $libID_range;
			if ($libID_range =~ /,/)
			{
				if ((($libID_begin >= $`) && ($libID_begin <= $')) || (($libID_end >= $`) && ($libID_end <= $'))
						|| (($` >= $libID_begin) && ($` <= $libID_end)) || (($' >= $libID_begin) && ($' <= $libID_end)))
				{
					die "[remtrace ERROR] The trace ID range of target \"$target_lib\" overlap with target \"$compareTarget\"\n";
				}
			}
		}
	}
}
close(TRC_ID);

if ($foundLib == 0)
{
	die "[remtrace ERROR] cannot find lib \"$target_lib\" in tng/remtrace/remtraceID\n";
}

my $libMaxID = 0;
if ($content[$#content] =~ /;/)
{
	$libMaxID = $`;
}
if ($libMaxID =~ /Id/)
{
	$libMaxID = 0;
}

if ($libID_end <= $libMaxID)
{
	print "== Please increace tng/remtrace/remtraceID with $target_lib number ==\n";
	print "== Or clean build: make clean_lib TARGET=$target_lib; partial build: ./mg.sh $target_lib ==\n";
	die "[remtrace ERROR] $target_lib libID_end:$libID_end <= libMaxID:$libMaxID\n";
}
