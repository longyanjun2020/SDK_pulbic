#!/usr/bin/perl

#use warnings;
use strict;
use Fcntl;
use File::Basename;

my $src_file = shift;
my $dst_file = shift;

my $src_dir = shift;
my $obj_dir = shift;

open (SRC_FILE, "< $src_file") or die "cannot read \"$src_file\" file\n";
open (OUT_FILE, "> $dst_file") or die "cannot write \"$dst_file\" file\n";

my $strreadline;
while(defined($strreadline = <SRC_FILE>))
{
	if (  ($strreadline =~ /\Q$src_dir\E/i  ) )
	{
		my  $out_modulename = substr ( $strreadline,index($strreadline, "$src_dir")+ length("$src_dir") ,255); 
		$out_modulename =  $obj_dir.$out_modulename;
		#print "$out_modulename\n";
		print OUT_FILE "$out_modulename";
	}
}
		
close(SRC_FILE);
close(OUT_FILE);
