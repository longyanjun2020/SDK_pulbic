#! /bin/perl
use strict;
use Getopt::Std;
use warnings;

getopts('auw');
our ($opt_a, $opt_u, $opt_w);

if(($#ARGV)<0){
    print "Usage: mingpath (-a|-u|-w) NAME...\n",
          "\tconvert Unix and Windows format paths\n\n",
          "-a, output absolute path\n",
          "-u, (default) print UNIX form of NAMEs\n",
          "-w, print windows form of NAMEs(C:\\WINNT)\n";
    exit;
}

foreach(@ARGV){
    chomp;
    s;\\;\/;g;
    if($opt_w && (!$opt_u)){
        #-w: windows path
        if(m/^\w+\:/){
            #case 1: windows absolute path
            #print "case 1\n";
            # already windows path
        }elsif(m/^\//){
            #case 2: unix absolute path 
            s/^\/(\w+)\//$1\:\//g;
        }elsif($opt_a){
            #case 3: relative paths but transferred to absolute path
            my $pwd=readpipe("pwd");
            chomp($pwd);
            $_=$pwd.'/'.$_;
            s/([\/|\\])\.[\/|\\]/$1/g;
            s/^\/(\w+)\//$1\:\//g;
        }
        #case 4: relative paths
        # ignore it!!
        # One still problem: if abc\def
        #   will become abcdef

        s/\/(\s+)/$1/g;
        s/\/+/\\/g;
    }else{
        #-u: output unix path
        if(m/^\//){
            #case 1: already unix absolute path
            # ignore it!!
        }elsif(m/^\w+\:/){
            #case 2: windows absolute path
            s/^(\w+)\:[\/|\\]?/\/\l$1\//g;
        }elsif($opt_a){
            #case 3: relative path but transferred to absolute path is needed
            my $pwd=readpipe("pwd");
            chomp($pwd);
            $_=$pwd.'/'.$_;
        }
        1 while(s#\/\.\/#\/#g);
        s;[\\|\/]+;\/;g;
        1 while(s,\/[^/.][^/]*\/\.\.\/,\/,g);
    }
    printf "%s\n", $_;
}
exit 0;
