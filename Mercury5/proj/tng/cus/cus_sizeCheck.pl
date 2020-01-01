#!/usr/bin/perl

use strict;

my $product_name = shift;
my $cus_project = shift;
my $cus_size = shift;
my $mmap_support = shift;
my $cus_folder = "./build/$product_name/$cus_project/";
my $i=0;
my @filelist;
my $size;
my $maxCusSize=0;
my $valid=1;
my $mmap_cus_size=0;

@filelist = glob $cus_folder . "*.cus";

if( $mmap_support eq "TRUE" )
{

	#print "product=$product_name \n";
	#print "filelist= @filelist \n";
	#print "cus_size= $cus_size \n";
	#print "mmap_support= $mmap_support \n";
	for ($i=0; $i<(@filelist); $i++)
	{
		$size = -s $filelist[$i]; 
		if( $size > $maxCusSize )
		{
			$maxCusSize = $size;
		}
		#print "i=$i, size=$size, " . $filelist[$i] .  "\n";		
	}
	
	#print "MAX CUS Size=$maxCusSize \n";
	if( $cus_size eq "MMAP_CUS_64MB" )
	{
		$mmap_cus_size = 64 * 1024 * 1024;
	}
	elsif( $cus_size eq "MMAP_CUS_32MB" )
	{
		$mmap_cus_size = 32 * 1024 * 1024;	
	}
	elsif( $cus_size eq "MMAP_CUS_16MB" )
	{
		$mmap_cus_size = 16 * 1024 * 1024;	
	}		
	else
	{
		print "invalid MMAP_CUS_SIZE = $cus_size. \n";
		exit 1;	
	}
		
	if( $maxCusSize > $mmap_cus_size )
	{
		print "ERROR!!! Please check the size of Language Pack files. Those files must be less than CUS_MMAP_SIZE \n";
		print "The max size of LangPack is $maxCusSize.  CUS_MMAP_SIZE is $cus_size \n";
		exit 1;	
	}	
}

	