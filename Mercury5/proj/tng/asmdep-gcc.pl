#!/usr/bin/perl

use strict;
use File::Basename;
use Getopt::Std;

my %options=();
getopts("q",\%options);

# get ASM command line set by "tpp.mak"
my $line = $ENV{ASM_LINE};
die "ASM_LINE not defined\n" if ($line eq "");

# get output file name and directory
my $out = shift;
my $dir = dirname($out);
my $tng = dirname($0);

# open output file
open(OUT, "> $out") or die "cannot write to \"$out\"\n";

# for each given source file
foreach my $asm (@ARGV)
{
	# create a object file name
	my $obj = "$dir/" . basename($asm);

	if ($asm =~  m/.+\.asm$/) {
		$obj =~ s/.asm$/.o/;
	} elsif ($asm =~ m/.+\.S$/) {
		$obj =~ s/.S$/.o/;
	} else {
		die "Unknown assembly file suffix $asm";
	}


	# complete command line with files names
	my $cmd = $line . " -E -MM -o $obj.d $asm";
	print "$0 calling: $cmd\n";

	 if($options{q}){
         system("$tng/trace.pl info warning_stop_off userout_off echo -e \"asmdep:\t\" $obj $asm");
     }else{
	system("$tng/trace.pl info warning_stop_off userout_on echo -e \"asmdep:\t\" $obj $asm");
     }
	# execute and save results
	my $result = `$cmd`;
	open (RESULT, "< $obj.d");
	my @lines = <RESULT>;
	close(RESULT);
#	$result =~ s/\r\n/\n/g;
#	print "$0 results:\n$result\n";
#	print OUT $result;
	print OUT @lines;
#	system("rm $obj.d");
}

close(OUT);
