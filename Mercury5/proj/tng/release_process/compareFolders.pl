#!/usr/bin/perl

#####
## SYNTAX:
## perl tng/release_process/compareFolders.pl oldFolder newFolder
#####

use warnings;
use strict;

my $oldFolder = shift;
my $newFolder = shift;
my $outBatch = "sc/customer/product/common/mak/release_mak/dellibs.bat";

my @fileArray;
my @oldFiles;
my @newFiles;

sub find
{
	my $pathname = shift;
	my @dir = <*>;
	
	for my $path (@dir)
	{
		if (-d $path)
		{
			chdir $path;
			print "find $pathname/$path\n";
			find("$pathname/$path");
			chdir "../";
		}
		elsif ($path =~ /\.lib$/)
		{
			push @fileArray, "$pathname/$path";
		}
	}
}

$oldFolder =~ s/\\/\//g;
print "===find $oldFolder\n";
chdir $oldFolder;
find($oldFolder);
@oldFiles = @fileArray;
my @tmpOld = split(/\//, $oldFolder);
for (0 ... $#tmpOld)
{
	chdir "../";
}

@fileArray = ();

$newFolder =~ s/\\/\//g;
print "===find $newFolder\n";
chdir $newFolder;
find($newFolder);
@newFiles = @fileArray;
my @tmpNew = split(/\//, $newFolder);
for (0 ... $#tmpNew)
{
	chdir "../";
}

my @batOld = ();
if (-e $outBatch)
{
	open(BAT_FILE, "$outBatch") or die "cannot read \"$outBatch\" file\n";
	@batOld=<BAT_FILE>;
	close(BAT_FILE);
}

open(BAT_FILE, ">> $outBatch") or die "cannot read \"$outBatch\" file\n";

for my $oldFile (@oldFiles)
{
	my $fileMatch = 0;
	my $oldFilePath = "";
	
	if ($oldFile =~ /\/libs\//)
	{
		$oldFilePath = $';
	}
	
	for my $newFile (@newFiles)
	{
		my $newFilePath = "";
		
		if ($newFile =~ /\/libs\//)
		{
			$newFilePath = $';
		}
		if ($oldFilePath eq $newFilePath)
		{
			$fileMatch = 1;
			last;
		}
	}
	
	if ($fileMatch == 0)
	{
		my $existFile = 0;
		for my $oldFileName (@batOld)
		{
			if ($oldFileName eq "rm -Rf sc/libs/$oldFilePath\n")
			{
				$existFile = 1;
				last;
			}
		}
		if ($existFile == 0)
		{
			print "Del lib: $oldFile\n";
			print BAT_FILE "rm -Rf sc/libs/$oldFilePath\n";
		}
	}
}

# del empty folders
#print BAT_FILE "\ndir $oldFolder /ad /b /s |sort /r >>d:kill.txt\n";
#print BAT_FILE "For /f %%i in (d:kill.txt) DO rd %%i\n";
#print BAT_FILE "echo y |del d:kill.txt\n";

close(BAT_FILE);

# merge dellibs.bat
my @libName = ();
for my $newFile (@newFiles)
{
	my $fileMatch = 0;
	my $newFilePath = "";
	
	if ($newFile =~ /\/libs\//)
	{
		$newFilePath = $';
	}
	
	for my $oldFile (@oldFiles)
	{
		my $oldFilePath = "";
		
		if ($oldFile =~ /\/libs\//)
		{
			$oldFilePath = $';
		}
		if ($oldFilePath eq $newFilePath)
		{
			$fileMatch = 1;
			last;
		}
	}
	
	if ($fileMatch == 0)
	{
		print "Add lib: $newFilePath\n";
		push @libName, $newFilePath;
	}
}

open(BAT_FILE, "$outBatch") or die "cannot read \"$outBatch\" file\n";
my @batContent=<BAT_FILE>;
close(BAT_FILE);

open(BAT_FILE, "> $outBatch") or die "cannot read \"$outBatch\" file\n";
for my $batLine (@batContent)
{
	my $libMatch = 0;
	for my $libLine (@libName)
	{
		if ($batLine =~ /$libLine/)
		{
			$libMatch = 1;
			last;
		}
	}
	if ($libMatch == 0)
	{
		print BAT_FILE $batLine;
	}
}
close(BAT_FILE);
