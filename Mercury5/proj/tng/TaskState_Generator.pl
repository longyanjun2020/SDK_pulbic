#!/usr/bin/perl
# Author: Neil-wl.Yang
# Date: 2011/01/31
use strict;
use warnings;
use Getopt::Std;

getopts('i:o:h');
our ($opt_i, $opt_o, $opt_h);
if((!$opt_i) or (!$opt_o) or ($opt_h) ){
    print   qq#Usage: TaskState_Generator.pl -i <input folder> -o <output file> [-h]\n#,
            qq#\t-i: specify the folder sys_rtk_defi.h located, necessary!\n#,
            qq#\t-o: specify the output filename, necessary!\n#,
            qq#\t-h: show usage#;
    exit 0;
}

my $fin;
my $fout;
my $task_stat_file="$opt_i/sys_rtk_defi.h";
open($fin, "< $task_stat_file") or die qq^TaskState_Generator.pl: unable to open $opt_i\n^;
my %task_stat;
my $parsing=0;
while(<$fin>){
    chomp;
    s#\/\/.*##g;
    if($parsing){
        if(m/^#define\s+(RTK_\w+)\s+(0x\d+)\s*$/){
            $task_stat{$1}=hex($2);
        }elsif(m/^#define\s+(RTK_\w+)\s+(\d+)\s*$/){
            $task_stat{$1}=$2;
        }elsif(m(^\/\*{6,}\s)){
            $parsing=0;
            last;
        }
    }else{
        if(m(^\/\*{7,}\s*Task\s*states\s*\*{7,}\/$)){
            $parsing=1;
        }
    }
}
close($fin);

open($fout, "> $opt_o") or die qq#TaskState_Generator.pl: unable to open $opt_o\n#;

map{
    printf $fout "%02x %s\n", $task_stat{$_}, $_;
}sort {
    $task_stat{$a} <=> $task_stat{$b}
} keys %task_stat;
close($fout);
