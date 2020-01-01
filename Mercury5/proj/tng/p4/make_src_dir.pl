#!/usr/bin/perl

# Purpose: check if the file structure is consistent with the path setting in p4_access_right.txt

#use warnings;
use strict;
use File::Copy;
use File::Path;

my $path_file;
my $pathCodebase;
my $src_folder;
my $srcShouldExist;
my $srcRelativePath;

$path_file = $ARGV[0];
$pathCodebase = $ARGV[1];

open(PATHS, "< $path_file") or die "cannot read $path_file\n";
my @pathLines=<PATHS>;
close(PATHS);

for my $line (@pathLines)
{
    $srcShouldExist = 3;
    $_ = $line;
    chomp;
    print "line=$_\n";

    # if this line is not a comment
    if (/mobile_sz.*\-.*EMMI\//)
    {
        # $' is something like Big2line_v1.07_integration/proj/sc/...
        # this helps find out "/proj/sc/", for e.g.
        $_ = $';

        # find out proj/sc/
        # Very strangly! I cannot use /integration(\S*)src\/\.\.\./i;
        /mainline\W*\/(\S*)\.\.\./i;

        $_ = $1;
        print "parsed path=$_\n";
        
        if (m/src\/$/i)
        {
            $srcShouldExist = 0;
            $srcRelativePath = $_;
            $src_folder = "$pathCodebase/$srcRelativePath";
            print "SRC $src_folder\n";
        }
    }
    if (/mobile_2.*\-.*EMMI\//)
    {
        # $' is something like Big2line_v1.07_integration/proj/sc/...
        # this helps find out "/proj/sc/", for e.g.
        $_ = $';

        # find out proj/sc/
        # Very strangly! I cannot use /integration(\S*)src\/\.\.\./i;
        /mainline\W*\/(\S*)\.\.\./i;

        $_ = $1;
        print "parsed path=$_\n";
        
        if (m/src|src_cus\//i)
        {
            $srcShouldExist = 0;
            $srcRelativePath = $_;
            $src_folder = "$pathCodebase/$srcRelativePath";
            print "SRC $src_folder\n";
        }
    }
    elsif (/mobile_sz.*apollo\//)
    {
        $srcShouldExist = 1;
        # $' is something like Big2line_v1.07_integration/proj/sc/...
        # this helps find out "/proj/sc/", for e.g.
        $_ = $';
        # find out proj/sc/
        /EMMI\/mainline\W*\/(\S*)\.\.\./i;

        $_ = $1;
        $src_folder = "$pathCodebase/$_";
    }

    # The source directory should be absent
    if ($srcShouldExist == 0)
    {
        if (-e $src_folder)
        {
            # Warning: the source directory should've not existed but it is there
            print "==> $srcShouldExist should've not existed\n";
        }
        else
        {
            # make dir since the folder doesn't exist
            print "make dir: $src_folder\n";
            mkpath($src_folder, 0755) || die "$!";
        }
    }
}
