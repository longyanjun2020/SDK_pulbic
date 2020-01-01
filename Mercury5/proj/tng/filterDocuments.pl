#!/usr/bin/perl

use warnings;
use strict;
use File::Copy;
use Archive::Zip qw( :ERROR_CODES :CONSTANTS );

my %used;

my $docDir = shift;
my $docSettings = shift;

sub compareVersion
{
	my $version1 = shift;
	my $version2 = shift;
	
	$version1 =~ s/\_v//i;
	if ($version1 =~ /\./)
	{
		$version1 = $`;
	}
	
	$version2 =~ s/\_v//i;
	if ($version2 =~ /\./)
	{
		$version2 = $`;
	}
	
	if ($version1 > $version2)
	{
		return 1;
	}
	return 0;
}

my @releaseDocs;

sub getDocSettings
{
	my $settingFile = shift;
	open(SETTING_FILE, "< $settingFile") or die "cannot read \"$settingFile\" file\n";
	my @settingContent=<SETTING_FILE>;
	close(SETTING_FILE);
	
	my $idx;
	for($idx=0; $idx<=$#settingContent; $idx++)
	{
		my $line = $settingContent[$idx];
		if ($line =~ /<doc_info>/)
		{
			$idx++;
			my $filename = $settingContent[$idx];
			if ($filename =~ /<name>[0-9a-zA-Z_]+<\/name>/)
			{
				$idx++;
				$filename =~ s/<name>//;
				$filename =~ s/<\/name>//;
				$filename =~ s/\x09|\x0a|\x0d//g;
				my $release = $settingContent[$idx];
				if ($release =~ /yes|no/i)
				{
					$release = $&;
					if (($release eq "yes") || ($release eq "YES"))
					{
						push @releaseDocs, $filename;
					}
				}
			}
		}
	}
}

sub filterDocuments
{
	my @documents;

	my @allFiles = <*>;
	for my $path (@allFiles)
	{
		if (-d $path)
		{
			if ($path !~ /\.svn/i)
			{
				chdir $path;
				filterDocuments();
				chdir "../";
			}
		}
		else
		{
			if ($path =~ /\_v[0-9]+\./i)
			{
				my $name = $`;
				my $version = "$&"."$'";
				my $release = 0;
				
				print "found document $path\n";
				for my $doc (@releaseDocs)
				{
					if ($name eq $doc)
					{
						$release = 1;
					}
				}
				
				if ($release == 1)
				{
					my $found = 0;
					my $documentIdx;
					for ($documentIdx=0; $documentIdx<=$#documents; $documentIdx++)
					{
						my $document = $documents[$documentIdx];
						if ($document =~ /$name/)
						{
							$found = 1;
							my $tmpVersion = $';
							my $compareResult = compareVersion($version, $tmpVersion);
							if ($compareResult == 1)
							{
								print "replace $document by $path\n";
								unlink $document;
								delete $documents[$documentIdx];
								push @documents, $path;
							}
						}
					}
					if ($found == 0)
					{
						push @documents, $path;
					}
				}
				else
				{
					print "not release: $path\n";
					unlink $path;
				}
			}
			else
			{
				print "bad document version: $path\n";
				unlink $path;
			}
		}
	}
}

sub findCompressFiles
{
	my @zipFiles = <*>;
	for my $path (@zipFiles)
	{
		if (-d $path)
		{
			chdir $path;
			findCompressFiles();
			chdir "../";
		}
		elsif ($path =~ /\.zip/i)
		{
			my $obj = Archive::Zip->new();# new instance
			my $status = $obj->read($path);# read file contents

			if ($status != AZ_OK) {
				die('Error in file!');
			} else {
				$obj->extractTree(undef, );# extract files
			}
			unlink $path;
		}
	}
}

getDocSettings($docSettings);
chdir "$docDir";
filterDocuments();
findCompressFiles();
