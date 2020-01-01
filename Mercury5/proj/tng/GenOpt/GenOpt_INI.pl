#!/usr/bin/perl

use warnings;
use strict;
use File::Basename;
use File::Copy;


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