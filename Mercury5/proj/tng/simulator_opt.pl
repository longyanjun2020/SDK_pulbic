#!/usr/bin/perl

#use warnings;
use strict;
use Fcntl;
use File::Basename;
my %filter_define;
my %include_define;

#$filter_define{'__RTK_RELEASE__'}= 1;
$filter_define{'__RTK_DIAGNOSE_ENHANCE__'}= 1;
$filter_define{'__ACC_DEV__'}= 1;
$filter_define{'__AUTO_TEST_SCRIPT__'}= 1;
$filter_define{'__JAVA__'}= 1;
$filter_define{'__MMI_JAVA__'}= 1;
$filter_define{'__JAVA_DELTA__'}= 1;
$filter_define{'__FEATURE_JAVA_SUPPORTED__'}= 1;
$filter_define{'__MULTI_PROXY__'}= 1;
#filter __FULL_SIM_PATH__
$filter_define{'__FULL_SIM_PATH__'}= 1;
#filter __DUAL_POOL__
$filter_define{'__DUAL_POOL__'}= 1;
#$filter_define{'__DEBUG__'}= 1;

#include user option
#$include_define{'__RTK_RELEASE__'}= 1;
#include no__FULL_SIM_PATH__
$include_define{'no__DUAL_POOL__'}= 1;
#include no__FULL_SIM_PATH__
$include_define{'no__FULL_SIM_PATH__'}= 1;
$include_define{'__NO_POWER_DOWN__'}= 1;
$include_define{'__NEW_IO_MGT__'}= 1;
$include_define{'__NEW_BUS_MGT__'}= 1;
$include_define{'__SDK_SIMULATION__'}= 1;
$include_define{'__MONOBINARY__'}= 1;
$include_define{'__LCM_QVGA_HX8312A__'}= 1;

#$include_define{'__DEBUG__'}= 1;
#===================================
my $os=`uname`;
if ($os =~ m/Linux/i) {
	$os = "linux";
}
elsif ($os =~ m/Cygwin/i) {
	$os = "cygwin";
}
elsif ($os =~ m/Windows/i) {
	$os = "Win32";
}
elsif($os =~ m/msys|mingw/i{
    $os = "msys";
}else {
	die "unknown system";
}

sub trim($)
{
	my $string = shift;
	$string =~ s/^\s+//;
	$string =~ s/\s+$//;
	return $string;
}

# Left trim function to remove leading whitespace
sub ltrim($)
{
	my $string = shift;
	$string =~ s/^\s+//;
	return $string;
}

# Right trim function to remove trailing whitespace
sub rtrim($)
{
	my $string = shift;
	$string =~ s/\s+$//;
	return $string;
}


my $outFile = shift(@ARGV);

my $testfile='.\cc.txt';
my $tmp;
my $iIsFilter =0;
my @includeKey = keys %include_define;
# generate lint definition file
open(H_DEFINEFILE, "+> $outFile") or die "cannot read \"$outFile\" file\n";
my $varXX = "";
# write default
foreach $tmp (@includeKey)
{			
	print H_DEFINEFILE "/D \"$tmp\"\n";	
}
		

foreach $varXX (@ARGV)
{
	$iIsFilter = 0;
	$varXX = trim($varXX);
	
	if (  defined($filter_define{$varXX}) )
	{
		$iIsFilter = $filter_define{$varXX};
	}
	
	if ($iIsFilter ==0 )
	{
		if ($varXX =~ /^-d/i)
		{
			#print H_DEFINEFILE "$varXX\n";	
		}
		else
		{		
			print H_DEFINEFILE "/D \"$varXX\"\n";	
		}
	}
}
close(H_DEFINEFILE);

