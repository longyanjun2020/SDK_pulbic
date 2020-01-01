#!/usr/bin/perl
#---------------------------------------------------------------------------------------------
#
#             AIT Multimedia Network - CHP Compiler (C-language personal Home Page)
#                     (c) Copyright 2012, Alpha Imaging Technology Corp.
#               All rights reserved. Protected by international copyright laws.
#
#---------------------------------------------------------------------------------------------

use strict;
use Getopt::Std;
use File::Basename;

#---------------------------------------------------------------------------------------------
my $usage =<<EOF;
USAGE: $0  [OPTION]...  <CHP_FILE | CHP_PATH>

	Parsing the CHP file (C-language personal Home Page) into a C source

Options:
	-o file_path : output path or filename for all the generated CHP-C files
	-d <n> : enable debug for phase <n>
	-h : this help message
	CHP_FILE : input single compiling CHP file
	CHP_PATH : input compiling CHP path

Example:
	cd Firmware/NET
	bin/chp-compile.pl -o http/chp_C/ http/chp/
	bin/chp-compile.pl -o http/chp_C/multi-sel1.chp.c http/chp/multi-sel1.chp
EOF
	;


#---------------------------------------------------------------------------------------------
my %options=();
my ($inPath, $outPath, $debug);

get_options();
check_options();

#---------------------------------------------------------------------------------------------
my ($outALL);
my (@htmls, @codes, $outFP, $outALL);

if (substr( $inPath, -1, 1 ) eq "/") {
	$inPath = substr( $inPath, 0, -1 );

	if (substr( $outPath, -1, 1 ) eq "/") {
		$outPath = substr( $outPath, 0, -1 );
	}
	system("mkdir $outPath") if ! -d $outPath;
	open($outALL, ">", "$outPath/includes-all.c") or die "Can't open $outPath/includes-all.c: $!";

	printf $outALL <<EOF;
// THIS IS AUTOMATICALLY GENERATED FILE, DON'T EDIT IT !!!
// be sure to add "Firmware/NET/http/chp_C/" in the include path !!!

#include "inc/chp_engine.h"
EOF

	# input CHP source files: path
	my @files = glob("$inPath/*.chp");
	my $count = 0;
	foreach my $file (@files) {
        my $fname = basename($file); chomp $fname;
		compile_chp( "$inPath/$fname", "$outPath/$fname.c" );
		printf $outALL "#include \"$fname.c\"\n";
		if ($count++ == 0) {
			printf $outALL "\n#ifndef FILE_MAN__GETINFO\n";
			printf $outALL "#error If you are reading this while building, please run Prelude_MCP.bat. There should be one in your MCP folder.\n";
			printf $outALL "#endif\n\n";
		}
	}

	printf $outALL <<EOF;

void init_all_CHP_handlers()
{
EOF
	foreach my $file (@files) {
		my $fname = basename($file, ".chp");  chomp $fname;  # multi-sel1.chp
		my $ucFName = uc $fname;
		$ucFName =~ s/-/_/g;                               # MULTI_SEL1
		printf $outALL "\tregister_CHP_servlets( \"/cgi-bin/$fname.cgi\", ${ucFName}__WEB_READ, ${ucFName}__GETINFO );\n";
	}
	printf $outALL <<EOF;
}

EOF
}
else {
	# input CHP source file: single file
	compile_chp( $inPath, $outPath );
}

# Generate the inclues-all.c file
#---------------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------------
sub get_options() {
	if (!getopts("ho:d:",\%options) || $options{'h'}) {
		print $usage;
		exit 0;
	}
}

sub check_options() {
	$debug = 0;
	if ($options{'d'}) {
		$debug = $options{'d'};
	}

	$outPath = "";
	if ($options{'o'}) {
		$outPath = $options{'o'};
	}

	# Input CHP source: mixed HTML+C codes
	$inPath = $ARGV[0];
	die "input CHP file/path: $inPath doesn't exist !!" if ! -e $inPath;
}


# Compiling the CHP source file
#---------------------------------------------------------------------------------------------
sub normalize_chpName($)
{
	my $inName = $_;                                         # http/chp/multi-sel1.chp
	my $srcName = basename($inName, ".chp"); chomp $srcName; # multi-sel1.chp
	my $ucSrcName = uc $srcName;
	$ucSrcName =~ s/-/_/g;                                   # MULTI_SEL1
	return ( $srcName, $ucSrcName );
}

sub compile_chp($$)
{
	my ($inName, $outName) = @_;  # fullpath input / output file names

	open($outFP, ">", $outName) or die "Can't open $outName: $!";

	my $inFP;
	open($inFP,  "<", $inName)  or die "Can't open $inName: $!";

	# $srcName -> symbolized name: $ucSrcName
#	my ($srcName, $ucSrcName) = normalize_chpName( $inName );
	my $srcName = basename($inName, ".chp"); chomp $srcName; # multi-sel1.chp
	my $ucSrcName = uc $srcName;
	$ucSrcName =~ s/-/_/g;                                   # MULTI_SEL1

	my ($html, $code, $in_chp, $csub, $chp_wread_start, $has_getinfo);

	$in_chp = 0;
	$chp_wread_start = -1;
	$has_getinfo = 0;

	printf $outFP "// THIS IS AUTOMATICALLY GENERATED FILE, DON'T EDIT IT !!!\n\n";

	while (<$inFP>) {
		chomp;

		# Only parsing <?csub ... ?> at the very beginning of CHP codes
		#-------------------------------------------------------------
		if ($chp_wread_start < 0) {
			if ($_ =~ /\<\?[cC][sS][uU][bB]/) {
				$chp_wread_start = -2;
				@codes = ();
				next;
			}
			elsif ($_ =~ /\?\>/) {
				output_codes("", $ucSrcName);
				$chp_wread_start = 0;
				next;
			}
			elsif ($_ =~ /\s*int\s*CHP_GETINFO\s*\(\s*\)\s*/) {
				$has_getinfo = 1;
				push @codes, "int ${ucSrcName}__GETINFO( IN struct cgi_virt_file_t *_chp_fp_ )";
				next;
			}
			elsif ($_ =~ /^\s*(\w+?)\s*(\w+?)\((.*?)\)\s*$/) {
				# must be this format in one line: <type> <func_name> ( ... )
				push @codes, "$1 ${ucSrcName}__$2( struct cgi_virt_file_t *_chp_fp_, $3 )";
				next;
			}
			elsif ($chp_wread_start == -2) {
				push @codes, rtrim($_);
				next;
			}

			$chp_wread_start = 0;
		}

		if ($chp_wread_start == 0) {
			$chp_wread_start = 1;

			if (!$has_getinfo) {
				printf $outFP "#define ${ucSrcName}__GETINFO   NULL\n\n";
			}

			printf $outFP <<EOF;
int ${ucSrcName}__WEB_READ( IN struct cgi_virt_file_t *_chp_fp_ )
{
EOF
		}

		if ($_ =~ /\<\?[cC][hH][pP]/) {
			@codes = ();
			if ($_ =~ /\?\>/) {
				# has: ... <?chp  ... ?> ...
				$_ =~ /^(.*)\<\?[cC][hH][pP]\s*(.*?)\?\>(.*)$/;
				push @htmls, $1;
				push @codes, $2;
				$html = $3;

				output_htmls();  # output the HTMLs before the <?CHP mark
				output_codes("\t", $ucSrcName);

				push @htmls, $html;
			}
			else {
				# has: ... <?chp  ......
				$_ =~ /^(.*)\<\?[cC][hH][pP]\s*(.*)$/;
				push @htmls, $1;
				push @codes, $2;
				$in_chp = 1;

				output_htmls();  # output the HTMLs before the <?CHP mark
			}
		}
		elsif ($_ =~ /\?\>/) {
				# has: ... ?> ...
				$_ =~ /^(.*?)\?\>(.*)$/;
				push @codes, $1;
				@htmls = ();
				push @htmls, $2;
				$in_chp = 0;
	
				output_codes("\t", $ucSrcName);
		}
		elsif ($in_chp) {
			push @codes, rtrim($_);
		}
		else {
			push @htmls, trim($_);
		}
	}

	output_htmls();  # output the final HTMLs
	print $outFP "\treturn _chp_fp_->web_rwptr - _chp_fp_->web_rwbuf;\n}\n\n";
}

#---------------------------------------------------------------------------------------------
sub output_htmls()
{
	foreach my $hh (@htmls) {
		$hh =~ s/\"/\\\"/g;
		if (length($hh) > 0) {
			print $outFP "\tCHP_PRINTF(\"$hh\\n\");\n";
		}
	}
	print $outFP "\n";
	@htmls = ();
}

sub output_codes($$)
{
	my ($indent, $ucSrcName) = @_;
	print $outFP $indent . "// <?CHP\n";
	foreach my $cc (@codes) {
		if (length($cc) > 0) {
			$cc =~ s/(\w+)\s*\(\s*CSUB,/${ucSrcName}__$1(_chp_fp_,/;
			print $outFP $indent . "$cc\n";
		}
	}
	print $outFP $indent . "// ?>\n\n";
	@codes = ();
}

#---------------------------------------------------------------------------------------------
# Perl trim function to remove whitespace from the start and end of the string
sub trim($)
{
	my $string = shift;
	$string =~ s/^\s+//;
	$string =~ s/\s+$//;
	return $string;
}
# Left trim function to remove leading whitespace
sub ltrim($)
{
	my $string = shift;
	$string =~ s/^\s+//;
	return $string;
}
# Right trim function to remove trailing whitespace
sub rtrim($)
{
	my $string = shift;
	$string =~ s/\s+$//;
	return $string;
}

#---------------------------------------------------------------------------------------------
# Perl has two sets of quantifiers:
#      the maximal ones * ,  + ,  ? ,  and {}  (sometimes called greedy ), and
#      the minimal ones *? , +? , ?? , and {}? (sometimes called stingy )

