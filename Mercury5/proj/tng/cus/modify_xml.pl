#!/usr/bin/perl

use strict;

my $cus_path = shift;
my $cus_project = shift;
my $cus_res = shift;
my $xml_file = "sc/customer/default/src/mmi/resource/$cus_path/$cus_project.xml";

system("chmod 755 $xml_file");
sleep(1);
open(FILE, "<$xml_file");
my @file = <FILE>;
close(FILE);

open(FILE, ">$xml_file");
foreach (@file)
{
	if(/\<res_base\>(.*?)\<\/res_base\>/)
	{
		print FILE "<res_base>..\\$cus_res</res_base>\n";
	}
	else
	{
		print FILE $_;
	}
}
close(FILE);
