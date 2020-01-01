#!/usr/bin/perl
# Author: Neil-wl.Yang
# Date: 2011/01/31
use strict;
use warnings;
use Getopt::Std;

getopts('i:o:h');
our ($opt_i, $opt_o, $opt_h);
if((!$opt_i) or (!$opt_o) or ($opt_h) ){
    print   qq#Usage: exceptionType_Generator.pl -i <input folder> -o <output file> [-h]\n#,
            qq#\t-i: specify the folder sys_rtk_ho.h located, necessary!\n#,
            qq#\t-o: specify the output filename, necessary!\n#,
            qq#\t-h: show usage#;
    exit 0;
}

my $exception_file="$opt_i/sys_rtk_ho.h";
my $fin;
my $fout;

open($fin, "<", "$exception_file") or
    die "exceptionType_Generator.pl: unable to open $exception_file\n";
my %exception;
my $enum_num=0;

my $parsing=0;
while(<$fin>){
    chomp;
    s#\/\/.*##g; # eat comments
    s#\/\*.*\*\/##g; #eat comments
    next if(m/^$/);

    if($parsing){
        if(m/^\s*\}\s*rtk_Exception_e\s*;\s*$/){
            last;
        }elsif(m/^\s*\}\s*\w+\s*;\s*$/){
            $parsing=0;
            %exception=();
            $enum_num=0;
        }elsif(m/^\s*(\w+)\s*\=\s*(\d+)/){
            $exception{$1}=$2;
            $enum_num=$2+1;
        }elsif(m/^\s*(\w+)/){
            $exception{$1}=$enum_num;
            $enum_num++;
        }else{
            #warn "uncaught '$_'\n" if $opt_v;
        }
    }else{
        if(m/^\s*typedef\s+enum\s*\{\s*$/){
            $parsing=1;
        }
    }
}
close($fin);

open($fout, "> $opt_o") ||
    die "exceptionType_Generator.pl: unable to open $opt_o\n"; 
map{
    printf $fout "%02x %s\n",$exception{$_}, $_;
}sort {
    $exception{$a} <=> $exception{$b}
} keys %exception;
close($fout);
