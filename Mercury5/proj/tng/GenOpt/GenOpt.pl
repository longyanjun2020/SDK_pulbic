#!/usr/bin/perl

use warnings;
use strict;
use File::Basename;
use File::Copy;

my $XRG_ini = "XRG_config.ini";
my $XRG_option_file = "../tools/XRG/option.rte.2005";
my $XRG_readme_file = "./sc/customer/product/CompilerOptionReadMe.txt";
my $my_product=shift;
my $XRG_option_header = "../tools/XRG/option.h";

my $ostype=`uname`;
if($ostype =~ m/msys|mingw/i){
    $ostype='msys';
}

print "\nCreating XRG Option File.....  [$XRG_option_file]\n";
if($ostype eq "msys"){
    system "cmd \/c .\\\\tng\\\\GenOpt\\\\XRG_buildOpt.bat";
}else{
    system './tng/GenOpt/XRG_buildOpt.bat';
}
create_config_ini($XRG_ini, $my_product, $XRG_option_file, $XRG_readme_file);
system "./tng/copy_rte_to_header.pl $XRG_option_file $XRG_option_header";
system "rm -r $XRG_option_file";

my $MStarStudio_ini = "MStarStudio_config.ini";
my $MStarStudio_option_file = "./MStarStudio_Config/option.rte.2005";
my $MStarStudio_readme_file = "./sc/product/CompilerOptionReadMe.txt";
my $MStarStudio_option_header = "./MStarStudio_Config/option.h";
print "\nCreating PC Simulator Option File.....  [$MStarStudio_option_file]\n";
if($ostype eq "msys"){
    system "cmd \/c .\\\\tng\\\\GenOpt\\\\MStarStudio_buildOpt.bat";
}else{
    system './tng/GenOpt/MStarStudio_buildOpt.bat';
}
system "./tng/copy_rte_to_header.pl $MStarStudio_option_file $MStarStudio_option_header";
create_config_ini($MStarStudio_ini, $my_product, $MStarStudio_option_file, $MStarStudio_readme_file);
sleep(1);
system "rm -r $MStarStudio_option_file";

sub create_config_ini {
	my $create_file_name = shift;
	my $product_name = shift;
	my $option_file = shift;
	my $readme_file = shift;

	open CREATE_FILE_NAME, "> $create_file_name" or die "cannot write to ", $create_file_name, "\n";
	print CREATE_FILE_NAME "[SECTION]\n";
	print CREATE_FILE_NAME "NAME=$product_name\n";
	print CREATE_FILE_NAME "[COMPILE_OPTION]\n";
	print CREATE_FILE_NAME "RTE_FILE=$option_file\n";
	print CREATE_FILE_NAME "RTE_README=$readme_file\n";
	close CREATE_FILE_NAME;

}
