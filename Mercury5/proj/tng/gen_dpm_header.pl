#/usr/bin/perl -w

use warnings;
use strict;
use diagnostics;
use Math::BigFloat;

my @export_funcs;
my $token_idx;
my @token_text;
my $header_len;
my $dpm_name = $ARGV[0];
my $in_file = $ARGV[1];
my $intf_file = $ARGV[2];
my $out_file = $ARGV[3];

sub strLittleEndian
{	
		my $str_le;
		$str_le = sprintf ("%s%s%s%s", substr($_[0], 6, 2), substr($_[0], 4, 2), substr($_[0], 2, 2), substr($_[0], 0, 2));
		return $str_le;
}

	if ($intf_file ne "NULL") {
		open(INTFFILE, "<".$intf_file) or die "Can't open interface file: $!";

		while (<INTFFILE>) {
			chomp;
			if (/#define\s+DPM_NAME\s+(\S+)/) {
				$dpm_name = $1;
			}
			elsif (/#define\s+(\S+)\s+(\S+)/) {
				push @export_funcs, $1;
			}	
		}
		close INTFFILE;
	}

	open(OUTFILE, ">".$out_file) or die "Can't open output header file: $!";
	binmode OUTFILE;

	$header_len = 40 + ($#export_funcs + 1) * 4;
	my $text_sect_size = -s $ARGV[4];
	my $data_sect_size = -s $ARGV[5];

	print OUTFILE pack("A4", "DLMG"); 						# char Magic[DPM_MAGIC_LENGTH]; DLMG for G1 files
  print OUTFILE pack("I", $header_len);					# unsigned int  Header_Length;
	print OUTFILE pack("A12", $dpm_name);					# char DPM_Name[DPM_NAME_LENGTH];
	print OUTFILE pack("I", $text_sect_size);			# unsigned int  Text_Size;
	print OUTFILE pack("I", $data_sect_size);			# unsigned int  Data_Size;
	print OUTFILE pack("I", 0);										# unsigned int  Bss_Size;
  print OUTFILE pack("I", $#export_funcs + 1); 	# unsigned int  Num_Function;
  print OUTFILE pack("I", 0); 									# unsigned int  checkSum;

	for ($token_idx = 0; $token_idx <= $#export_funcs; $token_idx++) {
		if ($in_file ne "NULL") {
			open(INFILE, "<".$in_file) or die "Can't open input nm file: $!";

			while (<INFILE>) {
				chomp;
				if (/(\S+)\s+(\S+)\s+(\S+)/) {
					if ($3 eq $export_funcs[$token_idx]) {
          	print OUTFILE pack("H8", strLittleEndian($1));
					}
				}
			}
			close INFILE;
		}
	}
close OUTFILE;