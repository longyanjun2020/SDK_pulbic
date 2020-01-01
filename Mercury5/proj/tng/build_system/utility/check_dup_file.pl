#!/usr/bin/perl -sw
use strict;
use vars qw($h $i);

if(defined($h) or !defined($i)){
    print <<END;
Usage: $0 -i FOLDER [-h]
\t-i: specify the folder location of dfn files
\t-h: show this usage
END
    exit 0;
}

opendir my $dir, $i or die "$0: unable to open $i: $!\n";
my @dfn_files=grep {
    /\.dfn$/ && !/tsk_prio\.dfn/
}readdir $dir;
closedir $dir;

if(scalar(@dfn_files)>0){
    warn "checking if there are duplicated source file in @dfn_files...\n\n";
}else{
    warn "no dfn files found in $i, skip checking...\n\n";
    exit 0;
}

my %hash=();
for my $dfn_file (@dfn_files){
    (my $lib=$dfn_file)=~ s#\.dfn$#\.lib#;
    open my $fin, "<", "$i/$dfn_file" or next;
    while(<$fin>){
        if(/^(?:C_SRCS|CPP_SRCS) =\\?$/ .. /^$/){
            chomp;
            next unless (m/\.c\\?$/ or m/\.cpp\\?$/);
            s!^\s+!!;
            s!^\.\/!!;
            s!\\$!!;

            if(defined($hash{$_})){
                if($hash{$_} eq $_){
                    warn "ERROR: $_ is duplicated in $hash{$_}!\n";
                }else{
                    warn "ERROR: $_ is duplicated in $lib & $hash{$_}!\n";
                }
            }else{
                $hash{$_}=$lib;
            }
        }
    }
    close $fin;
}

exit 0;
