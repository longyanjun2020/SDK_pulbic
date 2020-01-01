#!/usr/bin/perl

#####
## SYNTAX:
## perl keepUnusedFiles.pl ReleaseConfigurations.xml keepFiles.log
#####

use warnings;
use strict;

# use module
use XML::Simple;
use Data::Dumper;
use File::Copy;

# ceate object
my $xml = new XML::Simple;

# read XML file
my $xmlFile = shift(@ARGV);
my $xmlData = $xml->XMLin($xmlFile, ForceArray=>1);	
my $logFile = shift(@ARGV);	

my $compareMatch = undef;
my @save_files = ();

open(LOG_FILE, "> $logFile") or die "cannot write\"$logFile\" file\n";	

if (-e "sc/customer/product/cust/saveLCMBase.txt")
{
	open(LCM_FILE, "sc/customer/product/cust/saveLCMBase.txt");
	@save_files=<LCM_FILE>;
	close(LCM_FILE);
}
else
{
	print LOG_FILE "sc/customer/product/cust/saveLCMBase.txt does not exist!\n";
}

open(NOMAKE_FILE, "> noMakeFiles.txt") or die "cannot write\"noMakeFiles.txt\" file\n";

#get values of key "make"	of the chk xml data
my $MakeArrayPtr = $xmlData->{"make"};	
my @RelFileArray = ();
my @libFileArray = ();
my @rel_files = ();

sub compareFiles
{
	my $cFile = shift;
	for (0 ... $#RelFileArray)
	{
		if ($RelFileArray[$_] eq $cFile)
		{
			return 1;
		}
	}
	for (0 ... $#libFileArray)
	{
		if ($libFileArray[$_] eq $cFile)
		{
			return 2;
		}
	}
	return 9;
}

sub compareFolders
{
	my $folderName = shift;
	for (0 ... $#rel_files)
	{
		$rel_files[$_] =~ s/\///g;
		$folderName =~ s/\///g;
		$rel_files[$_] =~ s/\x0d\x0a//ig;
		if ($folderName =~ /$rel_files[$_]/)
		{
			return 1;
		}
	}
}

#compare with "backup_src", if matched, cp to "sc"
sub parseFolder
{
	my $destinationPath = shift;
	my @cFiles = <*>;
	for my $path (@cFiles)
	{
		my $flag = 0;
		if (-d $path)
		{
			if ($path eq "test")
			{
				last;
			}
			unless(-e "$destinationPath/$path")
			{
				mkdir ("$destinationPath/$path");
			}
			if (compareFolders("$destinationPath/$path"))
			{
				print "Copy ", $path, " to ", $destinationPath, "\n";
				system("cp -r $path $destinationPath/");
				$flag = 1;
			}
			unless ($flag)
			{
				chdir $path;
				parseFolder("../$destinationPath/$path");
				chdir "../";
			}
			if ($destinationPath =~ /customer\/product\/cust/)
			{
				rmdir ("$path");
				rmdir ("$destinationPath/$path");
			}
			
			my $lcm_flag = 0;
			if ($destinationPath =~ /customer\/product\/cust\/drv\/lcm/)
			{
				for my $line (@save_files)
				{
					if ($line =~ /$path/)
					{
						$lcm_flag = 1;
					}
				}
				if ($lcm_flag == 0)
				{
					if ($path =~ /_base$/)
					{
						print LOG_FILE "rmdir: $destinationPath/$path\n";
						system("rm -r $path");
						system("rm -r $destinationPath/$path");
					}
				}
			}
		}
		else
		{
			if ($path =~ /\.c$/ || $path =~ /\.asm/ || $path =~ /\.S$/)
			{
				my $relResult = compareFiles($path);
				if (1 == $relResult)
				{
					print LOG_FILE "Copy ", $path, " to ", $destinationPath, "\n";
					copy($path,"$destinationPath/$path");
				}
				elsif (2 == $relResult)
				{
					print LOG_FILE "Del $path and $destinationPath/$path\n";
					system("rm -rf $path");
					system("rm -rf $destinationPath/$path");
				}
				elsif (9 == $relResult)
				{
					my $noMakPath = "$destinationPath/$path";
					if ($noMakPath =~ /\/rel_src\//)
					{
						print NOMAKE_FILE "$'\n";
					}
				}
			}
		}
	}
}

#get "REL_SRC_C_LIST" file name
foreach (@$MakeArrayPtr)
{
	my $makeData = $_;
	my $fileArrayPtr = $makeData->{"file"};
	my @fileArray = @$fileArrayPtr;
	for (0 ... $#fileArray)
	{
		if ($fileArray[$_]->{"default_value"}->[0] =~ /REL_SRC_/)
		{
			push @RelFileArray, $fileArray[$_]->{"file_name"}->[0];
		}
		elsif ($fileArray[$_]->{"default_value"}->[0] =~ /SRC_/)
		{
			push @libFileArray, $fileArray[$_]->{"file_name"}->[0];
		}
	}
}

chdir "sc";
if (-e "../tng/release_process/releaseFolders.txt")
{
	open(REL_FILE, "../tng/release_process/releaseFolders.txt") or die "cannot read \"release_process/releaseFolders.txt\" file\n";
	@rel_files=<REL_FILE>;
	close(REL_FILE);
}
else
{
	print LOG_FILE "cannot read \"release_process/releaseFolders.txt\" file\n";
}
parseFolder("../rel_src/sc");
chdir "../";

close (LOG_FILE);	
close (NOMAKE_FILE);
