#!/usr/bin/perl

$product = shift;
$version = shift;

open(FILE, ">>MStarStudio_Config/simPath.2005");

if($version == 1)
{
	print FILE "/I \"..\\..\\..\\sc\\customer\\product\\cust\\include\"\n";
	print FILE "/I \"..\\..\\sc\\customer\\product\\cust\\include\"\n";
	print FILE "/I \"..\\..\\..\\..\\sc\\customer\\product\\cust\\include\"\n";
	print FILE "/FI \"global_config_$product.h\" \n";
}
else
{
	print FILE "/I \"..\\..\\..\\sc\\customer\\product\\$product\"\n";
	print FILE "/I \"..\\..\\sc\\customer\\product\\$product\"\n";
	print FILE "/I \"..\\..\\..\\..\\sc\\customer\\product\\$product\"\n";
	print FILE "/FI \"global_config.h\" \n";
}
close(FILE);

