#!/usr/bin/perl

#####
## SYNTAX:
## perl copyAudioTable.pl
#####

use warnings;
use strict;

my $e2pFile = "./sc/customer/product/common/e2p/audioparam.e2p";
my $appFile = "./sc/customer/product/cust/drv/app_calibration_table/src/BaseTable/app_calibration_table.c";
my $arpFile = "./sc/customer/product/cust/drv/arp_calibration_table/src/BaseTable/arp_calibration_table.c";

my $e2pPath = "sc/customer/product/cust/e2p";
my $appPath = "sc/customer/product/cust/drv/app_calibration_table/src";
my $arpPath = "sc/customer/product/cust/drv/arp_calibration_table/src";

sub copyContent
{
	my $audioType = shift;
	my $srcFile = "";
	my @audioFiles = ();
	my $folderPath = "";
	
	if ($audioType eq "e2p")
	{
		$srcFile = $e2pFile;
		$folderPath = $e2pPath;
		chdir $folderPath;
		@audioFiles = <audioparam_*.e2p>;
	}
	elsif ($audioType eq "app")
	{
		$srcFile = $appFile;
		$folderPath = $appPath;
		chdir $folderPath;
		@audioFiles = <app_calibration_table_*.c>;
	}
	elsif ($audioType eq "arp")
	{
		$srcFile = $arpFile;
		$folderPath = $arpPath;
		chdir $folderPath;
		@audioFiles = <arp_calibration_table_*.c>;
	}
	
	my @tmpFolder = split(/\//, $folderPath);
	for (0 ... $#tmpFolder)
	{
		chdir "../";
	}
	
	for (0 ... $#audioFiles)
	{
		print "update $folderPath/$audioFiles[$_]\n";
		system "cp -f $srcFile $folderPath/$audioFiles[$_]\n";
	}
}

copyContent("e2p");
copyContent("app");
copyContent("arp");
