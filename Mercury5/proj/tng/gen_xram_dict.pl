#/usr/bin/perl -w

use warnings;
use strict;
use diagnostics;
use Math::BigFloat;

my $lnkinf_file = $ARGV[0];
my $xram_base = $ARGV[1];
my $in_file = $ARGV[2];
my $out_file = $ARGV[3];
my $xram_dict_size;
my $str_cmd;

	open(LINKINFFILE, "<".$lnkinf_file) or die "Can't open link info file: $!";
	while (<LINKINFFILE>) {
		chomp;
		if (/Execution Region XRAM_RO_END.+Base: 0x(\S+),/) {
			$xram_dict_size = hex($1) - hex($xram_base);
			$str_cmd = "head -c " . $xram_dict_size . " " . $in_file . " > " . $out_file;
			system($str_cmd);
		}
	}

	close LINKINFFILE;
