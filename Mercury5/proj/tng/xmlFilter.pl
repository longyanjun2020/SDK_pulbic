#!/usr/bin/perl

#####
## SYNTAX:
## perl xmlFilter.pl File.xml pattern
#####

use warnings;
use strict;

# use module
use XML::Simple;
use Data::Dumper;

# ceate object
my $xml = new XML::Simple;

# read XML file
my $xmlFile = shift(@ARGV);
my $inXmlData = $xml->XMLin($xmlFile, ForceArray=>1);	

my $pattern = shift(@ARGV);

#get values of key "make"	of the chk xml data
my $inMakeArrayPtr = $inXmlData->{"make"};	
my @MakeArray;
my $newMakeArrayPtr;


sub filter
{
	my @filterArr = @_;
	my $makeHash;
	
	foreach (@$inMakeArrayPtr)
	{
		my $makeData = $_;	
		my $oldFileArrayPtr = $makeData->{"file"};
		my @newFileArray;
		
		foreach(@$oldFileArrayPtr)
		{
			my $keep = 1;
			my $fileHashRef = $_;
			
			foreach(@filterArr)
			{
				if ($fileHashRef->{"default_value"}->[0] =~ /^\s*$_/)
				{
					$keep = 0;
					last;
				}			
			}
			
			if ($keep)
			{
				push @newFileArray, $fileHashRef;
			}
		}

		$makeData->{"file"} = \@newFileArray;

		push @MakeArray, $makeData;
	}
	
	$newMakeArrayPtr = \@MakeArray;
}


&filter($pattern);#"SRC_C_LIST"

my $outHash = 
{
	'make' => $newMakeArrayPtr
};

# create object
$xml = new XML::Simple;
# convert Perl array ref into XML document 
my $outXmlData = $xml->XMLout($outHash, NoAttr=>1, NoSort=>1, RootName=>'make_info');

open(OUTPUT_FILE, "> $xmlFile") or die "cannot write\"$xmlFile\" file\n";	
print OUTPUT_FILE $outXmlData;
close (OUTPUT_FILE);

#print Dumper(@MakeArray);
