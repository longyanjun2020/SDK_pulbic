#!/usr/bin/perl

use warnings;
use strict;
use File::Copy;
use File::Basename;
use Cwd;

my $homePath = cwd();
my $inPath  = shift;

chdir $inPath or die "cannot enter \"$inPath\"\n";
$inPath = cwd();
print "Enter $inPath\n";

sub scan_dir {
    my @files    = <*>;
    my $fullPath = "";
    my $dirPath  = "";
    my $newFullPath = "";

    for my $file (@files) {
        $dirPath  = cwd();
        $fullPath = $dirPath . "/" . $file;

        if ( -d $file ) {
            chdir $file;
            scan_dir();
            chdir "../";
        }
        else {

            # Duplicate all of the xxx.c with postfix _sati

        	my($name,$dir,$type) = fileparse($fullPath,'\..*');

        	if ( $type eq ".c" && ($name!~/_sati/))
        	{
        		$newFullPath = $dir . $name . "_sati" . $type;

            	# print "Copy $file to $newFullPath\n";
            	copy("$fullPath","$newFullPath");

            }
            else
            {
            	# print "Do not copy the files without extension .c or with _sati ...\n";
            	# print "$file\n";
            }
        }
    }
}

sub clear_sati {
    my @files    = <*>;
    my $fullPath = "";
    my $dirPath  = "";
    my $line  = "";
    my @array    = <*>;
    my $newFullPath = "";

    for my $file (@files) {
        $dirPath  = cwd();
        $fullPath = $dirPath . "/" . $file;

        if ( -d $file ) {
            chdir $file;
            clear_sati();
            chdir "../";
        }
		elsif ($file =~ /_sati.c$/) {

       		# delete the files with _sati
			# print "Delete $file\n";
			unlink "$fullPath" if (-e "$fullPath");
       }
    }
}

clear_sati();
scan_dir();
