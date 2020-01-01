#!/usr/bin/perl

use warnings;
use strict;

my $output = shift;
open OUT, "> $output" or die "cannot write to \"$output\"\n";

print OUT << "EOT";
#define __MOKA_DESCR_EEPROM__

#if defined(__GNUC__)
/* [Workaround]Pass the syntax checking of e2p parser */
typedef struct __va_list { void *__ap; } __builtin_va_list;
#endif

EOT

foreach my $name (@ARGV)
{
	print OUT "#include \"$name\"\n";
}
close OUT;
