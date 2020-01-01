#!/usr/bin/perl -sw
use strict;
use vars qw($l $h $f);

my $Version="v 1.1";
my $Date="Apr 2012";

##--------------------------------------------------------------------------------------------------
## Author  | Rev | Date     | Comment
##--------------------------------------------------------------------------------------------------
##  Neil   | 1.0 | xx/xx/11 | Creation, first version for DPM and SLDLM
##--------------------------------------------------------------------------------------------------
##  Carl   | 1.1 | 02/04/12 | for stacj lib
##--------------------------------------------------------------------------------------------------


if(defined($h) || !defined($l) || !defined($f)){
    print <<END;
Script to compress bin file and append header after binary
MStar Taiwan - $Date - version $Version    
Usage: $0 -l=LINKS[-h] <files to parse>
\t-l:
\t-f: functionality, 0: DPM+SLDLM, 1: stack lib
\t-h: show this usage
END
    exit 0;
}

sub basename{
    local ($_)=@_;
    s/.*\///;
    return $_;
}

my %lib_tab;
for(split /:/,$l){
    if(/\.lib$/){
        $lib_tab{&basename($_)}=$_;
    }
}

my @fun_name=(
    "SLDLM_LIB",
    "EMMI_SLDPM_LIB",
    "STACK_LIB",
    "MSTAR_LIB"
);

 
my @regex = map{
    qr!\b$_\b\(\"(\w+\.lib)\"\)!;
}@fun_name;

while(<>){
    s/[\n\r]//g;
    for my $i (0 .. $#fun_name){
        s^$regex[$i]^ 
            my $lib=$1;
            unless(exists($lib_tab{$lib})){
                "$fun_name[$i](\"$lib\")";
            }else{
                $lib_tab{$lib};
            }
        ^gxe;
    }
    print "$_\n";
}
