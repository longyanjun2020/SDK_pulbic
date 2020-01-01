#!/usr/bin/perl

use strict;
use Getopt::Std;

my $Verbose=0;
my $Input=0;
my $Output=0;
my $line;
my %FILE_HASH;
my $lint_file_lst="";

my %opts;
getopts("v:i:o:h",\%opts);
if (exists $opts{h}) {PrintHelp(); exit 1; }
if (exists $opts{i}) {$Input=$opts{i};}     else{print"\n No input file is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{o}) {$Output=$opts{o};}	else{print"\n No output file is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{v}) {$Verbose=$opts{v};}

#
# parsing $Input, transfer format, and dump to $output
#
if($Input eq "") {print"\n No lint cl file is specified!!\n\n";PrintHelp(); exit 1; }
if($Output eq "") {print"\n No output file is specified!!\n\n";PrintHelp(); exit 1; }
system("dos2unix.exe $Input");
open(LINT_PER_FILE, "< $Input") or die "cannot read \"$Input\" file\n";
open(OUTPUT, "> $Output") or die "cannot read \"$Output\" file\n";
print OUTPUT "CTS_SRC_C_LIST=\\\n" ;
while ($line=<LINT_PER_FILE>)
{
	$line =~ s/\n//g;
	dbg_print( $line. "\n" );
	
	next if($line!~m/(\.c)|(\.cpp)/);
	next if($line=~m/^\s*$/); 
	next if($line!~m/^.*sc/);

	$line =~ s/^.*proj\\sc//g;
	$line =~ s#\\#\/#g;
	$line = "\tsc".$line."\\\n";
	dbg_print( "\t\t".$line );
	
	# for lint
	$lint_file_lst.=$line;
	
	# for CppTestScan
	$line =~ s/\n//g;
	$line = "\t".get_notdir($line)."\n";
	print OUTPUT $line ;
	
};

print OUTPUT "\n\n\nCL_LIST=\\\n" ;
print OUTPUT $lint_file_lst ;
close OUTPUT;
close LINT_PER_FILE;


#
# user guide
#
sub PrintHelp {
    print <<"EOF";
Usage:$0 [-h] [-i input file] [-o output file] [-v verbose mode]
    -h: help, show this user guide
    -i: input file, specify the input file which contains the file in testing CL
    -o: output file, specify the output file for lint to include e.g. CL_LIST.mak
    -v: verbose mode, print debug messages, e.g. -v2
EOF
exit 0;
}


#
# debug print
#
sub dbg_print {
  if ($Verbose >= 2) { printf shift; }
}


#
# get_notdir:  /proj/sc/system/sys/sys.mak  --> sys.mak
#
sub get_notdir
{
	my $notdir = shift ;
	$notdir =~ s/(.*\/)//g;
	#print "--",$notdir."--\n";
	return $notdir
}



#
#sub get_basename:  /proj/sc/system/sys/sys.mak  --> sys
#
sub get_basename
{
	my $basename = shift ;
	$basename =~ s/(.*\/)|(\..*)//g;
	#print "--",$basename."--\n";
	return $basename

}


#
# get_suffix:  /proj/sc/system/sys/sys.mak  --> mak
#
sub get_suffix
{
	my $suffix = shift ;
	$suffix =~ s/(.*\/)|(.*\.)//g;
	#print "--",$suffix."--\n";
	return $suffix
}