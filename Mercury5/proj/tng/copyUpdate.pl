#!/usr/bin/perl

use File::Basename;
use File::Copy;
use File::Path;

sub END
{
	close INPUT_FILE;
}

die "Usage: genDeltaRelease delta_files.txt delta\n" if @ARGV != 2;

# open file handle
$input_file = shift (@ARGV);
open INPUT_FILE, "<$input_file"
	or die "files list $input_file not found\n";
	
$destDir = shift (@ARGV);	

print "Copy the updated files\n";
while (my $line = <INPUT_FILE>)
{
	chomp $line;
	my ($fname, $dir) =fileparse($line);

	if ($dir ne ".\/")
	{
		$newpath = sprintf("%s\/%s", $destDir , $dir);
		$newfile = sprintf("%s\/%s", $newpath , $fname);
		if (-d $dir)
		{
			if (-e $line)
			{
				if ($line =~ /\.mak/) 
				{
					#this is a mak file
					open MAK_FILE, "<$line" or die "cannot read \"$line\" file\n";
					my @content=<MAK_FILE>;
					close(MAK_FILE);
					for my $str (@content)
					{
						if ($str =~ /_src\.mak/)
						{
							chomp $str;
							$str =~ /include (.*)/;
							$updateMakFile = $1;
							my ($fname1, $dir1) =fileparse($updateMakFile);
							$newpath1 = sprintf("%s\/%s", $destDir , $dir1);
							$newfile1 = sprintf("%s\/%s", $newpath1 , $fname1);
							mkpath($newpath1,1,0755);
							copy($updateMakFile, $newfile1);
						}
					}
				} else
				{
					mkpath($newpath,1,0755);
					copy($line, $newfile);
				}
			}
		}
	} else
	{
		$newfile = sprintf("%s\/%s", $destDir , $fname);
		chomp $newfile;
		copy($fname, $newfile);
	}
}
