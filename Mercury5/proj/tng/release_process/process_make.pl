#!/usr/bin/perl

use warnings;
use strict;

#####
## SYNTAX:
## $ perl tng/release_process/process_make.pl
#####

my @makileList= ();
my $makFile;
my $newMakFile;
my @fileContent;
my @newFileContent;
my $lineData1;
my $lineData2;
my $found = 0;
my $preProduct;

if($#ARGV == 0)
{
    $preProduct = $ARGV[0];
}

# gat product list
opendir PRD, "./mak/" or die "cannot access product in \"", "mak/", "\"\n";
for my $prd (sort(readdir(PRD)))
{
	if($prd =~ /\.mak$/)
	{
		#print "$prd\n";
        if($#ARGV == 0)
        {
            if($prd =~ /$preProduct/)
            {
                push @makileList,$prd;
            }
        }
        else
        {
		    push @makileList,$prd; 
		}
	}
}
closedir PRD;

print "product option make file:\n";
foreach (@makileList)
{
    $found = 0;
    $makFile = "./mak/".$_;
    $newMakFile = "./mak/".$_;
    @fileContent = ();
    @newFileContent = ();
    
    print "-> $makFile\n";
    open(FILE, "<$makFile");
    @fileContent = <FILE>;
    close(FILE);
    
    foreach(@fileContent)
    {
        $lineData1 = $_; 
        if($lineData1 =~ /^# \*\* Alpha options \*\*/)
        {
            $found = 1;
            pop(@newFileContent);
            last;
        }
        push @newFileContent, $lineData1
    }
    
    if($found eq 0)
    {
        print "ERROR: can not find \"Alpha options\" section\n";
    }
    if( -e $newMakFile)
    {
        system("chmod 777 -R $newMakFile");
        unlink $newMakFile;
    }
    open (OUTFILE,">$newMakFile") || die("Cannot Open File $newMakFile");
    foreach (@newFileContent)
    {
    	print OUTFILE $_;
    }
    close(OUTFILE);    
}

print "Remove Eng Folder...\n";

system("chmod 777 -R ./mak/Eng");
system("rm -r -f ./mak/Eng");

print "Done!\n";


