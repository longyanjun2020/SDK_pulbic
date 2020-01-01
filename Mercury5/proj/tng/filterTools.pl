#!/usr/bin/perl

use warnings;
use strict;
use File::Copy;

my %used;

my $toolDir = shift;
my $toolSettings = shift;

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
	elsif ($version1 < $version2)
	{
		return 2;
	}
	return 0;
}

my @releaseTools;

sub getToolSettings
{
	my $settingFile = shift;
	open(SETTING_FILE, "< $settingFile") or die "cannot read \"$settingFile\" file\n";
	my @settingContent=<SETTING_FILE>;
	close(SETTING_FILE);
	
	my $idx;
	for($idx=0; $idx<=$#settingContent; $idx++)
	{
		my $line = $settingContent[$idx];
		if ($line =~ /<tool_info>/)
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
						print "release tool $filename\n";
						push @releaseTools, $filename;
					}
				}
			}
		}
	}
}

sub filterTools
{
	my @tools;

	my @allFiles = <*>;
	for my $path (@allFiles)
	{
		if (-d $path)
		{
			if ($path !~ /\.svn/i)
			{
				chdir $path;
				filterTools();
				chdir "../";
			}
		}
		else
		{
			if ($path =~ /\_v[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+/i)
			{
				my $name = $`;
				my $version = $&;
				my $release = 0;
				
				for my $tool (@releaseTools)
				{
					if ($name eq $tool)
					{
						$release = 1;
					}
				}
				
				if ($release == 1)
				{
					my $found = 0;
					my @versions = split(/\./,$version);
					my $toolIdx;
					for($toolIdx=0; $toolIdx<=$#tools; $toolIdx++)
					{
						my $tool = $tools[$toolIdx];
						if ($tool =~ /$name/)
						{
							if ($tool =~ /\_v[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+/i)
							{
								$found = 1;
								my $tmpVersion = $&;
								my @tmpVersions = split(/\./, $tmpVersion);
								my $compareResult = 0;
								
								my $idx;
								for($idx=0; $idx<=$#versions; $idx++)
								{
									if ($compareResult == 0)
									{
										my $subVersion = $versions[$idx];
										my $subTmpVersion = $tmpVersions[$idx];
										$compareResult = compareVersion($subVersion, $subTmpVersion);
									}
								}
								
								if ($compareResult == 1)
								{
									print "replace $tool by $path\n";
									unlink $tool;
									delete $tools[$toolIdx];
									push @tools, $path;
								}
							}
						}
					}
					if ($found == 0)
					{
						push @tools, $path;
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
				print "bad tool version: $path\n";
				unlink $path;
			}
		}
	}
}

getToolSettings($toolSettings);
chdir "$toolDir";
filterTools();
