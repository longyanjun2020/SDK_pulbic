#!/usr/bin/perl

use warnings;
use strict;

# get output file name
my $output = shift;

# get stub_dlm_dummy name
my $stub_dlm_dummp_file = shift;

# init results strings
my $dlms = "\\\n\tstub_dlm_dummy\.c";
# for each object name on the command line
for my $dlm (@ARGV)
{
	my $path;
	$dlms .= "\\\n\tstub_$dlm\.c";
}
$dlms .= "\\\n\tabi_headers_dlm_entry\.c";

# output results according to a makefile syntax
open(MAK, "> $output") or die "cannot write to \"$output\"\n";
print MAK "\n\n";
print MAK "# This makefile is auto generated in dlm_pre stage.\n\n";
print MAK "PATH_H += \$\(PATH_dlm_entry_pub\)\n\n";
print MAK "ifeq \(\$(COMPILER_VERSION),RVCTV22)\nC_OPTIONS+=--diag_suppress 2874\nendif\n\n";
print MAK "REL_SRC_C_LIST = $dlms\n\n";
close(MAK);

# create stub_dlm_dummy.c
open(STUB_DLM, "> $stub_dlm_dummp_file") or die "cannot write to \"$stub_dlm_dummp_file\"\n";
print STUB_DLM"\n\n";
print STUB_DLM "/* This file is auto generated in dlm_pre stage to create DLM library.\n";
print STUB_DLM " * Donnot remove theis file to avoid compile error */\n\n"; 
print STUB_DLM "void dlm_dummy_entry_func(void)\n{\n\treturn;\n}\n";
close(STUB_DLM);
