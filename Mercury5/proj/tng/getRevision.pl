#!/usr/bin/perl

sub END
{
	close INPUT_FILE;
	close OUTUPUT_FILE;
}

die "Usage: GenRevision rev.log ReleaseRevision \n" if @ARGV != 2;

# open file handle
$input_file = shift (@ARGV);
open INPUT_FILE, "<$input_file"
	or die "SVN log file $input_file not found\n";

$REV_NAME = shift (@ARGV);
	
$output_file = "../export_rev.txt";
if (-e $output_file)
{
open OUTUPUT_FILE, ">>$output_file"
	or die "$output_file can not be created\n";
} else
{
open OUTUPUT_FILE, ">$output_file"
	or die "$output_file can not be created\n";
}
	
while (<INPUT_FILE>)
{
	chomp;

	if (/^r(\d*)/)
	{
		$buffer = sprintf("%s=%s", $REV_NAME, $1);
		print OUTUPUT_FILE "$buffer\n";
	}
		
}