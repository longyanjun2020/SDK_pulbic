#!/usr/bin/perl

use warnings;
use strict;

my %used;

my $pattern = "#code release machine commands";

sub parseReleaseNote
{
	my $command = shift;
	my $releaseNote = shift;
	my $bashFile = shift;

	my $currentDir;
	if ($command =~ /\/RELEASE_SHELL/)
	{
		open(RELEASE_NOTE, "< $releaseNote") or die "cannot read \"$releaseNote\" file\n";
		my @content=<RELEASE_NOTE>;
		close(RELEASE_NOTE);
		
		for my $line (@content)
		{
			if ($line =~ /CurrentDirectory\=/)
			{
				$currentDir = $';
				$currentDir =~ s/\x0d\x0a//g;
			}
		}
		writeReleaseCmd($bashFile, $currentDir);
	}
	elsif ($command =~ /\/CLEAN_SHELL/)
	{
		open(RELEASE_NOTE, "< $releaseNote") or die "cannot read \"$releaseNote\" file\n";
		my @content=<RELEASE_NOTE>;
		close(RELEASE_NOTE);
		
		for my $line (@content)
		{
			if ($line =~ /CurrentDirectory\=/)
			{
				$currentDir = $';
				$currentDir =~ s/\x0d\x0a//g;
			}
		}
		writeCleanCmd($bashFile, $currentDir);
	}
	elsif ($command =~ /\/OFF_SHELL/)
	{
		open(RELEASE_NOTE, "< $releaseNote") or die "cannot read \"$releaseNote\" file\n";
		my @content=<RELEASE_NOTE>;
		close(RELEASE_NOTE);
		
		for my $line (@content)
		{
			if ($line =~ /CurrentDirectory\=/)
			{
				$currentDir = $';
				$currentDir =~ s/\x0d\x0a//g;
			}
		}
		writeOffCmd($bashFile, $currentDir);
	}
	elsif ($command =~ /\/CLEAN_ALL/)
	{
		cleanFile($bashFile);
	}
}

sub cleanFile
{
	my $bashFile = shift;
	my $foundPattern = 0;
	
	open(RELEASE_NOTE, "< $bashFile") or die "cannot read \"$bashFile\" file\n";
	my @content=<RELEASE_NOTE>;
	close(RELEASE_NOTE);
	
	open(OUTPUT_FILE, "> $bashFile") or die "cannot read \"$bashFile\" file\n";
	for my $line (@content)
	{
		if ($foundPattern == 0)
		{
			print OUTPUT_FILE $line;
		}
		
		if ($line =~ /$pattern/)
		{
			$foundPattern = 1;
		}
	}
	close(OUTPUT_FILE);
}

sub writeReleaseCmd
{
	my $bashFile = shift;
	my $currentDir = shift;

	my $foundPattern = 0;
	open(OUTPUT_FILE, "< $bashFile") or die "cannot read \"$bashFile\" file\n";
	my @content=<OUTPUT_FILE>;
	close(OUTPUT_FILE);

	my $data = $';
	$data =~ s/\"//g;
	open(OUTPUT_FILE, "> $bashFile") or die "cannot read \"$bashFile\" file\n";
	for my $line (@content)
	{
		if ($line =~ /$pattern/)
		{
			$foundPattern = 1;
		}
		print OUTPUT_FILE $line;
	}
	if ($foundPattern == 1)
	{
		print OUTPUT_FILE "\n";
		print OUTPUT_FILE "cd $currentDir\n";
		print OUTPUT_FILE "./auto_release.sh > auto_release_out.log \n";
		print OUTPUT_FILE "exit\n";
	}
	close(OUTPUT_FILE);
}

sub writeCleanCmd
{
	my $bashFile = shift;
	my $currentDir = shift;

	my $foundPattern = 0;
	open(OUTPUT_FILE, "< $bashFile") or die "cannot read \"$bashFile\" file\n";
	my @content=<OUTPUT_FILE>;
	close(OUTPUT_FILE);

	my $data = $';
	$data =~ s/\"//g;
	open(OUTPUT_FILE, "> $bashFile") or die "cannot read \"$bashFile\" file\n";
	for my $line (@content)
	{
		if ($line =~ /$pattern/)
		{
			$foundPattern = 1;
		}
		print OUTPUT_FILE $line;
	}
	if ($foundPattern == 1)
	{
		print OUTPUT_FILE "\n";
		print OUTPUT_FILE "cd $currentDir\n";
		print OUTPUT_FILE "./clean.sh > clean_out.log \n";
		print OUTPUT_FILE "exit\n";
	}
	close(OUTPUT_FILE);
}

sub writeOffCmd
{
	my $bashFile = shift;
	my $currentDir = shift;

	my $foundPattern = 0;
	open(OUTPUT_FILE, "< $bashFile") or die "cannot read \"$bashFile\" file\n";
	my @content=<OUTPUT_FILE>;
	close(OUTPUT_FILE);

	my $data = $';
	$data =~ s/\"//g;
	open(OUTPUT_FILE, "> $bashFile") or die "cannot read \"$bashFile\" file\n";
	for my $line (@content)
	{
		if ($line =~ /$pattern/)
		{
			$foundPattern = 1;
		}
		print OUTPUT_FILE $line;
	}
	if ($foundPattern == 1)
	{
		print OUTPUT_FILE "\n";
		print OUTPUT_FILE "cd $currentDir\n";
		print OUTPUT_FILE "./off.sh > off_out.log \n";
		print OUTPUT_FILE "exit\n";
	}
	close(OUTPUT_FILE);
}

# get command /G generate bashrc, /C clean bashrc
my $cmd = shift;

# get target file name
my $output = shift;

# get release notes
my $notes = shift;

parseReleaseNote($cmd, $notes, $output);