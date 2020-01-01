#!/usr/bin/perl

open(CMD, "find sc/application/mmi/common/inc/ -name \"mmi_layout*\"|") or die $!;
while(<CMD>)
{	
	next if(/mmi_layout_gen/);
	if(/undef/ && /mmi_layout/)
	{
		system ("rm -rf $_");
		next;
	}
	push @layouts, $_;
}
close(CMD);

foreach $layout_file (@layouts)
{
	$count = 0;
	open(FILE, "<$layout_file") or die $!;
	@file = <FILE>;
	close(FILE);
	
	$layout_file =~ /(.*)\.(.*)/;
 	$layout_file_new = $1."_undef.h";
	#print "$layout_file_new\n";
	open(FILE, ">$layout_file_new") or die $!;
	foreach $line (@file)
	{
		if($count == 0)
		{
			if($line =~ /^\#define/)
			{
				$line =~ /^\#define\s+(.*)/;
				$text = $1;
				$text =~ /(.*)_H__/;
				print FILE "#define\t$1_UNDEF_H__\n";			
			}
			elsif($line =~ /^\#ifndef/)
			{
				$line =~ /^\#ifndef\s+(.*)/;
				$text = $1;
				$text =~ /(.*)_H__/;
				print FILE "#ifndef\t$1_UNDEF_H__\n";			
			}
			else
			{
			  print FILE $line;
			}
		}		
		if($line =~ /^\#define/)
		{
			if($count == 0)
			{
				$count = 1;
				print FILE "#undef\t$text\n";
				next;
			}				
			
			if($line =~ /^\#define\s+(.*?)\s+/)
			{
				print FILE "#undef\t$1\n";
			}		
		}
	}
	print FILE "#endif\n";
	
	close(FILE);			
}
