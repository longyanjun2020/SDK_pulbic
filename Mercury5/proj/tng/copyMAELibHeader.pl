#!/usr/bin/perl

#use warnings;
#use strict;
use File::Copy;

# the source directory
my $SrcDir = shift;

# the destination directory
my $DestDir = shift;


sub copyLibHeaderFiles
{
	my $sourcePath = shift;
	my $destinationPath = shift;

	my @allFiles = <$sourcePath/*>;
	for my $path (@allFiles)
	{
		#print "$path\n";#test code
		my $last_slash = rindex($path, "/");

		if (-d $path)
		{
			my $DirName = substr($path, $last_slash + 1);

			unless(-e "$destinationPath/$DirName")
			{
				print "try to make dir $destinationPath/$DirName\n";#test code
				mkdir ("$destinationPath/$DirName");
			}
			copyLibHeaderFiles($path, "$destinationPath/$DirName");
		}
		else
		{
			my $FileName = substr($path, $last_slash + 1);
			if (($path =~ /\.h$/) || ($path =~ /\.lib$/))
			{
				print "copy $path to $destinationPath/$FileName\n";#test code
				copy($path, "$destinationPath/$FileName");
			}
		}
	}

}

if ((-d $SrcDir) && (-d $DestDir))
{
	copyLibHeaderFiles($SrcDir, $DestDir);
}