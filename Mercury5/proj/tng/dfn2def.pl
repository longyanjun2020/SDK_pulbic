#! /usr/bin/perl
use strict;
use warnings;
use Getopt::Std;

getopts('j:i:o:v');
our($opt_j, $opt_i, $opt_o, $opt_v);

sub uniq_sort(){
    my %temp_hash;
    map{$temp_hash{$_}++} @_;
    return sort(keys(%temp_hash));
}
sub debug_print{
    print "@_" if($opt_v)
}

if(!$opt_i){
    die "dfn2def.pl: input file is not specified with -i switch\n";
}

my $jobs=$opt_j?$opt_j:0;
my $inputFile=$opt_i;
my $outFolder=$opt_o?$opt_o:"";
&debug_print ("jobs=$jobs, inputFile=$inputFile,outFolder=$outFolder\n");

#for(@ARGV){
my $Fin;
my $Fout;

my $outputFile=$inputFile;
$outputFile =~ s#(.*)\..*#$1\.dfn2def.mak#;
open($Fin, "<","$inputFile") or die "dfn2def.pl: unable to open input file\n";

my @sources;
my $parsing=0;

for(<$Fin>){
    chomp;
    s#[\r\n]##g;
    s#\/\/#\/#g;
    s#\s\.\/#\ #g;
    next if(m/^$/);

    if($parsing==1){
        if(m/^\s+(.+)\s*\\\s*$/){
            my $line=$1;
            push @sources, $_ for(split(/\s+/,$line));
        }elsif(m/^\s+(.+)\s*$/){
            my $line=$1;
            push @sources, $_ for(split(/\s+/,$line));
            $parsing=0;
        }
    }else{
        if(m/(C|CPP)_SRCS\ =\\/){
            $parsing=1;
        }
    }
}
$parsing=0;
close($Fin);
my $cmd;
$cmd=$cmd."$_" while(<STDIN>);
chomp($cmd);

my $temp=$inputFile;
$temp =~ s#.*\/(.*)\..*#$1#;

open($Fout,">","$outputFile");
if($jobs!=0){
    print $Fout "$outFolder/$temp.cdep :";
    print $Fout " $outFolder/$temp.".$_.".d" for(0 .. $jobs-1);
    print $Fout "\n\tcat \$\^ > \$\@ \n\n.INTERMEDIATE: ";
    print $Fout " $outFolder/$temp.".$_.".d" for(0 .. $jobs-1);
    print $Fout "\n\n";
    
    my $sources_per_job=int(((scalar(@sources) % $jobs)==0)?(scalar(@sources) / $jobs):(scalar(@sources)/$jobs +1));
    &debug_print("per job: $sources_per_job\n");
    my $i;
    for($i=0;$i<($jobs-1);++$i){
        print $Fout "$outFolder/$temp.$i.d : ";
        print $Fout map{ 
                $_." ";
            } @sources[$i*($sources_per_job) .. ($i+1)*($sources_per_job)-1];
        print $Fout "\n\t$cmd\n";
    }
    print $Fout "$outFolder/$temp.$i.d : ";
    print $Fout map{ 
            $_." ";
        } @sources[$i*($sources_per_job) .. $#sources];
    print $Fout "\n\t$cmd\n";
}else{
    print $Fout "$outFolder/$temp.cdep : ";
    map{
        my $filename=$_;
        $filename =~ s#.*\/##;
        $filename =~ s#(.*)\..*#$1#;
        print $Fout " $outFolder/$filename.d";
    } @sources;
    print $Fout "\n\tcat \$\^ > \$\@ \n\n.INTERMEDIATE: ";
    map{
            my $basename=$_;
            $basename =~ s#.*\/##;
            $basename =~ s#(.*)\..*#$1#;
            print $Fout " $outFolder/$basename.d"
        }@sources;
    print $Fout "\n\n";

    map{
        my $basename=$_;
        $basename =~ s#.*\/##;
        $basename =~ s#(.*)\..*#$1#;
        print $Fout "$outFolder/$basename.d : $_\n";
        print $Fout "\t$cmd\n";
    } @sources;
}
close($Fout);
