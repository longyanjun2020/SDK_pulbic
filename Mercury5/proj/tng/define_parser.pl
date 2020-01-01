#! /bin/perl
use strict;
use warnings;
my %macros;
my @macros;
my $fin;
my $magic_string="just defined magic string!!\n";

if(scalar(@ARGV)<1) {
    print STDERR "define_parser.pl: no input file\n";
    exit 0;
}

foreach my $input_file(@ARGV){
    next if(!-e $input_file);
    my $input_file_pattern=$input_file;
    $input_file_pattern =~ s#\/#\\\/#g;
    open($fin, "cpp -dD -E $input_file | sed -n '\/$input_file_pattern\/,\/^# [0-9]\/\{p\}' |");
    while(<$fin>){
        s,[\n|\r],,g;
        if(m/^\s*#define\s+(\S+)\s*$/o){
            $macros{$1}=$magic_string;
            push @macros, $1;
        }elsif(m/^\s*#define\s+(\S+)\s+(.*)\s*$/o){
            my $key=$1;
            $macros{$key}=$2;
            $macros{$key} =~ s/\s+//g;
            #erase space char because extra space will confuse our make system
            push @macros, $key;
        }
    }
    close($fin);
}

if(@macros!=0){
    print join(" ", map{
            if($macros{$_} eq $magic_string){
                "$_";
            }else{
                "$_=$macros{$_}";
            }
        }@macros);
}
print "\n";
