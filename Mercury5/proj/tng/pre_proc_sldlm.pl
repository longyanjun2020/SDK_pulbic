#/usr/bin/perl -w

use warnings;
use strict;
use diagnostics;
use Math::BigFloat;

my $lnkinf_file = $ARGV[0];
my $output_dir = $ARGV[1];
my $str_last6;
my $str_cmd;

	open(LINKINFFILE, "<".$lnkinf_file) or die "Can't open link info file: $!";
	while (<LINKINFFILE>) {
		chomp;
		if (/Execution Region (\S+).+Size: 0x(\S+),/) {
			if ($2 eq '00000000') {
				$str_last6 = substr($1, length($1) - 6, 6);				
				if ($str_last6 eq '.sldlm') {
					print $1;
					print "\n";
					$str_cmd = "touch " . $output_dir . $1;
					print $str_cmd;
					print "\n";
					system($str_cmd);
				}
			}
		}
	}

	close LINKINFFILE;