#!/usr/bin/perl

use strict;

my $option_file = shift;
my $option_header = shift;

open(FILE, "<$option_file");
my @file = <FILE>;
close(FILE);

open(FILE, ">$option_header");
print FILE "#ifndef __OPTION_H__\n";
print FILE "#define __OPTION_H__\n\n";
foreach (@file)
{
	#for this case: /D "__FMS_RAI_DEBUG__=\"sdsdsddsd\""
	# -> #define __FMS_RAI_DEBUG__ "sdsdsddsd"
	if(/\"(.*?)\s*=\s*\\\"(.*?)\\\"\"/)
	{
		print FILE "#define $1\t\"$2\"\n";
	}
	#for this case: /D "__IVAN__="sdsdsddsd""
	# -> #define __IVAN__ "sdsdsddsd"
	elsif(/\"(.*?)\s*=\s*\"(.*?)\"\"/)
	{
		print FILE "#define $1\t\"$2\"\n";
	}
	#for this case: /D "__LCM_ROTATE_DIRECTION_CCW__=90"
	# -> #define __LCM_ROTATE_DIRECTION_CCW__  90
	elsif(/\"(.*?)\s*=\s*(.*?)\"/)
	{
		print FILE "#define $1\t$2\n";
	}
	#for this case: /D "__GAME_ENGINE_EMU__"
	# -> #define __GAME_ENGINE_EMU__ 1
	elsif(/\"(.*?)\"/)
	{
		print FILE "#define $1\t1\n";
	}
}
print FILE "#endif\n";
close(FILE);