#/usr/bin/perl -w

use warnings;
use strict;
use diagnostics;
use Math::BigFloat;

my $token_idx;
my @token_text;
my $header_len;
my $dlm_name;
my $in_file = $ARGV[0];
my $exec_reg = $ARGV[1];
my $lnkinf_file = $ARGV[2];
my $out_file = $ARGV[3];

	open(OUTFILE, ">".$out_file) or die "Can't open output header file: $!";
	binmode OUTFILE;

	$header_len = 40;
	my $text_sect_size = -s $in_file;
	my $bss_sect_size = 0;

	open(LINKINFFILE, "<".$lnkinf_file) or die "Can't open link info file: $!";
	while (<LINKINFFILE>) {
		chomp;
		if (/Execution Region (\S+).+Size: 0x(\S+),/) {
			if ($1 eq $exec_reg) {
				$bss_sect_size = $2;
			}
		}
	}

	print OUTFILE pack("A4", "DLMS"); 						# char Magic[DLM_MAGIC_LENGTH];
  print OUTFILE pack("I", $header_len);					# unsigned int  Header_Length;
	print OUTFILE pack("A12", "NULL");						# char DLM_Name[DLM_NAME_LENGTH];
	print OUTFILE pack("I", $text_sect_size);			# unsigned int  Text_Size;
	print OUTFILE pack("I", 0);										# unsigned int  Data_Size;
	print OUTFILE pack("I", hex($bss_sect_size));	# unsigned int  Bss_Size;
  print OUTFILE pack("I", 0);									 	# unsigned int  Num_Function;
  print OUTFILE pack("I", 0); 									# unsigned int  checkSum;

	close OUTFILE;
	close LINKINFFILE;
