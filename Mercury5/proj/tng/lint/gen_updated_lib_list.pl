#!/usr/bin/perl

use strict;
use Getopt::Std;
use IPC::Open3;

my $Verbose=0;
my $Input=0;
my $Output=0;
my $line;
my $out_folder="";
my @changed_filelist;
my @changed_libs;

my %opts;
getopts("v:i:o:h",\%opts);
if (exists $opts{h}) {PrintHelp(); exit 1; }
if (exists $opts{i}) {$Input=$opts{i};}     else{print"\n No input file is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{o}) {$Output=$opts{o};}	else{print"\n No output file is specified!!\n\n";PrintHelp(); exit 1; }
if (exists $opts{v}) {$Verbose=$opts{v};}

#
# parsing $Input, transfer format, and dump to $output
#
if($Input eq "") {print"\n No input file is specified!!\n\n";PrintHelp(); exit 1; }
if($Output eq "") {print"\n No output file is specified!!\n\n";PrintHelp(); exit 1; }
system("dos2unix.exe $Input");
open(LINTUNITS, "< $Input") or die "cannot read \"$Input\" file\n";
while ($line=<LINTUNITS>)
{
	$line =~ s/\n//g;
	dbg_print( $line. "\n" );

	next if($line!~m/(\.c)|(\.cpp)/);
	next if($line=~m/^\s*$/);
	next if($line!~m/^.*sc/);

	$line =~ s/^.*proj\\sc//g;
	$line =~ s#\\#\/#g;
	$line = "sc".$line;
	dbg_print($line."\n");


	# for lint
	push @changed_filelist, $line;

	# for CppTestScan
	$line =~ s/\n//g;
	$line = "\t".get_notdir($line)."\n";
	print OUTPUT $line ;

};
close LINTUNITS;

$out_folder = get_path($Output);
dbg_print("out_folder $out_folder\n");

my ($pid, $out, $err, $token);
use Symbol 'gensym'; $err=gensym;


@changed_filelist = uniq(@changed_filelist);
foreach $token (@changed_filelist)
{
    my $prog="grep $token $out_folder/*.dfn|cut -d':' -f1";
    my $pid=open3(undef, $out, $err, $prog);
    dbg_print($prog."\n");
    while(<$out>){
        chomp;
        dbg_print(get_basename($_)."\n");
        push @changed_libs,get_basename($_);
    }
    close $out; close $err;
    waitpid($pid, 0);
}

open(OUTPUT, "> $Output") or die "cannot read \"$Output\" file\n";
print OUTPUT "LST_UPDATED_LIB=\\\n" ;
print OUTPUT "\t\t".join("\\\n\t\t", @changed_libs);
close OUTPUT;



#
# user guide
#
sub PrintHelp {
    print <<"EOF";
Usage:$0 [-h] [-i input file] [-o output file] [-v verbose mode]
    -h: help, show this user guide
    -i: input file, lintUnits.opt
    -o: output file, updated_lib_list.txt
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
#sub get_path:  /proj/sc/system/sys/sys.mak  --> /proj/sc/system/sys/
#
sub get_path
{
	my $path = shift ;
	if ($path =~ m/(.*)\//) {
        $path = $1;
    }
	#print "--",$path."--\n";
	return $path

}

sub uniq {
    return keys %{{ map { $_ => 1 } @_ }};
}
