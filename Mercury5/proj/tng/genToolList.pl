#!/usr/bin/perl

use warnings;
use strict;
use File::Copy;

my %used;

my $toolDir = shift;
my $outputFileName = shift;
my @tools;

sub genToolList
{
	my $path = shift;
	my @allFiles = <*>;
	for my $path (@allFiles)
	{
		if (-d $path)
		{
			if ($path !~ /\.svn/i)
			{
				chdir $path;
				genToolList();
				chdir "../";
			}
		}
		else
		{
			if ($path =~ /\_v[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+/i)
			{
				my $name = $`;
				my $found = 0;
				for my $tool (@tools)
				{
					if ($tool eq $name)
					{
						$found = 1;
					}
				}
				if ($found == 0)
				{
					push @tools, $name;
				}
			}
			else
			{
				print "bad tool version: $path\n";
			}
		}
	}

}

chdir "$toolDir";
genToolList($toolDir);
chdir "../";

my $any_tool = 1;
if ($#tools == -1)
{
	$any_tool = 0;
}

open(INFILE, "< $outputFileName") or die "cannot read \"$outputFileName\" file\n";
my @content=<INFILE>;
close(INFILE);

open(OUTPUT, "> $outputFileName") or die "cannot write \"$outputFileName\" file\n";
#print OUTPUT "\<\?xml version=\"1.0\" encoding=\"utf-8\"\?\>\n";
#print OUTPUT "<tools>\n";

my $found_cnt = 1;
my $last_line;
for my $line (@content)
{
	if ($line =~ /<\/name>/)
	{
		my $name = $`;
		my $found = 0;
		my $tool;
		my @new_tools;
		$name =~ s/<name>//;
		$name =~ s/\x20//g;
		$name =~ s/\x09//g;
		while ($#tools + 1)
		{
			$tool = pop (@tools);
			if ($tool eq $name)
			{
				$found = 1;
			}
			else
			{
				push @new_tools, $tool;
			}
		}
		@tools = reverse @new_tools;
		unless ($found == 1)
		{
			$found_cnt = -3;
		}
	}
	if (($line !~ /<\/tools>/) && ($found_cnt == 1))
	{
		print OUTPUT $line;
		$last_line = $line;
	}
	unless ($found_cnt == 1)
	{
		$found_cnt ++;
	}
}

if ($any_tool == 0)
{
	close(OUTPUT);
	open(OUTPUT, "> $outputFileName") or die "cannot write \"$outputFileName\" file\n";
	print OUTPUT "\<\?xml version=\"1.0\" encoding=\"utf-8\"\?\>\n";
	print OUTPUT "<tools>\n";
}

for my $tool (@tools)
{
	if ($last_line !~ /<tool_info>/)
	{
		print OUTPUT "	<tool_info>\n";
	}
	print OUTPUT "		<name>$tool</name>\n";
	print OUTPUT "		<release>NO</release>\n";
	print OUTPUT "	</tool_info>\n";
	$last_line = "	</tool_info>\n";
}
print OUTPUT "</tools>\n";
close(OUTPUT);
