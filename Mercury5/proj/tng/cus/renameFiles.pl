#!/usr/bin/perl

use warnings;
use strict;
use Cwd;

my $bd = shift || "";
my $backdoor = "Yes_BD";

my $currentPath = cwd();

if ($currentPath =~ /\/proj/)
{
	$currentPath =~ s/$&//;
	$currentPath =~ s/$'//;
}

if (-e "$currentPath/proj/tng/cus/Delete_Details.txt")
{
	open(TXT_FILE, "$currentPath/proj/tng/cus/Delete_Details.txt") or die "cannot read \"Delete_Details.txt\" file\n";
	my @content=<TXT_FILE>;
	close(TXT_FILE);
	
	open(LOG_FILE, "> $currentPath/proj/tng/cus/Rename_Files.log") or die "cannot read \"Rename_Files.log\" file\n";
	
	my $existFlag = 0;
	
	print "\nRename files:\n";
	for (0 ... $#content)
	{
		$content[$_] =~ s/\x0d\x0a//;
		$content[$_] =~ s/^Del .//;
		$content[$_] =~ s/\\/\//g;
		if (-e "$currentPath$content[$_]")
		{
			print "$content[$_]\n";
			$existFlag = 1;
		}
	}
	
	if ($existFlag == 1)
	{
		print "\nRename all files? (or it will result build fail) [y/n]: ";
		
		my $in = "";
		if ($bd ne $backdoor)
		{
			chomp($in = <STDIN>);
		}
		else
		{
			$in = "y";
			print "Y\n";
		}
		
		if (($in eq "y") or ($in eq "Y"))
		{
			for (0 ... $#content)
			{
				if (-e "$currentPath$content[$_]")
				{
					print LOG_FILE "--Rename $content[$_] to $content[$_]\.backup\n";
					system("mv $currentPath$content[$_] $currentPath$content[$_]\.backup");
				}
			}
			print "\nRename all *.* files to *.*.backup \n(see $currentPath/proj/tng/cus/Rename_Files.log for more detail)\n";
		}
		else
		{
			print "\nThese files are not be renamed!\n";
		}
	}
	
	close(LOG_FILE);
}