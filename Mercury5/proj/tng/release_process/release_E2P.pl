#!/usr/bin/perl

#####
## SYNTAX:
## perl tng/release_process/release_E2P.pl tng/release_process/E2P_list.txt vt_false
#####

use warnings;
use strict;
use Cwd;

my $e2pList = shift;
my $vtBuild = shift || "vt_false";

my $fileName = "";
my $pattern = "";
my $lineNum = "";
my $oldVal = "";
my $newVal = "";

print "vtBuild: $vtBuild\n";

sub modifyE2P
{
	my @fileName_s = ();

	my @fname = split(/\//, $fileName);
	my $path = $fileName;
	if ($fileName =~ /\*/)
	{
		$fname[$#fname] =~ s/\*/\\\*/g;
	}
	$path =~ s/$fname[$#fname]//;
	
	if ($fileName =~ /\*/)
	{
		$fname[$#fname] =~ s/\\\*/\*/g;
	}
	
	chdir $path;
	if ($fileName =~ /\*/)
	{
		@fileName_s = <$fname[$#fname]>;
	}
	else
	{
		$fileName_s[0] = $fname[$#fname];
	}
	
	for (0 ... $#fileName_s)
	{
		my $nextLineFlag = 0;
		my $nextLineCnt = 0;
		
		open(E2P_FILE, "$fileName_s[$_]") or die "cannot read \"$fileName_s[$_]\" file\n";
		my @content=<E2P_FILE>;
		close(E2P_FILE);
		
		open(E2P_FILE, "> $fileName_s[$_]") or die "cannot read \"$fileName_s[$_]\" file\n";
		print "$fileName_s[$_]\n";
		for my $line (@content)
		{
			if ($line =~ /$pattern/) 
			{
				$nextLineFlag = 1;
				if (($pattern eq "WMpRelease") && ($vtBuild eq "vt_true"))
				{
					$nextLineFlag = 0;
				}
			}
			else
			{
				if($nextLineFlag == 1) 
				{
					$nextLineCnt ++;
					if ($nextLineCnt == $lineNum)
					{
						$nextLineFlag = 0;
						if ($vtBuild eq "vt_false")
						{
							if ($line =~ /$oldVal/)
							{
								#$line =~ s/$oldVal/$newVal/;
								$line = "$newVal\n";
								print "change $pattern value line $lineNum from $oldVal to $newVal\n\n";
							}
						}
						elsif ($vtBuild eq "vt_true")
						{
							if ($line =~ /$newVal/)
							{
								#$line =~ s/$newVal/$oldVal/;
								$line = "$oldVal\n";
								print "change $pattern value line $lineNum from $newVal to $oldVal\n\n";
							}
						}
					}
				}
			}
			print E2P_FILE $line;
		}
		close(E2P_FILE);
	}
}

# main function
open(E2P_LIST, "$e2pList") or die "cannot read \"$e2pList\" file\n";
my @e2pContent=<E2P_LIST>;
close(E2P_LIST);

my $pwd = cwd();

for my $listLine(@e2pContent)
{
	$listLine =~ s/\x0d\x0a//ig;
	if (($listLine !~ /^#/) && (length($listLine) != 0))
	{
		chdir $pwd;
		
		my @listParams = split(/ /, $listLine);
		$fileName = $listParams[0];
		$pattern = $listParams[1];
		$lineNum = $listParams[2];
		$oldVal = $listParams[3];
		$newVal = $listParams[4];
		
		modifyE2P();
	}
}

